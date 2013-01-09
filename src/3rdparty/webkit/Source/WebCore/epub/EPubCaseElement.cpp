#include "config.h"
#include "EPubCaseElement.h"

#include "Attribute.h"
#include "CSSPropertyNames.h"
#include "CSSValueKeywords.h"
#include "epubNames.h"

#if ENABLE(MATHML)
#include "MathMLNames.h"
#endif
#include "HTMLNames.h"
#if ENABLE(SVG)
#include "SVGNames.h"
#endif

namespace WebCore {

using namespace epubNames;

EPubCaseElement::EPubCaseElement(const QualifiedName& tagName, Document* document)
    : epubElement(tagName, document)
{
    ASSERT(hasTagName(epub_caseTag));
}

PassRefPtr<EPubCaseElement> EPubCaseElement::create(const QualifiedName& tagName, Document* document)
{
    return adoptRef(new EPubCaseElement(tagName, document));
}

// this will need to be updated as warranted by http://idpf.org/epub/switch/
static bool namespaceSupported(const AtomicString& namespaceURI)
{
#if ENABLE(MATHML)
    if (namespaceURI == MathMLNames::mathmlNamespaceURI)
    {
        return true;
    }
#endif
#if ENABLE(SVG)
    if (namespaceURI == SVGNames::svgNamespaceURI)
    {
        return true;
    }
#endif
    if (namespaceURI == HTMLNames::xhtmlNamespaceURI)
    {
        return true;
    }
    return false;
}

void EPubCaseElement::finishParsingChildren()
{
    Element *switchElement = this;
    for (; switchElement != NULL && !switchElement->isEPubSwitchElement(); switchElement = switchElement->parentElement()) {
    }
    if (switchElement != NULL && switchElement->isEPubSwitchElement()) {
        if (switchElement->isEPubSwitchHandled() || !namespaceSupported(fastGetAttribute(required_namespaceAttr))) {
            getInlineStyleDecl()->setProperty(CSSPropertyDisplay, CSSValueNone);
        }
        else {
            switchElement->setEPubSwitchHandled(true);
        }
    }
    epubElement::finishParsingChildren();
}

}
