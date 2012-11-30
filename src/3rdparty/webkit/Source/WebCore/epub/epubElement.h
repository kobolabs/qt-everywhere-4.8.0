#ifndef epubElement_h
#define epubElement_h

#if ENABLE(EPUB3)
#include "StyledElement.h"

namespace WebCore {

class epubElement : public StyledElement {
public:
    static PassRefPtr<epubElement> create(const QualifiedName& tagName, Document*);
protected:
    epubElement(const QualifiedName& tagName, Document*);
};
    
}

#endif // ENABLE(EPUB3)
#endif // epubElement_h
