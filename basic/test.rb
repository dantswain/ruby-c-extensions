$LOAD_PATH.unshift(File.dirname(__FILE__))

require 'string_thing'

string_thing = StringThing.new

input = "It's a secret to everybody."
output = string_thing.dohickey(input)

puts "string_thing.dohickey(\"#{input}\") = \"#{output}\""
puts "string_thing.dohickey(\"#{output}\") = \"#{string_thing.dohickey(output)}\""
