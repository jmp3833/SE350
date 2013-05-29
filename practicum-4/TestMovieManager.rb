require './MovieManager.rb'
require 'test/unit'

class MovieManagerTest < Test::Unit::TestCase
  
  def setup
    @test = MovieList.new
    @testMovie1 = "IRONMAN"
    @testRating1 = 10
    @testMovie2 = "AIRPLANE"
    @testRating2 = 2
    @testMovieObject1 = Movie.new(@testMovie1,@testRating1)
    @testMovieObject2 = Movie.new(@testMovie2,@testRating2)
    @test.movies[@testMovie1] = @testMovieObject1
    @test.movies[@testMovie2] = @testMovieObject2
  end
  
  def test_smokeTest
    testList = MovieList.new
    assert_not_nil( testList, "Should be able to create a MovieList collection")
  end

  #Tests if an added movie can be accessed in the
  #testList based on its name.   
  def test_for_maintained_collection
    assert_equal( @test.movies[@testMovie1],@testMovieObject1,"Manager does not keep proper collection based on movie name")
    assert_equal( @test.movies[@testMovie2],@testMovieObject2,"Manager does not keep proper collection based on movie name")
  end

  #Checks that a movie object contains its nessescary attributes.
  def test_for_correct_movie_attributes
    testReview = "No Review Entered"
    assert_equal(@testMovieObject1.name,@testMovie1,"Name of movie is not correctly populated.")
    assert_equal(@testMovieObject1.rating,@testRating1,"Rating of movie is not correctly populated.")
    
    assert_equal(@testMovieObject1.review,testReview,"Review of movie is not correctly populated.")  
  end
  
  #Checks if a movie entry can be created with any case string.
  def test_movie_list_entry
    testMovieObject = Movie.new("Movie",1)
    @test.movies["mOvIe"] = testMovieObject
    @test.movies["movie"] = testMovieObject
    @test.movies["MOVIE"] = testMovieObject

    assert_equal(@test.movies["mOvIe"],testMovieObject,"Cannot create a movie entry with a mixed case key.")
    assert_equal(@test.movies["movie"],testMovieObject,"Cannot create a movie entry with a lowercase key.")
    assert_equal(@test.movies["MOVIE"],testMovieObject,"Cannot create a movie entry with a uppercase key.")
  end
  
  #Checks that a movie name is stored as an all capital string. 
  def test_movie_name_entry
    testUpper = "IRONMAN"
    testLower = "ironman"
    testMixed = "IrOnMaN"
    testUpperObject = Movie.new(testUpper,1)
    testLowerObject = Movie.new(testLower,1)
    testMixedObject = Movie.new(testMixed,1)

    assert_equal(testUpperObject.name,"IRONMAN","Cannot create movie with uppercase name")
    assert_equal(testLowerObject.name,"IRONMAN","Cannot create movie with lowercase name")
    assert_equal(testMixedObject.name,"IRONMAN","Cannot create movie with mixed case name")
  end

  #Validates if a rating is properly checked for its default boundries"
  def test_for_valid_rating 
    titleString = "IRONMAN"
    testUpperBound = Movie.new(titleString,12212)
    testLowerBound = Movie.new(titleString,0)
    testInRangeBound = Movie.new(titleString,3)
    testNoInput = Movie.new(titleString)

    assert_equal(testUpperBound.rating,5,"Rating does not default on invalid input")
    assert_equal(testLowerBound.rating,5,"Rating does not default on invalid input")
    assert_equal(testNoInput.rating,5,"Rating does not default on no input")
    assert_equal(testInRangeBound.rating,3,"Valid rating is not accepted")

  end
  #Checks that a review can be given to a movie object.
  def test_for_valid_review
    testObject1 = Movie.new(@testMovie1,2,"Hello World")
    testObject2 = Movie.new(@testMovie1)
   
    assert_equal(testObject1.review,"Hello World","Cannot provide a movie with a rating string")
    assert_equal(testObject2.review,"No Review Entered","Cannot provide a movie with no review")
  end
  #checks to see if a movie can be properly deleted from the list.
  def test_for_movie_deletion
    testList = MovieList.new
    testMovie = Movie.new("MOVIE")
    testList.movies["MOVIE"] = testMovie
    
    assert_equal( testList.delete(testMovie),testMovie,"Movie not correctly deleted")    
    assert_equal( testList.delete(Movie.new("IRONMEN")),nil,"Trying to delete a non existent movie!")   
  end

  #tests that a collection of movie names can be sorted in alphabetical order. 
  def test_for_alphabetic_sort
    list = MovieList.new
    ironman = Movie.new("IRONMAN")
    movie = Movie.new("MOVIE")
    list.add(movie)
    list.add(ironman)
    sortedArray = list.sortByName
    assert_equal(sortedArray[0],"IRONMAN","List did not correctly sort by name")
    assert_equal(sortedArray[1],"MOVIE","List did not correctly sort by name") 

  end

  #tests that a movie collection can sort in descending order. 
  def tests_for_rating_sort
    list = MovieList.new
    ironman = Movie.new("IRONMAN",6)
    movie = Movie.new("MOVIE",4)
    noRating = Movie.new("NORATING")

    list.add(movie)
    list.add(ironman)
    list.add(noRating)

    sortedArray = list.sortByRating
    assert_equal(sortedArray[0].rating,6,"List did not correctly sort by rating")
    assert_equal(sortedArray[1].rating,5,"List did not correctly sort by rating") 
    assert_equal(sortedArray[2].rating,4,"List did not correctly sort by rating") 
    
  end
end 
