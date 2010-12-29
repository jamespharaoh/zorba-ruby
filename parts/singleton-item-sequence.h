/*
 * zorba-ruby/parts/singleton-item-sequence.h
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

class ItemSequence :
	public ZorbaWrapperShadowImpl <ItemSequence, void> {

protected:

	ItemSequence (VALUE self_ruby, VALUE rubyClass);

public:

	virtual ~ItemSequence () { }

	virtual zorba::ItemSequence_t zorba () = 0;
};

class SingletonItemSequence :
	public virtual ItemSequence {

	Item * item;

	SingletonItemSequence (VALUE caster_ruby, Item * item_arg);

public:

	virtual string toString () { return "SingletonItemSequence"; }

	virtual zorba::ItemSequence_t zorba ();

	static VALUE initialize (VALUE self_ruby, VALUE item_ruby);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, SingletonItemSequence, rb_cObject)

ZR_CLASS_METHOD (SingletonItemSequence, initialize, 1);

#endif
#ifdef IMPLEMENTATION_PART

ItemSequence::ItemSequence (VALUE caster_ruby, VALUE rubyClass) :
	ZorbaWrapperShadowImpl <ItemSequence, void> (
		caster_ruby, (ItemSequence *) this, NULL, rubyClass) {
}

SingletonItemSequence::SingletonItemSequence (VALUE caster_ruby, Item * item_arg) :
	ItemSequence (caster_ruby, cSingletonItemSequence) {

	item = item_arg;
}

zorba::ItemSequence_t SingletonItemSequence::zorba () {
	return zorba::ItemSequence_t (new zorba::SingletonItemSequence (* item->zorba ()));
}

VALUE SingletonItemSequence::initialize (VALUE self_ruby, VALUE item_ruby) {

	ZR_REAL (Item, item);

	ItemSequence * itemSequence = new SingletonItemSequence (self_ruby, item);

	rb_iv_set (self_ruby, "@shadow", itemSequence->shadow ());

	return self_ruby;
}

#endif
