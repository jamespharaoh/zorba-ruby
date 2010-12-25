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

	Zorba () { }

public:

	~Zorba () { }

	zorba::Zorba * zorba () { return self_zorba; }

	VALUE ruby () { return self_ruby; }

	static Zorba * get_instance (void * store_real);

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

VALUE Zorba_compile_query (int argc, VALUE * argv, VALUE self_ruby) {

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
	ZR_REAL_OPT (zorba::StaticContext_t, staticContext);

	auto_ptr <zorba::XQuery_t> xquery_real (new zorba::XQuery_t ());

	if (staticContext_real) {
		* xquery_real = self_real->zorba ()->compileQuery (query_string, * staticContext_real);
	} else {
		* xquery_real = self_real->zorba ()->compileQuery (query_string);
	}

	return XQuery_wrap (xquery_real.release ());
}

VALUE Zorba_create_query (VALUE self_ruby) {

	ZR_REAL (Zorba, self);

	auto_ptr <zorba::XQuery_t> xquery_real (new zorba::XQuery_t ());
	* xquery_real = self_real->zorba ()->createQuery ();

	return XQuery_wrap (xquery_real.release ());
}

VALUE Zorba_create_static_context (VALUE self_ruby) {

	ZR_REAL (Zorba, self);

	zorba::StaticContext_t staticContext_zorba = self_real->zorba ()->createStaticContext ();

	StaticContext * staticContext = StaticContext::wrap (staticContext_zorba);

	return staticContext->ruby ();
}

VALUE Zorba_get_instance (VALUE self_ruby, VALUE store_ruby) {

	ZR_REAL (void, store);

	Zorba * zorba_real = Zorba::get_instance (store_real);

	return zorba_real->ruby ();
}

Zorba * Zorba::get_instance (void * store_real) {

	Zorba * zorba_real = new Zorba ();

	zorba_real->self_zorba = zorba::Zorba::getInstance (store_real);

	zorba_real->self_ruby = Data_Wrap_Struct (
		cZorba,
		Zorba::mark,
		Zorba::del,
		zorba_real);

	return zorba_real;
}

VALUE Zorba_item_factory (VALUE self_ruby) {

	ZR_REAL (Zorba, self);

	zorba::ItemFactory * itemFactory_zorba = self_real->zorba ()->getItemFactory ();

	ItemFactory * itemFactory = ItemFactory::wrap (itemFactory_zorba);

	return itemFactory->ruby ();
}

VALUE Zorba_shutdown (VALUE self_ruby) {

	ZR_REAL (Zorba, self);

	self_real->zorba ()->shutdown ();

	return Qnil;
}

VALUE Zorba_version (VALUE self_ruby) {

	auto_ptr <zorba::Version> version_real (new zorba::Version ());

	* version_real = zorba::Zorba::version ();

	return Version_wrap (version_real.release ());
}

VALUE Zorba_xml_data_manager (VALUE self_ruby) {

	ZR_REAL (Zorba, self);

	zorba::XmlDataManager * xml_data_manager_real = self_real->zorba ()->getXmlDataManager ();

	return Data_Wrap_Struct (cXmlDataManager, 0, 0, xml_data_manager_real);
}

void Zorba::del (Zorba * zorba) {
	delete zorba;
}

void Zorba::mark (Zorba * zorba) {
}

#endif
