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

#endif
#ifdef RUBY_PART

ZR_CLASS_MODULE (Zorba, StoreManager)

ZR_MODULE_SINGLETON_METHOD (StoreManager, get_store, 0)

#endif
#ifdef IMPLEMENTATION_PART

VALUE StoreManager_get_store (VALUE self_ruby) {

	void *store_real = zorba::StoreManager::getStore ();

	return Data_Wrap_Struct (cStore, 0, 0, store_real);
}

#endif
