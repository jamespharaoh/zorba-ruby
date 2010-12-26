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

#ifdef INTERFACE_PART

class Zorba {

	zorba::Zorba * self_zorba;
	VALUE self_ruby;

	Zorba (zorba::Zorba * zorba_zorba);
	~Zorba () { }

public:

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

	VALUE query_ruby, staticContext_ruby;
	switch (argc) {
	case 1:
		query_ruby = argv[0];
		staticContext_ruby = Qnil;
		break;
	case 2:
		query_ruby = argv[0];
		staticContext_ruby = argv[1];
		break;
	default:
		rb_raise (rb_eArgError, "Expected 1 or 2 args, got %d", argc);
	}

	ZR_REAL (Zorba, self);
	zorba::String query_string (StringValueCStr (query_ruby));
	ZR_REAL_OPT (StaticContext, staticContext);

	zorba::XQuery_t xquery_zorba;

	if (staticContext) {
		xquery_zorba = self->zorba ()->compileQuery (query_string, staticContext->zorba ());
	} else {
		xquery_zorba = self->zorba ()->compileQuery (query_string);
	}

	XQuery * xquery = new XQuery (xquery_zorba);

	return xquery->ruby ();
}

VALUE Zorba::create_query (VALUE self_ruby) {

	ZR_REAL (Zorba, self);

	zorba::XQuery_t xquery_zorba;

	xquery_zorba = self->zorba ()->createQuery ();

	XQuery * xquery = new XQuery (xquery_zorba);

	return xquery->ruby ();
}

VALUE Zorba::create_static_context (VALUE self_ruby) {

	ZR_REAL (Zorba, self);

	zorba::StaticContext_t staticContext_zorba = self->zorba ()->createStaticContext ();

	StaticContext * staticContext = new StaticContext (self, staticContext_zorba);

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

	ItemFactory * itemFactory = new ItemFactory (itemFactory_zorba);

	return itemFactory->ruby ();
}

VALUE Zorba::shutdown (VALUE self_ruby) {

	ZR_REAL (Zorba, self);

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
	ZR_DEBUG ("Zorba::del %p\n", zorba);
	delete zorba;
}

void Zorba::mark (Zorba * zorba) {
}

#endif
