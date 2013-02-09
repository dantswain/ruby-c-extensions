These are my notes for planning the talk.

# Vague Ideas/Notes
 
 - Why would anyone care what I have to say on the topic? => Background
 - Build up a C extension through the talk
 - What are C extensions good for?
 - What are C extensions NOT good for?
 - Under what circumstances can you even use a C extension?
 - Make sure to point out the [Ruby cross reference](http://rxr.whitequark.org/mri/source)
 - The pick-axe has a whole chapter on this: http://media.pragprog.com/titles/ruby3/ext_ruby.pdf
 - Readme from the source https://github.com/ruby/ruby/blob/trunk/README.EXT
 - Gotchas

# Rough outline

 - Introduction
 - Background/Self-history (What have I used C extensions for)
 - When (not) to use C extensions
    - Use C for raw performance
        + Specialized string processing
        + When you do the same specialized operation over and over again and can therefore optimize it to death
        + Handling huge data structures
        + Raw access to binary data
        + Numerical processing
    - Use C to bridge with existing C/C++ libraries
    - Don't use C to do something your Ruby implementation already does really well
        + Don't rewrite MRI
        + If you're thinking about rewriting Rack in C, you're gonna have a bad time. (Rethink your architecture.)
        + Don't "C Extension all of the things!"
 - Compatibility concerns/Gotchas
     + The API was developed for MRI ("standard" Ruby)
     + Should be mostly compatible with C/C++-based VMs, though you may experience hiccups
     + Notably does NOT work with JRuby
     + The API is strictly in C, but can be used with C++ code
     + You lose some speed at the interface (as well as code manageability)
 - Basic procedure - 10,000 foot view
    - Create your c source
        + Actual algorithm
        + Interface layer
    - Create an 'extconf.rb' => `ruby extconf.rb` creates a Makefile
    - Make => Creates 'your-extension.bundle' (`RbConfig::CONFIG['DLEXT']`)
    - require 'your-extension'
    - (Optional) Create a wrapper class in Ruby
 - Create the c source (basics)
    - Interface layer
    - Convert to/from Ruby data structures
 - Build and use
    - extconf.rb
    - make
    - require
    - wrappers (C and Ruby in the same class)
