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

class XQuery {

	zorba::XQuery_t self_zorba;
	VALUE self_ruby;

public:

	XQuery (zorba::XQuery_t & xquery);

	const zorba::XQuery_t & zorba () { return self_zorba; }
	VALUE ruby () { return self_ruby; }

	static VALUE close (VALUE self_ruby);
	static VALUE clone (VALUE self_ruby);
	static VALUE compile (VALUE self_ruby, VALUE query_ruby);
	static VALUE dynamic_context (VALUE self_ruby);
	static VALUE execute (VALUE self_ruby);
	static VALUE iterator (VALUE self_ruby);
	static VALUE filename_eq (VALUE self_ruby, VALUE value_ruby);

	static void mark (XQuery * xquery);
	static void del (XQuery * xquery);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, XQuery, rb_cObject)

ZR_CLASS_METHOD (XQuery, clone, 0)
ZR_CLASS_METHOD (XQuery, close, 0)
ZR_CLASS_METHOD (XQuery, compile, 1)
ZR_CLASS_METHOD (XQuery, dynamic_context, 0)
ZR_CLASS_METHOD (XQuery, execute, 0)
ZR_CLASS_METHOD (XQuery, iterator, 0)
ZR_CLASS_METHOD (XQuery, filename_eq, 1)

#endif
#ifdef IMPLEMENTATION_PART

XQuery::XQuery (zorba::XQuery_t & xquery_zorba) {

	self_zorba = xquery_zorba;

	self_ruby = Data_Wrap_Struct (cXQuery, mark, del, this);
}

VALUE XQuery::close (VALUE self_ruby) {

	ZR_REAL (zorba::XQuery_t, self);

	(* self)->close ();

	return Qnil;
}

VALUE XQuery::clone (VALUE self_ruby) {

	ZR_REAL (zorba::XQuery_t, self);

	zorba::XQuery_t cloned_zorba;

	cloned_zorba = (* self)->clone ();

	XQuery * cloned = new XQuery (cloned_zorba);

	return cloned->ruby ();
}

VALUE XQuery::compile (VALUE self_ruby, VALUE query_ruby) {

	ZR_REAL (zorba::XQuery_t, self);

	(* self)->compile (StringValueCStr (query_ruby));

	return Qnil;
}

VALUE XQuery::dynamic_context (VALUE self_ruby) {

	ZR_REAL (zorba::XQuery_t, self);

	zorba::DynamicContext * dynamicContext_zorba = (* self)->getDynamicContext ();

	DynamicContext * dynamicContext = new DynamicContext (dynamicContext_zorba);

	return dynamicContext->ruby ();
}

VALUE XQuery::execute (VALUE self_ruby) {

	ZR_REAL (zorba::XQuery_t, self);

	basic_ostringstream<char> out;

	(*self)->execute (out);

	return rb_str_new2 (out.str ().c_str ());
}

VALUE XQuery::iterator (VALUE self_ruby) {

	ZR_REAL (zorba::XQuery_t, self);

	zorba::Iterator_t iterator_zorba = (* self)->iterator ();

	Iterator * iterator = new Iterator (iterator_zorba);

	return iterator->ruby ();
}

VALUE XQuery::filename_eq (VALUE self_ruby, VALUE value_ruby) {

	ZR_REAL (zorba::XQuery_t, self);

	(* self)->setFileName (StringValueCStr (value_ruby));

	return Qnil;
}

void XQuery::mark (XQuery * xquery) {
}

void XQuery::del (XQuery * xquery) {
	delete xquery;
}

#endif
