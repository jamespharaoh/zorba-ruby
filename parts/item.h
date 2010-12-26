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

class Item : public ZorbaWrapperOwned <zorba::Item> {

	virtual ~Item () { }

public:

	Item (Zorba * owner);

	virtual string toString () { return "Item"; }

	static VALUE string_value (VALUE self_ruby);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, Item, rb_cObject)

ZR_CLASS_METHOD (Item, string_value, 0)

#endif
#ifdef IMPLEMENTATION_PART

Item::Item (Zorba * owner) :
	ZorbaWrapperOwned <zorba::Item> (owner, true, new zorba::Item (), cItem) {
}

VALUE Item::string_value (VALUE self_ruby) {

	ZR_REAL (Item, self);

	zorba::String string = self->zorba ()->getStringValue ();

	return rb_str_new2 (string.c_str ());
}

#endif
