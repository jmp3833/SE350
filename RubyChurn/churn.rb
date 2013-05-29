#churn.rb iterates over an SVN directory and generates a histogram
#of the most frequently updated low level directories.

#Author: Justin Peterson

#source folder
resultString = `svn list https://sdcc.svn.sourceforge.net/svnroot/sdcc/trunk/sdcc/src/`

resultsArray = resultString.split("\n")
subsystems = []
iterator = 0

#creates an array of subdirectories
resultsArray.each do |line|
	if line.end_with?("/")
		line.delete!("/")
		subsystems[iterator] = line
		iterator+=1
	end
end

#creates the list of revisions
occurrenceArray = []
iterator = 0
dateString = ARGV[0]

subsystems.each do |sys|
	result = `svn log --revision 'HEAD:{#{dateString}}' https://sdcc.svn.sourceforge.net/svnroot/sdcc/trunk/sdcc/src/#{sys}`
	rArray = result.split("------------------------------------------------------------------------")
	occurrenceArray[iterator] = rArray.size
	iterator+=1
	
end

subHash = Hash.new
iterator = 0

#adds the array elements into a hashmap
subsystems.each do |i|
	subHash[i] = occurrenceArray[iterator]
	iterator+=1
end

sortedArray = subHash.sort_by{|key, value| value}

#sorts the hashmap into a two dimensional array
longest = sortedArray.inject do |memo,word|
   memo.length > word.length ? memo : word
end

longestLength = longest[1];

#generates a histogram on the data.
sortedArray.each{|directory| printf("%-#{longestLength/15}.#{longestLength/15}s #{'*' * (directory[1] / 10 + 1) } (#{directory[1]}) \n",directory[0]) }

