class Thinker < ActiveRecord::Base
  
  #validates basic characteristics of the name
  validates :name, :length => {:minimum => 1,:maximum => 35}, :uniqueness => true 
  #Validates the name and URL using regex expressions. 
  validates :name, :format => { :with => /^[a-zA-z]/, :with => /\A[a-zA-Z0-9 \-']+\z/, :on => :create}
  validates :url, :format => { :with => URI::regexp(%w(http https)),:on => :create}
  validates :url, :uniqueness => true, :length => {:maximum => 120} 
  validates :email, :format => { :with => /\A[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]+\z/ }
  
  has_many :follows, :foreign_key => "follower_id", :class_name => "Follow"
  has_many :followed, :foreign_key => "followee_id", :class_name => "Follow"
  has_many :thoughts
  has_many :thumbs
  
  
  

  
end
