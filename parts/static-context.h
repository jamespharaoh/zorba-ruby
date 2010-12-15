/*
 * zorba-ruby/parts/static-context.h
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

template <class T>
class SmartishPtr {

	SmartPtr <T> smart;
	T * stupid;

public:

	SmartishPtr (T * value) :
		smart (NULL),
		stupid (value) {
	}

	SmartishPtr (SmartPtr <T> & value) :
		smart (value),
		stupid (NULL) {
	}

	T & operator * () const {
		return * (stupid ? stupid : smart);
	}

	T * operator -> () const {
		return stupid ? stupid : smart.get ();
	}

	bool is_smart () const {
		return stupid ? false : true;
	}

	bool is_stupid () const {
		return stupid ? true : false;
	}
};

void StaticContext_mark (SmartishPtr <StaticContext> * staticContext);
void StaticContext_delete (SmartishPtr <StaticContext> * staticContext);
VALUE StaticContext_wrap (StaticContext *);
VALUE StaticContext_wrap (StaticContext_t &);

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, StaticContext, rb_cObject)

ZR_CLASS_METHOD (StaticContext, add_module_uri_resolver, 1)
ZR_CLASS_METHOD (StaticContext, register_module, 1)

#endif
#ifdef IMPLEMENTATION_PART

void StaticContext_delete (SmartishPtr <StaticContext> * staticContext_real) {
	delete staticContext_real;
}

void StaticContext_mark (SmartishPtr <StaticContext> * staticContext_real) {
	// TODO
	cout << "STATIC CONTEXT MARK TODO!\n";
}

VALUE StaticContext_wrap (StaticContext * staticContext_orig) {

	auto_ptr <SmartishPtr <StaticContext> > staticContext_real (
		new SmartishPtr <StaticContext> (staticContext_orig));

	return Data_Wrap_Struct (
		cStaticContext,
		StaticContext_mark,
		StaticContext_delete,
		staticContext_real.release ());
}

VALUE StaticContext_wrap (StaticContext_t & staticContext_orig) {

	auto_ptr <SmartishPtr <StaticContext> > staticContext_real (
		new SmartishPtr <StaticContext> (staticContext_orig));

	return Data_Wrap_Struct (
		cStaticContext,
		StaticContext_mark,
		StaticContext_delete,
		staticContext_real.release ());
}

VALUE StaticContext_add_module_uri_resolver (VALUE self, VALUE moduleUriResolver) {

	ZR_REAL (SmartishPtr <StaticContext>, self);

	ModuleUriResolverWrapper * moduleUriResolver_real =
		new ModuleUriResolverWrapper (moduleUriResolver);

	(* self_real)->addModuleURIResolver (moduleUriResolver_real);

	return Qnil;
}

VALUE StaticContext_register_module (VALUE self, VALUE module) {

	ZR_REAL (SmartishPtr <StaticContext>, self);

	ExternalModuleWrapper * module_real =
		new ExternalModuleWrapper (module);

	(* self_real)->registerModule (module_real);

	return Qnil;
}

#endif
