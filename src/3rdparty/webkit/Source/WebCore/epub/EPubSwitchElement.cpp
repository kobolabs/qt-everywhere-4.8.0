#include "config.h"
#include "EPubSwitchElement.h"
#include "epubNames.h"
#include <QDebug>

namespace WebCore {

using namespace epubNames;

EPubSwitchElement::EPubSwitchElement(const QualifiedName& tagName, Document* document)
    : epubElement(tagName, document), _switchHandled(false)
{
    ASSERT(hasTagName(epub_switchTag));
}

PassRefPtr<EPubSwitchElement> EPubSwitchElement::create(const QualifiedName& tagName, Document* document)
{
    return adoptRef(new EPubSwitchElement(tagName, document));
}

}
