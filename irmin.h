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
IrminType* irmin_type_list(IrminType* x884);
IrminType* irmin_type_array(IrminType* x885);
IrminType* irmin_type_option(IrminType* x886);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminSchema* x889);
IrminType* irmin_type_pair(IrminType* x891, IrminType* x890);
IrminType* irmin_type_triple(IrminType* x894, IrminType* x893,
                             IrminType* x892);
void irmin_type_free(IrminType* x895);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int x897);
IrminValue* irmin_value_bool(_Bool x898);
IrminValue* irmin_value_string(char* x899);
IrminValue* irmin_value_string_len(char* x901, int x900);
char* irmin_value_get_string(IrminValue* x903, int* x902);
int irmin_value_get_int(IrminValue* x904);
_Bool irmin_value_get_bool(IrminValue* x905);
IrminValue* irmin_value_bytes(char* x906);
IrminValue* irmin_value_bytes_len(char* x908, int x907);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x911, IrminValue* x910);
IrminValue* irmin_value_list_hd(IrminValue* x912);
IrminValue* irmin_value_list_tl(IrminValue* x913);
IrminValue* irmin_value_array_new(int x915, IrminValue* x914);
void irmin_value_array_set(IrminValue* x918, int x917, IrminValue* x916);
IrminValue* irmin_value_array_get(IrminValue* x920, int x919);
IrminValue* irmin_value_option(IrminValue* x921);
IrminValue* irmin_value_pair(IrminValue* x923, IrminValue* x922);
IrminValue* irmin_value_triple(IrminValue* x926, IrminValue* x925,
                               IrminValue* x924);
char* irmin_value_to_string(IrminType* x929, IrminValue* x928, int* x927);
IrminValue* irmin_value_of_string(IrminType* x932, char* x931, int x930);
char* irmin_value_to_bin(IrminValue* x934, int* x933);
IrminValue* irmin_value_of_bin(IrminType* x937, char* x936, int x935);
char* irmin_value_to_json(IrminValue* x939, int* x938);
IrminValue* irmin_value_of_json(IrminType* x942, char* x941, int x940);
void irmin_value_free(IrminValue* x943);
IrminInfo* irmin_info_new(IrminSchema* x946, char* x945, char* x944);
IrminInfo* irmin_info_update(IrminSchema* x950, char* x949, char* x948,
                             IrminInfo* x947);
char* irmin_info_message(IrminSchema* x952, IrminInfo* x951);
char* irmin_info_author(IrminSchema* x954, IrminInfo* x953);
int64_t irmin_info_date(IrminSchema* x956, IrminInfo* x955);
void irmin_info_free(IrminInfo* x957);
IrminConfig* irmin_config_new(IrminSchema* x958);
void irmin_config_free(IrminConfig* x959);
_Bool irmin_config_set(IrminConfig* x963, char* x962, IrminType* x961,
                       IrminValue* x960);
IrminPath* irmin_path(IrminSchema* x965, char** x964);
void irmin_path_free(IrminPath* x966);
void irmin_hash_free(IrminHash* x967);
char* irmin_hash_get_string(IrminSchema* x969, IrminHash* x968);
Irmin* irmin_main(IrminSchema* x971, IrminRepo* x970);
Irmin* irmin_of_branch(IrminSchema* x974, IrminRepo* x973, char* x972);
IrminCommit* irmin_get_head(Irmin* x975);
void irmin_set_head(Irmin* x977, IrminCommit* x976);
_Bool irmin_fast_forward(Irmin* x979, IrminCommit* x978);
_Bool irmin_merge_with_branch(Irmin* x982, char* x981, IrminInfo* x980);
_Bool irmin_merge_with_commit(Irmin* x985, IrminCommit* x984,
                              IrminInfo* x983);
_Bool irmin_set(Irmin* x989, IrminPath* x988, IrminValue* x987,
                IrminInfo* x986);
_Bool irmin_test_and_set(Irmin* x994, IrminPath* x993, IrminValue* x992,
                         IrminValue* x991, IrminInfo* x990);
_Bool irmin_test_and_set_tree(Irmin* x999, IrminPath* x998, IrminTree* x997,
                              IrminTree* x996, IrminInfo* x995);
_Bool irmin_set_tree(Irmin* x1003, IrminPath* x1002, IrminTree* x1001,
                     IrminInfo* x1000);
IrminValue* irmin_get(Irmin* x1005, IrminPath* x1004);
IrminTree* irmin_get_tree(Irmin* x1007, IrminPath* x1006);
void irmin_remove(Irmin* x1010, IrminPath* x1009, IrminInfo* x1008);
_Bool irmin_mem(Irmin* x1012, IrminPath* x1011);
_Bool irmin_mem_tree(Irmin* x1014, IrminPath* x1013);
void irmin_free(Irmin* x1015);
IrminTree* irmin_tree_new(IrminSchema* x1016);
IrminTree* irmin_tree_clone(IrminSchema* x1018, IrminTree* x1017);
_Bool irmin_tree_mem(IrminSchema* x1021, IrminTree* x1020, IrminPath* x1019);
_Bool irmin_tree_mem_tree(IrminSchema* x1024, IrminTree* x1023,
                          IrminPath* x1022);
IrminValue* irmin_tree_find(IrminSchema* x1027, IrminTree* x1026,
                            IrminPath* x1025);
IrminTree* irmin_tree_find_tree(IrminSchema* x1030, IrminTree* x1029,
                                IrminPath* x1028);
void irmin_tree_add(IrminSchema* x1034, IrminTree* x1033, IrminPath* x1032,
                    IrminValue* x1031);
void irmin_tree_add_tree(IrminSchema* x1038, IrminTree* x1037,
                         IrminPath* x1036, IrminTree* x1035);
void irmin_tree_remove(IrminSchema* x1041, IrminTree* x1040,
                       IrminPath* x1039);
void irmin_tree_free(IrminTree* x1042);
IrminSchema* irmin_schema_pack(char* x1044, char* x1043);
IrminSchema* irmin_schema_git(char* x1045);
IrminSchema* irmin_schema_fs(char* x1047, char* x1046);
IrminSchema* irmin_schema_mem(char* x1049, char* x1048);
void irmin_schema_free(IrminSchema* x1050);
IrminRepo* irmin_repo_new(IrminSchema* x1052, IrminConfig* x1051);
void irmin_repo_free(IrminRepo* x1053);
IrminInfo* irmin_commit_info(IrminSchema* x1055, IrminCommit* x1054);
IrminHash* irmin_commit_hash(IrminSchema* x1057, IrminCommit* x1056);
IrminCommit* irmin_commit_of_hash(IrminSchema* x1060, IrminRepo* x1059,
                                  IrminHash* x1058);
int irmin_commit_parents_length(IrminSchema* x1062, IrminCommit* x1061);
IrminCommit* irmin_commit_parent(IrminSchema* x1065, IrminCommit* x1064,
                                 int x1063);
void irmin_commit_free(IrminCommit* x1066);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(void**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
