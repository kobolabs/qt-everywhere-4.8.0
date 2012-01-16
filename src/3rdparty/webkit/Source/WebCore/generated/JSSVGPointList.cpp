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

#include "config.h"

#if ENABLE(SVG)

#include "JSSVGPointList.h"

#include "ExceptionCode.h"
#include "JSDOMBinding.h"
#include "JSSVGPoint.h"
#include "SVGPointList.h"
#include <runtime/Error.h>
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSSVGPointList);

/* Hash table */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSSVGPointListTableValues[3] =
{
    { "numberOfItems", DontDelete | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGPointListNumberOfItems), (intptr_t)0 THUNK_GENERATOR(0) },
    { "constructor", DontEnum | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsSVGPointListConstructor), (intptr_t)0 THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSSVGPointListTable = { 4, 3, JSSVGPointListTableValues, 0 };
/* Hash table for constructor */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSSVGPointListConstructorTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSSVGPointListConstructorTable = { 1, 0, JSSVGPointListConstructorTableValues, 0 };
class JSSVGPointListConstructor : public DOMConstructorObject {
public:
    JSSVGPointListConstructor(JSC::ExecState*, JSC::Structure*, JSDOMGlobalObject*);

    virtual bool getOwnPropertySlot(JSC::ExecState*, const JSC::Identifier&, JSC::PropertySlot&);
    virtual bool getOwnPropertyDescriptor(JSC::ExecState*, const JSC::Identifier&, JSC::PropertyDescriptor&);
    static const JSC::ClassInfo s_info;
    static JSC::Structure* createStructure(JSC::JSGlobalData& globalData, JSC::JSValue prototype)
    {
        return JSC::Structure::create(globalData, prototype, JSC::TypeInfo(JSC::ObjectType, StructureFlags), AnonymousSlotCount, &s_info);
    }
protected:
    static const unsigned StructureFlags = JSC::OverridesGetOwnPropertySlot | JSC::ImplementsHasInstance | DOMConstructorObject::StructureFlags;
};

const ClassInfo JSSVGPointListConstructor::s_info = { "SVGPointListConstructor", &DOMConstructorObject::s_info, &JSSVGPointListConstructorTable, 0 };

JSSVGPointListConstructor::JSSVGPointListConstructor(ExecState* exec, Structure* structure, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(structure, globalObject)
{
    ASSERT(inherits(&s_info));
    putDirect(exec->globalData(), exec->propertyNames().prototype, JSSVGPointListPrototype::self(exec, globalObject), DontDelete | ReadOnly);
}

bool JSSVGPointListConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPointListConstructor, JSDOMWrapper>(exec, &JSSVGPointListConstructorTable, this, propertyName, slot);
}

bool JSSVGPointListConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGPointListConstructor, JSDOMWrapper>(exec, &JSSVGPointListConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSSVGPointListPrototypeTableValues[8] =
{
    { "clear", DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsSVGPointListPrototypeFunctionClear), (intptr_t)0 THUNK_GENERATOR(0) },
    { "initialize", DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsSVGPointListPrototypeFunctionInitialize), (intptr_t)1 THUNK_GENERATOR(0) },
    { "getItem", DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsSVGPointListPrototypeFunctionGetItem), (intptr_t)1 THUNK_GENERATOR(0) },
    { "insertItemBefore", DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsSVGPointListPrototypeFunctionInsertItemBefore), (intptr_t)2 THUNK_GENERATOR(0) },
    { "replaceItem", DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsSVGPointListPrototypeFunctionReplaceItem), (intptr_t)2 THUNK_GENERATOR(0) },
    { "removeItem", DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsSVGPointListPrototypeFunctionRemoveItem), (intptr_t)1 THUNK_GENERATOR(0) },
    { "appendItem", DontDelete | Function, (intptr_t)static_cast<NativeFunction>(jsSVGPointListPrototypeFunctionAppendItem), (intptr_t)1 THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSSVGPointListPrototypeTable = { 18, 15, JSSVGPointListPrototypeTableValues, 0 };
const ClassInfo JSSVGPointListPrototype::s_info = { "SVGPointListPrototype", &JSC::JSObjectWithGlobalObject::s_info, &JSSVGPointListPrototypeTable, 0 };

JSObject* JSSVGPointListPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSSVGPointList>(exec, globalObject);
}

bool JSSVGPointListPrototype::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticFunctionSlot<JSObject>(exec, &JSSVGPointListPrototypeTable, this, propertyName, slot);
}

