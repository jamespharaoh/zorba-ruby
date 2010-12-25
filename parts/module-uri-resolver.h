/*
 * zorba-ruby/parts/module-uri-resolver-wrapper.h
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

class ModuleUriResolver : public zorba::ModuleURIResolver {

	VALUE self_ruby;

	VALUE shadow_ruby;

	ModuleUriResolver () { }

public:

	~ModuleUriResolver () { }

	VALUE ruby () { return self_ruby; }

	VALUE shadow () { return shadow_ruby; }

	auto_ptr <zorba::ModuleURIResolverResult> resolveTargetNamespace (
		const zorba::String & targetNamespaceURI,
		const zorba::StaticContext& staticContext);

	auto_ptr <zorba::ModuleURIResolverResult> resolve (
		const zorba::String& uri,
		const zorba::StaticContext& staticContext);

	static void mark (ModuleUriResolver *);

	static void del (ModuleUriResolver *);

	static ModuleUriResolver * initialize (VALUE self);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, ModuleUriResolver, rb_cObject)

ZR_CLASS_METHOD (ModuleUriResolver, initialize, 0)

#endif
#ifdef IMPLEMENTATION_PART

VALUE ModuleUriResolver_initialize (VALUE self_ruby) {

	ModuleUriResolver * selfZorba = ModuleUriResolver::initialize (self_ruby);

	rb_iv_set (self_ruby, "@shadow", selfZorba->ruby ());

	return self_ruby;
}

auto_ptr <zorba::ModuleURIResolverResult> ModuleUriResolver::resolveTargetNamespace (
		const zorba::String & targetNamespaceURI,
		const zorba::StaticContext& staticContext) {

	VALUE retRuby_ruby = zr_funcall (
		shadow_ruby,
		rb_intern ("resolve_target_namespace"),
		1,
		rb_str_new2 (targetNamespaceURI.c_str ()));

	VALUE retZorba_ruby = rb_iv_get (retRuby_ruby, "@shadow");
	ZR_REAL (zorba::ModuleURIResolverResult, retZorba);

	return auto_ptr <zorba::ModuleURIResolverResult> (retZorba_real);
}

auto_ptr <zorba::ModuleURIResolverResult> ModuleUriResolver::resolve (
		const zorba::String& uri,
		const zorba::StaticContext& staticContext) {

	VALUE ret_ruby = zr_funcall (
		shadow_ruby,
		rb_intern ("resolve"),
		1,
		rb_str_new2 (uri.c_str ()));

	VALUE retShadow_ruby = rb_iv_get (ret_ruby, "@shadow");
	ZR_REAL (zorba::ModuleURIResolverResult, retShadow);

	return auto_ptr <zorba::ModuleURIResolverResult> (retShadow_real);
}

void ModuleUriResolver::del (ModuleUriResolver * moduleUriResolver) {
	delete moduleUriResolver;
}

void ModuleUriResolver::mark (ModuleUriResolver * moduleUriResolver) {
}

ModuleUriResolver * ModuleUriResolver::initialize (VALUE shadow_ruby) {

	ModuleUriResolver * moduleUriResolver = new ModuleUriResolver ();

	moduleUriResolver->shadow_ruby = shadow_ruby;

	VALUE moduleUriResolver_ruby = Data_Wrap_Struct (
		cModuleUriResolver,
		ModuleUriResolver::mark,
		ModuleUriResolver::del,
		moduleUriResolver);

	moduleUriResolver->self_ruby = moduleUriResolver_ruby;

	return moduleUriResolver;
}

#endif