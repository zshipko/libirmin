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
void caml_startup(char *argv[]);
void caml_shutdown();
IrminType* irmin_type_unit(void);
IrminType* irmin_type_bool(void);
IrminType* irmin_type_int(void);
IrminType* irmin_type_string(void);
IrminType* irmin_type_bytes(void);
IrminType* irmin_type_list(IrminType* x1040);
IrminType* irmin_type_array(IrminType* x1041);
IrminType* irmin_type_option(IrminType* x1042);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1045);
IrminType* irmin_type_commit(IrminRepo* x1046);
IrminType* irmin_type_tree(IrminRepo* x1047);
IrminType* irmin_type_hash(IrminRepo* x1048);
IrminType* irmin_type_contents(IrminRepo* x1049);
IrminType* irmin_type_pair(IrminType* x1051, IrminType* x1050);
IrminType* irmin_type_triple(IrminType* x1054, IrminType* x1053,
                             IrminType* x1052);
char* irmin_type_name(IrminType* x1056, int* x1055);
void irmin_type_free(IrminType* x1057);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int x1059);
IrminValue* irmin_value_bool(_Bool x1060);
IrminValue* irmin_value_make(void* x1061);
IrminValue* irmin_value_string(char* x1063, int x1062);
char* irmin_value_get_string(IrminValue* x1065, int* x1064);
int irmin_value_get_int(IrminValue* x1066);
_Bool irmin_value_get_bool(IrminValue* x1067);
IrminValue* irmin_value_bytes(char* x1069, int x1068);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1072, IrminValue* x1071);
IrminValue* irmin_value_list_hd(IrminValue* x1073);
IrminValue* irmin_value_list_tl(IrminValue* x1074);
IrminValue* irmin_value_array_new(int x1076, IrminValue* x1075);
void irmin_value_array_set(IrminValue* x1079, int x1078, IrminValue* x1077);
IrminValue* irmin_value_array_get(IrminValue* x1081, int x1080);
IrminValue* irmin_value_option(IrminValue* x1082);
IrminValue* irmin_value_pair(IrminValue* x1084, IrminValue* x1083);
IrminValue* irmin_value_triple(IrminValue* x1087, IrminValue* x1086,
                               IrminValue* x1085);
char* irmin_value_to_string(IrminType* x1090, IrminValue* x1089, int* x1088);
IrminValue* irmin_value_of_string(IrminType* x1093, char* x1092, int x1091);
char* irmin_value_to_bin(IrminType* x1096, IrminValue* x1095, int* x1094);
IrminValue* irmin_value_of_bin(IrminType* x1099, char* x1098, int x1097);
char* irmin_value_to_json(IrminType* x1102, IrminValue* x1101, int* x1100);
IrminValue* irmin_value_of_json(IrminType* x1105, char* x1104, int x1103);
_Bool irmin_value_equal(IrminType* x1108, IrminValue* x1107,
                        IrminValue* x1106);
int irmin_value_compare(IrminType* x1111, IrminValue* x1110,
                        IrminValue* x1109);
void irmin_value_free(IrminValue* x1112);
IrminInfo* irmin_info_new(IrminRepo* x1115, char* x1114, char* x1113);
IrminInfo* irmin_info_update(IrminRepo* x1119, char* x1118, char* x1117,
                             IrminInfo* x1116);
char* irmin_info_message(IrminRepo* x1122, IrminInfo* x1121, int* x1120);
char* irmin_info_author(IrminRepo* x1125, IrminInfo* x1124, int* x1123);
int64_t irmin_info_date(IrminRepo* x1127, IrminInfo* x1126);
void irmin_info_free(IrminInfo* x1128);
void irmin_log_level(char* x1129);
IrminConfig* irmin_config_pack(char* x1131, char* x1130);
IrminConfig* irmin_config_git(char* x1132);
IrminConfig* irmin_config_git_mem(char* x1133);
IrminConfig* irmin_config_fs(char* x1135, char* x1134);
IrminConfig* irmin_config_mem(char* x1137, char* x1136);
void irmin_config_free(IrminConfig* x1138);
_Bool irmin_config_set(IrminConfig* x1142, char* x1141, IrminType* x1140,
                       IrminValue* x1139);
IrminPath* irmin_path(IrminRepo* x1144, char** x1143);
IrminPath* irmin_path_of_string(IrminRepo* x1147, char* x1146, int x1145);
char* irmin_path_to_string(IrminRepo* x1150, IrminPath* x1149, int* x1148);
IrminPath* irmin_path_parent(IrminRepo* x1152, IrminPath* x1151);
IrminPath* irmin_path_append(IrminRepo* x1156, IrminPath* x1155, char* x1154,
                             int x1153);
