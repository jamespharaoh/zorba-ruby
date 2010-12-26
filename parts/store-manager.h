/*
 * zorba-ruby/parts/store-manager.h
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

class StoreManager {

public:

	static VALUE get_store (VALUE self_ruby);
	static VALUE shutdown_store (VALUE self_ruby, VALUE store_ruby);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_MODULE (Zorba, StoreManager)

ZR_MODULE_SINGLETON_METHOD (StoreManager, get_store, 0)
ZR_MODULE_SINGLETON_METHOD (StoreManager, shutdown_store, 1)

#endif
#ifdef IMPLEMENTATION_PART

VALUE StoreManager::get_store (VALUE self_ruby) {

	void * store = zorba::StoreManager::getStore ();

	return Data_Wrap_Struct (cStore, 0, 0, store);
}

VALUE StoreManager::shutdown_store (VALUE self_ruby, VALUE store_ruby) {

	ZR_REAL (void, store);

	zorba::StoreManager::shutdownStore (store);

	return Qnil;
}

#endif
