#include "config.h"
#include "Hyphenation.h"
#include <wtf/text/AtomicString.h>
#if OS(LINUX) || OS(DARWIN)
#include "hyphen.h"
#include <dlfcn.h>
#endif
#include <QCoreApplication>
#include <QRegExp>
#include <QDebug>
#include <QFile>
#include <QHash>

namespace WebCore {

static QHash<AtomicString, bool> availableDictionaries;

static QByteArray dictionaryPathForLocale(const AtomicString& localeIdentifier)
{
    QString locale(reinterpret_cast<const QChar *>(localeIdentifier.characters()), localeIdentifier.length());
    QByteArray dictionaryPath = QString("/usr/share/hyphen/hyph_%1.dic").arg(locale).toAscii();
    if (QFile::exists(dictionaryPath)) {
        return dictionaryPath;
    }
    dictionaryPath = QString("%1/hyphenDicts/hyph_%2.dic").arg(QCoreApplication::applicationDirPath()).arg(locale).toAscii();
    if (QFile::exists(dictionaryPath)) {
        return dictionaryPath;
    }
    dictionaryPath = QString("%1/hyphenDicts/hyph_%2.dic").arg(QCoreApplication::applicationDirPath()).arg(locale.left(2)).toAscii();
    if (QFile::exists(dictionaryPath)) {
        return dictionaryPath;
    }
    return QByteArray();
}

bool canHyphenate(const AtomicString& localeIdentifier)
{
#if OS(LINUX) || OS(DARWIN)
    if (!availableDictionaries.contains(localeIdentifier)) {
        availableDictionaries[localeIdentifier] = dictionaryPathForLocale(localeIdentifier).size() > 0;
    }
    return availableDictionaries[localeIdentifier];
#else
    return false;
#endif
}

size_t lastHyphenLocation(const UChar* characters, size_t length, size_t beforeIndex, const AtomicString& localeIdentifier)
{
#if OS(LINUX) || OS(DARWIN)
    static bool initialized = false;
    static HyphenDict *(*hnj_hyphen_load)(const char *);
    static void (*hnj_hyphen_free)(HyphenDict *);
    static int (*hnj_hyphen_hyphenate2)(HyphenDict *, const char *, int, char *, char *, char ***, int **, int **);
    if (!initialized) {
        void *lib = dlopen(NULL, RTLD_LAZY);
        hnj_hyphen_load = (HyphenDict *(*)(const char *)) dlsym(lib, "hnj_hyphen_load");
        hnj_hyphen_free = (void (*)(HyphenDict *)) dlsym(lib, "hnj_hyphen_free");
        hnj_hyphen_hyphenate2 = (int (*)(HyphenDict *, const char *, int, char *, char *, char ***, int **, int **)) dlsym(lib, "hnj_hyphen_hyphenate2");
        if (hnj_hyphen_load == NULL) {
            return 0;
        }
        initialized = true;
    }
    static HyphenDict *dict = NULL;
    static AtomicString dictLocale;
    if (dict == NULL || dictLocale != localeIdentifier) {
        if (dict) {
            hnj_hyphen_free(dict);
            dict = NULL;
        }
        QByteArray dictionaryPath = dictionaryPathForLocale(localeIdentifier);
        dict = hnj_hyphen_load(dictionaryPath.constData());
        dictLocale = localeIdentifier;
        if (dict == NULL) {
            qWarning() << "Couldn't load a hyphenation dictionary!";
            return 0;
        }
    }

    QString s = QString(reinterpret_cast<const QChar *>(characters), length).replace(QRegExp("[^A-Z0-9]", Qt::CaseInsensitive), " ").remove(QRegExp("\\s+$")).toLower();
    QByteArray c = s.simplified().toUtf8();
    int leadingSpaces = length - c.length();

    if (c.length() - c.lastIndexOf(" ") <= 5) {
        return 0;
    }

    char *hyphens = (char *) malloc(c.size() + 5);
    char *hword = (char *) malloc(c.size() * 2);
    bzero(hyphens, c.size() + 5);
    bzero(hword, c.size() * 2);

    char **rep = NULL;
    int *pos = NULL;
    int *cut = NULL;
    int index = 0;

    hnj_hyphen_hyphenate2(dict, c.constData(), c.size(), hyphens, hword, &rep, &pos, &cut);

    for (int i = beforeIndex - 2 - leadingSpaces; i > 0; i--) {
        if (hyphens[i] & 1) {
            index = i + 1 + leadingSpaces;
            break;
        }
    }

    free(rep);
    free(pos);
    free(cut);

    free(hyphens);
    free(hword);

    return index;
#else
    return 0;
#endif
}

}