bool JSSVGPointListPrototype::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticFunctionDescriptor<JSObject>(exec, &JSSVGPointListPrototypeTable, this, propertyName, descriptor);
}

const ClassInfo JSSVGPointList::s_info = { "SVGPointList", &JSDOMWrapper::s_info, &JSSVGPointListTable, 0 };

JSSVGPointList::JSSVGPointList(Structure* structure, JSDOMGlobalObject* globalObject, PassRefPtr<SVGListPropertyTearOff<SVGPointList> > impl)
    : JSDOMWrapper(structure, globalObject)
    , m_impl(impl)
{
    ASSERT(inherits(&s_info));
}

JSObject* JSSVGPointList::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSSVGPointListPrototype(exec->globalData(), globalObject, JSSVGPointListPrototype::createStructure(globalObject->globalData(), globalObject->objectPrototype()));
}

bool JSSVGPointList::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSSVGPointList, Base>(exec, &JSSVGPointListTable, this, propertyName, slot);
}

bool JSSVGPointList::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSSVGPointList, Base>(exec, &JSSVGPointListTable, this, propertyName, descriptor);
}

JSValue jsSVGPointListNumberOfItems(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGPointList* castedThis = static_cast<JSSVGPointList*>(asObject(slotBase));
    UNUSED_PARAM(exec);
    JSValue result =  jsNumber(castedThis->impl()->numberOfItems());
    return result;
}


JSValue jsSVGPointListConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSSVGPointList* domObject = static_cast<JSSVGPointList*>(asObject(slotBase));
    return JSSVGPointList::getConstructor(exec, domObject->globalObject());
}

JSValue JSSVGPointList::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSSVGPointListConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}

EncodedJSValue JSC_HOST_CALL jsSVGPointListPrototypeFunctionClear(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSSVGPointList::s_info))
        return throwVMTypeError(exec);
    JSSVGPointList* castedThis = static_cast<JSSVGPointList*>(asObject(thisValue));
    SVGListPropertyTearOff<SVGPointList> * imp = static_cast<SVGListPropertyTearOff<SVGPointList> *>(castedThis->impl());
    ExceptionCode ec = 0;

    imp->clear(ec);
    setDOMException(exec, ec);
    return JSValue::encode(jsUndefined());
}

EncodedJSValue JSC_HOST_CALL jsSVGPointListPrototypeFunctionInitialize(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSSVGPointList::s_info))
        return throwVMTypeError(exec);
    JSSVGPointList* castedThis = static_cast<JSSVGPointList*>(asObject(thisValue));
    SVGListPropertyTearOff<SVGPointList> * imp = static_cast<SVGListPropertyTearOff<SVGPointList> *>(castedThis->impl());
    if (exec->argumentCount() < 1)
        return throwVMError(exec, createSyntaxError(exec, "Not enough arguments"));
    ExceptionCode ec = 0;
    if (exec->argumentCount() > 0 && !exec->argument(0).isUndefinedOrNull() && !exec->argument(0).inherits(&JSSVGPoint::s_info))
        return throwVMTypeError(exec);
    SVGPropertyTearOff<FloatPoint>* item(toSVGPoint(exec->argument(0)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());


    JSC::JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->initialize(item, ec)));
    setDOMException(exec, ec);
    return JSValue::encode(result);
}

EncodedJSValue JSC_HOST_CALL jsSVGPointListPrototypeFunctionGetItem(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSSVGPointList::s_info))
        return throwVMTypeError(exec);
    JSSVGPointList* castedThis = static_cast<JSSVGPointList*>(asObject(thisValue));
    SVGListPropertyTearOff<SVGPointList> * imp = static_cast<SVGListPropertyTearOff<SVGPointList> *>(castedThis->impl());
    if (exec->argumentCount() < 1)
        return throwVMError(exec, createSyntaxError(exec, "Not enough arguments"));
    ExceptionCode ec = 0;
    unsigned index(exec->argument(0).toUInt32(exec));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());


    JSC::JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->getItem(index, ec)));
    setDOMException(exec, ec);
    return JSValue::encode(result);
}

