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

class ItemSequence {

	zorba::ItemSequence * self_zorba;

	VALUE self_ruby;

	~ItemSequence () { }

public:

	ItemSequence (VALUE klass, zorba::ItemSequence *);

	zorba::ItemSequence * zorba () { return self_zorba; }

	VALUE ruby () { return self_ruby; }

	static void mark (ItemSequence *);
	static void del (ItemSequence *);
};

class SingletonItemSequence : public ItemSequence {

public:

	static VALUE new_new (VALUE self_ruby, VALUE item_ruby);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, SingletonItemSequence, rb_cObject)

ZR_CLASS_SINGLETON_METHOD (SingletonItemSequence, new_new, 1);

#endif
#ifdef IMPLEMENTATION_PART

ItemSequence::ItemSequence (VALUE klass, zorba::ItemSequence * itemSequence_zorba) {

	self_zorba = itemSequence_zorba;

	self_ruby = Data_Wrap_Struct (klass, mark, del, this);
}

VALUE SingletonItemSequence::new_new (VALUE self_ruby, VALUE item_ruby) {

	ZR_REAL (Item, item);

	zorba::ItemSequence * itemSequence_zorba = new zorba::SingletonItemSequence (* item->zorba ());

	ItemSequence * itemSequence = new ItemSequence (cSingletonItemSequence, itemSequence_zorba);

	return itemSequence->ruby ();
}

void ItemSequence::mark (ItemSequence * itemSequence) {
}

void ItemSequence::del (ItemSequence * itemSequence) {
	delete itemSequence;
}

#endif
