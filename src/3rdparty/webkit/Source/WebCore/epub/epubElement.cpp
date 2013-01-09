#include "config.h"

#if ENABLE(EPUB3)

#include "epubElement.h"

#include "epubNames.h"
#include "RenderObject.h"

namespace WebCore {
    
using namespace epubNames;
    
epubElement::epubElement(const QualifiedName& tagName, Document* document)
    : StyledElement(tagName, document, CreateStyledElement)
{
}
    
PassRefPtr<epubElement> epubElement::create(const QualifiedName& tagName, Document* document)
{
    return adoptRef(new epubElement(tagName, document));
}
    
}

#endif // ENABLE(EPUB3)
