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

class ModuleUriResolver :
	public ZorbaWrapperShadowImpl <ModuleUriResolver, zorba::ModuleURIResolver> {

	class Delegate : public zorba::ModuleURIResolver {

		ModuleUriResolver * target;

	public:

		Delegate (ModuleUriResolver * target_arg) {
			target = target_arg;
		}

		auto_ptr <zorba::ModuleURIResolverResult> resolveTargetNamespace (
			const zorba::String & targetNamespaceURI,
			const zorba::StaticContext& staticContext);

		auto_ptr <zorba::ModuleURIResolverResult> resolve (
			const zorba::String& uri,
			const zorba::StaticContext& staticContext);
	};

	ModuleUriResolver (VALUE);

public:

	virtual ~ModuleUriResolver () { }

	zorba::ModuleURIResolver * delegate () {
		return new Delegate (this);
	}

	virtual string toString () { return "ModuleUriResolver"; }

	static VALUE initialize (VALUE self);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, ModuleUriResolver, rb_cObject)

ZR_CLASS_METHOD (ModuleUriResolver, initialize, 0)

#endif
#ifdef IMPLEMENTATION_PART

ModuleUriResolver::ModuleUriResolver (VALUE caster_ruby) :
	ZorbaWrapperShadowImpl <ModuleUriResolver, zorba::ModuleURIResolver> (
		caster_ruby, (ModuleUriResolver *) this, NULL, cModuleUriResolver) {
}

VALUE ModuleUriResolver::initialize (VALUE self_ruby) {

	ModuleUriResolver * self = new ModuleUriResolver (self_ruby);

	rb_iv_set (self_ruby, "@shadow", self->shadow ());

	return self_ruby;
}

auto_ptr <zorba::ModuleURIResolverResult> ModuleUriResolver::Delegate::resolveTargetNamespace (
		const zorba::String & targetNamespaceURI,
		const zorba::StaticContext& staticContext) {

	VALUE ret_ruby = zr_funcall (
		target->caster (),
		rb_intern ("resolve_target_namespace"),
		1,
		rb_str_new2 (targetNamespaceURI.c_str ()));

	ZR_SHADOW (ModuleUriResolverResult, ret);

	return auto_ptr <zorba::ModuleURIResolverResult> (ret->delegate ());
}

auto_ptr <zorba::ModuleURIResolverResult> ModuleUriResolver::Delegate::resolve (
		const zorba::String& uri,
		const zorba::StaticContext& staticContext) {

	VALUE ret_ruby = zr_funcall (
		target->caster (),
		rb_intern ("resolve"),
		1,
		rb_str_new2 (uri.c_str ()));

	ZR_SHADOW (ModuleUriResolverResult, ret);

	return auto_ptr <zorba::ModuleURIResolverResult> (ret->delegate ());
}

#endif
