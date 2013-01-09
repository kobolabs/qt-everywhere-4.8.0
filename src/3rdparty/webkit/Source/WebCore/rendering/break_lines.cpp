/*
 * Copyright (C) 2005, 2007, 2010 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "break_lines.h"

#include "Font.h"
#include "TextBreakIterator.h"
#include <wtf/StdLibExtras.h>
#include <wtf/unicode/CharacterNames.h>
#include <unicode/uchar.h>

#if PLATFORM(MAC)
#include <CoreServices/CoreServices.h>
#endif

namespace WebCore {

static inline bool isBreakableSpace(UChar ch, bool treatNoBreakSpaceAsBreak)
{
    switch (ch) {
    case ' ':
    case '\n':
    case '\t':
        return true;
    case noBreakSpace:
        return treatNoBreakSpaceAsBreak;
    default:
        return false;
    }
}

static const UChar asciiLineBreakTableFirstChar = '!';
static const UChar asciiLineBreakTableLastChar = 127;

// Pack 8 bits into one byte
#define B(a, b, c, d, e, f, g, h) \
    ((a) | ((b) << 1) | ((c) << 2) | ((d) << 3) | ((e) << 4) | ((f) << 5) | ((g) << 6) | ((h) << 7))

// Line breaking table row for each digit (0-9)
#define DI { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

// Line breaking table row for ascii letters (a-z A-Z)
#define AL { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }

#define F 0xFF

// Line breaking table for printable ASCII characters. Line breaking opportunities in this table are as below:
// - before openning punctuations such as '(', '<', '[', '{' after certain characters (compatible with Firefox 3.6);
// - after '-' and '?' (backward-compatible, and compatible with Internet Explorer).
// Please refer to <https://bugs.webkit.org/show_bug.cgi?id=37698> for line breaking matrixes of different browsers
// and the ICU standard.
static const unsigned char asciiLineBreakTable[][(asciiLineBreakTableLastChar - asciiLineBreakTableFirstChar) / 8 + 1] = {
    //  !  "  #  $  %  &  '  (     )  *  +  ,  -  .  /  0  1-8   9  :  ;  <  =  >  ?  @     A-X      Y  Z  [  \  ]  ^  _  `     a-x      y  z  {  |  }  ~  DEL
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // !
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // "
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // #
    { B(0, 0, 0, 0, 0, 0, 0, 0), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0) }, // $
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // %
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // &
    { B(0, 0, 0, 0, 0, 0, 0, 0), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0) }, // '
    { B(0, 0, 0, 0, 0, 0, 0, 0), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0) }, // (
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // )
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // *
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // +
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // ,
    { B(1, 1, 1, 1, 1, 1, 1, 1), B(1, 1, 1, 1, 1, 1, 1, 1), F, B(1, 1, 1, 1, 1, 1, 1, 1), F, F, F, B(1, 1, 1, 1, 1, 1, 1, 1), F, F, F, B(1, 1, 1, 1, 1, 1, 1, 1) }, // -
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // .
    { B(0, 0, 0, 0, 0, 0, 0, 0), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0) }, // /
    DI,  DI,  DI,  DI,  DI,  DI,  DI,  DI,  DI,  DI, // 0-9
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // :
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // ;
    { B(0, 0, 0, 0, 0, 0, 0, 0), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0) }, // <
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // =
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // >
    { B(0, 0, 1, 1, 1, 1, 0, 1), B(0, 1, 1, 0, 1, 0, 0, 1), F, B(1, 0, 0, 1, 1, 1, 0, 1), F, F, F, B(1, 1, 1, 1, 0, 1, 1, 1), F, F, F, B(1, 1, 1, 1, 0, 1, 1, 0) }, // ?
    { B(0, 0, 0, 0, 0, 0, 0, 0), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0) }, // @
    AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL, // A-Z
    { B(0, 0, 0, 0, 0, 0, 0, 0), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0) }, // [
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // '\'
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // ]
    { B(0, 0, 0, 0, 0, 0, 0, 0), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0) }, // ^
    { B(0, 0, 0, 0, 0, 0, 0, 0), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0) }, // _
    { B(0, 0, 0, 0, 0, 0, 0, 0), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0) }, // `
    AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL,  AL, // a-z
    { B(0, 0, 0, 0, 0, 0, 0, 0), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0) }, // {
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // |
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // }
    { B(0, 0, 0, 0, 0, 0, 0, 1), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 1, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 1, 0, 0, 0, 0, 0) }, // ~
    { B(0, 0, 0, 0, 0, 0, 0, 0), B(0, 0, 0, 0, 0, 0, 0, 0), 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0), 0, 0, 0, B(0, 0, 0, 0, 0, 0, 0, 0) }, // DEL
};

#undef B
#undef F
#undef DI
#undef AL

COMPILE_ASSERT(WTF_ARRAY_LENGTH(asciiLineBreakTable) == asciiLineBreakTableLastChar - asciiLineBreakTableFirstChar + 1, TestLineBreakTableConsistency);

bool isNonStarterCharacter(UChar ch)
{
    // As we cannot use ubrk_following here. we check the line break property
    // to guess if the line can be broken before this.
    ULineBreak lineBreak = (ULineBreak)u_getIntPropertyValue(ch, UCHAR_LINE_BREAK);
    // Using Table 2 Example Pair Table of
    // http://www.unicode.org/reports/tr14/tr14-15.html
    // (Unicode 4.0.1) for MacOS.
    // http://www.unicode.org/reports/tr14/tr14-22.html
    // (Unicode 5.1) for Android.
    // And Requirements for Japanese Text Layout, 3.1.7 Characters Not Starting a Line
    // http://www.w3.org/TR/2012/NOTE-jlreq-20120403/#characters_not_starting_a_line
    switch (lineBreak) {
    case U_LB_NONSTARTER:
    case U_LB_CLOSE_PARENTHESIS:
    case U_LB_CLOSE_PUNCTUATION:
    case U_LB_EXCLAMATION:
    case U_LB_BREAK_SYMBOLS:
    case U_LB_INFIX_NUMERIC:
    case U_LB_ZWSPACE:
    case U_LB_WORD_JOINER:
        return true;
    default:
        break;
    }
    // Special care for Requirements for Japanese Text Layout
    switch (ch) {
    case 0x2019: // RIGHT SINGLE QUOTATION MARK
    case 0x201D: // RIGHT DOUBLE QUOTATION MARK
    case 0x00BB: // RIGHT-POINTING DOUBLE ANGLE QUOTATION MARK
    case 0x2010: // HYPHEN
    case 0x2013: // EN DASH
        return true;
    default:
        break;
    }
    return false;
}

bool isNonEndingCharacter(UChar ch)
{
    // As we cannot use ubrk_following here. we checks the line break property
    // to guess if the line can be broken before this.
    ULineBreak lineBreak = (ULineBreak)u_getIntPropertyValue(ch, UCHAR_LINE_BREAK);
    // Using Table 2 Example Pair Table of
    // http://www.unicode.org/reports/tr14/tr14-15.html
    // (Unicode 4.0.1) for MacOS.
    // http://www.unicode.org/reports/tr14/tr14-22.html
    // (Unicode 5.1) for Android.
    // And Requirements for Japanese Text Layout, 3.1.8 Characters Not Ending a Line
    // http://www.w3.org/TR/2012/NOTE-jlreq-20120403/#characters_not_ending_a_line
    switch (lineBreak) {
    case U_LB_OPEN_PUNCTUATION:
        return true;
    default:
        break;
    }
    // Special care for Requirements for Japanese Text Layout
    switch (ch) {
    case 0x2018: // LEFT SINGLE QUOTATION MARK
    case 0x201C: // LEFT DOUBLE QUOTATION MARK
    case 0x00AB: // LEFT-POINTING DOUBLE ANGLE QUOTATION MARK
        return true;
    default:
        break;
    }
    return false;
}
    
static inline bool shouldBreakAfter(UChar ch, UChar nextCh)
{
    switch (ch) {
    case ideographicComma:
    case ideographicFullStop:
        // FIXME: cases for ideographicComma and ideographicFullStop are a workaround for an issue in Unicode 5.0
        // which is likely to be resolved in Unicode 5.1 <http://bugs.webkit.org/show_bug.cgi?id=17411>.
        // We may want to remove or conditionalize this workaround at some point.
        return !isNonStarterCharacter(nextCh);
    default:
        // If both ch and nextCh are ASCII characters, use a lookup table for enhanced speed and for compatibility
        // with other browsers (see comments for asciiLineBreakTable for details).
        if (ch >= asciiLineBreakTableFirstChar && ch <= asciiLineBreakTableLastChar
                && nextCh >= asciiLineBreakTableFirstChar && nextCh <= asciiLineBreakTableLastChar) {
            const unsigned char* tableRow = asciiLineBreakTable[ch - asciiLineBreakTableFirstChar];
            int nextChIndex = nextCh - asciiLineBreakTableFirstChar;
            return tableRow[nextChIndex / 8] & (1 << (nextChIndex % 8));
        }
        // Otherwise defer to the Unicode algorithm by returning false.
        return false;
    }
}

static inline bool needsLineBreakIterator(UChar ch)
{
    return ch > asciiLineBreakTableLastChar && ch != noBreakSpace;
}

int nextBreakablePosition(LazyLineBreakIterator& lazyBreakIterator, int pos, bool treatNoBreakSpaceAsBreak)
{
    const UChar* str = lazyBreakIterator.string();
    int len = lazyBreakIterator.length();
    int nextBreak = -1;

    UChar lastCh = pos > 0 ? str[pos - 1] : 0;
    for (int i = pos; i < len; i++) {
        UChar ch = str[i];

        if (isBreakableSpace(ch, treatNoBreakSpaceAsBreak) || shouldBreakAfter(lastCh, ch))
            return i;

        if (needsLineBreakIterator(ch) || needsLineBreakIterator(lastCh)) {
            if (nextBreak < i && i) {
                TextBreakIterator* breakIterator = lazyBreakIterator.get();
                if (breakIterator)
                    nextBreak = textBreakFollowing(breakIterator, i - 1);
            }
            // These characters are not kinsoku characters according to Unicode 6.0,
            // However, they are in JLreq (http://www.w3.org/TR/jlreq/). We need
            // special treatment here.
            if (i == nextBreak && !isBreakableSpace(lastCh, treatNoBreakSpaceAsBreak)
                && !Font::isUnbreakableCharactersPair(lastCh, ch))
                return i;
        }

        lastCh = ch;
    }

    return len;
}

} // namespace WebCore
