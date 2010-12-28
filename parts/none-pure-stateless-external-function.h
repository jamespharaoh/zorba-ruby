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

	virtual ~StatelessExternalFunction () { }

	virtual zorba::StatelessExternalFunction * delegate (ZorbaWrapperOwner *) = 0;
};

class NonePureStatelessExternalFunction :
	public ZorbaWrapperShadowImpl <StatelessExternalFunction, void>,
	public virtual StatelessExternalFunction {

	class Delegate : public zorba::NonePureStatelessExternalFunction {

		ZorbaWrapperOwner * owner;

		::NonePureStatelessExternalFunction * target;

	public:

		Delegate (ZorbaWrapperOwner * owner, ::NonePureStatelessExternalFunction * target) {
			this->owner = owner;
			this->target = target;
		}

		virtual zorba::String getLocalName () const;

		virtual zorba::String getURI () const;

		virtual zorba::ItemSequence_t evaluate (
			const Arguments_t &,
			const zorba::StaticContext *,
			const zorba::DynamicContext *) const;
	};

	NonePureStatelessExternalFunction (VALUE caster_ruby);

public:

	virtual ~NonePureStatelessExternalFunction () { }

	virtual string toString () { return "NonePureStatelessExternalFunction"; }

	virtual zorba::NonePureStatelessExternalFunction * delegate (ZorbaWrapperOwner * owner) {
		return new Delegate (owner, this);
	}

	static VALUE initialize (VALUE self_ruby);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, NonePureStatelessExternalFunction, rb_cObject)

ZR_CLASS_METHOD (NonePureStatelessExternalFunction, initialize, 0)

#endif
#ifdef IMPLEMENTATION_PART

NonePureStatelessExternalFunction::NonePureStatelessExternalFunction (VALUE caster_ruby) :
	ZorbaWrapperShadowImpl <StatelessExternalFunction, void> (
		caster_ruby, (StatelessExternalFunction *) this, NULL, cNonePureStatelessExternalFunction) {
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
	StaticContextRaw * staticContext = new StaticContextRaw (
		owner, (zorba::StaticContext *) staticContext_zorba);

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

#endif
