/* ruby.h is the header for the Ruby/C API */
#include <ruby.h>

/* By declaring this variable to be static, it will get
 * loaded when the shared library is loaded.
 *
 * VALUE is the general data type in the API.
 * All data to/from Ruby is either VALUE or ID */
static VALUE rb_cStringThing;


/* We'll go into more detail about these below,
 * but they have to be declared up front */
static VALUE dohickey(VALUE self, VALUE input_string_ruby);
void finalize_string_thing(VALUE unused);


/* This is where we initialize our extension.  The convention
 * is Init_<extension name>.  It gets called when the shared
 * library is loaded. */
void Init_string_thing_ext(void)
{

  /* Create the class using rb_define_class:
   *   rb_define_class(<Name in Ruby>, <base class>) */
  rb_cStringThing = rb_define_class("StringThing", rb_cObject);

  /* Define a method on our StringThing class:
   *   rb_define_method(<C Class Object>, <Name in Ruby>, 
   *                    <C function>, <Number of arguments>)
   * We end up with StringThing.new.dohickey("some string")  */
  rb_define_method(rb_cStringThing, "dohickey", dohickey, 1);

  /* Set the callback for when the extension is unloaded
   * so we can clean up (optional). */
  rb_set_end_proc(finalize_string_thing, 0);
}


/* Our workhorse function.  Basic idea:
 * 1) Convert input data from Ruby to C
 * 2) Operate on C data
 * 3) Convert output data from C to Ruby
 *
 * Note we always have N+1 arguments, the first argument
 * is always 'self' (e.g., the class instance). */
static VALUE dohickey(VALUE self, VALUE input_string_ruby)
{

  /****************************************/
  /* 1) Convert input data from Ruby to C */
  /****************************************/

  /* Get a pointer to the underlying string data */
  const char* input_string = StringValuePtr(input_string_ruby);

  /* We also need the size of the string... 
   *   (there is no guarantee that our Ruby string is
   *     null-terminated!) */

  /* ID is for :symbols (they get compiled to integers!).
   * Use rb_intern to convert a string to a symbol */
  ID byte_size = rb_intern("bytesize");

  /* Get the size of the string in bytes.  Two things to note:
   *   1) FIX2LONG(x) converts a FIX number (Ruby)
   *        long integer (C)
   *   2) Calling ruby methods from inside c:
   *      rb_funcall(<Ruby object>, <symbol>, <# arguments>, ... <arguments>)
   *        => same as Object.send(:symbol, arguments) */
  size_t len = FIX2LONG(rb_funcall(input_string_ruby, byte_size, 0));

  /* We also need to declare the output Ruby object */
  VALUE output_string_ruby;

  /****************************************/
  /* 1) Operate on C data                 */
  /****************************************/

  /* Allocate a placeholder for our output string */
  char* output_string = (char *)calloc(len, sizeof(char));

  /* Some variables we'll need */
  char curr_val;
  size_t ix;

  /* loop over the input string */
  for(ix = 0; ix < len; ix++)
  {
    /* kind of like rot13, but for all printable ASCII chars */
    curr_val = input_string[ix];
    if(curr_val < 32 || curr_val > 126)
    {
      output_string[ix] = curr_val;
    }
    else
    {
      output_string[ix] = 32 + ((126 - 32) - (curr_val - 32));
    }
  }

  /*****************************************/
  /* 3) Convert output data from C to Ruby */
  /*****************************************/

  /* Convert to the C string to an a Ruby String
   * (US-ASCII encoded). */
  output_string_ruby = rb_usascii_str_new(output_string, len);

  /* We need to free the data we malloc'd above.  
   * Note we do this because rb_usascii_str_new 
   * copies the data from its input argument. */
  free(output_string);

  /* Return the new string - note we DON'T have to 
   * worry about GC on this - it'll be automatically
   * managed by the VM.  */
  return output_string_ruby;
}


/* Not really using this - just for show */
void finalize_string_thing(VALUE unused)
{
  /* free memory, etc */
}


