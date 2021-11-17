#pragma once
#include <stdbool.h>
#include <stdint.h>
typedef struct IrminSchema IrminSchema;
typedef struct IrminType IrminType;
typedef struct IrminValue IrminValue;
typedef struct IrminConfig IrminConfig;
typedef struct IrminRepo IrminRepo;
typedef struct Irmin Irmin;
typedef struct IrminPath IrminPath;
typedef struct IrminTree IrminTree;
typedef struct IrminCommit IrminCommit;
typedef struct IrminInfo IrminInfo;
typedef struct IrminHash IrminHash;
IrminType* irmin_type_unit(void);
IrminType* irmin_type_bool(void);
IrminType* irmin_type_int(void);
IrminType* irmin_type_string(void);
IrminType* irmin_type_bytes(void);
IrminType* irmin_type_list(IrminType* x876);
IrminType* irmin_type_array(IrminType* x877);
IrminType* irmin_type_option(IrminType* x878);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_pair(IrminType* x882, IrminType* x881);
IrminType* irmin_type_triple(IrminType* x885, IrminType* x884,
                             IrminType* x883);
void irmin_type_free(IrminType* x886);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int x888);
IrminValue* irmin_value_bool(_Bool x889);
IrminValue* irmin_value_string(char* x890);
IrminValue* irmin_value_string_len(char* x892, int x891);
char* irmin_value_to_string(IrminType* x895, IrminValue* x894, int* x893);
char* irmin_value_get_string(IrminValue* x897, int* x896);
int irmin_value_get_int(IrminValue* x898);
_Bool irmin_value_get_bool(IrminValue* x899);
IrminValue* irmin_value_bytes(char* x900);
IrminValue* irmin_value_bytes_len(char* x902, int x901);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x905, IrminValue* x904);
IrminValue* irmin_value_list_hd(IrminValue* x906);
IrminValue* irmin_value_list_tl(IrminValue* x907);
IrminValue* irmin_value_array_new(int x909, IrminValue* x908);
void irmin_value_array_set(IrminValue* x912, int x911, IrminValue* x910);
IrminValue* irmin_value_array_get(IrminValue* x914, int x913);
IrminValue* irmin_value_option(IrminValue* x915);
IrminValue* irmin_value_pair(IrminValue* x917, IrminValue* x916);
IrminValue* irmin_value_triple(IrminValue* x920, IrminValue* x919,
                               IrminValue* x918);
IrminValue* irmin_value_of_string(IrminType* x923, char* x922, int x921);
char* irmin_value_to_bin(IrminValue* x925, int* x924);
IrminValue* irmin_value_of_bin(IrminType* x928, char* x927, int x926);
char* irmin_value_to_json(IrminValue* x930, int* x929);
IrminValue* irmin_value_of_json(IrminType* x933, char* x932, int x931);
void irmin_value_free(IrminValue* x934);
IrminInfo* irmin_info_new(IrminSchema* x937, char* x936, char* x935);
IrminInfo* irmin_info_update(IrminSchema* x941, char* x940, char* x939,
                             IrminInfo* x938);
char* irmin_info_message(IrminSchema* x943, IrminInfo* x942);
char* irmin_info_author(IrminSchema* x945, IrminInfo* x944);
int64_t irmin_info_date(IrminSchema* x947, IrminInfo* x946);
void irmin_info_free(IrminInfo* x948);
IrminConfig* irmin_config_new(IrminSchema* x949);
void irmin_config_free(IrminConfig* x950);
_Bool irmin_config_set(IrminConfig* x954, char* x953, IrminType* x952,
                       IrminValue* x951);
