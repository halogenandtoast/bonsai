#include "vm.h"

#ifndef _CLASS_H_
#define _CLASS_H_

struct Method {
  const char *name;
  VALUE (*c_method)();
  struct Method *method;
};

struct Class {
  const char *name;
  struct Method *method;
};

VALUE bs_class_create(const char *name);
void bs_add_method(VALUE klass, const char *name, VALUE (*c_method)());

#endif
