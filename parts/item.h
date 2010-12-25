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

void Item_delete (zorba::Item *);
void Item_mark (zorba::Item *);
VALUE Item_wrap (zorba::Item *);

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, Item, rb_cObject)

ZR_CLASS_METHOD (Item, string_value, 0)

#endif
#ifdef IMPLEMENTATION_PART

void Item_delete (zorba::Item * item_real) {
	delete item_real;
}

void Item_mark (zorba::Item * item_real) {
	// do nothing
}

VALUE Item_wrap (zorba::Item * item_real) {

	return Data_Wrap_Struct (
		cItem,
		Item_mark,
		Item_delete,
		(void *) item_real);
}

VALUE Item_string_value (VALUE self_ruby) {

	ZR_REAL (zorba::Item, self);

	zorba::String string = self_real->getStringValue ();

	return rb_str_new2 (string.c_str ());
}

#endif
