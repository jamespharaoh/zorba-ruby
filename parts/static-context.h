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

class StaticContext :
	public virtual ZorbaWrapperOwned {

public:

	virtual zorba::StaticContext * zorba () = 0;

	static VALUE add_module_uri_resolver (VALUE self_ruby, VALUE moduleUriResolverRuby_ruby);
	static VALUE free (VALUE self_ruby);
	static VALUE load_prolog (VALUE self_ruby, VALUE prolog_ruby, VALUE hints_ruby);
	static VALUE register_module (VALUE self_ruby, VALUE module_ruby);
};

class StaticContextCounted :
	public ZorbaWrapperOwnedImpl <StaticContext, zorba::StaticContext_t>,
	public virtual StaticContext {

public:

	StaticContextCounted (ZorbaWrapperOwner * owner, zorba::StaticContext_t * staticContext_zorba);

	virtual string toString () { return "StaticContextCounted"; }

	virtual zorba::StaticContext * zorba () {
		return self_zorba->get ();
	}
};

class StaticContextRaw :
	public ZorbaWrapperOwnedImpl <StaticContext, zorba::StaticContext>,
	public virtual StaticContext {

public:

	StaticContextRaw (ZorbaWrapperOwner * owner, zorba::StaticContext * staticContext_zorba);

	virtual string toString () { return "StaticContextRaw"; }

	virtual zorba::StaticContext * zorba () {
		return self_zorba;
	}
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, StaticContext, rb_cObject)

ZR_CLASS_METHOD (StaticContext, add_module_uri_resolver, 1)
ZR_CLASS_METHOD (StaticContext, free, 0)
ZR_CLASS_METHOD (StaticContext, load_prolog, 2)
ZR_CLASS_METHOD (StaticContext, register_module, 1)

#endif
#ifdef IMPLEMENTATION_PART

StaticContextCounted::StaticContextCounted (ZorbaWrapperOwner * owner, zorba::StaticContext_t * staticContext_zorba) :
	ZorbaWrapperOwnedImpl <StaticContext, zorba::StaticContext_t> (owner, true, staticContext_zorba, cStaticContext) {
}

StaticContextRaw::StaticContextRaw (ZorbaWrapperOwner * owner, zorba::StaticContext * staticContext_zorba) :
	ZorbaWrapperOwnedImpl <StaticContext, zorba::StaticContext> (owner, false, staticContext_zorba, cStaticContext) {
}

VALUE StaticContext::add_module_uri_resolver (VALUE self_ruby, VALUE moduleUriResolverRuby_ruby) {

	ZR_REAL (StaticContext, self);

	VALUE moduleUriResolverZorba_ruby = rb_iv_get (moduleUriResolverRuby_ruby, "@shadow");

	ZR_REAL (ModuleUriResolver, moduleUriResolverZorba);

	self->zorba ()->addModuleURIResolver (moduleUriResolverZorba);

	return Qnil;
}

VALUE StaticContext::free (VALUE self_ruby) {

	ZR_REAL (StaticContext, self);

	self->zorba ()->free ();

	return Qnil;
}

VALUE StaticContext::load_prolog (VALUE self_ruby, VALUE prolog_ruby, VALUE hints_ruby) {

	ZR_REAL (StaticContext, self);
	const char * prolog = StringValueCStr (prolog_ruby);
	ZR_SHADOW (CompilerHints, hints);

	self->zorba ()->loadProlog (zorba::String (prolog), hints->zorba ());
}

VALUE StaticContext::register_module (VALUE self_ruby, VALUE module_ruby) {

	ZR_REAL (StaticContext, self);

	ExternalModuleWrapper * module =
		new ExternalModuleWrapper (self->owner (), module_ruby);

	self->zorba ()->registerModule (module);

	return Qnil;
}

#endif
