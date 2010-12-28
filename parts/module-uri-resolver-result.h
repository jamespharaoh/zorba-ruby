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

class ModuleUriResolverResult :
	public ZorbaWrapperShadowImpl <ModuleUriResolverResult, zorba::URIResolverResult> {

	class Delegate :
		public zorba::ModuleURIResolverResult {

		ModuleUriResolverResult * target;

	public:

		Delegate (ModuleUriResolverResult * target_arg) {
			target = target_arg;
		}

		virtual std::istream * getModuleStream () const;
		virtual void getModuleURL (string & moduleUrl) const;
		virtual void getComponentURIs (vector <string> & componentUris) const;
	};

public:

	ModuleUriResolverResult (VALUE caster_ruby);

	virtual string toString () { return "ModuleUriResolverResult"; }

	zorba::ModuleURIResolverResult * delegate () {
		return new Delegate (this);
	}

	static VALUE initialize (VALUE self);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, ModuleUriResolverResult, cUriResolverResult)

ZR_CLASS_METHOD (ModuleUriResolverResult, initialize, 0);

#endif
#ifdef IMPLEMENTATION_PART

ModuleUriResolverResult::ModuleUriResolverResult (VALUE caster_ruby) :
	ZorbaWrapperShadowImpl <ModuleUriResolverResult, zorba::URIResolverResult> (
		caster_ruby, (ModuleUriResolverResult *) this, new zorba::URIResolverResult (), cModuleUriResolverResult) {
}

VALUE ModuleUriResolverResult::initialize (VALUE self_ruby) {

	ModuleUriResolverResult * self = new ModuleUriResolverResult (self_ruby);

	rb_iv_set (self_ruby, "@shadow", self->shadow ());

	return self_ruby;
}

std::istream * ModuleUriResolverResult::Delegate::getModuleStream () const {

	VALUE ret = zr_funcall (
		target->caster (),
		rb_intern ("module_source"),
		0);

	auto_ptr<basic_istringstream<char> > in (
		new basic_istringstream<char> (StringValueCStr (ret)));

	return in.release ();
}

void ModuleUriResolverResult::Delegate::getModuleURL (string& moduleUrl) const {

	VALUE ret = zr_funcall (
		target->caster (),
		rb_intern ("module_url"),
		0);

	moduleUrl = StringValueCStr (ret);
}

void ModuleUriResolverResult::Delegate::getComponentURIs (vector<string>& componentUris) const {

	VALUE ret = zr_funcall (
		target->caster (),
		rb_intern ("component_uris"),
		0);

	for (int i = 0; i < RARRAY (ret)->len; i++) {
		VALUE item = RARRAY (ret)->ptr [i];
		componentUris.push_back (StringValueCStr (item));
	}
}

#endif
