/*
 * zorba-ruby/parts/zorba.h
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

#ifdef STUBS_PART

class ZorbaWrapper;
template <class T> class ZorbaWrapperOwned;

#endif
#ifdef INTERFACE_PART

class ZorbaWrapper {

protected:

	ZorbaWrapper () { }

	virtual ~ZorbaWrapper () { }

public:

	virtual void unwrap () = 0;

	virtual const char * toString () = 0;
};

template <class T>
class ZorbaWrapperOwned : public ZorbaWrapper {

	T * self_zorba;
	VALUE self_ruby;

	static void mark_static (T * self) {
	}

	static void delete_static (T * self) {
		delete self;
	}

protected:

	Zorba * owner;
	bool isOwned;

	ZorbaWrapperOwned (Zorba * owner, bool isOwned, T * self_zorba, VALUE rubyClass) {
ZR_DEBUG ("init %p\n", this);

		this->owner = owner;
		this->isOwned = isOwned;

		this->self_zorba = self_zorba;

		self_ruby = Data_Wrap_Struct (rubyClass, mark_static, delete_static, this);

		owner->addOwned (this);
ZR_DEBUG ("init %p done\n", this);
	}

	virtual ~ZorbaWrapperOwned () {
ZR_DEBUG ("destroy %s %p\n", toString (), this);

		unwrap ();
ZR_DEBUG ("destroy %p done\n", this);
	}

	virtual void unwrap () {

		if (! self_zorba)
			return;
ZR_DEBUG ("unwrap %s %p\n", toString (), this);

		if (isOwned)
			delete self_zorba;
		self_zorba = NULL;

		owner->removeOwned (this);
ZR_DEBUG ("unwrap %p done\n", this);
	}

public:

	T * zorba () { return self_zorba; }
	VALUE ruby () { return self_ruby; }
};

#endif
#ifdef IMPLEMENTATION_PART

#endif
