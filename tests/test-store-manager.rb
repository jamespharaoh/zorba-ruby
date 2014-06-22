require "test/unit"
require "zorba"

class TestStoreManager < Test::Unit::TestCase

	def test_manual_shutdown
		store = Zorba::StoreManager.get_store
		Zorba::StoreManager.shutdown_store store
	end

	def test_automatic_shutdown
		store = Zorba::StoreManager.get_store
		store = nil
		GC.start
	end

end
