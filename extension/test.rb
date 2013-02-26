require 'string_thing'

st = StringThing.new
# the wrapped call defined in lib/string_thing.rb
puts st.wrapped_call "Hello, World!"
# the original call defined in the extension
puts st.dohickey "Hello, World!"
