/*
 * zorba-ruby/parts/xquery.h
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

void xqueryDelete (XQuery_t *);

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, XQuery, rb_cObject)

ZR_CLASS_METHOD (XQuery, execute, 0)

#endif
#ifdef IMPLEMENTATION_PART

void xqueryDelete (XQuery_t * xquery) {
	delete xquery;
}

VALUE XQuery_execute (VALUE self) {

	XQuery_t *self_real;
	Data_Get_Struct (self, XQuery_t, self_real);

	basic_ostringstream<char> out;

	(*self_real)->execute (out);

	return rb_str_new2 (out.str ().c_str ());
}

#endif
