/*
 * zorba-ruby/parts.h
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

#ifndef ZR_CLASS
#define ZR_CLASS(name, parent)
#endif

#ifndef ZR_CLASS_CLASS
#define ZR_CLASS_CLASS(under, name, parent)
#endif

#ifndef ZR_CLASS_CONST
#define ZR_CLASS_CONST(klass, name, args)
#endif

#ifndef ZR_CLASS_EXCEP
#define ZR_CLASS_EXCEP(under, name, parent)
#endif

#ifndef ZR_CLASS_METHOD
#define ZR_CLASS_METHOD(klass, name, args)
#endif

#ifndef ZR_CLASS_MODULE
#define ZR_CLASS_MODULE(under, name)
#endif

#ifndef ZR_CLASS_SINGLETON_METHOD
#define ZR_CLASS_SINGLETON_METHOD(klass, name, args)
#endif

#ifndef ZR_MODULE_SINGLETON_METHOD
#define ZR_MODULE_SINGLETON_METHOD(module, name, args)
#endif

#include "parts/zorba.h"

#include "parts/zorba-wrapper.h"

#include "parts/compiler-hints.h"
#include "parts/dynamic-context.h"
#include "parts/external-module-wrapper.h"
#include "parts/item.h"
#include "parts/item-factory.h"
#include "parts/iterator.h"
#include "parts/module-uri-resolver.h"
#include "parts/none-pure-stateless-external-function.h"
#include "parts/singleton-item-sequence.h"
#include "parts/static-context.h"
#include "parts/store-manager.h"
#include "parts/uri-resolver-result.h"
#include "parts/version.h"
#include "parts/xquery.h"
#include "parts/zorba-exception.h"

#include "parts/module-uri-resolver-result.h"

#undef ZR_CLASS
#undef ZR_CLASS_CLASS
#undef ZR_CLASS_CONST
#undef ZR_CLASS_EXCEP
#undef ZR_CLASS_METHOD
#undef ZR_CLASS_MODULE
#undef ZR_CLASS_SINGLETON_METHOD
#undef ZR_MODULE_SINGLETON_METHOD
