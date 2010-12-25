/*
 * zorba-ruby/parts/xquery.h
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

void XQuery_delete (zorba::XQuery_t *);
void XQuery_mark (zorba::XQuery_t *);
VALUE XQuery_wrap (zorba::XQuery_t *);

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, XQuery, rb_cObject)

ZR_CLASS_METHOD (XQuery, clone, 0)
ZR_CLASS_METHOD (XQuery, compile, 1)
ZR_CLASS_METHOD (XQuery, dynamic_context, 0)
ZR_CLASS_METHOD (XQuery, execute, 0)
ZR_CLASS_METHOD (XQuery, iterator, 0)
ZR_CLASS_METHOD (XQuery, filename_eq, 1)

#endif
#ifdef IMPLEMENTATION_PART

void XQuery_delete (zorba::XQuery_t * xquery_real) {
	delete xquery_real;
}

void XQuery_mark (zorba::XQuery_t * xquery_real) {
	// do nothing
}

VALUE XQuery_wrap (zorba::XQuery_t * xquery_real) {

	return Data_Wrap_Struct (
		cXQuery,
		XQuery_mark,
		XQuery_delete,
		(void *) xquery_real);
}

VALUE XQuery_clone (VALUE self_ruby) {

	ZR_REAL (zorba::XQuery_t, self);

	zorba::XQuery_t * cloned_real = new zorba::XQuery_t ();

	* cloned_real = (* self_real)->clone ();

	return XQuery_wrap (cloned_real);
}

VALUE XQuery_compile (VALUE self_ruby, VALUE query_ruby) {

	ZR_REAL (zorba::XQuery_t, self);

	(* self_real)->compile (StringValueCStr (query_ruby));

	return Qnil;
}

VALUE XQuery_dynamic_context (VALUE self_ruby) {

	ZR_REAL (zorba::XQuery_t, self);

	zorba::DynamicContext * dynamicContext_zorba = (* self_real)->getDynamicContext ();

	ZrDynamicContext * dynamicContext = ZrDynamicContext::wrap (dynamicContext_zorba);

	return dynamicContext->ruby ();
}

VALUE XQuery_execute (VALUE self_ruby) {

	ZR_REAL (zorba::XQuery_t, self);

	basic_ostringstream<char> out;

	(*self_real)->execute (out);

	return rb_str_new2 (out.str ().c_str ());
}

VALUE XQuery_iterator (VALUE self_ruby) {

	ZR_REAL (zorba::XQuery_t, self);

	auto_ptr <zorba::Iterator_t> iterator_real (new zorba::Iterator_t ());

	* iterator_real = (* self_real)->iterator ();
	VALUE iterator = Iterator_wrap (iterator_real.release ());

	return iterator;
}

VALUE XQuery_filename_eq (VALUE self_ruby, VALUE value_ruby) {

	ZR_REAL (zorba::XQuery_t, self);

	(* self_real)->setFileName (StringValueCStr (value_ruby));

	return Qnil;
}

#endif
