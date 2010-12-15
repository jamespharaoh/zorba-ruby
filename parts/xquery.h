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

void XQuery_delete (XQuery_t *);
void XQuery_mark (XQuery_t *);
VALUE XQuery_wrap (XQuery_t *);

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, XQuery, rb_cObject)

ZR_CLASS_METHOD (XQuery, compile, 1)
ZR_CLASS_METHOD (XQuery, execute, 0)
ZR_CLASS_METHOD (XQuery, iterator, 0)
ZR_CLASS_METHOD (XQuery, filename_eq, 1)

#endif
#ifdef IMPLEMENTATION_PART

void XQuery_delete (XQuery_t * xquery_real) {
	delete xquery_real;
}

void XQuery_mark (XQuery_t * xquery_real) {
	// do nothing
}

VALUE XQuery_wrap (XQuery_t * xquery_real) {

	return Data_Wrap_Struct (
		cXQuery,
		XQuery_mark,
		XQuery_delete,
		(void *) xquery_real);
}

VALUE XQuery_compile (VALUE self, VALUE query) {

	ZR_REAL (XQuery_t, self);

	(* self_real)->compile (StringValueCStr (query));

	return Qnil;
}

VALUE XQuery_execute (VALUE self) {

	ZR_REAL (XQuery_t, self);

	basic_ostringstream<char> out;

	(*self_real)->execute (out);

	return rb_str_new2 (out.str ().c_str ());
}

VALUE XQuery_iterator (VALUE self) {

	ZR_REAL (XQuery_t, self);

	auto_ptr <Iterator_t> iterator_real (new Iterator_t ());

	* iterator_real = (* self_real)->iterator ();
	VALUE iterator = Iterator_wrap (iterator_real.release ());

	return iterator;
}

VALUE XQuery_filename_eq (VALUE self, VALUE value) {

	ZR_REAL (XQuery_t, self);

	(* self_real)->setFileName (StringValueCStr (value));

	return Qnil;
}

#endif
