#include "config.h"
#include "Hyphenation.h"
#if OS(LINUX)
#include <wtf/text/AtomicString.h>
#include <hyphen.h>
#include <QRegExp>
#include <QDebug>
#include <QFile>
#include <QHash>
#endif

namespace WebCore {

static QHash<AtomicString, bool> availableDictionaries;

static QByteArray dictionaryPathForLocale(const AtomicString& localeIdentifier)
{
    QString locale(reinterpret_cast<const QChar *>(localeIdentifier.characters()), localeIdentifier.length());
    QByteArray dictionaryPath = QString("/usr/share/hyphen/hyph_%1.dic").arg(locale).toAscii();
    return dictionaryPath;
}

bool canHyphenate(const AtomicString& localeIdentifier)
{
#if OS(LINUX)
    if (!availableDictionaries.contains(localeIdentifier)) {
        availableDictionaries[localeIdentifier] = QFile::exists(dictionaryPathForLocale(localeIdentifier));
    }
    return availableDictionaries[localeIdentifier];
#else
    return false;
#endif
}

size_t lastHyphenLocation(const UChar* characters, size_t length, size_t beforeIndex, const AtomicString& localeIdentifier)
{
#if OS(LINUX)
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
    
    if (length < 5) {
        return 0;
    }

    QByteArray c = QString(reinterpret_cast<const QChar *>(characters), length).replace(QRegExp("[^A-Z0-9]", Qt::CaseInsensitive), " ").toLower().toUtf8();

    char *hyphens = (char *) malloc(c.size() + 5);
    char *hword = (char *) malloc(c.size() * 2);
    bzero(hyphens, c.size() + 5);
    bzero(hword, c.size() * 2);

    char **rep = NULL;
    int *pos = NULL;
    int *cut = NULL;
    int index = 0;

    hnj_hyphen_hyphenate2(dict, c.constData(), c.size(), hyphens, hword, &rep, &pos, &cut);
    
    for (int i = beforeIndex - 2; i >= 0; i--) {
        if (hyphens[i] & 1) {
            index = i + 1;
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
