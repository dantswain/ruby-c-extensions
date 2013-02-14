#include <ruby.h>

static VALUE rb_cStringThing;
static ID _byte_size;

void finalize_string_thing(VALUE unused)
{
  /* free memory, etc */
}

/* scramble the text */
static VALUE dohickey(VALUE self, VALUE input_string_ruby)
{
  const char* input_string = StringValuePtr(input_string_ruby);
  size_t len = FIX2LONG(rb_funcall(input_string_ruby, _byte_size, 0));

  char* output_string = (char *)calloc(len, sizeof(char));

  char curr_val;
  size_t ix;

  VALUE output_string_ruby;

  for(ix = 0; ix < len; ix++)
  {
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

  output_string_ruby = rb_usascii_str_new(output_string, len);

  /* rb_usascii_str_new copies the data, so we can free it here */
  free(output_string);

  return output_string_ruby;
}

void Init_string_thing(void)
{
  rb_cStringThing = rb_define_class("StringThing", rb_cObject);
  _byte_size = rb_intern("bytesize");

  rb_define_module_function(rb_cStringThing, "dohickey", dohickey, 1);

  /* set the callback for when the extension is unloaded */
  rb_set_end_proc(finalize_string_thing, 0);
}  
