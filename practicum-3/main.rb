require './phonetic'

p = Phonetic.new
input = STDIN.read

input.each_line{|line|
   
     string = ""
     lineArray = input.split(" ")

     #Line is alphabetic
     if lineArray[0] == "A2P"
       lineArray.slice!(0)
       lineArray.each {|c| string += c}
       puts p.to_phonetic(string) 

     #Line is phonetic
     elsif lineArray[0] == "P2A"
       lineArray.slice!(0)
       lineArray.each {|c| string += (c + " ")} 
       puts p.from_phonetic(string)
     
     else
       puts p.auto_detect(line)
     end	

}
