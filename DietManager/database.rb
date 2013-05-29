#database.rb
#parses a database text file and produces a database of simple 
#foods and recipe objects. 

#Author: Justin Peterson

require "csv"

#Creates basic food object, with a name and number of calories
class BasicFood
	attr_accessor :numCalories
	attr_accessor :name
	#Number of calories, and the string name of the basic food
	def initialize(numCalories,name) 
		@numCalories = numCalories
		@name = name
	end
end

#creates a recipe, composed of BasicFood objects
class Recipe
	attr_accessor :name
	attr_accessor :foods
	attr_accessor :totalCalories
	#array of food objects in the recipe, name of the recipe, and
	#it's total number of calories. 
	def initialize(foods,name) 
		@foods = foods
		@name = name
		@totalCalories = 0
 	        foods.keys.each{|food| @totalCalories += (food.numCalories.to_i * foods[food])}
	end
end

#Generates a database taken from the foodDB text file
class FoodDB
	attr_accessor :menu
	#Creates a database which stores simple food objects and recipes. 
	def initialize
		#Menu which stores all foods and recipes
		@menu = Hash.new
	end
	#simple method to format the printing of a BasicFood object
	def printBasicFood(basicFood,outStream)
		printString = ""
		printString += basicFood.name
		printString += " "
		printString += basicFood.numCalories.to_s
		printString += "\n"
		outStream.print printString
		return printString
	end
	#print method for a recipe object
	def printRecipe(recipe,outStream)
        	printString = ""
		printString += recipe.name
		printString +=  " "
	        printString +=  recipe.totalCalories.to_s
		printString +=  "\n"

		recipe.foods.keys.each do |food|
			multipleCalories = recipe.foods[food].to_i * food.numCalories.to_i
			if recipe.foods[food] > 1
			printString +=  "   "
			printString += food.name
			printString += " ("
			printString += recipe.foods[food].to_s
			printString +=  ") "
			printString +=  multipleCalories.to_s
			printString += "\n"
			else
			printString += 	"   "
			printString += food.name
			printString += " "
			printString += food.numCalories.to_s
			printString += "\n"
			end
			
		end
	 	outStream.print printString
		return printString
	end
	
	#Populate the database by parsing the food database text file
	def popDatabase(textFile)
		CSV.foreach(textFile) do |line|
			if line[1] == "b"
				@food = BasicFood.new(line[2],line[0]) 
				@menu[line[0]] = @food
			elsif line[1] == "r"
				foodHash = Hash.new(0)
				line.each do |i|
					if @menu.has_key?(i)
						if @menu[i].is_a?(BasicFood)
							foodHash[@menu[i]] +=1
						end
					end
				end
						 
				@recipe = Recipe.new(foodHash,line[0])
				@menu[line[0]] = @recipe
			else 
				puts("Incorrect file format")
			end
		end
	end

	#formats and prints the entire menu database
	def printMenu(outStream)
		@menu.keys.each do |i|
			if @menu[i].is_a?(BasicFood)
				printBasicFood(@menu[i],outStream) 
			else
				printRecipe(@menu[i],outStream)
			end
		end
	end

	#prints a simple food or recipe by its name
	def print(name,outStream)
		nameString = name.chomp
		if @menu[nameString].is_a?(BasicFood)
			printBasicFood(@menu[nameString],outStream)
		elsif @menu[nameString].is_a?(Recipe)
			printRecipe(@menu[nameString],outStream)
		else
			puts("This name does not exist in the database!")
		end
	end
	#lists foods that contain a given prefix
	def find(prefix,outStream)
		preFormat = prefix.chomp
		@menu.keys.each do |i|
			if i.include?(preFormat)
				print(i,outStream)
			end
		end
	end
	#adds a new food to the database. 
	def new_food(name,calories,databaseFile)
		
		#Create a string to write to the text file
		writeString = ""
		writeString += name
		writeString += ",b,"
		writeString += calories.to_s
		writeString += "\n"
		if File.exist?(databaseFile)
			File.open(databaseFile).each_line do |line|
				if line.split(",")[0] == writeString.split(",")[0]
					puts "This food is already in the database!"
					return
				end
			end
			File.open(databaseFile,'a'){|f|f.write(writeString)}
			puts "The new item has been added!"
		else
			puts "The database file does not exist!"
		end

	end
	#adds anew recipe to the database. returns an error
	#if a food doesnt exist in the database.
	#recipeName - name of the recipe
	#namesArray - the names of simple foods in the database
	def new_recipe(recipeName,namesArray,databaseFile)
		writeString = ""
		writeString += recipeName
		writeString += ",r,"
		namesArray.each do |name|
			if(!(@menu.has_key?(name)))
				puts "Lacking a food item nessecary for the recipe!"
				return
			end
			writeString += name
			writeString += ","
		end
		writeString.slice!(writeString.length-1)
		writeString += "\n"
		if File.exist?(databaseFile)
			File.open(databaseFile).each_line do |line|
				if line.split(",")[0] == writeString.split(",")[0]
					puts "This recipe is already in the database!"
					return
				end
			end
			File.open(databaseFile,'a'){|f|f.write(writeString)}
			puts "The new recipe has been added!"
		else
			puts "The database file does not exist!"
		end
			
	end
	#Asks the user if they would like to save the 
	#database changes, then quits the program
	def quit(databaseFile)
		puts("Would you like to save your changes? (y/n)")
		selection = gets.chomp.downcase
		if selection == "y"
			save(databaseFile)
		elsif selection == "n"
			lines = File.readlines(databaseFile)
			File.open(databaseFile, "w") do |f|
  				lines.each { |line| f.puts(line) unless !(@menu.has_key?(line.split(",")[0])) }
			end 

		else
			puts "You have input an incorrect command"
		end
	end
	
	#Writes all changes to the database file to the menu hash.
	def save(databaseFile)
		popDatabase(databaseFile)
	end

end
