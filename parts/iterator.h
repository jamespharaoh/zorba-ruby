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

void Iterator_mark (Iterator_t *);
void Iterator_delete (Iterator_t *);
VALUE Iterator_wrap (Iterator *);

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, Iterator, rb_cObject)

ZR_CLASS_METHOD (Iterator, close, 0)
ZR_CLASS_METHOD (Iterator, next, 0)
ZR_CLASS_METHOD (Iterator, open, 0)

#endif
#ifdef IMPLEMENTATION_PART

void Iterator_mark (Iterator_t * iterator_real) {
	// do nothing
}

void Iterator_delete (Iterator_t * iterator_real) {
	delete iterator_real;
}

VALUE Iterator_wrap (Iterator_t * iterator_real) {

	return Data_Wrap_Struct (
		cIterator,
		Iterator_mark,
		Iterator_delete,
		(void *) iterator_real);
}

VALUE Iterator_close (VALUE self) {

	ZR_REAL (Iterator_t, self);

	(* self_real)->close ();

	return Qnil;
}

VALUE Iterator_next (VALUE self) {

	ZR_REAL (Iterator_t, self);

	auto_ptr <Item> item_real (new Item ());

	bool ret = (* self_real)->next (* item_real);
	if (! ret) return Qnil;

	return Item_wrap (item_real.release ());
}

VALUE Iterator_open (VALUE self) {

	ZR_REAL (Iterator_t, self);

	(* self_real)->open ();

	return Qnil;
}

#endif
