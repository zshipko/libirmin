#include "../include/irmin.h"
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_irmin_value_json() {
  AUTO IrminType *json = irmin_type_json();
  IrminValue *j1 = irmin_value_of_string(json, "{\"a\": 1}", -1);
  assert(j1 != NULL);
  irmin_value_free(j1);
}

void test_irmin_store() {
  // Setup config for git store
  AUTO IrminConfig *config = irmin_config_git(NULL);

  // Set root key
  AUTO IrminString *root = irmin_string_new("./tmp2", -1);
  AUTO IrminType *ty = irmin_type_string();
  assert(irmin_config_set(config, "root", ty, (IrminValue *)root));

  // Initialize repo and store
  AUTO IrminRepo *repo = irmin_repo_new(config);
  AUTO Irmin *store = irmin_main(repo);

  // Create new string value
  AUTO IrminString *a = irmin_string_new("123", 3);

  // Create path: a/b/c
  char *k[] = {"a", "b", "c", NULL};
  AUTO IrminPath *path = irmin_path(repo, k);

  // Create commit info
  AUTO IrminInfo *info = irmin_info_new(repo, "test", "set");

  // Set a/b/c to "123"
  assert(irmin_set(store, path, (IrminValue *)a, info));
  assert(irmin_mem(store, path));

  // Get a/b/c from store
  AUTO IrminString *v = (IrminString *)irmin_find(store, path);
  assert(v);

  // Get string representation
  uint64_t length = irmin_string_length(v);
  assert(strncmp(irmin_string_data(v), irmin_string_data(a), length) == 0);

  // Check that tree exists at a/b
  AUTO IrminPath *path1 = irmin_path_of_string(repo, "a/b", -1);
  assert(irmin_mem_tree(store, path1));

  // Get tree at a/b
  AUTO IrminTree *t = irmin_find_tree(store, path1);

  // Set d to "456"
  AUTO IrminPath *path2 = irmin_path_of_string(repo, "d", 1);
  AUTO IrminString *b = irmin_string_new("456", -1);
  irmin_tree_add(repo, t, path2, (IrminValue *)b);
  assert(irmin_tree_mem(repo, t, path2));

  // Commit updated tree
  AUTO IrminInfo *info1 = irmin_info_new(repo, "test", "tree");
  irmin_set_tree(store, path1, t, info1);

  // Ensure the store contains a/b/d
  AUTO IrminPath *path3 = irmin_path_of_string(repo, "a/b/d", -1);
  assert(irmin_mem(store, path3));
}

int main(int argc, char *argv[]) {
  irmin_log_level("debug");

  test_irmin_value_json();
  test_irmin_store();

  return 0;
}
