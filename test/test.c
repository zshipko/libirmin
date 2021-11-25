#include "../include/irmin.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  irmin_log_level("debug");
  puts("A");

  AUTO IrminConfig *config = irmin_config_git(NULL);

  puts("B");

  AUTO IrminType *ty = irmin_type_string();
  AUTO IrminValue *root = irmin_value_string("./tmp2", -1);

  assert(irmin_config_set(config, "root", ty, root));

  puts("C");

  AUTO IrminRepo *repo = irmin_repo_new(config);

  puts("D");

  AUTO Irmin *store = irmin_main(repo);

  char *x = "123";
  AUTO IrminValue *a = irmin_value_string(x, -1);

  char *k[] = {"a", "b", "c", NULL};
  AUTO IrminPath *path = irmin_path(repo, k);
  AUTO IrminInfo *info = irmin_info_new(repo, "testing", NULL);
  assert(irmin_set(store, path, a, info));
  assert(irmin_mem(store, path));

  AUTO IrminType *json = irmin_type_json();
  IrminValue *j1 = irmin_value_of_string(json, "{\"a\": 1}", -1);
  assert(j1 != NULL);
  irmin_value_free(j1);

  char *s = irmin_value_get_string(irmin_find(store, path), NULL);
  puts(s);
  free(s);

  puts("TREE");

  AUTO IrminPath *path1 = irmin_path_of_string(repo, "a/b", -1);
  assert(irmin_mem_tree(store, path1));
  AUTO IrminTree *t = irmin_find_tree(store, path1);

  puts("TREE1");

  AUTO IrminPath *path2 = irmin_path_of_string(repo, "d", 1);

  AUTO IrminValue *b = irmin_value_string("456", -1);
  irmin_tree_add(repo, t, path2, b);

  AUTO IrminInfo *info1 = irmin_info_new(repo, "tree", NULL);
  irmin_set_tree(store, path1, t, info1);

  puts("TREE3");
  AUTO IrminPath *path3 = irmin_path_of_string(repo, "a/b/d", -1);
  assert(irmin_mem(store, path3));

  return 0;
}
