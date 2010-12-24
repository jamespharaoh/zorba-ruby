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

class StaticContext {

	static map <zorba::StaticContext *, StaticContext *> instances;

	zorba::StaticContext * zorbaValue;

	VALUE rubyValue;

	StaticContext () { }

public:

	~StaticContext ();

	zorba::StaticContext * zorba () { return zorbaValue; }

	VALUE ruby () { return rubyValue; }

	static void mark (StaticContext *);

	static void del (StaticContext *);

	static StaticContext * wrap (zorba::StaticContext *);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, StaticContext, rb_cObject)

ZR_CLASS_METHOD (StaticContext, add_module_uri_resolver, 1)
ZR_CLASS_METHOD (StaticContext, register_module, 1)

#endif
#ifdef IMPLEMENTATION_PART

map <zorba::StaticContext *, StaticContext *> StaticContext::instances;

VALUE StaticContext_add_module_uri_resolver (VALUE self, VALUE moduleUriResolverRuby) {

	ZR_REAL (StaticContext, self);

	VALUE moduleUriResolverZorba = rb_iv_get (moduleUriResolverRuby, "@shadow");

	ZR_REAL (ModuleUriResolver, moduleUriResolverZorba);

	self_real->zorba ()->addModuleURIResolver (moduleUriResolverZorba_real);

	return Qnil;
}

VALUE StaticContext_register_module (VALUE self, VALUE module) {

	ZR_REAL (StaticContext, self);

	ExternalModuleWrapper * module_real =
		new ExternalModuleWrapper (module);

	self_real->zorba ()->registerModule (module_real);

	return Qnil;
}

void StaticContext::del (StaticContext * staticContext) {
	delete staticContext;
}

void StaticContext::mark (StaticContext * staticContext) {
}

StaticContext * StaticContext::wrap (zorba::StaticContext * staticContext_zorba) {

	if (instances.count (staticContext_zorba))
		return instances [staticContext_zorba];

	StaticContext * staticContext = new StaticContext ();

	staticContext->zorbaValue = staticContext_zorba;

	staticContext->rubyValue = Data_Wrap_Struct (
		cStaticContext,
		StaticContext::mark,
		StaticContext::wrap,
		staticContext);

	instances [staticContext_zorba] = staticContext;

	return staticContext;
}

#endif
