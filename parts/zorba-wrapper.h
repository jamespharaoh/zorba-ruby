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
template <class Owner> class ZorbaWrapperOwned;
template <class Owner, class T> class ZorbaWrapperOwnedImpl;

#endif
#ifdef INTERFACE_PART

class ZorbaWrapper {

protected:

	ZorbaWrapper () { }

	virtual ~ZorbaWrapper () { }

public:

	virtual string toString () = 0;

	virtual void disown () = 0;
};

template <class Owner>
class ZorbaWrapperOwned : public virtual ZorbaWrapper {

public:

	virtual Owner * owner () = 0;
	virtual bool isOwned () = 0;
};

template <class Owner, class T>
class ZorbaWrapperOwnedImpl : public virtual ZorbaWrapperOwned<Owner>, public virtual ZorbaWrapper {

	static void mark_static (ZorbaWrapperOwnedImpl <Owner, T> * self) {
	}

	static void delete_static (ZorbaWrapperOwnedImpl <Owner, T> * self) {
		self->disown ();
		delete self;
	}

protected:

	Owner * owner_val;
	bool isOwned_val;

	T * self_zorba;
	VALUE self_ruby;

	ZorbaWrapperOwnedImpl (Owner * owner_arg, bool isOwned_arg, T * self_zorba, VALUE rubyClass) {

		owner_val = owner_arg;
		isOwned_val = isOwned_arg;

		this->self_zorba = self_zorba;

		self_ruby = Data_Wrap_Struct (rubyClass, mark_static, delete_static,
			(ZorbaWrapperOwnedImpl <Owner, T> *) this);

		if (isOwned_val)
			owner_val->addOwned (this);
	}

	virtual ~ZorbaWrapperOwnedImpl () {
	}

public:

	virtual Owner * owner () { return owner_val; }
	virtual bool isOwned () { return isOwned_val; }

	T * zorba () { return self_zorba; }
	VALUE ruby () { return self_ruby; }

	virtual void disown () {

		if (! self_zorba)
			return;

		if (isOwned_val)
			delete self_zorba;
		self_zorba = NULL;

		owner_val->removeOwned (this);
	}
};

#endif
#ifdef IMPLEMENTATION_PART

#endif
