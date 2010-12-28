/*
 * zorba-ruby/parts/external-module-wrapper.h
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

class ExternalModule :
	public ZorbaWrapperShadowImpl <ExternalModule, zorba::ExternalModule> {

	class Delegate :
		public zorba::ExternalModule {

		ZorbaWrapperOwner * owner_val;
		::ExternalModule * target;

	public:

		Delegate (ZorbaWrapperOwner * owner_arg, ::ExternalModule * target_arg) {
			owner_val = owner_arg;
			target = target_arg;
		}

		virtual zorba::StatelessExternalFunction * getExternalFunction (zorba::String aLocalname) const;

		virtual zorba::String getURI () const;
	};

protected:

	virtual ~ExternalModule () { }

public:

	ExternalModule (VALUE caster_ruby);

	virtual string toString () { return "ExternalModule"; }

	zorba::ExternalModule * delegate (ZorbaWrapperOwner * owner_arg) {
		return new Delegate (owner_arg, this);
	}

	static VALUE initialize (VALUE self_ruby);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, ExternalModule, rb_cObject)

ZR_CLASS_METHOD (ExternalModule, initialize, 0)

#endif
#ifdef IMPLEMENTATION_PART

ExternalModule::ExternalModule (VALUE self_ruby) :
	ZorbaWrapperShadowImpl <ExternalModule, zorba::ExternalModule> (
		self_ruby, NULL, cExternalModule) {
}

VALUE ExternalModule::initialize (VALUE self_ruby) {

	ExternalModule * self =
		new ExternalModule (self_ruby);

	rb_iv_set (self_ruby, "@shadow", self->shadow ());

	return self_ruby;
}

zorba::StatelessExternalFunction * ExternalModule::Delegate::getExternalFunction (
		zorba::String localName) const {

	VALUE ret = zr_funcall (
		target->caster (),
		rb_intern ("external_function"),
		1,
		rb_str_new2 (localName.c_str ()));

	VALUE shadow_ruby = rb_iv_get (ret, "@shadow");

	ZR_REAL (StatelessExternalFunction, shadow);

	return shadow->delegate (owner_val);
}

zorba::String ExternalModule::Delegate::getURI () const {

	VALUE ret = zr_funcall (
		target->caster (),
		rb_intern ("uri"),
		0);

	return RSTRING (ret)->ptr;
}

#endif
