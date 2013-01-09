#include "config.h"
#include "EPubDefaultElement.h"
#include "epubNames.h"
#include "CSSPropertyNames.h"
#include "CSSValueKeywords.h"

namespace WebCore {

using namespace epubNames;

EPubDefaultElement::EPubDefaultElement(const QualifiedName& tagName, Document* document)
    : epubElement(tagName, document)
{
    ASSERT(hasTagName(epub_defaultTag));
}

PassRefPtr<EPubDefaultElement> EPubDefaultElement::create(const QualifiedName& tagName, Document* document)
{
    return adoptRef(new EPubDefaultElement(tagName, document));
}

void EPubDefaultElement::finishParsingChildren()
{
    Element *switchElement = this;
    for (; switchElement != NULL && !switchElement->isEPubSwitchElement(); switchElement = switchElement->parentElement()) {
    }
    if (switchElement != NULL && switchElement->isEPubSwitchElement()) {
        if (switchElement->isEPubSwitchHandled()) {
            getInlineStyleDecl()->setProperty(CSSPropertyDisplay, CSSValueNone);
        }
        else {
            switchElement->setEPubSwitchHandled(true);
        }
    }
    epubElement::finishParsingChildren();
}

}
