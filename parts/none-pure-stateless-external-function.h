/*
 * zorba-ruby/parts/none-pure-stateless-external-function.h
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

class StatelessExternalFunction {

public:

	virtual zorba::StatelessExternalFunction * delegate () = 0;
};

class NonePureStatelessExternalFunction : public StatelessExternalFunction {

	class Delegate : public zorba::NonePureStatelessExternalFunction {

		::NonePureStatelessExternalFunction * target;

	public:

		Delegate (::NonePureStatelessExternalFunction * target) :
			target (target) {
		}

		virtual zorba::String getLocalName () const;

		virtual zorba::String getURI () const;

		virtual zorba::ItemSequence_t evaluate (
			const Arguments_t &,
			const zorba::StaticContext *,
			const zorba::DynamicContext *) const;
	};

	VALUE caster_ruby;
	VALUE shadow_ruby;

	~NonePureStatelessExternalFunction () { }

public:

	NonePureStatelessExternalFunction (VALUE caster_ruby);

	VALUE caster () { return caster_ruby; }
	VALUE shadow () { return shadow_ruby; }

	virtual zorba::NonePureStatelessExternalFunction * delegate () {
		return new Delegate (this);
	}

	static VALUE initialize (VALUE self_ruby);

	static void mark (NonePureStatelessExternalFunction *);
	static void del (NonePureStatelessExternalFunction *);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, NonePureStatelessExternalFunction, rb_cObject)

ZR_CLASS_METHOD (NonePureStatelessExternalFunction, initialize, 0)

#endif
#ifdef IMPLEMENTATION_PART

NonePureStatelessExternalFunction::NonePureStatelessExternalFunction (VALUE caster_ruby) {

	this->caster_ruby = caster_ruby;

	shadow_ruby = Data_Wrap_Struct (cNonePureStatelessExternalFunction, mark, del, this);
}

VALUE NonePureStatelessExternalFunction::initialize (VALUE self_ruby) {

	NonePureStatelessExternalFunction * self =
		new NonePureStatelessExternalFunction (self_ruby);

	rb_iv_set (self_ruby, "@shadow", self->shadow ());

	return self_ruby;
}

zorba::String NonePureStatelessExternalFunction::Delegate::getLocalName () const {
	cout << "w0\n";
	exit (0);
}

zorba::String NonePureStatelessExternalFunction::Delegate::getURI () const {
	cout << "w1\n";
	exit (0);
}

zorba::ItemSequence_t NonePureStatelessExternalFunction::Delegate::evaluate (
		const Arguments_t & arguments,
		const zorba::StaticContext * staticContext_zorba,
		const zorba::DynamicContext * dynamicContext) const {

	// TODO maintain constness in ruby
	StaticContext * staticContext = new StaticContext ((zorba::StaticContext *) staticContext_zorba);

	VALUE itemSequence_ruby = zr_funcall (
		target->caster (),
		rb_intern ("evaluate"),
		3,
		Qnil,
		staticContext->ruby (),
		Qnil);

	ZR_REAL (zorba::ItemSequence_t, itemSequence);

	return * itemSequence;
}

void NonePureStatelessExternalFunction::mark (NonePureStatelessExternalFunction * nonePureStatelessExternalFunction) {
}

void NonePureStatelessExternalFunction::del (NonePureStatelessExternalFunction * nonePureStatelessExternalFunction) {
	delete nonePureStatelessExternalFunction;
}

#endif
