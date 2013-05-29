# Movie Manager 
# 
# Manages a collection of movie objects. 
# 
# Name: Justin Peterson
#
# Change Log - Identify the modifications made to the orginal code
# (1) - added attr_accessors to grab attributes 
# (2) - changed upcase to name.upcase in delete function
# (3) - changed sortbyname to sort by the keys instead of the entire hash. 
# (4) - changed sortByRating to sort in decending order instead of ascending. 

class MovieList
  attr_accessor :movies
  attr_accessor :numberOfMovies
  def initialize
    @movies = Hash.new
    @numberOfMovies = 0    
  end
  
  def size
    @numberOfMovies
   end
  
  def add(movieToAdd )
    @movies.store( movieToAdd.name, movieToAdd)
    @numberOfMovies += 1  
  end
  
  def delete(movieToDelete)    
    @movies.delete(movieToDelete.name.upcase)
  end
  
  def getMovie(movieToFind)    
    @movies.fetch(movieToFind.upcase, nil) 
  end
  
  def sortByName	
     @movies.keys.sort   
  end
  
  def sortByRating
    list = @movies.values.sort_by { |x| -x.rating }
  end    
    
 end

# Movie Class - Models a movie entry - maintains movie title as an uppercase string,
#                     rating (1-10) and text review.
#
# Change Log - Identify the modifications made to the orginal code
# (1) - changed upcase! to upcase (generating a new variable, no ! is needed)
# (2) - created attr_reader and writer for name attribute
# (3) - Created logic to set default rating and allow for no rating
# (4) - Changed || to && when checking range of rating values  

class Movie
    attr_reader :name
    attr_writer :name
    attr_reader :rating
    attr_reader :review
    attr_writer :review
      
    def initialize( aName, aRating=5, aReview="No Review Entered" )
        @name=aName.upcase 
	self.rating=aRating
	@review=aReview
    end

    def rating=(value)
	if value <= 10 && value >= 1 
          @rating = value
        else
          @rating = 5
        end
  
     end
end
