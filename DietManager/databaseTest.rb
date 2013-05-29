#databaseTest.rb is a simple test case suite for the DietManager project.
#Author: Justin Peterson

require './database'
require 'test/unit'

class OutStream
	def print(string)
		stringArray = string.split(" ")
		return stringArray
	end	
end

class DatabaseTest < Test::Unit::TestCase

	# Create a new database for the next test

	def setup
		@myDatabase = FoodDB.new
		@myDatabase.popDatabase("TestDB.txt")
		@myOutStream = OutStream.new
  	end

	# Is the database correctly populated?

	def test_for_populated_database
		assert(@myDatabase.menu.keys[0] == "Orange","Database was not correctly populated.")
		assert(@myDatabase.menu.keys[4] == "PB&J Sandwich","Database was not correctly populated.")
		assert(@myDatabase.menu.keys[3] == "Jelly","Database was not correctly populated.")
	
	end
	#test the print(name) method on basic foods
	def test_for_correct_BasicFood_search
		result = @myDatabase.print("Orange",@myOutStream)
		assert(result.chomp! == "Orange 67","Database lookup failed")
		result = @myDatabase.print("Jelly",@myOutStream)
		assert(result.chomp! == "Jelly 155","Database lookup failed")
		result = @myDatabase.print("Bread",@myOutStream)
		assert(result.chomp! == "Bread 78","Database lookup failed")
	end
	#tests the addition of a new food into the database
	def test_for_new_food
		@myDatabase.new_food("TestFood",100,"TestDB.txt")
		@myDatabase.new_food("TestFood2",150,"TestDB.txt")
		@myDatabase.save("TestDB.txt")
		assert(@myDatabase.menu.keys.include?("TestFood"),"new food not correctly added into database!")
		assert(@myDatabase.menu.keys.include?("TestFood2"),"new food not correctly added into database!")
	end
	#tests for the addition of a new recipe into the database
	def test_for_new_recipe
		ingredients = ["Peanut Butter","Jelly"]
		@myDatabase.new_recipe("PBJELLY",ingredients,"TestDB.txt")
		#assert(@myDatabase.menu.keys.include?("PBJELLY"),"new recipe not correctly added into database")
	end
	
end
