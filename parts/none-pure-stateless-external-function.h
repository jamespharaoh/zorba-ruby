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

class NonePureStatelessExternalFunctionWrapper : public NonePureStatelessExternalFunction {

	VALUE shadow;

public:

	NonePureStatelessExternalFunctionWrapper (VALUE shadow) {
		this->shadow = shadow;
	}

	virtual ~NonePureStatelessExternalFunctionWrapper () {
		cout << "TODO ~NonePureStatelessExternalFunctionWrapper\n";
		exit (0);
	}

	virtual String getLocalName () const;

	virtual String getURI () const;

	virtual ItemSequence_t evaluate (const Arguments_t &, const StaticContext *, const DynamicContext *) const;
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, NonePureStatelessExternalFunction, rb_cObject)

ZR_CLASS_METHOD (NonePureStatelessExternalFunction, initialize, 0);

#endif
#ifdef IMPLEMENTATION_PART

VALUE NonePureStatelessExternalFunction_initialize (VALUE self) {

	NonePureStatelessExternalFunctionWrapper* shadow_real = new NonePureStatelessExternalFunctionWrapper (self);
	VALUE shadow = Data_Wrap_Struct (cNonePureStatelessExternalFunction, 0, 0/* TODO? */, shadow_real);

	rb_iv_set (self, "@shadow", shadow);

	return self;
}

String NonePureStatelessExternalFunctionWrapper::getLocalName () const {
	cout << "w0\n";
	exit (0);
}

String NonePureStatelessExternalFunctionWrapper::getURI () const {
	cout << "w1\n";
	exit (0);
}

ItemSequence_t NonePureStatelessExternalFunctionWrapper::evaluate (
		const Arguments_t& arguments_real,
		const StaticContext* staticContext_real,
		const DynamicContext* dynamicContext_real) const {

	VALUE staticContext = StaticContext_wrap (staticContext_real);

	VALUE itemSequence = zr_funcall (
		shadow,
		rb_intern ("evaluate"),
		3,
		Qnil,
		staticContext,
		Qnil);

	ItemSequence_t * itemSequence_real;
	Data_Get_Struct (itemSequence, ItemSequence_t, itemSequence_real);

	return * itemSequence_real;
}

#endif
