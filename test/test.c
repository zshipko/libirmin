#include "irmin.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  puts("A");
  // irmin_init(argv);

  AUTO IrminSchema *schema = irmin_schema_new("irf", NULL, NULL, NULL);

  puts("B");
  AUTO IrminConfig *config = irmin_config_new(schema);

  puts("C");

  AUTO IrminType *ty = irmin_type_string();
  AUTO IrminValue *root = irmin_value_string("./tmp2");
  assert(irmin_config_set(config, "root", ty, root));

  AUTO IrminRepo *repo = irmin_repo_new(schema, config);

  AUTO Irmin *store = irmin_master(schema, repo);

  char *x = "123";
  AUTO IrminValue *a = irmin_value_string(x);

  char *k[] = {"a", "b", "c", NULL};
  AUTO IrminKey *key = irmin_key(schema, k);
  assert(irmin_set(store, key, a));

  char *s = irmin_value_to_string(ty, irmin_get(store, key));
  puts(s);

  return 0;
}
