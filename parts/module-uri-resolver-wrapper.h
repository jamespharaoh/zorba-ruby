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

class ModuleUriResolverWrapper : public zorba::ModuleURIResolver {

	VALUE value;

public:

	ModuleUriResolverWrapper (VALUE value) {
		this->value = value;
	}

	virtual ~ModuleUriResolverWrapper () {
		cout << "0\n";
		exit (0);
	}

	virtual auto_ptr<zorba::ModuleURIResolverResult> resolveTargetNamespace (
			const zorba::String& targetNamespaceURI,
			const zorba::StaticContext& staticContext);

	virtual auto_ptr<zorba::ModuleURIResolverResult> resolve (
			const zorba::String& uri,
			const zorba::StaticContext& staticContext);
};

#endif
#ifdef IMPLEMENTATION_PART

auto_ptr<zorba::ModuleURIResolverResult> ModuleUriResolverWrapper::resolveTargetNamespace (
		const zorba::String& targetNamespaceURI,
		const zorba::StaticContext& staticContext) {

	VALUE ret = zr_funcall (
		value,
		rb_intern ("resolve_target_namespace"),
		1,
		rb_str_new2 (targetNamespaceURI.c_str ()));

	VALUE shadow = rb_iv_get (ret, "@shadow");
	ZR_REAL (zorba::ModuleURIResolverResult, shadow);

	return auto_ptr<zorba::ModuleURIResolverResult> (shadow_real);
}

auto_ptr<zorba::ModuleURIResolverResult> ModuleUriResolverWrapper::resolve (
		const zorba::String& uri,
		const zorba::StaticContext& staticContext) {

	VALUE ret = zr_funcall (
		value,
		rb_intern ("resolve"),
		1,
		rb_str_new2 (uri.c_str ()));

	VALUE shadow = rb_iv_get (ret, "@shadow");
	ZR_REAL (zorba::ModuleURIResolverResult, shadow);

	return auto_ptr<zorba::ModuleURIResolverResult> (shadow_real);
}

#endif
