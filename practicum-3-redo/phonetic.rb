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
    phonString = ""
    line.each_char do |char|
      if char.match(/^[[:alpha:]]$/)
        phonString += LETTERS[char]
      end
    end
    puts phonString	
  end


  # Translate a sequence of phonetic alphabet code words 
  # to their alphabetic equivalent
  def from_phonetic(line)

  	 ### YOUR CODE HERE ###

  end

  # Auto-detect if the line is phonetic or not. 
  # Does this by checking if the first word is in the phonetic alphabet
  # Delegates to from_phonetic or to_phonetic
  def auto_detect(line)

      ### YOUR CODE HERE ###

  end
end

