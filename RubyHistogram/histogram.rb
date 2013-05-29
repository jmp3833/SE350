#Histogram.rb

#A simple histogram showing the rate at 
#which letters occur in a text file.

#Justin Peterson SE 350
#Sample ruby scripting exercise
#histogram.rb


#create a new hash map
bag = Hash.new(0)
lineArray = []
occurrenceArray = []

STDIN.each do|newLine|	
	#Preform string operations
	newLine.chomp!
	newLine.downcase!
	newLine.gsub!(/[^a-z ]/,"")
	newLine.strip!
	lineArray = newLine.split(/ +/)

	
	#Add elements to the hash map	
	lineArray.each{|i| bag[i] += 1 }

	#Creates an array to store occurances based on command line arguments.
	if ARGV[0] == nil

		occurrenceArray = bag.select{|key,value| value >= 2}.to_a
	else
		
		occurrenceArray = bag.select{|key,value| value >= ARGV[0].to_i}.to_a
	end
		
	occurrenceArray.sort! do |x, y|
		if x[1] == y[1]
			comp = x[0] <=> y[0]

		else
			comp = y[1] <=> x[1]

		end
		comp
	end

end

longest = lineArray.inject do |memo,word|
   memo.length > word.length ? memo : word

end
longestLength = longest.length;

occurrenceArray.each{|pair| printf("%-#{longestLength}.#{longestLength}s #{'*' * pair[1]} \n", pair[0]) }

