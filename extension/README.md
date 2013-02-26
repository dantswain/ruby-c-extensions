# C Extension Gem

This shows how to take the basic extension in ../basic and create a simple gem.

## Files

 - ext
    - string\_thing
        - string\_thing\_ext.c  - Only difference from previous version is to change `Init_string_thing` to `Init_string_thing_ext`
        - extconf.rb  - Change `string_thing` to `string_thing_ext`
 - lib
    - string\_thing.rb - Ruby class wrapper
 - string\_thing.gemspec

## Build & Run

```
gem build string_thing.gemspec   # -> string_thing-0.0.1.gem
gem install string_thing-0.0.1.gem
```

```
>> require 'string_thing'
true
>> st = StringThing.new
#<StringThing:0x007ff40a8cd830>
>> st.wrapped_call("Hello, World.")
"V922/r~G/,2:p"
>> st.dohickey("Hello, World.")
"V922/r~G/,2:p"
```

```
gem uninstall string_thing
```
