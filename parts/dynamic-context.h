/*
 * zorba-ruby/parts/dynamic-context.h
 *
 * Copyright 2010 James Pharaoh <james@phsys.co.uk>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifdef INTERFACE_PART

class DynamicContext {

	zorba::DynamicContext * self_zorba;
	VALUE self_ruby;

	~DynamicContext ();

public:

	DynamicContext (zorba::DynamicContext *);

	zorba::DynamicContext * zorba () { return self_zorba; }
	VALUE ruby () { return self_ruby; }

	static VALUE set_variable (VALUE self_ruby, VALUE qname_ruby, VALUE item_ruby);

	static void mark (DynamicContext *);
	static void del (DynamicContext *);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, DynamicContext, rb_cObject)

ZR_CLASS_METHOD (DynamicContext, set_variable, 2)

#endif
#ifdef IMPLEMENTATION_PART

DynamicContext::DynamicContext (zorba::DynamicContext * dynamicContext_zorba) {

	self_zorba = dynamicContext_zorba;

	self_ruby = Data_Wrap_Struct (
		cDynamicContext,
		DynamicContext::mark,
		DynamicContext::del,
		this);
}

VALUE DynamicContext::set_variable (VALUE self_ruby, VALUE qname_ruby, VALUE item_ruby) {

	ZR_REAL (DynamicContext, self);
	ZR_REAL (Item, item);

	self->zorba ()->setVariable (
		zorba::String (StringValueCStr (qname_ruby)),
		* item->zorba ());

	return Qnil;
}

void DynamicContext::del (DynamicContext * dynamicContext) {
	delete dynamicContext;
}

void DynamicContext::mark (DynamicContext * dynamicContext) {
}

#endif
