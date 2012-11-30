#ifndef EPubDefaultElement_h
#define EPubDefaultElement_h

#include "epubElement.h"

namespace WebCore {
    
class EPubDefaultElement : public epubElement {
public:
    static PassRefPtr<EPubDefaultElement> create(const QualifiedName& tagName, Document*);
    virtual void finishParsingChildren();
private:
    EPubDefaultElement(const QualifiedName& tagName, Document*);
};
    
}

#endif // EPubDefaultElement_h
