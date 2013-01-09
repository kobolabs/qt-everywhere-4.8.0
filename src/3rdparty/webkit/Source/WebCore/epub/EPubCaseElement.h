#ifndef EPubCaseElement_h
#define EPubCaseElement_h

#include "epubElement.h"

namespace WebCore {

class EPubCaseElement : public epubElement {
public:
    static PassRefPtr<EPubCaseElement> create(const QualifiedName&, Document*);
    void finishParsingChildren();
private:
    EPubCaseElement(const QualifiedName&, Document*);
};

} // namespace WebCore

#endif // EPubCaseElement_h
