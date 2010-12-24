/*
 * zorba-ruby/parts/zorba-exception.h
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

void zr_raise (const zorba::ZorbaException &);
void zr_raise (const RubyException &);

#endif
#ifdef RUBY_PART

ZR_CLASS_EXCEP (Zorba, ZorbaException, rb_eStandardError)

ZR_CLASS_EXCEP (Zorba, QueryException, eZorbaException)
ZR_CLASS_EXCEP (Zorba, SerializationException, eZorbaException)
ZR_CLASS_EXCEP (Zorba, SystemException, eZorbaException)

ZR_CLASS_EXCEP (Zorba, DynamicException, eQueryException)
ZR_CLASS_EXCEP (Zorba, StaticException, eQueryException)
ZR_CLASS_EXCEP (Zorba, TypeException, eQueryException)
ZR_CLASS_EXCEP (Zorba, UserException, eQueryException)

#endif
#ifdef IMPLEMENTATION_PART

void zr_raise (const zorba::ZorbaException & zorbaException) {

	if (RTEST (currentException)) {
		VALUE currentExceptionTemp = currentException;
		currentException = Qnil;
		rb_exc_raise (currentExceptionTemp);
	}

	VALUE rubyExceptionClass = eZorbaException;

	if (dynamic_cast <const zorba::QueryException *> (& zorbaException)) {
		rubyExceptionClass = eQueryException;

		if (dynamic_cast <const zorba::DynamicException *> (& zorbaException)) {
			rubyExceptionClass = eDynamicException;

		} else if (dynamic_cast <const zorba::StaticException *> (& zorbaException)) {
			rubyExceptionClass = eStaticException;

		} else if (dynamic_cast <const zorba::TypeException *> (& zorbaException)) {
			rubyExceptionClass = eTypeException;

		} else if (dynamic_cast <const zorba::UserException *> (& zorbaException)) {
			rubyExceptionClass = eUserException;
		}

	} else if (dynamic_cast <const zorba::SerializationException *> (& zorbaException)) {
		rubyExceptionClass = eSerializationException;

	} else if (dynamic_cast <const zorba::SystemException *> (& zorbaException)) {
		rubyExceptionClass = eSystemException;
	}

	rb_raise (rubyExceptionClass, "[%s] %s",
		zorba::ZorbaException::getErrorCodeAsString (
			zorbaException.getErrorCode ()).c_str (),
		zorbaException.getDescription ().c_str ());
}

void zr_raise (const RubyException & rubyException) {
	cout << "got ruby exception\n";
	exit (0);
}

#endif
