/*
 * zorba-ruby/parts/zorba.h
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

#ifdef STUBS_PART

class Zorba;

#endif
#ifdef INTERFACE_PART

class Zorba :
	public virtual ZorbaWrapperOwner {

	zorba::Zorba * self_zorba;
	VALUE self_ruby;

	Zorba (zorba::Zorba * zorba_zorba);
	~Zorba () { }

public:

	virtual string toString () { return "Zorba"; }

	zorba::Zorba * zorba () { return self_zorba; }
	VALUE ruby () { return self_ruby; }

	static VALUE compile_query (int argc, VALUE * argv, VALUE self_ruby);
	static VALUE create_query (VALUE self_ruby);
	static VALUE create_static_context (VALUE self_ruby);
	static VALUE get_instance (VALUE self_ruby, VALUE store_ruby);
	static VALUE item_factory (VALUE self_ruby);
	static VALUE shutdown (VALUE self_ruby);
	static VALUE version (VALUE self_ruby);
	static VALUE xml_data_manager (VALUE self_ruby);

	static Zorba * get_instance (void * store);

	static void mark (Zorba *);
	static void del (Zorba *);
};

#endif
#ifdef RUBY_PART

ZR_CLASS (Zorba, rb_cObject)

ZR_CLASS_SINGLETON_METHOD (Zorba, get_instance, 1)
ZR_CLASS_SINGLETON_METHOD (Zorba, version, 0)

ZR_CLASS_METHOD (Zorba, compile_query, VAR_C)
ZR_CLASS_METHOD (Zorba, create_query, 0)
ZR_CLASS_METHOD (Zorba, create_static_context, 0)
ZR_CLASS_METHOD (Zorba, item_factory, 0)
ZR_CLASS_METHOD (Zorba, shutdown, 0)
ZR_CLASS_METHOD (Zorba, xml_data_manager, 0)

#endif
#ifdef IMPLEMENTATION_PART

Zorba::Zorba (zorba::Zorba * zorba_zorba) {

	self_zorba = zorba_zorba;

	self_ruby = Data_Wrap_Struct (
		cZorba,
		Zorba::mark,
		Zorba::del,
		this);
}

VALUE Zorba::compile_query (int argc, VALUE * argv, VALUE self_ruby) {

	if (argc < 1 || argc > 3)
		rb_raise (rb_eArgError, "Expected 1-3 args, got %d", argc);

	VALUE query_ruby = argv [0];
	VALUE staticContext_ruby = argc >= 2 ? argv [1] : Qnil;
	VALUE compilerHints_ruby = argc >= 3 ? argv [2] : Qnil;

	ZR_REAL (Zorba, self);
	zorba::String query_string (StringValueCStr (query_ruby));
	ZR_REAL_OPT (StaticContext, staticContext);
	ZR_SHADOW_OPT (CompilerHints, compilerHints);

	zorba::XQuery_t xquery_zorba;

	if (staticContext) {
		xquery_zorba = self->zorba ()->compileQuery (query_string, staticContext->zorba ());
	} else {
		xquery_zorba = self->zorba ()->compileQuery (query_string);
	}

	XQuery * xquery = new XQuery (self, xquery_zorba);

	return xquery->ruby ();
}

VALUE Zorba::create_query (VALUE self_ruby) {

	ZR_REAL (Zorba, self);

	zorba::XQuery_t xquery_zorba;

	xquery_zorba = self->zorba ()->createQuery ();

	XQuery * xquery = new XQuery (self, xquery_zorba);

	return xquery->ruby ();
}

VALUE Zorba::create_static_context (VALUE self_ruby) {

	ZR_REAL (Zorba, self);

	zorba::StaticContext_t * staticContext_zorba =
		new zorba::StaticContext_t (self->zorba ()->createStaticContext ());

	StaticContextCounted * staticContext = new StaticContextCounted (self, staticContext_zorba);

	return staticContext->ruby ();
}

VALUE Zorba::get_instance (VALUE self_ruby, VALUE store_ruby) {

	ZR_REAL (void, store);

	zorba::Zorba * zorba_zorba = zorba::Zorba::getInstance (store);

	Zorba * zorba = new Zorba (zorba_zorba);

	return zorba->ruby ();
}

VALUE Zorba::item_factory (VALUE self_ruby) {

	ZR_REAL (Zorba, self);

	zorba::ItemFactory * itemFactory_zorba = self->zorba ()->getItemFactory ();

	ItemFactory * itemFactory = new ItemFactory (self, itemFactory_zorba);

	return itemFactory->ruby ();
}

VALUE Zorba::shutdown (VALUE self_ruby) {

	ZR_REAL (Zorba, self);

	self->disownOwned ();

	self->zorba ()->shutdown ();

	return Qnil;
}

VALUE Zorba::version (VALUE self_ruby) {

	const zorba::Version * version_zorba = & zorba::Zorba::version ();

	Version * version = new Version (version_zorba);

	return version->ruby ();
}

VALUE Zorba::xml_data_manager (VALUE self_ruby) {

	ZR_REAL (Zorba, self);

	zorba::XmlDataManager * xml_data_manager = self->zorba ()->getXmlDataManager ();

	return Data_Wrap_Struct (cXmlDataManager, 0, 0, xml_data_manager);
}

void Zorba::del (Zorba * zorba) {
	delete zorba;
}

void Zorba::mark (Zorba * zorba) {
}

#endif
