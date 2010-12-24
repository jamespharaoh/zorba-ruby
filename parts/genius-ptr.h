/*
 * zorba-ruby/parts/genius-ptr.h
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

template <class T, VALUE & klass>
class GeniusPtr {

	SmartPtr <T> mySmart;
	T * myStupid;
	bool myOwned;

public:

	GeniusPtr (SmartPtr <T> & newSmart) :
		mySmart (newSmart),
		myStupid (NULL),
		myOwned (false) {
	}

	GeniusPtr (T * newStupid, bool newOwned) :
		mySmart (NULL),
		myStupid (newStupid),
		myOwned (newOwned) {
	}

	GeniusPtr (GeniusPtr & genius) :
		mySmart (genius.mySmart),
		myStupid (genius.myStupid),
		myOwned (false) {
	}

	T * get () const {
		return myStupid ? myStupid : mySmart.get ();
	}

	T * operator -> () const {
		return get ();
	}

	T & operator * () const {
		return * get ();
	}

	operator T * () const {
		return * get ();
	}

	operator bool () const {
		return myStupid || mySmart.get () ? true : false;
	}

	SmartPtr <T> & smart () {
		return mySmart;
	}

	static VALUE wrap (T * value, bool owned) {
		GeniusPtr * genius = new GeniusPtr (value, owned);
		return Data_Wrap_Struct (klass, mark, del, genius);
	}

	static VALUE wrap (SmartPtr <T> value) {
		GeniusPtr * genius = new GeniusPtr (value);
		return Data_Wrap_Struct (klass, mark, del, genius);
	}

	static void del (GeniusPtr * genius) {
		if (genius->myStupid && genius->myOwned)
			delete genius->myStupid;
	}

	static void mark (GeniusPtr * genius) {
		// TODO something clever here
	}
};

template <class T, VALUE & klass>
class DumbPtr {

	T * myDumb;
	bool myOwned;

public:

	DumbPtr (T * newDumb, bool newOwned) :
		myDumb (newDumb),
		myOwned (newOwned) {
	}

	static VALUE wrap (T * value, bool owned) {
		DumbPtr * dumb = new DumbPtr (value, owned);
		return Data_Wrap_Struct (klass, mark, del, dumb);
	}

	static void del (DumbPtr * dumb) {
		if (dumb->myDumb && dumb->myOwned)
			delete dumb->myDumb;
	}

	static void mark (DumbPtr * dumb) {
		// TODO something clever here
	}
};

#endif
#ifdef IMPLEMENTATION_PART

#endif