_Bool irmin_path_equal(IrminRepo* x1159, IrminPath* x1158, IrminPath* x1157);
void irmin_path_free(IrminPath* x1160);
void irmin_hash_free(IrminHash* x1161);
_Bool irmin_hash_equal(IrminRepo* x1164, IrminHash* x1163, IrminHash* x1162);
char* irmin_hash_to_string(IrminRepo* x1167, IrminHash* x1166, int* x1165);
IrminHash* irmin_hash_of_string(IrminRepo* x1170, char* x1169, int x1168);
Irmin* irmin_main(IrminRepo* x1171);
Irmin* irmin_of_branch(IrminRepo* x1173, char* x1172);
IrminCommit* irmin_get_head(Irmin* x1174);
void irmin_set_head(Irmin* x1176, IrminCommit* x1175);
_Bool irmin_fast_forward(Irmin* x1178, IrminCommit* x1177);
_Bool irmin_merge_with_branch(Irmin* x1181, char* x1180, IrminInfo* x1179);
_Bool irmin_merge_with_commit(Irmin* x1184, IrminCommit* x1183,
                              IrminInfo* x1182);
_Bool irmin_set(Irmin* x1188, IrminPath* x1187, IrminValue* x1186,
                IrminInfo* x1185);
_Bool irmin_test_and_set(Irmin* x1193, IrminPath* x1192, IrminValue* x1191,
                         IrminValue* x1190, IrminInfo* x1189);
_Bool irmin_test_and_set_tree(Irmin* x1198, IrminPath* x1197,
                              IrminTree* x1196, IrminTree* x1195,
                              IrminInfo* x1194);
_Bool irmin_set_tree(Irmin* x1202, IrminPath* x1201, IrminTree* x1200,
                     IrminInfo* x1199);
IrminValue* irmin_find(Irmin* x1204, IrminPath* x1203);
IrminTree* irmin_find_tree(Irmin* x1206, IrminPath* x1205);
void irmin_remove(Irmin* x1209, IrminPath* x1208, IrminInfo* x1207);
_Bool irmin_mem(Irmin* x1211, IrminPath* x1210);
_Bool irmin_mem_tree(Irmin* x1213, IrminPath* x1212);
void irmin_free(Irmin* x1214);
IrminTree* irmin_tree_new(IrminRepo* x1215);
IrminTree* irmin_tree_clone(IrminRepo* x1217, IrminTree* x1216);
_Bool irmin_tree_mem(IrminRepo* x1220, IrminTree* x1219, IrminPath* x1218);
_Bool irmin_tree_mem_tree(IrminRepo* x1223, IrminTree* x1222,
                          IrminPath* x1221);
IrminValue* irmin_tree_find(IrminRepo* x1226, IrminTree* x1225,
                            IrminPath* x1224);
IrminTree* irmin_tree_find_tree(IrminRepo* x1229, IrminTree* x1228,
                                IrminPath* x1227);
void irmin_tree_add(IrminRepo* x1233, IrminTree* x1232, IrminPath* x1231,
                    IrminValue* x1230);
void irmin_tree_add_tree(IrminRepo* x1237, IrminTree* x1236,
                         IrminPath* x1235, IrminTree* x1234);
void irmin_tree_remove(IrminRepo* x1240, IrminTree* x1239, IrminPath* x1238);
_Bool irmin_tree_equal(IrminRepo* x1243, IrminTree* x1242, IrminTree* x1241);
void irmin_tree_free(IrminTree* x1244);
IrminRepo* irmin_repo_new(IrminConfig* x1245);
void irmin_repo_free(IrminRepo* x1246);
IrminInfo* irmin_commit_info(IrminRepo* x1248, IrminCommit* x1247);
IrminHash* irmin_commit_hash(IrminRepo* x1250, IrminCommit* x1249);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1252, IrminHash* x1251);
int irmin_commit_parents_length(IrminRepo* x1254, IrminCommit* x1253);
IrminCommit* irmin_commit_parent(IrminRepo* x1257, IrminCommit* x1256,
                                 int x1255);
_Bool irmin_commit_equal(IrminRepo* x1260, IrminCommit* x1259,
                         IrminCommit* x1258);
void irmin_commit_free(IrminCommit* x1261);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
