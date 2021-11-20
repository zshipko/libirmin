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
IrminType* irmin_type_list(IrminType* x1012);
IrminType* irmin_type_array(IrminType* x1013);
IrminType* irmin_type_option(IrminType* x1014);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1017);
IrminType* irmin_type_commit(IrminRepo* x1018);
IrminType* irmin_type_tree(IrminRepo* x1019);
IrminType* irmin_type_hash(IrminRepo* x1020);
IrminType* irmin_type_contents(IrminRepo* x1021);
IrminType* irmin_type_pair(IrminType* x1023, IrminType* x1022);
IrminType* irmin_type_triple(IrminType* x1026, IrminType* x1025,
                             IrminType* x1024);
char* irmin_type_name(IrminType* x1028, int* x1027);
void irmin_type_free(IrminType* x1029);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int x1031);
IrminValue* irmin_value_bool(_Bool x1032);
IrminValue* irmin_value_string(char* x1034, int x1033);
char* irmin_value_get_string(IrminValue* x1036, int* x1035);
int irmin_value_get_int(IrminValue* x1037);
_Bool irmin_value_get_bool(IrminValue* x1038);
IrminValue* irmin_value_bytes(char* x1040, int x1039);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1043, IrminValue* x1042);
IrminValue* irmin_value_list_hd(IrminValue* x1044);
IrminValue* irmin_value_list_tl(IrminValue* x1045);
IrminValue* irmin_value_array_new(int x1047, IrminValue* x1046);
void irmin_value_array_set(IrminValue* x1050, int x1049, IrminValue* x1048);
IrminValue* irmin_value_array_get(IrminValue* x1052, int x1051);
IrminValue* irmin_value_option(IrminValue* x1053);
IrminValue* irmin_value_pair(IrminValue* x1055, IrminValue* x1054);
IrminValue* irmin_value_triple(IrminValue* x1058, IrminValue* x1057,
                               IrminValue* x1056);
char* irmin_value_to_string(IrminType* x1061, IrminValue* x1060, int* x1059);
IrminValue* irmin_value_of_string(IrminType* x1064, char* x1063, int x1062);
char* irmin_value_to_bin(IrminType* x1067, IrminValue* x1066, int* x1065);
IrminValue* irmin_value_of_bin(IrminType* x1070, char* x1069, int x1068);
char* irmin_value_to_json(IrminType* x1073, IrminValue* x1072, int* x1071);
IrminValue* irmin_value_of_json(IrminType* x1076, char* x1075, int x1074);
_Bool irmin_value_equal(IrminType* x1079, IrminValue* x1078,
                        IrminValue* x1077);
int irmin_value_compare(IrminType* x1082, IrminValue* x1081,
                        IrminValue* x1080);
void irmin_value_free(IrminValue* x1083);
IrminInfo* irmin_info_new(IrminRepo* x1086, char* x1085, char* x1084);
IrminInfo* irmin_info_update(IrminRepo* x1090, char* x1089, char* x1088,
                             IrminInfo* x1087);
char* irmin_info_message(IrminRepo* x1093, IrminInfo* x1092, int* x1091);
char* irmin_info_author(IrminRepo* x1096, IrminInfo* x1095, int* x1094);
int64_t irmin_info_date(IrminRepo* x1098, IrminInfo* x1097);
void irmin_info_free(IrminInfo* x1099);
void irmin_log_level(char* x1100);
IrminConfig* irmin_config_pack(char* x1102, char* x1101);
IrminConfig* irmin_config_git(char* x1103);
IrminConfig* irmin_config_git_mem(char* x1104);
IrminConfig* irmin_config_fs(char* x1106, char* x1105);
IrminConfig* irmin_config_mem(char* x1108, char* x1107);
void irmin_config_free(IrminConfig* x1109);
_Bool irmin_config_set(IrminConfig* x1113, char* x1112, IrminType* x1111,
                       IrminValue* x1110);
