#include "class.h"
#include <stdlib.h>

VALUE bs_class_create(const char *name) {
  struct Class *klass = (struct Class *) malloc(sizeof(struct Class));
  klass->name = name;
  return (VALUE) klass;
}

void bs_add_method(VALUE object, const char *name, VALUE (*c_method)()) {
  struct Class *klass = (struct Class *) object;
  struct Method *new_method = (struct Method *) malloc(sizeof(struct Method));

  new_method->method = klass->method;
  new_method->name = name;
  new_method->c_method = c_method;

  klass->method = new_method;
}
