/*
 * zorba-ruby/parts/item.h
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

class Item {

	zorba::Item self_zorba;

	VALUE self_ruby;

	~Item () { }

public:

	Item ();

	zorba::Item & zorba () { return self_zorba; }

	VALUE ruby () { return self_ruby; }

	static void mark (Item *);

	static void del (Item *);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, Item, rb_cObject)

ZR_CLASS_METHOD (Item, string_value, 0)

#endif
#ifdef IMPLEMENTATION_PART

Item::Item () {
	self_ruby = Data_Wrap_Struct (
		cItem,
		Item::mark,
		Item::del,
		this);
}

void Item::mark (Item * item) {
}

void Item::del (Item * item) {
	ZR_DEBUG ("Item::del %p %s\n", item, item->zorba ().getStringValue ().c_str ());
	delete item;
}

VALUE Item_string_value (VALUE self_ruby) {

	ZR_REAL (Item, self);

	zorba::String string = self->zorba ().getStringValue ();

	return rb_str_new2 (string.c_str ());
}

#endif
