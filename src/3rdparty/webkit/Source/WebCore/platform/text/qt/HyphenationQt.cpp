#include "config.h"
#include "Hyphenation.h"
#if OS(LINUX)
#include <hyphen.h>
#include <QRegExp>
#include <QDebug>
#endif

namespace WebCore {

bool canHyphenate(const AtomicString& localeIdentifier)
{
#if OS(LINUX)
    return true;
#else
    return false;
#endif
}

size_t lastHyphenLocation(const UChar* characters, size_t length, size_t beforeIndex, const AtomicString& localeIdentifier)
{
#if OS(LINUX)
    static HyphenDict *dict = NULL;
    if (dict == NULL) {
        dict = hnj_hyphen_load("/usr/share/hyphen/hyph_en_US.dic");
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
