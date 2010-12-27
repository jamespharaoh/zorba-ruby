/*
 * zorba-ruby/parts/iterator.h
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

class Iterator :
	public ZorbaWrapperOwnedImpl <Iterator, zorba::Iterator_t> {

	virtual ~Iterator () { }

public:

	Iterator (ZorbaWrapperOwner * owner);

	virtual string toString () { return "Iterator"; }

	zorba::Iterator_t & zorba () { return * self_zorba; }

	static VALUE close (VALUE self_ruby);
	static VALUE next (VALUE self_ruby);
	static VALUE open (VALUE self_ruby);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, Iterator, rb_cObject)

ZR_CLASS_METHOD (Iterator, close, 0)
ZR_CLASS_METHOD (Iterator, next, 0)
ZR_CLASS_METHOD (Iterator, open, 0)

#endif
#ifdef IMPLEMENTATION_PART

Iterator::Iterator (ZorbaWrapperOwner * owner) :
	ZorbaWrapperOwnedImpl <Iterator, zorba::Iterator_t> (
		owner, true, new zorba::Iterator_t (), cIterator) {
}

VALUE Iterator::close (VALUE self_ruby) {

	ZR_REAL (Iterator, self);

	self->zorba ()->close ();

	return Qnil;
}

VALUE Iterator::next (VALUE self_ruby) {

	ZR_REAL (Iterator, self);

	Item * item = new Item (self->owner ());

	bool ret = self->zorba ()->next (* item->zorba ());
	if (! ret) return Qnil;

	return item->ruby ();
}

VALUE Iterator::open (VALUE self_ruby) {

	ZR_REAL (Iterator, self);

	self->zorba ()->open ();

	return Qnil;
}

#endif
