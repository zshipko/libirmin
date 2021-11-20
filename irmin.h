#pragma once
#include <stdbool.h>
#include <stdint.h>
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
IrminType* irmin_type_list(IrminType* x913);
IrminType* irmin_type_array(IrminType* x914);
IrminType* irmin_type_option(IrminType* x915);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x918);
IrminType* irmin_type_pair(IrminType* x920, IrminType* x919);
IrminType* irmin_type_triple(IrminType* x923, IrminType* x922,
                             IrminType* x921);
void irmin_type_free(IrminType* x924);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int x926);
IrminValue* irmin_value_bool(_Bool x927);
IrminValue* irmin_value_string(char* x928);
IrminValue* irmin_value_string_len(char* x930, int x929);
char* irmin_value_get_string(IrminValue* x932, int* x931);
int irmin_value_get_int(IrminValue* x933);
_Bool irmin_value_get_bool(IrminValue* x934);
IrminValue* irmin_value_bytes(char* x935);
IrminValue* irmin_value_bytes_len(char* x937, int x936);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x940, IrminValue* x939);
IrminValue* irmin_value_list_hd(IrminValue* x941);
IrminValue* irmin_value_list_tl(IrminValue* x942);
IrminValue* irmin_value_array_new(int x944, IrminValue* x943);
void irmin_value_array_set(IrminValue* x947, int x946, IrminValue* x945);
IrminValue* irmin_value_array_get(IrminValue* x949, int x948);
IrminValue* irmin_value_option(IrminValue* x950);
IrminValue* irmin_value_pair(IrminValue* x952, IrminValue* x951);
IrminValue* irmin_value_triple(IrminValue* x955, IrminValue* x954,
                               IrminValue* x953);
char* irmin_value_to_string(IrminType* x958, IrminValue* x957, int* x956);
IrminValue* irmin_value_of_string(IrminType* x961, char* x960, int x959);
char* irmin_value_to_bin(IrminValue* x963, int* x962);
IrminValue* irmin_value_of_bin(IrminType* x966, char* x965, int x964);
char* irmin_value_to_json(IrminValue* x968, int* x967);
IrminValue* irmin_value_of_json(IrminType* x971, char* x970, int x969);
void irmin_value_free(IrminValue* x972);
IrminInfo* irmin_info_new(IrminRepo* x975, char* x974, char* x973);
IrminInfo* irmin_info_update(IrminRepo* x979, char* x978, char* x977,
                             IrminInfo* x976);
char* irmin_info_message(IrminRepo* x982, IrminInfo* x981, int* x980);
char* irmin_info_author(IrminRepo* x985, IrminInfo* x984, int* x983);
int64_t irmin_info_date(IrminRepo* x987, IrminInfo* x986);
void irmin_info_free(IrminInfo* x988);
void irmin_log_level(char* x989);
IrminConfig* irmin_config_pack(char* x991, char* x990);
IrminConfig* irmin_config_git(char* x992);
IrminConfig* irmin_config_git_mem(char* x993);
IrminConfig* irmin_config_fs(char* x995, char* x994);
IrminConfig* irmin_config_mem(char* x997, char* x996);
void irmin_config_free(IrminConfig* x998);
_Bool irmin_config_set(IrminConfig* x1002, char* x1001, IrminType* x1000,
                       IrminValue* x999);
IrminPath* irmin_path(IrminRepo* x1004, char** x1003);
IrminPath* irmin_path_of_string(IrminRepo* x1007, char* x1006, int x1005);
char* irmin_path_to_string(IrminRepo* x1010, IrminPath* x1009, int* x1008);
void irmin_path_free(IrminPath* x1011);
void irmin_hash_free(IrminHash* x1012);
char* irmin_hash_to_string(IrminRepo* x1015, IrminHash* x1014, int* x1013);
char* irmin_hash_of_string(IrminRepo* x1018, IrminHash* x1017, int* x1016);
Irmin* irmin_main(IrminRepo* x1019);
Irmin* irmin_of_branch(IrminRepo* x1021, char* x1020);
IrminCommit* irmin_get_head(Irmin* x1022);
void irmin_set_head(Irmin* x1024, IrminCommit* x1023);
_Bool irmin_fast_forward(Irmin* x1026, IrminCommit* x1025);
_Bool irmin_merge_with_branch(Irmin* x1029, char* x1028, IrminInfo* x1027);
_Bool irmin_merge_with_commit(Irmin* x1032, IrminCommit* x1031,
                              IrminInfo* x1030);
_Bool irmin_set(Irmin* x1036, IrminPath* x1035, IrminValue* x1034,
                IrminInfo* x1033);
_Bool irmin_test_and_set(Irmin* x1041, IrminPath* x1040, IrminValue* x1039,
                         IrminValue* x1038, IrminInfo* x1037);
_Bool irmin_test_and_set_tree(Irmin* x1046, IrminPath* x1045,
                              IrminTree* x1044, IrminTree* x1043,
                              IrminInfo* x1042);
_Bool irmin_set_tree(Irmin* x1050, IrminPath* x1049, IrminTree* x1048,
                     IrminInfo* x1047);
IrminValue* irmin_find(Irmin* x1052, IrminPath* x1051);
IrminTree* irmin_find_tree(Irmin* x1054, IrminPath* x1053);
void irmin_remove(Irmin* x1057, IrminPath* x1056, IrminInfo* x1055);
_Bool irmin_mem(Irmin* x1059, IrminPath* x1058);
_Bool irmin_mem_tree(Irmin* x1061, IrminPath* x1060);
void irmin_free(Irmin* x1062);
IrminTree* irmin_tree_new(IrminRepo* x1063);
IrminTree* irmin_tree_clone(IrminRepo* x1065, IrminTree* x1064);
_Bool irmin_tree_mem(IrminRepo* x1068, IrminTree* x1067, IrminPath* x1066);
_Bool irmin_tree_mem_tree(IrminRepo* x1071, IrminTree* x1070,
                          IrminPath* x1069);
IrminValue* irmin_tree_find(IrminRepo* x1074, IrminTree* x1073,
                            IrminPath* x1072);
IrminTree* irmin_tree_find_tree(IrminRepo* x1077, IrminTree* x1076,
                                IrminPath* x1075);
void irmin_tree_add(IrminRepo* x1081, IrminTree* x1080, IrminPath* x1079,
                    IrminValue* x1078);
void irmin_tree_add_tree(IrminRepo* x1085, IrminTree* x1084,
                         IrminPath* x1083, IrminTree* x1082);
void irmin_tree_remove(IrminRepo* x1088, IrminTree* x1087, IrminPath* x1086);
void irmin_tree_free(IrminTree* x1089);
IrminRepo* irmin_repo_new(IrminConfig* x1090);
void irmin_repo_free(IrminRepo* x1091);
IrminInfo* irmin_commit_info(IrminRepo* x1093, IrminCommit* x1092);
IrminHash* irmin_commit_hash(IrminRepo* x1095, IrminCommit* x1094);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1097, IrminHash* x1096);
int irmin_commit_parents_length(IrminRepo* x1099, IrminCommit* x1098);
IrminCommit* irmin_commit_parent(IrminRepo* x1102, IrminCommit* x1101,
                                 int x1100);
void irmin_commit_free(IrminCommit* x1103);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(void**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
