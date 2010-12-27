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

class XQuery :
	public ZorbaWrapperOwnedImpl <XQuery, zorba::XQuery_t>,
	public ZorbaWrapperOwner {

public:

	XQuery (ZorbaWrapperOwner * owner, zorba::XQuery_t & xquery);

	zorba::XQuery * zorba () { return self_zorba->get (); }

	virtual string toString () { return "XQuery"; }

	static VALUE close (VALUE self_ruby);
	static VALUE clone (VALUE self_ruby);
	static VALUE compile (VALUE self_ruby, VALUE query_ruby);
	static VALUE dynamic_context (VALUE self_ruby);
	static VALUE execute (VALUE self_ruby);
	static VALUE iterator (VALUE self_ruby);
	static VALUE filename_eq (VALUE self_ruby, VALUE value_ruby);
	static VALUE timeout_eq (VALUE self_ruby, VALUE value_ruby);

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
ZR_CLASS_METHOD (XQuery, filename_eq, 1)
ZR_CLASS_METHOD (XQuery, iterator, 0)
ZR_CLASS_METHOD (XQuery, timeout_eq, 1)

#endif
#ifdef IMPLEMENTATION_PART

XQuery::XQuery (ZorbaWrapperOwner * owner, zorba::XQuery_t & xquery_zorba) :
	ZorbaWrapperOwnedImpl <XQuery, zorba::XQuery_t> (
		owner, true, new zorba::XQuery_t (xquery_zorba), cXQuery) {
}

VALUE XQuery::close (VALUE self_ruby) {

	ZR_REAL (XQuery, self);

	self->zorba ()->close ();

	return Qnil;
}

VALUE XQuery::clone (VALUE self_ruby) {

	ZR_REAL (XQuery, self);

	zorba::XQuery_t cloned_zorba;

	cloned_zorba = self->zorba ()->clone ();

	XQuery * cloned = new XQuery (self->owner (), cloned_zorba);

	return cloned->ruby ();
}

VALUE XQuery::compile (VALUE self_ruby, VALUE query_ruby) {

	ZR_REAL (XQuery, self);

	self->zorba ()->compile (StringValueCStr (query_ruby));

	return Qnil;
}

VALUE XQuery::dynamic_context (VALUE self_ruby) {

	ZR_REAL (XQuery, self);

	zorba::DynamicContext * dynamicContext_zorba = self->zorba ()->getDynamicContext ();

	DynamicContext * dynamicContext = new DynamicContext (dynamicContext_zorba);

	return dynamicContext->ruby ();
}

VALUE XQuery::execute (VALUE self_ruby) {

	ZR_REAL (XQuery, self);

	basic_ostringstream <char> out;

	self->zorba ()->execute (out);

	return rb_str_new2 (out.str ().c_str ());
}

VALUE XQuery::iterator (VALUE self_ruby) {

	ZR_REAL (XQuery, self);

	Iterator * iterator = new Iterator (self);

	iterator->zorba () = self->zorba ()->iterator ();

	return iterator->ruby ();
}

VALUE XQuery::filename_eq (VALUE self_ruby, VALUE value_ruby) {

	ZR_REAL (XQuery, self);

	self->zorba ()->setFileName (StringValueCStr (value_ruby));

	return Qnil;
}

VALUE XQuery::timeout_eq (VALUE self_ruby, VALUE value_ruby) {

	ZR_REAL (XQuery, self);

	self->zorba ()->setTimeout (NUM2INT (value_ruby));

	return Qnil;
}

void XQuery::mark (XQuery * xquery) {
}

void XQuery::del (XQuery * xquery) {
	delete xquery;
}

#endif
