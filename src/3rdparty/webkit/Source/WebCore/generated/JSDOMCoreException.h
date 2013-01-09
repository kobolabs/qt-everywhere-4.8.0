/*
    This file is part of the WebKit open source project.
    This file has been generated by generate-bindings.pl. DO NOT MODIFY!

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA 02110-1301, USA.
*/

#ifndef JSDOMCoreException_h
#define JSDOMCoreException_h

#include "JSDOMBinding.h"
#include <runtime/JSGlobalObject.h>
#include <runtime/JSObjectWithGlobalObject.h>
#include <runtime/ObjectPrototype.h>

namespace WebCore {

class DOMCoreException;

class JSDOMCoreException : public JSDOMWrapper {
    typedef JSDOMWrapper Base;
public:
    JSDOMCoreException(JSC::Structure*, JSDOMGlobalObject*, PassRefPtr<DOMCoreException>);
    static JSC::JSObject* createPrototype(JSC::ExecState*, JSC::JSGlobalObject*);
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertySlot&);
    virtual bool getOwnPropertyDescriptor(JSC::ExecState*, const JSC::Identifier& propertyName, JSC::PropertyDescriptor&);
    static const JSC::ClassInfo s_info;

    static JSC::Structure* createStructure(JSC::JSGlobalData& globalData, JSC::JSValue prototype)
    {
        return JSC::Structure::create(globalData, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), AnonymousSlotCount, &s_info);
    }

    static JSC::JSValue getConstructor(JSC::ExecState*, JSC::JSGlobalObject*);
    DOMCoreException* impl() const { return m_impl.get(); }

private:
    RefPtr<DOMCoreException> m_impl;
protected:
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

JSC::JSValue toJS(JSC::ExecState*, JSDOMGlobalObject*, DOMCoreException*);
DOMCoreException* toDOMCoreException(JSC::JSValue);

class JSDOMCoreExceptionPrototype : public JSC::JSObjectWithGlobalObject {
    typedef JSC::JSObjectWithGlobalObject Base;
public:
    static JSC::JSObject* self(JSC::ExecState*, JSC::JSGlobalObject*);
    static const JSC::ClassInfo s_info;
    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier&, JSC::PropertySlot&);
    virtual bool getOwnPropertyDescriptor(JSC::ExecState*, const JSC::Identifier&, JSC::PropertyDescriptor&);
    static JSC::Structure* createStructure(JSC::JSGlobalData& globalData, JSC::JSValue prototype)
    {
        return JSC::Structure::create(globalData, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), AnonymousSlotCount, &s_info);
    }
    JSDOMCoreExceptionPrototype(JSC::JSGlobalData& globalData, JSC::JSGlobalObject* globalObject, JSC::Structure* structure) : JSC::JSObjectWithGlobalObject(globalData, globalObject, structure) { }
protected:
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | Base::StructureFlags;
};

// Functions

JSC::EncodedJSValue JSC_HOST_CALL jsDOMCoreExceptionPrototypeFunctionToString(JSC::ExecState*);
// Attributes

JSC::JSValue jsDOMCoreExceptionCode(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionName(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionMessage(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionConstructor(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
// Constants

JSC::JSValue jsDOMCoreExceptionINDEX_SIZE_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionDOMSTRING_SIZE_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionHIERARCHY_REQUEST_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionWRONG_DOCUMENT_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionINVALID_CHARACTER_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionNO_DATA_ALLOWED_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionNO_MODIFICATION_ALLOWED_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionNOT_FOUND_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionNOT_SUPPORTED_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionINUSE_ATTRIBUTE_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionINVALID_STATE_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionSYNTAX_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionINVALID_MODIFICATION_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionNAMESPACE_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionINVALID_ACCESS_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionVALIDATION_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionTYPE_MISMATCH_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionSECURITY_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionNETWORK_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionABORT_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionURL_MISMATCH_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);
JSC::JSValue jsDOMCoreExceptionQUOTA_EXCEEDED_ERR(JSC::ExecState*, JSC::JSValue, const JSC::Identifier&);

} // namespace WebCore

#endif
