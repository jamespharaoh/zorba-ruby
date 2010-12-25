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

void Version_mark (zorba::Version *);
void Version_delete (zorba::Version *);
VALUE Version_wrap (zorba::Version *);

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

void Version_mark (zorba::Version * version) {
	// do nothing
}

void Version_delete (zorba::Version * version) {
	delete version;
}

VALUE Version_wrap (zorba::Version * version) {
	return Data_Wrap_Struct (
		cVersion,
		Version_mark,
		Version_delete,
		(void *) version);
}

VALUE Version_major_version (VALUE self_ruby) {
	ZR_REAL (zorba::Version, self);
	return INT2NUM (self->getMajorVersion ());
}

VALUE Version_minor_version (VALUE self_ruby) {
	ZR_REAL (zorba::Version, self);
	return INT2NUM (self->getMajorVersion ());
}

VALUE Version_patch_version (VALUE self_ruby) {
	ZR_REAL (zorba::Version, self);
	return INT2NUM (self->getMajorVersion ());
}

VALUE Version_to_s (VALUE self_ruby) {
	ZR_REAL (zorba::Version, self);
	return rb_str_new2 (self->getVersion ().c_str ());
}

VALUE Version_version (VALUE self_ruby) {
	ZR_REAL (zorba::Version, self);
	return rb_str_new2 (self->getVersion ().c_str ());
}

#endif
