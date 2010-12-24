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

VALUE ItemFactory_wrap (const zorba::ItemFactory *);

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, ItemFactory, rb_cObject)

ZR_CLASS_METHOD (ItemFactory, create_element_node, 6);
ZR_CLASS_METHOD (ItemFactory, create_integer, 1);
ZR_CLASS_METHOD (ItemFactory, create_qname, 2);
ZR_CLASS_METHOD (ItemFactory, create_string, 1);

#endif
#ifdef IMPLEMENTATION_PART

VALUE ItemFactory_wrap (const zorba::ItemFactory * itemFactory_real) {

	VALUE itemFactory = Data_Wrap_Struct (
		cItemFactory,
		0,
		0,
		(void *) itemFactory_real);

	return itemFactory;
}

zorba::Item Item_get (VALUE item) {
	if (! RTEST (item)) return zorba::Item ();
	ZR_REAL (zorba::Item, item);
	return * item_real;
}

VALUE ItemFactory_create_element_node (
		VALUE self,
		VALUE parent,
		VALUE nodeName,
		VALUE typeName,
		VALUE hasTypedValue,
		VALUE hasEmptyValue,
		VALUE nsBindings) {

	ZR_REAL (zorba::ItemFactory, self);

	zorba::Item parent_real = Item_get (parent);

	zorba::Item * item_real = new zorba::Item ();
	* item_real = self_real->createElementNode (
		parent_real,
		Item_get (nodeName),
		Item_get (typeName),
		RTEST (hasTypedValue) ? true : false,
		RTEST (hasEmptyValue) ? true : false,
		vector<pair<zorba::String,zorba::String> > ());
	VALUE item = Data_Wrap_Struct (cItem, 0, 0, item_real);

	return item;
}

VALUE ItemFactory_create_integer (VALUE self, VALUE integer) {

	ZR_REAL (zorba::ItemFactory, self);

	zorba::Item * item_real = new zorba::Item ();
	* item_real = self_real->createInteger (NUM2ULONG (integer));
	VALUE item = Data_Wrap_Struct (cItem, 0, Item_delete, item_real);

	return item;
}

VALUE ItemFactory_create_qname (VALUE self, VALUE ns, VALUE localName) {

	ZR_REAL (zorba::ItemFactory, self);

	zorba::Item * item_real = new zorba::Item ();
	* item_real = self_real->createQName (RSTRING (ns)->ptr, RSTRING (localName)->ptr);
	VALUE item = Data_Wrap_Struct (cItem, 0, Item_delete, item_real);

	return item;
}

VALUE ItemFactory_create_string (VALUE self, VALUE str) {

	ZR_REAL (zorba::ItemFactory, self);

	zorba::Item * item_real = new zorba::Item ();
	* item_real = self_real->createString (RSTRING (str)->ptr);
	VALUE item = Data_Wrap_Struct (cItem, 0, Item_delete, item_real);

	return item;
}

#endif
