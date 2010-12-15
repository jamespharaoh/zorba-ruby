/*
 * zorba-ruby/parts/module-uri-resolver-result.h
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

class ModuleUriResolverResultWrapper : public ModuleURIResolverResult {

public:

	VALUE shadow;

	ModuleUriResolverResultWrapper (VALUE shadow) {
		this->shadow = shadow;
	}

	virtual std::istream* getModuleStream () const {

		VALUE ret = zr_funcall (
			shadow,
			rb_intern ("module_source"),
			0);

		auto_ptr<basic_istringstream<char> > in (
			new basic_istringstream<char> (StringValueCStr (ret)));

		return in.release ();
	}

	virtual void getModuleURL (string& moduleUrl) const {

		VALUE ret = zr_funcall (
			shadow,
			rb_intern ("module_url"),
			0);

		moduleUrl = StringValueCStr (ret);
	}

	virtual void getComponentURIs (vector<string>& componentUris) const {

		VALUE ret = zr_funcall (
			shadow,
			rb_intern ("component_uris"),
			0);

		for (int i = 0; i < RARRAY (ret)->len; i++) {
			VALUE item = RARRAY (ret)->ptr [i];
			componentUris.push_back (StringValueCStr (item));
		}
	}
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, ModuleUriResolverResult, cUriResolverResult)

ZR_CLASS_METHOD (ModuleUriResolverResult, initialize, 0);

#endif
#ifdef IMPLEMENTATION_PART

VALUE ModuleUriResolverResult_initialize (VALUE self) {

	ModuleUriResolverResultWrapper* shadow_real = new ModuleUriResolverResultWrapper (self);
	VALUE shadow = Data_Wrap_Struct (cModuleUriResolverResult, 0, 0/* TODO? */, shadow_real);

	rb_iv_set (self, "@shadow", shadow);

	return self;
}

#endif