EncodedJSValue JSC_HOST_CALL jsSVGPointListPrototypeFunctionInsertItemBefore(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSSVGPointList::s_info))
        return throwVMTypeError(exec);
    JSSVGPointList* castedThis = static_cast<JSSVGPointList*>(asObject(thisValue));
    SVGListPropertyTearOff<SVGPointList> * imp = static_cast<SVGListPropertyTearOff<SVGPointList> *>(castedThis->impl());
    if (exec->argumentCount() < 2)
        return throwVMError(exec, createSyntaxError(exec, "Not enough arguments"));
    ExceptionCode ec = 0;
    if (exec->argumentCount() > 0 && !exec->argument(0).isUndefinedOrNull() && !exec->argument(0).inherits(&JSSVGPoint::s_info))
        return throwVMTypeError(exec);
    SVGPropertyTearOff<FloatPoint>* item(toSVGPoint(exec->argument(0)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());
    unsigned index(exec->argument(1).toUInt32(exec));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());


    JSC::JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->insertItemBefore(item, index, ec)));
    setDOMException(exec, ec);
    return JSValue::encode(result);
}

EncodedJSValue JSC_HOST_CALL jsSVGPointListPrototypeFunctionReplaceItem(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSSVGPointList::s_info))
        return throwVMTypeError(exec);
    JSSVGPointList* castedThis = static_cast<JSSVGPointList*>(asObject(thisValue));
    SVGListPropertyTearOff<SVGPointList> * imp = static_cast<SVGListPropertyTearOff<SVGPointList> *>(castedThis->impl());
    if (exec->argumentCount() < 2)
        return throwVMError(exec, createSyntaxError(exec, "Not enough arguments"));
    ExceptionCode ec = 0;
    if (exec->argumentCount() > 0 && !exec->argument(0).isUndefinedOrNull() && !exec->argument(0).inherits(&JSSVGPoint::s_info))
        return throwVMTypeError(exec);
    SVGPropertyTearOff<FloatPoint>* item(toSVGPoint(exec->argument(0)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());
    unsigned index(exec->argument(1).toUInt32(exec));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());


    JSC::JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->replaceItem(item, index, ec)));
    setDOMException(exec, ec);
    return JSValue::encode(result);
}

EncodedJSValue JSC_HOST_CALL jsSVGPointListPrototypeFunctionRemoveItem(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSSVGPointList::s_info))
        return throwVMTypeError(exec);
    JSSVGPointList* castedThis = static_cast<JSSVGPointList*>(asObject(thisValue));
    SVGListPropertyTearOff<SVGPointList> * imp = static_cast<SVGListPropertyTearOff<SVGPointList> *>(castedThis->impl());
    if (exec->argumentCount() < 1)
        return throwVMError(exec, createSyntaxError(exec, "Not enough arguments"));
    ExceptionCode ec = 0;
    unsigned index(exec->argument(0).toUInt32(exec));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());


    JSC::JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->removeItem(index, ec)));
    setDOMException(exec, ec);
    return JSValue::encode(result);
}

EncodedJSValue JSC_HOST_CALL jsSVGPointListPrototypeFunctionAppendItem(ExecState* exec)
{
    JSValue thisValue = exec->hostThisValue();
    if (!thisValue.inherits(&JSSVGPointList::s_info))
        return throwVMTypeError(exec);
    JSSVGPointList* castedThis = static_cast<JSSVGPointList*>(asObject(thisValue));
    SVGListPropertyTearOff<SVGPointList> * imp = static_cast<SVGListPropertyTearOff<SVGPointList> *>(castedThis->impl());
    if (exec->argumentCount() < 1)
        return throwVMError(exec, createSyntaxError(exec, "Not enough arguments"));
    ExceptionCode ec = 0;
    if (exec->argumentCount() > 0 && !exec->argument(0).isUndefinedOrNull() && !exec->argument(0).inherits(&JSSVGPoint::s_info))
        return throwVMTypeError(exec);
    SVGPropertyTearOff<FloatPoint>* item(toSVGPoint(exec->argument(0)));
    if (exec->hadException())
        return JSValue::encode(jsUndefined());


    JSC::JSValue result = toJS(exec, castedThis->globalObject(), WTF::getPtr(imp->appendItem(item, ec)));
    setDOMException(exec, ec);
    return JSValue::encode(result);
}

JSC::JSValue toJS(JSC::ExecState* exec, JSDOMGlobalObject* globalObject, SVGListPropertyTearOff<SVGPointList> * impl)
{
    return wrap<JSSVGPointList>(exec, globalObject, impl);
}

SVGListPropertyTearOff<SVGPointList> * toSVGPointList(JSC::JSValue value)
{
    return value.inherits(&JSSVGPointList::s_info) ? static_cast<JSSVGPointList*>(asObject(value))->impl() : 0;
}

}

#endif // ENABLE(SVG)
