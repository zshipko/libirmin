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
IrminType* irmin_type_list(IrminType* x898);
IrminType* irmin_type_array(IrminType* x899);
IrminType* irmin_type_option(IrminType* x900);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x903);
IrminType* irmin_type_pair(IrminType* x905, IrminType* x904);
IrminType* irmin_type_triple(IrminType* x908, IrminType* x907,
                             IrminType* x906);
void irmin_type_free(IrminType* x909);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int x911);
IrminValue* irmin_value_bool(_Bool x912);
IrminValue* irmin_value_string(char* x913);
IrminValue* irmin_value_string_len(char* x915, int x914);
char* irmin_value_get_string(IrminValue* x917, int* x916);
int irmin_value_get_int(IrminValue* x918);
_Bool irmin_value_get_bool(IrminValue* x919);
IrminValue* irmin_value_bytes(char* x920);
IrminValue* irmin_value_bytes_len(char* x922, int x921);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x925, IrminValue* x924);
IrminValue* irmin_value_list_hd(IrminValue* x926);
IrminValue* irmin_value_list_tl(IrminValue* x927);
IrminValue* irmin_value_array_new(int x929, IrminValue* x928);
void irmin_value_array_set(IrminValue* x932, int x931, IrminValue* x930);
IrminValue* irmin_value_array_get(IrminValue* x934, int x933);
IrminValue* irmin_value_option(IrminValue* x935);
IrminValue* irmin_value_pair(IrminValue* x937, IrminValue* x936);
IrminValue* irmin_value_triple(IrminValue* x940, IrminValue* x939,
                               IrminValue* x938);
char* irmin_value_to_string(IrminType* x943, IrminValue* x942, int* x941);
IrminValue* irmin_value_of_string(IrminType* x946, char* x945, int x944);
char* irmin_value_to_bin(IrminValue* x948, int* x947);
IrminValue* irmin_value_of_bin(IrminType* x951, char* x950, int x949);
char* irmin_value_to_json(IrminValue* x953, int* x952);
IrminValue* irmin_value_of_json(IrminType* x956, char* x955, int x954);
void irmin_value_free(IrminValue* x957);
IrminInfo* irmin_info_new(IrminRepo* x960, char* x959, char* x958);
IrminInfo* irmin_info_update(IrminRepo* x964, char* x963, char* x962,
                             IrminInfo* x961);
char* irmin_info_message(IrminRepo* x966, IrminInfo* x965);
char* irmin_info_author(IrminRepo* x968, IrminInfo* x967);
int64_t irmin_info_date(IrminRepo* x970, IrminInfo* x969);
void irmin_info_free(IrminInfo* x971);
void irmin_log_level(char* x972);
IrminConfig* irmin_config_pack(char* x974, char* x973);
IrminConfig* irmin_config_git(char* x975);
IrminConfig* irmin_config_git_mem(char* x976);
IrminConfig* irmin_config_fs(char* x978, char* x977);
IrminConfig* irmin_config_mem(char* x980, char* x979);
void irmin_config_free(IrminConfig* x981);
_Bool irmin_config_set(IrminConfig* x985, char* x984, IrminType* x983,
                       IrminValue* x982);
IrminPath* irmin_path(IrminRepo* x987, char** x986);
IrminPath* irmin_path_of_string(IrminRepo* x989, char* x988);
char* irmin_string_of_path(IrminRepo* x991, IrminPath* x990);
void irmin_path_free(IrminPath* x992);
void irmin_hash_free(IrminHash* x993);
char* irmin_hash_get_string(IrminRepo* x995, IrminHash* x994);
Irmin* irmin_main(IrminRepo* x996);
Irmin* irmin_of_branch(IrminRepo* x998, char* x997);
IrminCommit* irmin_get_head(Irmin* x999);
void irmin_set_head(Irmin* x1001, IrminCommit* x1000);
_Bool irmin_fast_forward(Irmin* x1003, IrminCommit* x1002);
_Bool irmin_merge_with_branch(Irmin* x1006, char* x1005, IrminInfo* x1004);
_Bool irmin_merge_with_commit(Irmin* x1009, IrminCommit* x1008,
                              IrminInfo* x1007);
_Bool irmin_set(Irmin* x1013, IrminPath* x1012, IrminValue* x1011,
                IrminInfo* x1010);
_Bool irmin_test_and_set(Irmin* x1018, IrminPath* x1017, IrminValue* x1016,
                         IrminValue* x1015, IrminInfo* x1014);
_Bool irmin_test_and_set_tree(Irmin* x1023, IrminPath* x1022,
                              IrminTree* x1021, IrminTree* x1020,
                              IrminInfo* x1019);
_Bool irmin_set_tree(Irmin* x1027, IrminPath* x1026, IrminTree* x1025,
                     IrminInfo* x1024);
IrminValue* irmin_find(Irmin* x1029, IrminPath* x1028);
IrminTree* irmin_find_tree(Irmin* x1031, IrminPath* x1030);
void irmin_remove(Irmin* x1034, IrminPath* x1033, IrminInfo* x1032);
_Bool irmin_mem(Irmin* x1036, IrminPath* x1035);
_Bool irmin_mem_tree(Irmin* x1038, IrminPath* x1037);
void irmin_free(Irmin* x1039);
IrminTree* irmin_tree_new(IrminRepo* x1040);
IrminTree* irmin_tree_clone(IrminRepo* x1042, IrminTree* x1041);
_Bool irmin_tree_mem(IrminRepo* x1045, IrminTree* x1044, IrminPath* x1043);
_Bool irmin_tree_mem_tree(IrminRepo* x1048, IrminTree* x1047,
                          IrminPath* x1046);
IrminValue* irmin_tree_find(IrminRepo* x1051, IrminTree* x1050,
                            IrminPath* x1049);
IrminTree* irmin_tree_find_tree(IrminRepo* x1054, IrminTree* x1053,
                                IrminPath* x1052);
void irmin_tree_add(IrminRepo* x1058, IrminTree* x1057, IrminPath* x1056,
                    IrminValue* x1055);
void irmin_tree_add_tree(IrminRepo* x1062, IrminTree* x1061,
                         IrminPath* x1060, IrminTree* x1059);
void irmin_tree_remove(IrminRepo* x1065, IrminTree* x1064, IrminPath* x1063);
void irmin_tree_free(IrminTree* x1066);
IrminRepo* irmin_repo_new(IrminConfig* x1067);
void irmin_repo_free(IrminRepo* x1068);
IrminInfo* irmin_commit_info(IrminRepo* x1070, IrminCommit* x1069);
IrminHash* irmin_commit_hash(IrminRepo* x1072, IrminCommit* x1071);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1074, IrminHash* x1073);
int irmin_commit_parents_length(IrminRepo* x1076, IrminCommit* x1075);
IrminCommit* irmin_commit_parent(IrminRepo* x1079, IrminCommit* x1078,
                                 int x1077);
void irmin_commit_free(IrminCommit* x1080);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(void**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