IrminPath* irmin_path(IrminSchema* x956, char** x955);
void irmin_path_free(IrminPath* x957);
void irmin_hash_free(IrminHash* x958);
char* irmin_hash_get_string(IrminSchema* x960, IrminHash* x959);
Irmin* irmin_main(IrminSchema* x962, IrminRepo* x961);
Irmin* irmin_of_branch(IrminSchema* x965, IrminRepo* x964, char* x963);
IrminCommit* irmin_get_head(Irmin* x966);
void irmin_set_head(Irmin* x968, IrminCommit* x967);
_Bool irmin_fast_forward(Irmin* x970, IrminCommit* x969);
_Bool irmin_merge_with_branch(Irmin* x973, char* x972, IrminInfo* x971);
_Bool irmin_merge_with_commit(Irmin* x976, IrminCommit* x975,
                              IrminInfo* x974);
_Bool irmin_set(Irmin* x980, IrminPath* x979, IrminValue* x978,
                IrminInfo* x977);
_Bool irmin_test_and_set(Irmin* x985, IrminPath* x984, IrminValue* x983,
                         IrminValue* x982, IrminInfo* x981);
_Bool irmin_test_and_set_tree(Irmin* x990, IrminPath* x989, IrminTree* x988,
                              IrminTree* x987, IrminInfo* x986);
_Bool irmin_set_tree(Irmin* x994, IrminPath* x993, IrminTree* x992,
                     IrminInfo* x991);
IrminValue* irmin_get(Irmin* x996, IrminPath* x995);
IrminTree* irmin_get_tree(Irmin* x998, IrminPath* x997);
void irmin_remove(Irmin* x1001, IrminPath* x1000, IrminInfo* x999);
_Bool irmin_mem(Irmin* x1003, IrminPath* x1002);
_Bool irmin_mem_tree(Irmin* x1005, IrminPath* x1004);
void irmin_free(Irmin* x1006);
IrminTree* irmin_tree_new(IrminSchema* x1007);
IrminTree* irmin_tree_clone(IrminSchema* x1009, IrminTree* x1008);
_Bool irmin_tree_mem(IrminSchema* x1012, IrminTree* x1011, IrminPath* x1010);
_Bool irmin_tree_mem_tree(IrminSchema* x1015, IrminTree* x1014,
                          IrminPath* x1013);
IrminValue* irmin_tree_find(IrminSchema* x1018, IrminTree* x1017,
                            IrminPath* x1016);
IrminTree* irmin_tree_find_tree(IrminSchema* x1021, IrminTree* x1020,
                                IrminPath* x1019);
void irmin_tree_add(IrminSchema* x1025, IrminTree* x1024, IrminPath* x1023,
                    IrminValue* x1022);
void irmin_tree_add_tree(IrminSchema* x1029, IrminTree* x1028,
                         IrminPath* x1027, IrminTree* x1026);
void irmin_tree_remove(IrminSchema* x1032, IrminTree* x1031,
                       IrminPath* x1030);
void irmin_tree_free(IrminTree* x1033);
IrminSchema* irmin_schema_pack(char* x1035, char* x1034);
IrminSchema* irmin_schema_git(char* x1036);
IrminSchema* irmin_schema_fs(char* x1038, char* x1037);
IrminSchema* irmin_schema_mem(char* x1040, char* x1039);
void irmin_schema_free(IrminSchema* x1041);
IrminRepo* irmin_repo_new(IrminSchema* x1043, IrminConfig* x1042);
void irmin_repo_free(IrminRepo* x1044);
IrminInfo* irmin_commit_info(IrminSchema* x1046, IrminCommit* x1045);
IrminHash* irmin_commit_hash(IrminSchema* x1048, IrminCommit* x1047);
IrminCommit* irmin_commit_of_hash(IrminSchema* x1051, IrminRepo* x1050,
                                  IrminHash* x1049);
int irmin_commit_parents_length(IrminSchema* x1053, IrminCommit* x1052);
IrminCommit* irmin_commit_parent(IrminSchema* x1056, IrminCommit* x1055,
                                 int x1054);
void irmin_commit_free(IrminCommit* x1057);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(void**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
