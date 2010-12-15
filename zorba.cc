/*
 * zorba-ruby/zorba.cc
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

#include <cstdarg>
#include <exception>
#include <iostream>
#include <sstream>

#include <ruby.h>

#include <zorba/external_function.h>
#include <zorba/external_module.h>
#include <zorba/singleton_item_sequence.h>
#include <zorba/store_manager.h>
#include <zorba/uri_resolvers.h>
#include <zorba/xquery.h>
#include <zorba/zorba.h>

using namespace std;
using namespace zorba;

VALUE cStore;
VALUE mStoreManager;
VALUE cXmlDataManager;
VALUE eZorbaException;

VALUE currentException = Qnil;

class RubyException : public exception {
};

void raise (const ZorbaException & zorbaException) {

	if (RTEST (currentException)) {
		VALUE currentExceptionTemp = currentException;
		currentException = Qnil;
		rb_exc_raise (currentExceptionTemp);
	}

	rb_raise (eZorbaException, "[%s] %s",
		ZorbaException::getErrorCodeAsString (zorbaException.getErrorCode ()).c_str (),
		zorbaException.getDescription ().c_str ());
}

void raise (const RubyException & rubyException) {
	cout << "got ruby exception\n";
	exit (0);
}

const char * zr_map_method_name (const char * name) {
	static char * pointer = NULL;

	if (pointer) free (pointer);
	pointer = NULL;

	int len = strlen (name);
	pointer = (char *) malloc (len + 1);
	strcpy (pointer, name);

	if (len > 3 && strcmp (name + len - 3, "_eq") == 0) {
		pointer [len - 3] = '=';
		pointer [len - 2] = 0;
		return pointer;
	}

	return pointer;
}

VALUE zr_funcall_nest (VALUE args) {
	return rb_apply (
		rb_ary_entry (args, 0),
		rb_ary_entry (args, 1),
		rb_ary_entry (args, 2));
}

VALUE zr_funcall (VALUE self, VALUE name, int argc, ...) {

	va_list ap;
	int i;

	VALUE args1 = rb_ary_new2 (argc);

	va_start (ap, argc);
	for (int i = 0; i < argc; i++) {
		VALUE arg = va_arg (ap, VALUE);
		rb_ary_store (args1, i, arg);
	}
	va_end (ap);

	VALUE args2 =
		rb_ary_new3 (3,
			self,
			name,
			args1);

	int result;
	VALUE ret = rb_protect (&zr_funcall_nest, args2, &result);

	if (result) {
		currentException = rb_gv_get ("$!");
		cout << "excep: " << currentException << endl;
		throw new RubyException ();
	}

	return ret;
}

#define INTERFACE_PART
#include "parts.h"
#undef INTERFACE_PART

// -------------------- ruby class and module globals

#define RUBY_PART

#define ZR_CLASS(name, parent) \
	VALUE c##name;

#define ZR_CLASS_CLASS(under, name, parent) \
	VALUE c##name;

#define ZR_CLASS_CONST(klass, name, args)
#define ZR_CLASS_METHOD(klass, name, args)
#define ZR_CLASS_SINGLETON_METHOD(klass, name, args)

#include "parts.h"

#undef RUBY_PART

#undef ZR_CLASS
#undef ZR_CLASS_CLASS
#undef ZR_CLASS_CONST
#undef ZR_CLASS_METHOD
#undef ZR_CLASS_SINGLETON_METHOD

// --------------------

#define IMPLEMENTATION_PART
#include "parts.h"
#undef IMPLEMENTATION_PART

VALUE mStoreManager_get_store (VALUE self) {

	void *store_real = StoreManager::getStore ();
	return Data_Wrap_Struct (cStore, 0, 0, store_real);
}

// -------------------- wrap ruby methods

#define RUBY_PART

#define ZR_CLASS(name, parent)
#define ZR_CLASS_CLASS(under, name, parent)
#define ZR_CLASS_CONST(klass, name, args)

#define ZR_WRAP_INVOKE_0(name, self, argv) \
	return name (self)

#define ZR_WRAP_INVOKE_1(name, self, argv) \
	return name (self, argv[0])

#define ZR_WRAP_INVOKE_2(name, self, argv) \
	return name (self, argv[0], argv[1])

#define ZR_WRAP_INVOKE_3(name, self, argv) \
	return name (self, argv[0], argv[1], argv[2])

#define ZR_WRAP_INVOKE_4(name, self, argv) \
	return name (self, argv[0], argv[1], argv[2], argv[3])

#define ZR_WRAP_INVOKE_5(name, self, argv) \
	return name (self, argv[0], argv[1], argv[2], argv[3], argv[4])

#define ZR_WRAP_INVOKE_6(name, self, argv) \
	return name (self, argv[0], argv[1], argv[2], argv[3], argv[4], argv[5])

#define ZR_WRAP_INVOKE_7(name, self, argv) \
	return name (self, argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6])

#define ZR_CLASS_METHOD(klass, name, args) \
	VALUE klass##_##name##_wrap (int argc, VALUE *argv, VALUE self) { \
		try { \
			ZR_WRAP_INVOKE_##args (klass##_##name, self, argv); \
		} \
		catch (ZorbaException & e) { raise (e); } \
		catch (RubyException & e) { raise (e); } \
	}

#define ZR_CLASS_SINGLETON_METHOD(klass, name, args) \
	VALUE klass##_##name##_wrap (int argc, VALUE *argv, VALUE self) { \
		try { \
			ZR_WRAP_INVOKE_##args (klass##_##name, self, argv); \
		} \
		catch (ZorbaException & e) { raise (e); } \
		catch (RubyException & e) { raise (e); } \
	}

#include "parts.h"

#undef RUBY_PART

#undef ZR_CLASS
#undef ZR_CLASS_CLASS
#undef ZR_CLASS_CONST
#undef ZR_CLASS_METHOD
#undef ZR_CLASS_SINGLETON_METHOD

#undef ZR_CLASS_INVOKE_0
#undef ZR_CLASS_INVOKE_1
#undef ZR_CLASS_INVOKE_2
#undef ZR_CLASS_INVOKE_3
#undef ZR_CLASS_INVOKE_4
#undef ZR_CLASS_INVOKE_5
#undef ZR_CLASS_INVOKE_6
#undef ZR_CLASS_INVOKE_7

// -------------------- 

extern "C"
void Init_zorba () {

#define INIT_PART
#include "parts.h"
#undef INIT_PART

// -------------------- initialise classes, methods etc

#define RUBY_PART

#define ZR_CLASS(name, parent) \
	c##name = rb_define_class (#name, parent);

#define ZR_CLASS_CLASS(under, name, parent) \
	c##name = rb_define_class_under (c##under, #name, parent);

#define ZR_CLASS_CONST(klass, name, value) \
	rb_define_const (c##klass, #name, value);

#define ZR_CLASS_METHOD(klass, name, args) \
	rb_define_method (c##klass, zr_map_method_name (#name), RUBY_METHOD_FUNC (klass##_##name##_wrap), -1);

#define ZR_CLASS_SINGLETON_METHOD(klass, name, args) \
	rb_define_singleton_method (c##klass, zr_map_method_name (#name), RUBY_METHOD_FUNC (klass##_##name##_wrap), -1);

#include "parts.h"

#undef RUBY_PART

#undef ZR_CLASS
#undef ZR_CLASS_CLASS
#undef ZR_CLASS_CONST
#undef ZR_CLASS_METHOD
#undef ZR_CLASS_SINGLETON_METHOD

// --------------------

	cStore = rb_define_class_under (cZorba, "Store", rb_cObject);

	mStoreManager = rb_define_module_under (cZorba, "StoreManager");
	rb_define_singleton_method (mStoreManager, "get_store", RUBY_METHOD_FUNC (mStoreManager_get_store), 0);

	cXmlDataManager = rb_define_class_under (cZorba, "XmlDataManager", rb_cObject);

	eZorbaException = rb_define_class ("ZorbaException", rb_eException);

}
