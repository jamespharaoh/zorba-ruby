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

#endif
#ifdef RUBY_PART

ZR_CLASS (Zorba, rb_cObject)

ZR_CLASS_SINGLETON_METHOD (Zorba, get_instance, 1)
ZR_CLASS_SINGLETON_METHOD (Zorba, version, 0)

ZR_CLASS_METHOD (Zorba, compile_query, VAR_C)
ZR_CLASS_METHOD (Zorba, create_query, 0)
ZR_CLASS_METHOD (Zorba, create_static_context, 0)
ZR_CLASS_METHOD (Zorba, item_factory, 0)
ZR_CLASS_METHOD (Zorba, xml_data_manager, 0)

#endif
#ifdef IMPLEMENTATION_PART

VALUE Zorba_compile_query (int argc, VALUE * argv, VALUE self) {

	VALUE query, staticContext;
	switch (argc) {
	case 1:
		query = argv[0];
		staticContext = Qnil;
		break;
	case 2:
		query = argv[0];
		staticContext = argv[1];
		break;
	default:
		rb_raise (rb_eArgError, "Expected 1 or 2 args, got %d", argc);
	}

	ZR_REAL (zorba::Zorba, self);
	zorba::String query_string (RSTRING (query)->ptr);
	ZR_REAL_OPT (zorba::StaticContext_t, staticContext);

	auto_ptr <zorba::XQuery_t> xquery_real (new zorba::XQuery_t ());

	if (staticContext_real) {
		* xquery_real = self_real->compileQuery (query_string, * staticContext_real);
	} else {
		* xquery_real = self_real->compileQuery (query_string);
	}

	return XQuery_wrap (xquery_real.release ());
}

VALUE Zorba_create_query (VALUE self) {

	ZR_REAL (zorba::Zorba, self);

	auto_ptr <zorba::XQuery_t> xquery_real (new zorba::XQuery_t ());
	* xquery_real = self_real->createQuery ();

	return XQuery_wrap (xquery_real.release ());
}

VALUE Zorba_create_static_context (VALUE self) {

	ZR_REAL (zorba::Zorba, self);

	zorba::StaticContext_t * staticContext_real = new zorba::StaticContext_t ();
	* staticContext_real = self_real->createStaticContext ();

	VALUE staticContext = Data_Wrap_Struct (
		cStaticContext,
		StaticContext_mark,
		StaticContext_delete,
		staticContext_real);

	return staticContext;
}

VALUE Zorba_get_instance (VALUE self, VALUE store) {

	ZR_REAL (void, store);

	zorba::Zorba * zorba_real = zorba::Zorba::getInstance (store_real);

	return Data_Wrap_Struct (cZorba, 0, 0, zorba_real);
}

VALUE Zorba_item_factory (VALUE self) {

	ZR_REAL (zorba::Zorba, self);

	zorba::ItemFactory * itemFactory_real = self_real->getItemFactory ();

	return Data_Wrap_Struct (cItemFactory, 0, 0, itemFactory_real);
}

VALUE Zorba_version (VALUE self) {

	auto_ptr <zorba::Version> version_real (new zorba::Version ());

	* version_real = zorba::Zorba::version ();

	return Version_wrap (version_real.release ());
}

VALUE Zorba_xml_data_manager (VALUE self) {

	ZR_REAL (zorba::Zorba, self);

	zorba::XmlDataManager * xml_data_manager_real = self_real->getXmlDataManager ();

	return Data_Wrap_Struct (cXmlDataManager, 0, 0, xml_data_manager_real);
}

#endif
