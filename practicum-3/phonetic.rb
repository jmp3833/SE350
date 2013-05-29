# Convert to/from phonetic alphabet
# SOLUTION

class Phonetic

  LETTERS = Hash[
             'A', 'ALPHA',
             'B', 'BRAVO',
             'C', 'CHARLIE',
             'D', 'DELTA',
             'E', 'ECHO',
             'F', 'FOXTROT',
             'G', 'GOLF',
             'H', 'HOTEL',
             'I', 'INDIA',
             'J', 'JULIET',
             'K', 'KILO',
             'L', 'LIMA',
             'M', 'MIKE',
             'N', 'NOVEMBER',
             'O', 'OSCAR',
             'P', 'PAPA',
             'Q', 'QUEBEC',
             'R', 'ROMEO',
             'S', 'SIERRA',
             'T', 'TANGO',
             'U', 'UNIFORM',
             'V', 'VICTOR',
             'W', 'WHISKEY',
             'X', 'XRAY',
             'Y', 'YANKEE',
             'Z', 'ZULU'
             ]

  # Translate a line to its phonetic alphabet equivalent
  def to_phonetic(line)
   
   string = ""
   lineArray = line.split(" ")
   iterator = 0
   
   #Iterate over each word to be converted
   lineArray.each do |word|
     #Format each word string
     word.gsub!(/\W+/, '')
     word.upcase!
     #Convert the word to its phonetic equivalent
     while iterator < word.length   
       string += LETTERS[word[iterator]]
       string += " "
       iterator+=1
     end
   end
   #remove the end space character
   string = string[0..string.length-2]
   return string
  end

  # Translate a sequence of phonetic alphabet code words 
  # to their alphabetic equivalent
  def from_phonetic(line)

    lineArray = line.split(" ")
    string = ""
    #convert the value to its alphabetic equivalenr
    lineArray.each do |word|
      if LETTERS.has_value?(word)
        string += (LETTERS.key(word)) 
      end
    end
    return string 
  end

  # Auto-detect if the line is phonetic or not. 
  # Does this by checking if the first word is in the phonetic alphabet
  # Delegates to from_phonetic or to_phonetic
  def auto_detect(line)

      lineArray = line.split(" ")

      if(LETTERS.has_value?(lineArray[0]))
        return from_phonetic(line)
      else
	return to_phonetic(line)
      end
  end
end

 

