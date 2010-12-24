/*
 * zorba-ruby/parts/uri-resolver-result.h
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

ZR_CLASS_CLASS (Zorba, UriResolverResult, rb_cObject)

ZR_CLASS_METHOD (UriResolverResult, error_eq, 1)

ZR_CLASS_CONST (UriResolverResult, UR_NOERROR, INT2NUM (zorba::URIResolverResult::UR_NOERROR))

ZR_CLASS_CONST (UriResolverResult, UR_FODC0002, INT2NUM (zorba::URIResolverResult::UR_FODC0002))
ZR_CLASS_CONST (UriResolverResult, UR_FODC0003, INT2NUM (zorba::URIResolverResult::UR_FODC0003))
ZR_CLASS_CONST (UriResolverResult, UR_FODC0004, INT2NUM (zorba::URIResolverResult::UR_FODC0004))
ZR_CLASS_CONST (UriResolverResult, UR_FODC0005, INT2NUM (zorba::URIResolverResult::UR_FODC0005))

ZR_CLASS_CONST (UriResolverResult, UR_XQST0046, INT2NUM (zorba::URIResolverResult::UR_XQST0046))
ZR_CLASS_CONST (UriResolverResult, UR_XQST0057, INT2NUM (zorba::URIResolverResult::UR_XQST0057))
ZR_CLASS_CONST (UriResolverResult, UR_XQST0059, INT2NUM (zorba::URIResolverResult::UR_XQST0059))
ZR_CLASS_CONST (UriResolverResult, UR_XQST0088, INT2NUM (zorba::URIResolverResult::UR_XQST0088))

#endif
#ifdef IMPLEMENTATION_PART

VALUE UriResolverResult_error_eq (VALUE self, VALUE error) {

	VALUE shadow = rb_iv_get (self, "@shadow");
	ZR_REAL (zorba::URIResolverResult, shadow);

	shadow_real->setError ((zorba::URIResolverResult::ErrorCode) NUM2INT (error));
}

#endif
