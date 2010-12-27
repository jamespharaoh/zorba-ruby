
require "zorba"

def example_1 zorba
	query = zorba.compile_query "1 + 2"
	puts query.execute
	return true
end

def example_2 zorba
	query = zorba.compile_query "1 + 2"
	iterator = query.iterator
	iterator.open
	while item = iterator.next do
		puts item.string_value
	end
	iterator.close
	return true
end

def example_3 zorba
	query = zorba.compile_query "1 div 0"
	begin
		puts query.execute
	rescue Zorba::DynamicException
		$stderr.puts $!
		return true
	end
	return false
end

def example_4 zorba
	begin
		query = zorba.compile_query "for $x in (1, 2, 3)"
	rescue Zorba::StaticException
		$stderr.puts $!
		return true
	end
	return false
end

def example_5 zorba
	puts "NOT IMPLEMENTED"
	return true

	query_string = "for $i in (1, 2, 3)"
	in_stream = create_in_from_string query_string
	begin
		query = zorba.compile_query in_stream
		puts query.execute
	catch Zorba::StaticExcpetion
		$stderr.puts $!
		return true
	catch Zorba::DynamicException
		$stderr.puts $!
	end
	return false
end

def example_6 zorba
	hints = Zorba::CompilerHints.new
	hints.opt_level = Zorba::CompilerHints::ZORBA_OPT_LEVEL_O0
	query = zorba.compile_query "1 + 1", nil, hints
	$stdout.puts query.execute
	return true
end

def example_7 zorba
	$stdout.puts Zorba.version
	return true
end

def example_8 zorba
	query = zorba.create_query
	query.filename = "foo.xq"
	query.compile "1 + 2"
	$stdout.puts query.execute
	return true
end

def example_9 zorba
	begin
		query = zorba.compile_query "1 + 1"
		query.compile "1 + 2"
	rescue Zorba::SystemException
		$stdout.puts $!
		return true
	end
	return false
end

def example_10 zorba
	query_1 = zorba.compile_query "declare variable $i external; 1 to $i"
	query_2 = query_1.clone

	iterator_1 = query_1.iterator
	dyn_context_1 = query_1.dynamic_context
	dyn_context_1.set_variable "i", zorba.item_factory.create_integer(5)

	iterator_1.open
	while item = iterator_1.next
		dynamic_context_2 = query_2.dynamic_context
		dynamic_context_2.set_variable "i", item

		iterator_2 = query_2.iterator
		iterator_2.open
		while item = iterator_2.next
			$stdout.print item.string_value
		end
		iterator_2.close
		$stdout.puts
	end
	iterator_1.close
	return true
end

def example_11 zorba
	context_with_prolog = zorba.create_static_context
	prolog = [
		"declare variable $x := 2;\n",
		"declare function local:f ($n) { $x + $n };\n",
	].join ""
	hints = Zorba::CompilerHints.new
	context_with_prolog.load_prolog prolog, hints

	query = zorba.compile_query "local:f ($x + 1)", context_with_prolog
	$stdout.puts query.execute
	return true
end

def example_12 zorba
	query = zorba.compile_query "<a><b attr='1'/><b attr='2'/></a>"

	iterator = query.iterator
	iterator.open

	while item = iterator.next
		child_iter = item.children

		child_iter.open
		while child = child_iter.next

			$stdout.puts "node name #{child.node_name}"
			attr_iter = child.attributes

			attr_iter.open

			while attr = attr_iter.next
				$stdout.puts "  attribute value #{attr.string_value}"
			end
			attr_iter.close
		end
		child_iter.close
	end

	iterator.close;

	return true
end

def example_13 zorba
	query = zorba.create_query
	query.timeout = 1

	begin
		query.compile "while (fn:true()) {()};"
		$stdout.puts query.execute
	rescue Zorba::SystemException
		$stdout.puts "query interrupted after 1 second"
		return true
	end

	return false
end

def example_14 zorba
	str = "a"
	str += "b";
	str += "c";
	return str == "abc"
end

begin

	store = Zorba::StoreManager.get_store
	zorba = Zorba::get_instance store

	(1..13).each do |i|
		puts "executing example #{i}"
		send "example_#{i}", zorba or exit 1
	end

ensure
	zorba.shutdown if zorba
	Zorba::StoreManager.shutdown_store store if store
end

exit 0
