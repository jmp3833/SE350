require './DiGraph'
require 'test/unit'

class DiGraphTest < Test::Unit::TestCase

  # Create a new graph for the next test

  def setup
    @myGraph = DiGraph.new
  end

  # Is a new graph empty?
  # Does it have size zero?

  def test_for_empty_graph
    assert( @myGraph.empty?, "New graph not empty")
    assert( @myGraph.numVertices == 0, "New graph does not have a size of zero")
  end

  def test_for_adding_vertices
    @myGraph.addVertex("A")
    @myGraph.addVertex("B")
    @myGraph.addVertex("C")
    assert( @myGraph.numVertices == 3, "New vertices were not correctly added")
  end

  def test_for_adding_edges
    @myGraph.addEdge("A","B")
    @myGraph.addEdge("B","C")
    @myGraph.addEdge("C","A")
    @myGraph.addEdge("A","C")
    assert(@myGraph.edge?("A","B"), "The newly added edges do not exist")   
    assert(@myGraph.inDegree("A") == 1, "Incorrect number of in degrees")
    assert(@myGraph.inDegree("C") == 2, "Incorrect number of in degrees")
    assert(@myGraph.outDegree("A") == 2, "Incorrect number of out edges")
  end


end