IrminPath* irmin_path(IrminRepo* x1115, char** x1114);
IrminPath* irmin_path_of_string(IrminRepo* x1118, char* x1117, int x1116);
char* irmin_path_to_string(IrminRepo* x1121, IrminPath* x1120, int* x1119);
_Bool irmin_path_equal(IrminRepo* x1124, IrminPath* x1123, IrminPath* x1122);
void irmin_path_free(IrminPath* x1125);
void irmin_hash_free(IrminHash* x1126);
_Bool irmin_hash_equal(IrminRepo* x1129, IrminHash* x1128, IrminHash* x1127);
char* irmin_hash_to_string(IrminRepo* x1132, IrminHash* x1131, int* x1130);
IrminHash* irmin_hash_of_string(IrminRepo* x1135, char* x1134, int x1133);
Irmin* irmin_main(IrminRepo* x1136);
Irmin* irmin_of_branch(IrminRepo* x1138, char* x1137);
IrminCommit* irmin_get_head(Irmin* x1139);
void irmin_set_head(Irmin* x1141, IrminCommit* x1140);
_Bool irmin_fast_forward(Irmin* x1143, IrminCommit* x1142);
_Bool irmin_merge_with_branch(Irmin* x1146, char* x1145, IrminInfo* x1144);
_Bool irmin_merge_with_commit(Irmin* x1149, IrminCommit* x1148,
                              IrminInfo* x1147);
_Bool irmin_set(Irmin* x1153, IrminPath* x1152, IrminValue* x1151,
                IrminInfo* x1150);
_Bool irmin_test_and_set(Irmin* x1158, IrminPath* x1157, IrminValue* x1156,
                         IrminValue* x1155, IrminInfo* x1154);
_Bool irmin_test_and_set_tree(Irmin* x1163, IrminPath* x1162,
                              IrminTree* x1161, IrminTree* x1160,
                              IrminInfo* x1159);
_Bool irmin_set_tree(Irmin* x1167, IrminPath* x1166, IrminTree* x1165,
                     IrminInfo* x1164);
IrminValue* irmin_find(Irmin* x1169, IrminPath* x1168);
IrminTree* irmin_find_tree(Irmin* x1171, IrminPath* x1170);
void irmin_remove(Irmin* x1174, IrminPath* x1173, IrminInfo* x1172);
_Bool irmin_mem(Irmin* x1176, IrminPath* x1175);
_Bool irmin_mem_tree(Irmin* x1178, IrminPath* x1177);
void irmin_free(Irmin* x1179);
IrminTree* irmin_tree_new(IrminRepo* x1180);
IrminTree* irmin_tree_clone(IrminRepo* x1182, IrminTree* x1181);
_Bool irmin_tree_mem(IrminRepo* x1185, IrminTree* x1184, IrminPath* x1183);
_Bool irmin_tree_mem_tree(IrminRepo* x1188, IrminTree* x1187,
                          IrminPath* x1186);
IrminValue* irmin_tree_find(IrminRepo* x1191, IrminTree* x1190,
                            IrminPath* x1189);
IrminTree* irmin_tree_find_tree(IrminRepo* x1194, IrminTree* x1193,
                                IrminPath* x1192);
void irmin_tree_add(IrminRepo* x1198, IrminTree* x1197, IrminPath* x1196,
                    IrminValue* x1195);
void irmin_tree_add_tree(IrminRepo* x1202, IrminTree* x1201,
                         IrminPath* x1200, IrminTree* x1199);
void irmin_tree_remove(IrminRepo* x1205, IrminTree* x1204, IrminPath* x1203);
_Bool irmin_tree_equal(IrminRepo* x1208, IrminTree* x1207, IrminTree* x1206);
void irmin_tree_free(IrminTree* x1209);
IrminRepo* irmin_repo_new(IrminConfig* x1210);
void irmin_repo_free(IrminRepo* x1211);
IrminInfo* irmin_commit_info(IrminRepo* x1213, IrminCommit* x1212);
IrminHash* irmin_commit_hash(IrminRepo* x1215, IrminCommit* x1214);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1217, IrminHash* x1216);
int irmin_commit_parents_length(IrminRepo* x1219, IrminCommit* x1218);
IrminCommit* irmin_commit_parent(IrminRepo* x1222, IrminCommit* x1221,
                                 int x1220);
_Bool irmin_commit_equal(IrminRepo* x1225, IrminCommit* x1224,
                         IrminCommit* x1223);
void irmin_commit_free(IrminCommit* x1226);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
