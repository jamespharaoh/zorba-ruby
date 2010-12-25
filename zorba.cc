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
#include <map>
#include <set>
#include <sstream>

#include <ruby.h>

#include <zorba/dynamic_context.h>
#include <zorba/external_function.h>
#include <zorba/external_module.h>
#include <zorba/options.h>
#include <zorba/singleton_item_sequence.h>
#include <zorba/store_manager.h>
#include <zorba/uri_resolvers.h>
#include <zorba/xquery.h>
#include <zorba/zorba.h>

#define ZR_REAL(type, name) \
	type * name##_real; \
	Data_Get_Struct (name##_ruby, type, name##_real)

#define ZR_SHADOW(type, name) \
	VALUE name##Shadow_ruby = rb_iv_get (name##_ruby, "@shadow"); \
	type * name##_real; \
	Data_Get_Struct (name##Shadow_ruby, type, name##_real)

#define ZR_REAL_OPT(type, name) \
	type * name##_real; \
	if (name##_ruby == Qnil) name##_real = NULL; \
	else Data_Get_Struct (name##_ruby, type, name##_real)

#define ZR_DEBUG(...) \
	fprintf (stderr, __VA_ARGS__)

using namespace std;

VALUE cStore;
VALUE cXmlDataManager;

VALUE currentException = Qnil;

class RubyException : public exception {
};

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

#define ZR_CLASS_MODULE(under, name) \
	VALUE m##name;

#define ZR_CLASS_EXCEP(under, name, parent) \
	VALUE e##name;

#define ZR_CLASS_CONST(klass, name, args)
#define ZR_CLASS_METHOD(klass, name, args)
#define ZR_CLASS_SINGLETON_METHOD(klass, name, args)
#define ZR_MODULE_SINGLETON_METHOD(module, name, args)

#include "parts.h"

#undef RUBY_PART

#undef ZR_CLASS
#undef ZR_CLASS_CLASS
#undef ZR_CLASS_CONST
#undef ZR_CLASS_EXCEP
#undef ZR_CLASS_METHOD
#undef ZR_CLASS_MODULE
#undef ZR_CLASS_SINGLETON_METHOD
#undef ZR_MODULE_SINGLETON_METHOD

// -------------------- implementation

#define IMPLEMENTATION_PART
#include "parts.h"
#undef IMPLEMENTATION_PART

// -------------------- wrap ruby methods

#define RUBY_PART

#define ZR_CLASS(name, parent)
#define ZR_CLASS_CLASS(under, name, parent)
#define ZR_CLASS_CONST(klass, name, args)
#define ZR_CLASS_EXCEP(under, name, parent)
#define ZR_CLASS_MODULE(under, name)

#define ZR_WRAP_INVOKE_VAR_C(name, self, argc, argv) \
	return name (argc, argv, self)

#define ZR_WRAP_INVOKE_0(name, self, argc, argv) \
	if (argc != 0) rb_raise (rb_eArgError, "Expected 0 arguments, got %d", argc); \
	return name (self)

#define ZR_WRAP_INVOKE_1(name, self, argc, argv) \
	if (argc != 1) rb_raise (rb_eArgError, "Expected 1 arguments, got %d", argc); \
	return name (self, argv[0])

#define ZR_WRAP_INVOKE_2(name, self, argc, argv) \
	if (argc != 2) rb_raise (rb_eArgError, "Expected 2 arguments, got %d", argc); \
	return name (self, argv[0], argv[1])

#define ZR_WRAP_INVOKE_3(name, self, argc, argv) \
	if (argc != 3) rb_raise (rb_eArgError, "Expected 3 arguments, got %d", argc); \
	return name (self, argv[0], argv[1], argv[2])

#define ZR_WRAP_INVOKE_4(name, self, argc, argv) \
	if (argc != 4) rb_raise (rb_eArgError, "Expected 4 arguments, got %d", argc); \
	return name (self, argv[0], argv[1], argv[2], argv[3])

#define ZR_WRAP_INVOKE_5(name, self, argc, argv) \
	if (argc != 5) rb_raise (rb_eArgError, "Expected 5 arguments, got %d", argc); \
	return name (self, argv[0], argv[1], argv[2], argv[3], argv[4])

#define ZR_WRAP_INVOKE_6(name, self, argc, argv) \
	if (argc != 6) rb_raise (rb_eArgError, "Expected 6 arguments, got %d", argc); \
	return name (self, argv[0], argv[1], argv[2], argv[3], argv[4], argv[5])

#define ZR_WRAP_INVOKE_7(name, self, argc, argv) \
	if (argc != 7) rb_raise (rb_eArgError, "Expected 7 arguments, got %d", argc); \
	return name (self, argv[0], argv[1], argv[2], argv[3], argv[4], argv[5], argv[6])

#define ZR_CLASS_METHOD(klass, name, args) \
	VALUE klass##_##name##_wrap (int argc, VALUE *argv, VALUE self) { \
		try { \
			ZR_WRAP_INVOKE_##args (klass##_##name, self, argc, argv); \
		} \
		catch (zorba::ZorbaException & e) { zr_raise (e); } \
		catch (RubyException & e) { zr_raise (e); } \
	}

#define ZR_CLASS_SINGLETON_METHOD(klass, name, args) \
	VALUE klass##_##name##_wrap (int argc, VALUE *argv, VALUE self) { \
		try { \
			ZR_WRAP_INVOKE_##args (klass##_##name, self, argc, argv); \
		} \
		catch (zorba::ZorbaException & e) { zr_raise (e); } \
		catch (RubyException & e) { zr_raise (e); } \
	}

#define ZR_MODULE_SINGLETON_METHOD(module, name, args) \
	VALUE module##_##name##_wrap (int argc, VALUE *argv, VALUE self) { \
		try { \
			ZR_WRAP_INVOKE_##args (module##_##name, self, argc, argv); \
		} \
		catch (zorba::ZorbaException & e) { zr_raise (e); } \
		catch (RubyException & e) { zr_raise (e); } \
	}

#include "parts.h"

#undef RUBY_PART

#undef ZR_CLASS
#undef ZR_CLASS_CLASS
#undef ZR_CLASS_CONST
#undef ZR_CLASS_EXCEP
#undef ZR_CLASS_METHOD
#undef ZR_CLASS_MODULE
#undef ZR_CLASS_SINGLETON_METHOD
#undef ZR_MODULE_SINGLETON_METHOD

#undef ZR_CLASS_INVOKE_VAR_C
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

#define ZR_CLASS_EXCEP(under, name, parent) \
	e##name = rb_define_class_under (c##under, #name, parent);

#define ZR_CLASS_METHOD(klass, name, args) \
	rb_define_method (c##klass, zr_map_method_name (#name), RUBY_METHOD_FUNC (klass##_##name##_wrap), -1);

#define ZR_CLASS_MODULE(under, name) \
	m##name = rb_define_module_under (c##under, #name);

#define ZR_CLASS_SINGLETON_METHOD(klass, name, args) \
	rb_define_singleton_method (c##klass, zr_map_method_name (#name), RUBY_METHOD_FUNC (klass##_##name##_wrap), -1);

#define ZR_MODULE_SINGLETON_METHOD(module, name, args) \
	rb_define_singleton_method (m##module, zr_map_method_name (#name), RUBY_METHOD_FUNC (module##_##name##_wrap), -1);

#include "parts.h"

#undef RUBY_PART

#undef ZR_CLASS
#undef ZR_CLASS_CLASS
#undef ZR_CLASS_CONST
#undef ZR_CLASS_EXCEP
#undef ZR_CLASS_METHOD
#undef ZR_CLASS_MODULE
#undef ZR_CLASS_SINGLETON_METHOD
#undef ZR_MODULE_SINGLETON_METHOD

// --------------------

	cStore = rb_define_class_under (cZorba, "Store", rb_cObject);

	cXmlDataManager = rb_define_class_under (cZorba, "XmlDataManager", rb_cObject);

}
