/*
 * zorba-ruby/parts/version.h
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

class Version {

	const zorba::Version * self_zorba;
	VALUE self_ruby;

	~Version () { }

public:

	Version (const zorba::Version *);

	const zorba::Version * zorba () { return self_zorba; }
	VALUE ruby () { return self_ruby; }

	static VALUE major_version (VALUE self_ruby);
	static VALUE minor_version (VALUE self_ruby);
	static VALUE patch_version (VALUE self_ruby);
	static VALUE to_s (VALUE self_ruby);
	static VALUE version (VALUE self_ruby);

	static void mark (Version *);
	static void del (Version *);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, Version, rb_cObject)

ZR_CLASS_METHOD (Version, major_version, 0)
ZR_CLASS_METHOD (Version, minor_version, 0)
ZR_CLASS_METHOD (Version, patch_version, 0)
ZR_CLASS_METHOD (Version, to_s, 0)
ZR_CLASS_METHOD (Version, version, 0)

#endif
#ifdef IMPLEMENTATION_PART

Version::Version (const zorba::Version * version_zorba) {

	self_zorba = version_zorba;

	self_ruby = Data_Wrap_Struct (
		cVersion,
		Version::mark,
		Version::del,
		this);
}

void Version::mark (Version * version) {
}

void Version::del (Version * version) {
	delete version;
}

VALUE Version::major_version (VALUE self_ruby) {
	ZR_REAL (zorba::Version, self);
	return INT2NUM (self->getMajorVersion ());
}

VALUE Version::minor_version (VALUE self_ruby) {
	ZR_REAL (zorba::Version, self);
	return INT2NUM (self->getMajorVersion ());
}

VALUE Version::patch_version (VALUE self_ruby) {
	ZR_REAL (zorba::Version, self);
	return INT2NUM (self->getMajorVersion ());
}

VALUE Version::to_s (VALUE self_ruby) {
	ZR_REAL (zorba::Version, self);
	return rb_str_new2 (self->getVersion ().c_str ());
}

VALUE Version::version (VALUE self_ruby) {
	ZR_REAL (zorba::Version, self);
	return rb_str_new2 (self->getVersion ().c_str ());
}

#endif
