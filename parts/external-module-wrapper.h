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

class ExternalModuleWrapper : public zorba::ExternalModule {

	Zorba * owner;

	VALUE value;

public:

	ExternalModuleWrapper (Zorba * owner, VALUE value) {
		this->owner = owner;
		this->value = value;
	}

	virtual ~ExternalModuleWrapper () {
		cout << "TODO ~ExternalModuleWrapper\n";
		exit (0);
	}

	virtual zorba::StatelessExternalFunction * getExternalFunction (zorba::String aLocalname) const;

	virtual zorba::String getURI () const;
};

#endif
#ifdef IMPLEMENTATION_PART

zorba::StatelessExternalFunction * ExternalModuleWrapper::getExternalFunction (
		zorba::String localName) const {

	VALUE ret = zr_funcall (
		value,
		rb_intern ("external_function"),
		1,
		rb_str_new2 (localName.c_str ()));

	VALUE shadow_ruby = rb_iv_get (ret, "@shadow");

	ZR_REAL (StatelessExternalFunction, shadow);

	return shadow->delegate (owner);
}

zorba::String ExternalModuleWrapper::getURI () const {

	VALUE ret = zr_funcall (
		value,
		rb_intern ("uri"),
		0);

	return RSTRING (ret)->ptr;
}

#endif
