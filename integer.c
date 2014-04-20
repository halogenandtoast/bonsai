/*  */
/* VALUE cInteger; */
/*  */
/* VALUE bs_integer_puts(VALUE self) { */
/*   printf("%d\n", (int)(self >> 1)); */
/*   return self; */
/* } */
/*  */
/* VALUE bs_integer_plus(VALUE self, VALUE other) { */
/*   int left = (int)(self >> 1); */
/*   int right = (int)(other >> 1); */
/*   int result = left + right; */
/*   return INT2FIX(result); */
/* } */
/*  */
/* void integer_init() { */
/*   cInteger = bs_class_create("Integer"); */
/*   bs_add_method(cInteger, "puts", bs_integer_puts); */
/*   bs_add_method(cInteger, "+", bs_integer_plus); */
/* } */
