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

class ItemFactory :
	public ZorbaWrapperOwnedImpl <ItemFactory, zorba::ItemFactory> {

	virtual ~ItemFactory () { }

public:

	ItemFactory (ZorbaWrapperOwner * owner, zorba::ItemFactory *);

	virtual string toString () { return "ItemFactory"; }

	static VALUE create_element_node (VALUE, VALUE, VALUE, VALUE, VALUE, VALUE, VALUE);
	static VALUE create_integer (VALUE self_ruby, VALUE integer_ruby);
	static VALUE create_qname (VALUE self_ruby, VALUE ns_ruby, VALUE localName_ruby);
	static VALUE create_string (VALUE self_ruby, VALUE str_ruby);
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

ItemFactory::ItemFactory (ZorbaWrapperOwner * owner, zorba::ItemFactory * itemFactory_zorba) :
	ZorbaWrapperOwnedImpl <ItemFactory, zorba::ItemFactory> (owner, false, itemFactory_zorba, cItemFactory) {
}

VALUE ItemFactory::create_element_node (
		VALUE self_ruby,
		VALUE parent_ruby,
		VALUE nodeName_ruby,
		VALUE typeName_ruby,
		VALUE hasTypedValue_ruby,
		VALUE hasEmptyValue_ruby,
		VALUE nsBindings_ruby) {

	ZR_REAL (ItemFactory, self);
	ZR_REAL_OPT (Item, parent);
	ZR_REAL_OPT (Item, nodeName);
	ZR_REAL_OPT (Item, typeName);

	zorba::Item null_zorba;

	Item * item = new Item (self->owner ());

	* item->zorba () = self->zorba ()->createElementNode (
		parent ? * parent->zorba () : null_zorba,
		nodeName ? * nodeName->zorba () : null_zorba,
		typeName ? * typeName->zorba () : null_zorba,
		RTEST (hasTypedValue_ruby) ? true : false,
		RTEST (hasEmptyValue_ruby) ? true : false,
		vector<pair<zorba::String,zorba::String> > ());

	return item->ruby ();
}

VALUE ItemFactory::create_integer (VALUE self_ruby, VALUE integer_ruby) {

	ZR_REAL (ItemFactory, self);

	Item * item = new Item (self->owner ());

	* item->zorba () = self->zorba ()->createInteger (NUM2ULONG (integer_ruby));

	return item->ruby ();
}

VALUE ItemFactory::create_qname (VALUE self_ruby, VALUE ns_ruby, VALUE localName_ruby) {

	ZR_REAL (ItemFactory, self);

	Item * item = new Item (self->owner ());

	* item->zorba () = self->zorba ()->createQName (RSTRING (ns_ruby)->ptr, RSTRING (localName_ruby)->ptr);

	return item->ruby ();
}

VALUE ItemFactory::create_string (VALUE self_ruby, VALUE str_ruby) {

	ZR_REAL (ItemFactory, self);

	Item * item = new Item (self->owner ());

	* item->zorba () = self->zorba ()->createString (RSTRING (str_ruby)->ptr);

	return item->ruby ();
}

#endif
