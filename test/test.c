#include "../irmin.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  puts("A");

  AUTO IrminSchema *schema = irmin_schema_pack(NULL, NULL);

  puts("B");
  AUTO IrminConfig *config = irmin_config_new(schema);

  AUTO IrminType *ty = irmin_type_string();
  AUTO IrminValue *root = irmin_value_string("./tmp2");

  assert(irmin_config_set(config, "root", ty, root));

  puts("C");

  AUTO IrminRepo *repo = irmin_repo_new(schema, config);

  AUTO Irmin *store = irmin_main(schema, repo);

  char *x = "123";
  AUTO IrminValue *a = irmin_value_string(x);

  char *k[] = {"a", "b", "c", NULL};
  AUTO IrminPath *path = irmin_path(schema, k);
  AUTO IrminInfo *info = irmin_info_new(schema, "testing", NULL);
  assert(irmin_set(store, path, a, info));
  assert(irmin_mem(store, path));

  AUTO IrminType *json = irmin_type_json();
  IrminValue *j1 = irmin_value_of_string(json, "{\"a\": 1}", -1);
  assert(j1 != NULL);
  irmin_value_free(j1);

  char *s = irmin_value_get_string(irmin_get(store, path), NULL);
  puts(s);
  free(s);

  puts("TREE");

  char *k1[] = {"a", "b", NULL};
  AUTO IrminPath *path1 = irmin_path(schema, k1);
  AUTO IrminTree *t = irmin_get_tree(store, path1);

  puts("TREE1");

  char *k2[] = {"d", NULL};
  AUTO IrminPath *path2 = irmin_path(schema, k2);

  AUTO IrminValue *b = irmin_value_string("456");
  irmin_tree_add(schema, t, path2, b);

  AUTO IrminInfo *info1 = irmin_info_new(schema, "tree", NULL);
  irmin_set_tree(store, path1, t, info1);

  puts("TREE3");
  char *k3[] = {"a", "b", "d", NULL};
  AUTO IrminPath *path3 = irmin_path(schema, k3);
  assert(irmin_mem(store, path3));

  return 0;
}
