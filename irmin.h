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
IrminType* irmin_type_list(IrminType* x872);
IrminType* irmin_type_array(IrminType* x873);
IrminType* irmin_type_option(IrminType* x874);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x877);
IrminType* irmin_type_pair(IrminType* x879, IrminType* x878);
IrminType* irmin_type_triple(IrminType* x882, IrminType* x881,
                             IrminType* x880);
void irmin_type_free(IrminType* x883);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int x885);
IrminValue* irmin_value_bool(_Bool x886);
IrminValue* irmin_value_string(char* x887);
IrminValue* irmin_value_string_len(char* x889, int x888);
char* irmin_value_get_string(IrminValue* x891, int* x890);
int irmin_value_get_int(IrminValue* x892);
_Bool irmin_value_get_bool(IrminValue* x893);
IrminValue* irmin_value_bytes(char* x894);
IrminValue* irmin_value_bytes_len(char* x896, int x895);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x899, IrminValue* x898);
IrminValue* irmin_value_list_hd(IrminValue* x900);
IrminValue* irmin_value_list_tl(IrminValue* x901);
IrminValue* irmin_value_array_new(int x903, IrminValue* x902);
void irmin_value_array_set(IrminValue* x906, int x905, IrminValue* x904);
IrminValue* irmin_value_array_get(IrminValue* x908, int x907);
IrminValue* irmin_value_option(IrminValue* x909);
IrminValue* irmin_value_pair(IrminValue* x911, IrminValue* x910);
IrminValue* irmin_value_triple(IrminValue* x914, IrminValue* x913,
                               IrminValue* x912);
char* irmin_value_to_string(IrminType* x917, IrminValue* x916, int* x915);
IrminValue* irmin_value_of_string(IrminType* x920, char* x919, int x918);
char* irmin_value_to_bin(IrminValue* x922, int* x921);
IrminValue* irmin_value_of_bin(IrminType* x925, char* x924, int x923);
char* irmin_value_to_json(IrminValue* x927, int* x926);
IrminValue* irmin_value_of_json(IrminType* x930, char* x929, int x928);
void irmin_value_free(IrminValue* x931);
IrminInfo* irmin_info_new(IrminRepo* x934, char* x933, char* x932);
IrminInfo* irmin_info_update(IrminRepo* x938, char* x937, char* x936,
                             IrminInfo* x935);
char* irmin_info_message(IrminRepo* x940, IrminInfo* x939);
char* irmin_info_author(IrminRepo* x942, IrminInfo* x941);
int64_t irmin_info_date(IrminRepo* x944, IrminInfo* x943);
void irmin_info_free(IrminInfo* x945);
IrminConfig* irmin_config_pack(char* x947, char* x946);
IrminConfig* irmin_config_git(char* x948);
IrminConfig* irmin_config_git_mem(char* x949);
IrminConfig* irmin_config_fs(char* x951, char* x950);
IrminConfig* irmin_config_mem(char* x953, char* x952);
void irmin_config_free(IrminConfig* x954);
_Bool irmin_config_set(IrminConfig* x958, char* x957, IrminType* x956,
                       IrminValue* x955);
IrminPath* irmin_path(IrminRepo* x960, char** x959);
void irmin_path_free(IrminPath* x961);
void irmin_hash_free(IrminHash* x962);
char* irmin_hash_get_string(IrminRepo* x964, IrminHash* x963);
Irmin* irmin_main(IrminRepo* x965);
Irmin* irmin_of_branch(IrminRepo* x967, char* x966);
IrminCommit* irmin_get_head(Irmin* x968);
void irmin_set_head(Irmin* x970, IrminCommit* x969);
_Bool irmin_fast_forward(Irmin* x972, IrminCommit* x971);
_Bool irmin_merge_with_branch(Irmin* x975, char* x974, IrminInfo* x973);
_Bool irmin_merge_with_commit(Irmin* x978, IrminCommit* x977,
                              IrminInfo* x976);
_Bool irmin_set(Irmin* x982, IrminPath* x981, IrminValue* x980,
                IrminInfo* x979);
_Bool irmin_test_and_set(Irmin* x987, IrminPath* x986, IrminValue* x985,
                         IrminValue* x984, IrminInfo* x983);
_Bool irmin_test_and_set_tree(Irmin* x992, IrminPath* x991, IrminTree* x990,
                              IrminTree* x989, IrminInfo* x988);
_Bool irmin_set_tree(Irmin* x996, IrminPath* x995, IrminTree* x994,
                     IrminInfo* x993);
IrminValue* irmin_find(Irmin* x998, IrminPath* x997);
IrminTree* irmin_find_tree(Irmin* x1000, IrminPath* x999);
void irmin_remove(Irmin* x1003, IrminPath* x1002, IrminInfo* x1001);
_Bool irmin_mem(Irmin* x1005, IrminPath* x1004);
_Bool irmin_mem_tree(Irmin* x1007, IrminPath* x1006);
void irmin_free(Irmin* x1008);
IrminTree* irmin_tree_new(IrminRepo* x1009);
IrminTree* irmin_tree_clone(IrminRepo* x1011, IrminTree* x1010);
_Bool irmin_tree_mem(IrminRepo* x1014, IrminTree* x1013, IrminPath* x1012);
_Bool irmin_tree_mem_tree(IrminRepo* x1017, IrminTree* x1016,
                          IrminPath* x1015);
IrminValue* irmin_tree_find(IrminRepo* x1020, IrminTree* x1019,
                            IrminPath* x1018);
IrminTree* irmin_tree_find_tree(IrminRepo* x1023, IrminTree* x1022,
                                IrminPath* x1021);
void irmin_tree_add(IrminRepo* x1027, IrminTree* x1026, IrminPath* x1025,
                    IrminValue* x1024);
void irmin_tree_add_tree(IrminRepo* x1031, IrminTree* x1030,
                         IrminPath* x1029, IrminTree* x1028);
void irmin_tree_remove(IrminRepo* x1034, IrminTree* x1033, IrminPath* x1032);
void irmin_tree_free(IrminTree* x1035);
IrminRepo* irmin_repo_new(IrminConfig* x1036);
void irmin_repo_free(IrminRepo* x1037);
IrminInfo* irmin_commit_info(IrminRepo* x1039, IrminCommit* x1038);
IrminHash* irmin_commit_hash(IrminRepo* x1041, IrminCommit* x1040);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1043, IrminHash* x1042);
int irmin_commit_parents_length(IrminRepo* x1045, IrminCommit* x1044);
IrminCommit* irmin_commit_parent(IrminRepo* x1048, IrminCommit* x1047,
                                 int x1046);
void irmin_commit_free(IrminCommit* x1049);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(void**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
