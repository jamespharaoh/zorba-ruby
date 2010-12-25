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

class NonePureStatelessExternalFunctionWrapper : public zorba::NonePureStatelessExternalFunction {

	VALUE shadow;

public:

	NonePureStatelessExternalFunctionWrapper (VALUE shadow) {
		this->shadow = shadow;
	}

	virtual ~NonePureStatelessExternalFunctionWrapper () {
		cout << "TODO ~NonePureStatelessExternalFunctionWrapper\n";
		exit (0);
	}

	virtual zorba::String getLocalName () const;

	virtual zorba::String getURI () const;

	virtual zorba::ItemSequence_t evaluate (
		const Arguments_t &,
		const zorba::StaticContext *,
		const zorba::DynamicContext *) const;
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, NonePureStatelessExternalFunction, rb_cObject)

ZR_CLASS_METHOD (NonePureStatelessExternalFunction, initialize, 0)

#endif
#ifdef IMPLEMENTATION_PART

VALUE NonePureStatelessExternalFunction_initialize (VALUE self_ruby) {

	NonePureStatelessExternalFunctionWrapper* shadow_real =
		new NonePureStatelessExternalFunctionWrapper (self_ruby);

	VALUE shadow_ruby = Data_Wrap_Struct (
		cNonePureStatelessExternalFunction,
		0,
		0, /* TODO? */
		shadow_real);

	rb_iv_set (self_ruby, "@shadow", shadow_ruby);

	return self_ruby;
}

zorba::String NonePureStatelessExternalFunctionWrapper::getLocalName () const {
	cout << "w0\n";
	exit (0);
}

zorba::String NonePureStatelessExternalFunctionWrapper::getURI () const {
	cout << "w1\n";
	exit (0);
}

zorba::ItemSequence_t NonePureStatelessExternalFunctionWrapper::evaluate (
		const Arguments_t & arguments_real,
		const zorba::StaticContext * staticContext_zorba,
		const zorba::DynamicContext * dynamicContext_real) const {

	// TODO maintain constness in ruby
	StaticContext * staticContext = StaticContext::wrap (
		(zorba::StaticContext *) staticContext_zorba);

	VALUE itemSequence_ruby = zr_funcall (
		shadow,
		rb_intern ("evaluate"),
		3,
		Qnil,
		staticContext->ruby (),
		Qnil);

	ZR_REAL (zorba::ItemSequence_t, itemSequence);

	return * itemSequence_real;
}

#endif
