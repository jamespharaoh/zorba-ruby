/*
 * zorba-ruby/parts/compiler-hints.h
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

class CompilerHints {

	Zorba_CompilerHints_t self_zorba;

	VALUE shadow_ruby;

	VALUE caster_ruby;

	CompilerHints (VALUE compilerHints_ruby);

	~CompilerHints () { }

public:

	Zorba_CompilerHints_t & zorba () { return self_zorba; }

	VALUE shadow () { return shadow_ruby; }

	VALUE caster () { return caster_ruby; }

	static void mark (CompilerHints *);

	static void del (CompilerHints *);

	static VALUE initialize (VALUE self);
	static VALUE opt_level_eq (VALUE self, VALUE value);
};

#endif
#ifdef RUBY_PART

ZR_CLASS_CLASS (Zorba, CompilerHints, rb_cObject)

ZR_CLASS_CONST (CompilerHints, ZORBA_OPT_LEVEL_O0, INT2NUM (ZORBA_OPT_LEVEL_O0))
ZR_CLASS_CONST (CompilerHints, ZORBA_OPT_LEVEL_O1, INT2NUM (ZORBA_OPT_LEVEL_O1))

ZR_CLASS_METHOD (CompilerHints, initialize, 0)
ZR_CLASS_METHOD (CompilerHints, opt_level_eq, 1)

#endif
#ifdef IMPLEMENTATION_PART

CompilerHints::CompilerHints (VALUE compilerHints_ruby) {

	caster_ruby = compilerHints_ruby;

	shadow_ruby = Data_Wrap_Struct (
		cCompilerHints,
		CompilerHints::mark,
		CompilerHints::del,
		this);
}

VALUE CompilerHints::initialize (VALUE self_ruby) {

	CompilerHints * shadow = new CompilerHints (self_ruby);

	rb_iv_set (self_ruby, "@shadow", shadow->shadow ());

	return self_ruby;
}

VALUE CompilerHints::opt_level_eq (VALUE self_ruby, VALUE value_ruby) {

	VALUE shadow_ruby = rb_iv_get (self_ruby, "@shadow");

	ZR_SHADOW (CompilerHints, self);

	self->zorba ().opt_level = (Zorba_opt_level_t) NUM2INT (value_ruby);

	return Qnil;
}

void CompilerHints::del (CompilerHints * compilerHints) {
	delete compilerHints;
}

void CompilerHints::mark (CompilerHints * compilerHints) {
}

#endif
