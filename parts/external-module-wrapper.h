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

class ExternalModuleWrapper : public ExternalModule {

	VALUE value;

public:

	ExternalModuleWrapper (VALUE value) {
		this->value = value;
	}

	virtual ~ExternalModuleWrapper () {
		cout << "TODO ~ExternalModuleWrapper\n";
		exit (0);
	}

	virtual StatelessExternalFunction* getExternalFunction (String aLocalname) const;

	virtual String getURI () const;
};

#endif
#ifdef IMPLEMENTATION_PART

StatelessExternalFunction* ExternalModuleWrapper::getExternalFunction (String localName) const {

	VALUE ret = rb_funcall (
		value,
		rb_intern ("external_function"),
		1,
		rb_str_new2 (localName.c_str ()));

	VALUE shadow = rb_iv_get (ret, "@shadow");

	StatelessExternalFunction *shadow_real;
	Data_Get_Struct (shadow, StatelessExternalFunction, shadow_real);

	return shadow_real;
}

String ExternalModuleWrapper::getURI () const {

	VALUE ret = rb_funcall (
		value,
		rb_intern ("uri"),
		0);

	return RSTRING (ret)->ptr;
}

#endif
