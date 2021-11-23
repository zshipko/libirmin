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
IrminType* irmin_type_list(IrminType* x1020);
IrminType* irmin_type_array(IrminType* x1021);
IrminType* irmin_type_option(IrminType* x1022);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1025);
IrminType* irmin_type_commit(IrminRepo* x1026);
IrminType* irmin_type_tree(IrminRepo* x1027);
IrminType* irmin_type_hash(IrminRepo* x1028);
IrminType* irmin_type_contents(IrminRepo* x1029);
IrminType* irmin_type_pair(IrminType* x1031, IrminType* x1030);
IrminType* irmin_type_triple(IrminType* x1034, IrminType* x1033,
                             IrminType* x1032);
char* irmin_type_name(IrminType* x1036, int* x1035);
void irmin_type_free(IrminType* x1037);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int x1039);
IrminValue* irmin_value_bool(_Bool x1040);
IrminValue* irmin_value_make(void* x1041);
IrminValue* irmin_value_string(char* x1043, int x1042);
char* irmin_value_get_string(IrminValue* x1045, int* x1044);
int irmin_value_get_int(IrminValue* x1046);
_Bool irmin_value_get_bool(IrminValue* x1047);
IrminValue* irmin_value_bytes(char* x1049, int x1048);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1052, IrminValue* x1051);
IrminValue* irmin_value_list_hd(IrminValue* x1053);
IrminValue* irmin_value_list_tl(IrminValue* x1054);
IrminValue* irmin_value_array_new(int x1056, IrminValue* x1055);
void irmin_value_array_set(IrminValue* x1059, int x1058, IrminValue* x1057);
IrminValue* irmin_value_array_get(IrminValue* x1061, int x1060);
IrminValue* irmin_value_option(IrminValue* x1062);
IrminValue* irmin_value_pair(IrminValue* x1064, IrminValue* x1063);
IrminValue* irmin_value_triple(IrminValue* x1067, IrminValue* x1066,
                               IrminValue* x1065);
char* irmin_value_to_string(IrminType* x1070, IrminValue* x1069, int* x1068);
IrminValue* irmin_value_of_string(IrminType* x1073, char* x1072, int x1071);
char* irmin_value_to_bin(IrminType* x1076, IrminValue* x1075, int* x1074);
IrminValue* irmin_value_of_bin(IrminType* x1079, char* x1078, int x1077);
char* irmin_value_to_json(IrminType* x1082, IrminValue* x1081, int* x1080);
IrminValue* irmin_value_of_json(IrminType* x1085, char* x1084, int x1083);
_Bool irmin_value_equal(IrminType* x1088, IrminValue* x1087,
                        IrminValue* x1086);
int irmin_value_compare(IrminType* x1091, IrminValue* x1090,
                        IrminValue* x1089);
void irmin_value_free(IrminValue* x1092);
IrminInfo* irmin_info_new(IrminRepo* x1095, char* x1094, char* x1093);
IrminInfo* irmin_info_update(IrminRepo* x1099, char* x1098, char* x1097,
                             IrminInfo* x1096);
char* irmin_info_message(IrminRepo* x1102, IrminInfo* x1101, int* x1100);
char* irmin_info_author(IrminRepo* x1105, IrminInfo* x1104, int* x1103);
int64_t irmin_info_date(IrminRepo* x1107, IrminInfo* x1106);
void irmin_info_free(IrminInfo* x1108);
void irmin_log_level(char* x1109);
IrminConfig* irmin_config_pack(char* x1111, char* x1110);
IrminConfig* irmin_config_git(char* x1112);
IrminConfig* irmin_config_git_mem(char* x1113);
IrminConfig* irmin_config_fs(char* x1115, char* x1114);
IrminConfig* irmin_config_mem(char* x1117, char* x1116);
void irmin_config_free(IrminConfig* x1118);
_Bool irmin_config_set(IrminConfig* x1122, char* x1121, IrminType* x1120,
                       IrminValue* x1119);
