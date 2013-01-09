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
#include "JSCDATASection.h"

#include "CDATASection.h"
#include <wtf/GetPtr.h>

using namespace JSC;

namespace WebCore {

ASSERT_CLASS_FITS_IN_CELL(JSCDATASection);

/* Hash table */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSCDATASectionTableValues[2] =
{
    { "constructor", DontEnum | ReadOnly, (intptr_t)static_cast<PropertySlot::GetValueFunc>(jsCDATASectionConstructor), (intptr_t)0 THUNK_GENERATOR(0) },
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSCDATASectionTable = { 2, 1, JSCDATASectionTableValues, 0 };
/* Hash table for constructor */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSCDATASectionConstructorTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSCDATASectionConstructorTable = { 1, 0, JSCDATASectionConstructorTableValues, 0 };
class JSCDATASectionConstructor : public DOMConstructorObject {
public:
    JSCDATASectionConstructor(JSC::ExecState*, JSC::Structure*, JSDOMGlobalObject*);

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

const ClassInfo JSCDATASectionConstructor::s_info = { "CDATASectionConstructor", &DOMConstructorObject::s_info, &JSCDATASectionConstructorTable, 0 };

JSCDATASectionConstructor::JSCDATASectionConstructor(ExecState* exec, Structure* structure, JSDOMGlobalObject* globalObject)
    : DOMConstructorObject(structure, globalObject)
{
    ASSERT(inherits(&s_info));
    putDirect(exec->globalData(), exec->propertyNames().prototype, JSCDATASectionPrototype::self(exec, globalObject), DontDelete | ReadOnly);
}

bool JSCDATASectionConstructor::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSCDATASectionConstructor, JSDOMWrapper>(exec, &JSCDATASectionConstructorTable, this, propertyName, slot);
}

bool JSCDATASectionConstructor::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSCDATASectionConstructor, JSDOMWrapper>(exec, &JSCDATASectionConstructorTable, this, propertyName, descriptor);
}

/* Hash table for prototype */
#if ENABLE(JIT)
#define THUNK_GENERATOR(generator) , generator
#else
#define THUNK_GENERATOR(generator)
#endif

static const HashTableValue JSCDATASectionPrototypeTableValues[1] =
{
    { 0, 0, 0, 0 THUNK_GENERATOR(0) }
};

#undef THUNK_GENERATOR
static JSC_CONST_HASHTABLE HashTable JSCDATASectionPrototypeTable = { 1, 0, JSCDATASectionPrototypeTableValues, 0 };
const ClassInfo JSCDATASectionPrototype::s_info = { "CDATASectionPrototype", &JSC::JSObjectWithGlobalObject::s_info, &JSCDATASectionPrototypeTable, 0 };

JSObject* JSCDATASectionPrototype::self(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMPrototype<JSCDATASection>(exec, globalObject);
}

const ClassInfo JSCDATASection::s_info = { "CDATASection", &JSText::s_info, &JSCDATASectionTable, 0 };

JSCDATASection::JSCDATASection(Structure* structure, JSDOMGlobalObject* globalObject, PassRefPtr<CDATASection> impl)
    : JSText(structure, globalObject, impl)
{
    ASSERT(inherits(&s_info));
}

JSObject* JSCDATASection::createPrototype(ExecState* exec, JSGlobalObject* globalObject)
{
    return new (exec) JSCDATASectionPrototype(exec->globalData(), globalObject, JSCDATASectionPrototype::createStructure(exec->globalData(), JSTextPrototype::self(exec, globalObject)));
}

bool JSCDATASection::getOwnPropertySlot(ExecState* exec, const Identifier& propertyName, PropertySlot& slot)
{
    return getStaticValueSlot<JSCDATASection, Base>(exec, &JSCDATASectionTable, this, propertyName, slot);
}

bool JSCDATASection::getOwnPropertyDescriptor(ExecState* exec, const Identifier& propertyName, PropertyDescriptor& descriptor)
{
    return getStaticValueDescriptor<JSCDATASection, Base>(exec, &JSCDATASectionTable, this, propertyName, descriptor);
}

JSValue jsCDATASectionConstructor(ExecState* exec, JSValue slotBase, const Identifier&)
{
    JSCDATASection* domObject = static_cast<JSCDATASection*>(asObject(slotBase));
    return JSCDATASection::getConstructor(exec, domObject->globalObject());
}

JSValue JSCDATASection::getConstructor(ExecState* exec, JSGlobalObject* globalObject)
{
    return getDOMConstructor<JSCDATASectionConstructor>(exec, static_cast<JSDOMGlobalObject*>(globalObject));
}


}
