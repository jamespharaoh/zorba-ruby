=begin

  zorba-ruby/test.rb

  Copyright 2010 James Pharaoh <james@phsys.co.uk>

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=end

require "pp"
require "zorba"

MAIN = <<EOF
	import module namespace lib = "lib";
	( lib:lala (lib:hoho (1)), lib:elem ());
EOF

LIB = <<EOF
	module namespace lib = "lib";
	declare function lib:lala ($in as xs:integer) as xs:integer {
		$in + $in + $in;
	};
	declare function lib:hoho ($in as xs:integer) as xs:integer external;
	declare function lib:elem () external;
EOF

class MyModuleUriResolverResult < Zorba::ModuleUriResolverResult
	attr_accessor :module_source
	attr_accessor :module_url
	attr_accessor :component_uris
end

class MyModuleUriResolver < Zorba::ModuleUriResolver

	def resolve_target_namespace target_namespace_uri
		result = MyModuleUriResolverResult.new
		result.component_uris = [ target_namespace_uri ]
		return result
	end

	def resolve name
		result = MyModuleUriResolverResult.new
		case name
		when "lib"
			result.error = Zorba::UriResolverResult::UR_NOERROR
			result.module_source = LIB
			result.module_url = "lib"
		else
			result.error = Zorba::UriResolverResult::UR_XQST0046
		end
		return result
	end
end

class MyModule

	def uri
		return "lib"
	end

	def external_function name
		return case name

		when "hoho"
			return MyFunction.new

		when "elem"
			return MyElemFunc.new

		else
			nil

		end
	end

end

class MyFunction < Zorba::NonePureStatelessExternalFunction

	def evaluate args, sctx, dctx
		item = $item_factory.create_integer 123
		return Zorba::SingletonItemSequence.new item
	end

end

class MyElemFunc < Zorba::NonePureStatelessExternalFunction

	def evaluate args, sctx, dctx
		name = $item_factory.create_qname "", "hello-world"
		type = $item_factory.create_qname "", "xsd:untyped"
		elem = $item_factory.create_element_node nil, name, type, false, false, nil
		name = $item_factory.create_qname "", "child"
		type = $item_factory.create_qname "", "xsd:untyped"
		elem1 = $item_factory.create_element_node elem, name, type, false, false, nil
		return Zorba::SingletonItemSequence.new elem
	end

end

$store = Zorba::StoreManager.get_store
$zorba = Zorba.get_instance $store
$data_manager = $zorba.xml_data_manager
$item_factory = $zorba.item_factory

sctx = $zorba.create_static_context
sctx.add_module_uri_resolver MyModuleUriResolver.new
sctx.register_module MyModule.new

(ARGV[0] ||= 1).to_i.times do
	xquery = $zorba.compile_query MAIN, sctx
	puts xquery.execute
	xquery.close
end

$zorba.shutdown
Zorba::StoreManager.shutdown_store $store

exit
