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

class ZrDynamicContext {

	static map <zorba::DynamicContext *, ZrDynamicContext *> instances;

	zorba::DynamicContext * zorbaValue;

	VALUE rubyValue;

	ZrDynamicContext () { }

public:

	~ZrDynamicContext ();

	zorba::DynamicContext * zorba () { return zorbaValue; }

	VALUE ruby () { return rubyValue; }

	static void mark (ZrDynamicContext *);

	static void del (ZrDynamicContext *);

	static ZrDynamicContext * wrap (zorba::DynamicContext *);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, DynamicContext, rb_cObject)

ZR_CLASS_METHOD (DynamicContext, set_variable, 2)

#endif
#ifdef IMPLEMENTATION_PART

map <zorba::DynamicContext *, ZrDynamicContext *> ZrDynamicContext::instances;

VALUE DynamicContext_set_variable (VALUE self_ruby, VALUE qname_ruby, VALUE item_ruby) {

	ZR_REAL (ZrDynamicContext, self);
	ZR_REAL (zorba::Item, item);

	self_real->zorba ()->setVariable (
		zorba::String (StringValueCStr (qname_ruby)),
		* item_real);

	return Qnil;
}

void ZrDynamicContext::del (ZrDynamicContext * zrDynamicContext) {
	delete zrDynamicContext;
}

void ZrDynamicContext::mark (ZrDynamicContext * zrDynamicContext) {
}

ZrDynamicContext * ZrDynamicContext::wrap (zorba::DynamicContext * dynamicContext_zorba) {

	if (instances.count (dynamicContext_zorba))
		return instances [dynamicContext_zorba];

	ZrDynamicContext * dynamicContext = new ZrDynamicContext ();

	dynamicContext->zorbaValue = dynamicContext_zorba;

	dynamicContext->rubyValue = Data_Wrap_Struct (
		cDynamicContext,
		ZrDynamicContext::mark,
		ZrDynamicContext::wrap,
		dynamicContext);

	instances [dynamicContext_zorba] = dynamicContext;

	return dynamicContext;
}

#endif
