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

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, SingletonItemSequence, rb_cObject)

ZR_CLASS_SINGLETON_METHOD (SingletonItemSequence, new, 1);

#endif
#ifdef IMPLEMENTATION_PART

VALUE SingletonItemSequence_new (VALUE self_ruby, VALUE item_ruby) {

	ZR_REAL (zorba::Item, item);

	zorba::ItemSequence_t * itemSequence = new zorba::ItemSequence_t ();

	* itemSequence = auto_ptr<zorba::ItemSequence> (
		new zorba::SingletonItemSequence (* item));

	VALUE itemSequence_ruby = Data_Wrap_Struct (
		cSingletonItemSequence,
		0,
		0, // TODO
		itemSequence);

	return itemSequence_ruby;
}

#endif
