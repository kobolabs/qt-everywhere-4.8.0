#ifndef EPubSwitchElement_h
#define EPubSwitchElement_h

#include "epubElement.h"

namespace WebCore {
    
class EPubSwitchElement : public epubElement {
public:
    static PassRefPtr<EPubSwitchElement> create(const QualifiedName& tagName, Document*);
    virtual bool isEPubSwitchElement() const { return true; }
    virtual bool isEPubSwitchHandled() const { return _switchHandled; }
    virtual void setEPubSwitchHandled(bool handled) { _switchHandled = handled; }
private:
    EPubSwitchElement(const QualifiedName& tagName, Document*);
    bool _switchHandled;
};
    
}

#endif // EPubSwitchElement_h
