#logger.rb
#A simple class to store logged food items that exist 
#in the food database. 
#Author - Justin Peterson

require 'date'
require './database.rb'
require 'csv'

#Creates an item based on the log text file
class LogItem
	attr_accessor :date
	attr_accessor :name

	#Creates a date object and name string to represent 
	#each logged food. 
	def initialize(date,name)
		@date = date
		@name = name
	end
end
	
#Loggs food items and checks them against the database.
class Log
	attr_accessor :log
	#Creates a hashmap data structure for each LogItem object
	def initialize
		@log = Hash.new
	end

	#adds CSV data from the log file into the log hashmap
	def parseLog(fileName)
		CSV.foreach(fileName) do |line|
			dateArray = line[0].split("-")
			date = Date.new(dateArray[0].to_i,dateArray[1].to_i,dateArray[2].to_i)
			foodLog = LogItem.new(date,line[1])
			@log[foodLog] = date
		end
			
	end

	#logs an item with today's date and adds it to the logfile.
	def logItem(name,database,logFile)

		writeString = ""
		writeString += Date.today.to_s
		writeString += ","
		writeString += name
		writeString += "\n"
		if database.menu.has_key?(name)
			File.open(logFile,'a'){|f|f.write(writeString)} 
			puts "The item has been logged!"		
		else
			puts "The item you're trying to log doesn't exist in the database!"
		end
		 
	end
	#logs an item with a timestamp based on the date object
	# parameter and adds it to the logfile.
	def logItemWithDate(name,date,database,logFile)

		writeString = ""
		writeString += date.to_s
		writeString += ","
		writeString += name
		writeString += "\n"
		if database.menu.has_key?(name)
			File.open(logFile,'a'){|f|f.write(writeString)} 
			puts "The item has been logged!"		
		else
			puts "The item you're trying to log doesn't exist in the database!"
		end
		 
	end
	#prints every item in the log, sorted by ascending date. 
	def showAll
		#stores the logs to print by each year
		logHash = Hash.new([])
		dateString = ""
		sortedArray = @log.sort_by {|logObject,date| date}
		sortedArray.each do |subArray|
			dateString += subArray[0].date.to_s
			dateString += ","
			dateString += subArray[0].name
			dateString += "\n"
			
		end
		puts dateString
	end
		
end
 
