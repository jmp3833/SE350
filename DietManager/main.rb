#main.rb
#Handles the command line interface for the Diet Manager.

#Allows the user to create and remove FoodItems,Recipies,
#and logs. 

#Author: Justin Peterson
require "./database.rb"
require "./logger.rb"
require "csv"
require "date"

logger = Log.new
database = FoodDB.new
database.popDatabase("FoodDB.txt")
logger.parseLog("DietLog.txt")


puts("Hello, and welcome to the Ruby Diet Manager!\n")
puts("Please type the name of your desired operation:\n(quit,print all,show all,print,find,new food,new recipe,log):")

selection = gets.chomp.downcase
QUIT = "quit"
PRINT_ALL = "print all"
PRINT = "print"
FIND = "find"
NEW_FOOD = "new food"
NEW_RECIPE = "new recipe"
LOG = "log"
SHOW_ALL = "show all"

#Preforms various method calls based on user's input. 
while selection!=(QUIT) do
	if selection == (PRINT_ALL)
		database.printMenu($stdout) 
	
	elsif selection == (PRINT)
		puts("What is the name of the item you would like to print?")
		itemName = gets
		database.print(itemName,$stdout)

	elsif selection == (FIND)
		puts("What prefix would you like to search using?")
		itemName = gets
		database.find(itemName,$stdout)
	elsif selection == (NEW_FOOD)
		puts("What is the name of the food you would like to add?\n(you must save and quit to add this item to the database!!)")
		foodName = gets.chomp
		puts("How many calories does this food have?")
		numCalories = gets.chomp
		database.new_food(foodName,numCalories,"FoodDB.txt")
	elsif selection == (NEW_RECIPE)
		puts("What is the name of the recipe you would like to add?\n(you must save and quit to add this item to the database!!)")
		recipeName = gets.chomp
		puts("What ingeridents go in your recipe? (please separate each item by a comma)")
		ingredientsString = gets.chomp!
		database.new_recipe(recipeName,ingredientsString.split(","),"FoodDB.txt")
	elsif selection == (LOG)
		puts("What is the name of the item you would like to log?")
		itemName = gets.chomp
		puts("Would you like this item logged for today?(y/n)")
		selection = gets.chomp.downcase
		if selection == "y"
			logger.logItem(itemName,database,"DietLog.txt")
		elsif selection == "n"
			puts("please enter the date you would like to log in year,month,day format,each element separated by a comma.")
			inputArray = gets.chomp.split(",")
			logDate = Date.new(inputArray[0].to_i,inputArray[1].to_i,inputArray[2].to_i)
			logger.logItemWithDate(itemName,logDate,database,"DietLog.txt")
		
		else
			puts "you have input an incorrect command"
		end
	elsif selection == (SHOW_ALL)
		logger.showAll
	
	else
		puts("This does not match a valid command, please try again.\n")
	end
	

	puts("Please type the name of your desired operation:\n(quit,print all,show all,print,find,new food,new recipe,log):")
	selection = gets.chomp.downcase
end

database.quit("FoodDB.txt")
puts("Thank you for using the Ruby Diet Manager!")


