require 'rake'

Gem::Specification.new do |gem|
  gem.name = "string_thing"
  gem.authors = ["Dan Swain"]
  gem.email = ["dan.t.swain@gmail.com"]
  gem.description = "Simple example of a gem using a C extension."
  gem.summary = "It's nothing fancy."
  gem.homepage = "http://github.com/dantswain/ruby-c-extensions"

  gem.files = FileList['lib/*.rb', 'lib/**/*.rb/', 'ext/**/*.rb',
                       'ext/**/*.c', 'spec/**/*.rb', 'examples/*.rb',
                       '[A-Z]*'].to_a
  gem.test_files = FileList['spec/**/*.rb'].to_a

  gem.require_paths = ["lib", "ext/string_thing"]

  gem.extensions = ['ext/string_thing/extconf.rb']

  gem.version = "0.0.1"
end
