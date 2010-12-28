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
class ZorbwWrapperOwner;
class ZorbaWrapperOwned;
template <class Wrapper, class Wrapped> class ZorbaWrapperOwnedImpl;

#endif
#ifdef INTERFACE_PART

class ZorbaWrapper {

protected:

	ZorbaWrapper () { }

	virtual ~ZorbaWrapper () { }

	virtual void disownOwned () { }

public:

	virtual string toString () = 0;

	virtual void disown () { }
};

class ZorbaWrapperOwner :
	public virtual ZorbaWrapper {

protected:

	set <ZorbaWrapperOwned *> owned;

	virtual void disownOwned ();

public:

	void addOwned (ZorbaWrapperOwned * wrapper) {
		owned.insert (wrapper);
	}

	void removeOwned (ZorbaWrapperOwned * wrapper) {
		owned.erase (wrapper);
	}
};

class ZorbaWrapperOwned :
	public virtual ZorbaWrapper {

public:

	virtual ZorbaWrapperOwner * owner () = 0;
	virtual bool isOwned () = 0;
};

template <class Wrapper, class Wrapped>
class ZorbaWrapperOwnedImpl : public virtual ZorbaWrapperOwned, public virtual ZorbaWrapper {

	static void mark_static (Wrapper * self) {
	}

	static void delete_static (Wrapper * self) {
		try {

			self->disown ();

			delete (ZorbaWrapperOwnedImpl <Wrapper, Wrapped> *) self;
		}
		catch (zorba::ZorbaException & e) { zr_raise (e); }
		catch (RubyException & e) { zr_raise (e); }
	}

protected:

	ZorbaWrapperOwner * owner_val;
	bool isOwned_val;

	Wrapped * self_zorba;
	VALUE self_ruby;

	ZorbaWrapperOwnedImpl (ZorbaWrapperOwner * owner_arg, bool isOwned_arg, Wrapped * self_zorba, VALUE rubyClass) {

		owner_val = owner_arg;
		isOwned_val = isOwned_arg;

		this->self_zorba = self_zorba;

		self_ruby = Data_Wrap_Struct (rubyClass, mark_static, delete_static, (Wrapper *) this);

		if (isOwned_val)
			owner_val->addOwned (this);
	}

	virtual ~ZorbaWrapperOwnedImpl () {
	}

public:

	virtual ZorbaWrapperOwner * owner () { return owner_val; }
	virtual bool isOwned () { return isOwned_val; }

	Wrapped * zorba () { return self_zorba; }
	VALUE ruby () { return self_ruby; }

	virtual void disown () {

		if (! self_zorba)
			return;

		disownOwned ();

		if (isOwned_val)
			delete self_zorba;
		self_zorba = NULL;

		owner_val->removeOwned (this);
	}

	static Wrapper * unwrap (VALUE self_ruby) {
		Wrapper * self;
		Data_Get_Struct (self_ruby, Wrapper, self);
		return self;
	}
};

template <class Wrapper, class Wrapped>
class ZorbaWrapperShadowImpl :
	public virtual ZorbaWrapper {

	static void mark_static (Wrapper * self) {
	}

	static void delete_static (Wrapper * self) {
		try {

			delete (ZorbaWrapperShadowImpl <Wrapper, Wrapped> *) self;

		}
		catch (zorba::ZorbaException & e) { zr_raise (e); }
		catch (RubyException & e) { zr_raise (e); }
	}

protected:

	Wrapped * self_zorba;

	VALUE caster_ruby;
	VALUE shadow_ruby;

	ZorbaWrapperShadowImpl (VALUE caster_ruby_arg, Wrapped * self_zorba, VALUE rubyClass) {

		this->self_zorba = self_zorba;

		caster_ruby = caster_ruby_arg;

		shadow_ruby = Data_Wrap_Struct (rubyClass, mark_static, delete_static, (Wrapper *) this);
	}

	virtual ~ZorbaWrapperShadowImpl () {
	}

public:

	VALUE shadow () { return shadow_ruby; }
	VALUE caster () { return caster_ruby; }
};

#endif
#ifdef IMPLEMENTATION_PART

void ZorbaWrapperOwner::disownOwned () {
	set <ZorbaWrapperOwned *> owned (this->owned);
	for (set <ZorbaWrapperOwned *>::iterator it = owned.begin (); it != owned.end (); it++)
		(* it)->disown ();
}

#endif
