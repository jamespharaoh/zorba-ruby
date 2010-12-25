/*
 * zorba-ruby/parts/item-factory.h
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

class ItemFactory {

	zorba::ItemFactory * self_zorba;

	VALUE self_ruby;

	ItemFactory () { }

public:

	~ItemFactory () { }

	zorba::ItemFactory * zorba () { return self_zorba; }

	VALUE ruby () { return self_ruby; }

	static void mark (ItemFactory *);

	static void del (ItemFactory *);

	static ItemFactory * wrap (zorba::ItemFactory *);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, ItemFactory, rb_cObject)

ZR_CLASS_METHOD (ItemFactory, create_element_node, 6);
ZR_CLASS_METHOD (ItemFactory, create_integer, 1);
ZR_CLASS_METHOD (ItemFactory, create_qname, 2);
ZR_CLASS_METHOD (ItemFactory, create_string, 1);

#endif
#ifdef IMPLEMENTATION_PART

void ItemFactory::mark (ItemFactory * itemFactory) {
}

void ItemFactory::del (ItemFactory * itemFactory) {
	delete itemFactory;
}

ItemFactory * ItemFactory::wrap (zorba::ItemFactory * itemFactory_zorba) {

	ItemFactory * itemFactory = new ItemFactory ();

	itemFactory->self_zorba = itemFactory_zorba;

	itemFactory->self_ruby = Data_Wrap_Struct (
		cItemFactory,
		ItemFactory::mark,
		ItemFactory::del,
		itemFactory);

	return itemFactory;
}

VALUE ItemFactory_create_element_node (
		VALUE self_ruby,
		VALUE parent_ruby,
		VALUE nodeName_ruby,
		VALUE typeName_ruby,
		VALUE hasTypedValue_ruby,
		VALUE hasEmptyValue_ruby,
		VALUE nsBindings_ruby) {

	ZR_REAL (ItemFactory, self);

	zorba::Item parent_real = Item_get (parent_ruby);

	zorba::Item * item_real = new zorba::Item ();
	* item_real = self_real->zorba ()->createElementNode (
		parent_real,
		Item_get (nodeName_ruby),
		Item_get (typeName_ruby),
		RTEST (hasTypedValue_ruby) ? true : false,
		RTEST (hasEmptyValue_ruby) ? true : false,
		vector<pair<zorba::String,zorba::String> > ());
	VALUE item = Data_Wrap_Struct (cItem, 0, 0, item_real);

	return item;
}

VALUE ItemFactory_create_integer (VALUE self_ruby, VALUE integer_ruby) {

	ZR_REAL (ItemFactory, self);

	zorba::Item * item_real = new zorba::Item ();
	* item_real = self_real->zorba ()->createInteger (NUM2ULONG (integer_ruby));
	VALUE item = Data_Wrap_Struct (cItem, 0, Item_delete, item_real);

	return item;
}

VALUE ItemFactory_create_qname (VALUE self_ruby, VALUE ns_ruby, VALUE localName_ruby) {

	ZR_REAL (ItemFactory, self);

	zorba::Item * item_real = new zorba::Item ();
	* item_real = self_real->zorba ()->createQName (RSTRING (ns_ruby)->ptr, RSTRING (localName_ruby)->ptr);
	VALUE item = Data_Wrap_Struct (cItem, 0, Item_delete, item_real);

	return item;
}

VALUE ItemFactory_create_string (VALUE self_ruby, VALUE str_ruby) {

	ZR_REAL (ItemFactory, self);

	zorba::Item * item_real = new zorba::Item ();
	* item_real = self_real->zorba ()->createString (RSTRING (str_ruby)->ptr);
	VALUE item = Data_Wrap_Struct (cItem, 0, Item_delete, item_real);

	return item;
}

#endif
