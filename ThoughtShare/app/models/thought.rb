class Thought < ActiveRecord::Base
  #conditions which check properties of a thought.
  
  validates_length_of :thought, :minimum => 5
  validates_length_of :thought, :maximum => 154
  validates_uniqueness_of :thought
  
  belongs_to :thinker
  has_many :thumbs

  
end