IrminPath* irmin_path(IrminRepo* x1124, char** x1123);
IrminPath* irmin_path_of_string(IrminRepo* x1127, char* x1126, int x1125);
char* irmin_path_to_string(IrminRepo* x1130, IrminPath* x1129, int* x1128);
_Bool irmin_path_equal(IrminRepo* x1133, IrminPath* x1132, IrminPath* x1131);
void irmin_path_free(IrminPath* x1134);
void irmin_hash_free(IrminHash* x1135);
_Bool irmin_hash_equal(IrminRepo* x1138, IrminHash* x1137, IrminHash* x1136);
char* irmin_hash_to_string(IrminRepo* x1141, IrminHash* x1140, int* x1139);
IrminHash* irmin_hash_of_string(IrminRepo* x1144, char* x1143, int x1142);
Irmin* irmin_main(IrminRepo* x1145);
Irmin* irmin_of_branch(IrminRepo* x1147, char* x1146);
IrminCommit* irmin_get_head(Irmin* x1148);
void irmin_set_head(Irmin* x1150, IrminCommit* x1149);
_Bool irmin_fast_forward(Irmin* x1152, IrminCommit* x1151);
_Bool irmin_merge_with_branch(Irmin* x1155, char* x1154, IrminInfo* x1153);
_Bool irmin_merge_with_commit(Irmin* x1158, IrminCommit* x1157,
                              IrminInfo* x1156);
_Bool irmin_set(Irmin* x1162, IrminPath* x1161, IrminValue* x1160,
                IrminInfo* x1159);
_Bool irmin_test_and_set(Irmin* x1167, IrminPath* x1166, IrminValue* x1165,
                         IrminValue* x1164, IrminInfo* x1163);
_Bool irmin_test_and_set_tree(Irmin* x1172, IrminPath* x1171,
                              IrminTree* x1170, IrminTree* x1169,
                              IrminInfo* x1168);
_Bool irmin_set_tree(Irmin* x1176, IrminPath* x1175, IrminTree* x1174,
                     IrminInfo* x1173);
IrminValue* irmin_find(Irmin* x1178, IrminPath* x1177);
IrminTree* irmin_find_tree(Irmin* x1180, IrminPath* x1179);
void irmin_remove(Irmin* x1183, IrminPath* x1182, IrminInfo* x1181);
_Bool irmin_mem(Irmin* x1185, IrminPath* x1184);
_Bool irmin_mem_tree(Irmin* x1187, IrminPath* x1186);
void irmin_free(Irmin* x1188);
IrminTree* irmin_tree_new(IrminRepo* x1189);
IrminTree* irmin_tree_clone(IrminRepo* x1191, IrminTree* x1190);
_Bool irmin_tree_mem(IrminRepo* x1194, IrminTree* x1193, IrminPath* x1192);
_Bool irmin_tree_mem_tree(IrminRepo* x1197, IrminTree* x1196,
                          IrminPath* x1195);
IrminValue* irmin_tree_find(IrminRepo* x1200, IrminTree* x1199,
                            IrminPath* x1198);
IrminTree* irmin_tree_find_tree(IrminRepo* x1203, IrminTree* x1202,
                                IrminPath* x1201);
void irmin_tree_add(IrminRepo* x1207, IrminTree* x1206, IrminPath* x1205,
                    IrminValue* x1204);
void irmin_tree_add_tree(IrminRepo* x1211, IrminTree* x1210,
                         IrminPath* x1209, IrminTree* x1208);
void irmin_tree_remove(IrminRepo* x1214, IrminTree* x1213, IrminPath* x1212);
_Bool irmin_tree_equal(IrminRepo* x1217, IrminTree* x1216, IrminTree* x1215);
void irmin_tree_free(IrminTree* x1218);
IrminRepo* irmin_repo_new(IrminConfig* x1219);
void irmin_repo_free(IrminRepo* x1220);
IrminInfo* irmin_commit_info(IrminRepo* x1222, IrminCommit* x1221);
IrminHash* irmin_commit_hash(IrminRepo* x1224, IrminCommit* x1223);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1226, IrminHash* x1225);
int irmin_commit_parents_length(IrminRepo* x1228, IrminCommit* x1227);
IrminCommit* irmin_commit_parent(IrminRepo* x1231, IrminCommit* x1230,
                                 int x1229);
_Bool irmin_commit_equal(IrminRepo* x1234, IrminCommit* x1233,
                         IrminCommit* x1232);
void irmin_commit_free(IrminCommit* x1235);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
