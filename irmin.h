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
IrminType* irmin_type_list(IrminType* x1069);
IrminType* irmin_type_array(IrminType* x1070);
IrminType* irmin_type_option(IrminType* x1071);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1074);
IrminType* irmin_type_commit(IrminRepo* x1075);
IrminType* irmin_type_tree(IrminRepo* x1076);
IrminType* irmin_type_hash(IrminRepo* x1077);
IrminType* irmin_type_contents(IrminRepo* x1078);
IrminType* irmin_type_pair(IrminType* x1080, IrminType* x1079);
IrminType* irmin_type_triple(IrminType* x1083, IrminType* x1082,
                             IrminType* x1081);
char* irmin_type_name(IrminType* x1085, int* x1084);
void irmin_type_free(IrminType* x1086);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int x1088);
IrminValue* irmin_value_bool(_Bool x1089);
IrminValue* irmin_value_make(void* x1090);
IrminValue* irmin_value_string(char* x1092, int x1091);
char* irmin_value_get_string(IrminValue* x1094, int* x1093);
int irmin_value_get_int(IrminValue* x1095);
_Bool irmin_value_get_bool(IrminValue* x1096);
IrminValue* irmin_value_bytes(char* x1098, int x1097);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1101, IrminValue* x1100);
IrminValue* irmin_value_list_hd(IrminValue* x1102);
IrminValue* irmin_value_list_tl(IrminValue* x1103);
IrminValue* irmin_value_array_new(int x1105, IrminValue* x1104);
void irmin_value_array_set(IrminValue* x1108, int x1107, IrminValue* x1106);
IrminValue* irmin_value_array_get(IrminValue* x1110, int x1109);
IrminValue* irmin_value_option(IrminValue* x1111);
IrminValue* irmin_value_pair(IrminValue* x1113, IrminValue* x1112);
IrminValue* irmin_value_triple(IrminValue* x1116, IrminValue* x1115,
                               IrminValue* x1114);
char* irmin_value_to_string(IrminType* x1119, IrminValue* x1118, int* x1117);
IrminValue* irmin_value_of_string(IrminType* x1122, char* x1121, int x1120);
char* irmin_value_to_bin(IrminType* x1125, IrminValue* x1124, int* x1123);
IrminValue* irmin_value_of_bin(IrminType* x1128, char* x1127, int x1126);
char* irmin_value_to_json(IrminType* x1131, IrminValue* x1130, int* x1129);
IrminValue* irmin_value_of_json(IrminType* x1134, char* x1133, int x1132);
_Bool irmin_value_equal(IrminType* x1137, IrminValue* x1136,
                        IrminValue* x1135);
int irmin_value_compare(IrminType* x1140, IrminValue* x1139,
                        IrminValue* x1138);
void irmin_value_free(IrminValue* x1141);
IrminInfo* irmin_info_new(IrminRepo* x1144, char* x1143, char* x1142);
IrminInfo* irmin_info_update(IrminRepo* x1148, char* x1147, char* x1146,
                             IrminInfo* x1145);
char* irmin_info_message(IrminRepo* x1151, IrminInfo* x1150, int* x1149);
char* irmin_info_author(IrminRepo* x1154, IrminInfo* x1153, int* x1152);
int64_t irmin_info_date(IrminRepo* x1156, IrminInfo* x1155);
void irmin_info_free(IrminInfo* x1157);
void irmin_log_level(char* x1158);
IrminConfig* irmin_config_pack(char* x1160, char* x1159);
IrminConfig* irmin_config_git(char* x1161);
IrminConfig* irmin_config_git_mem(char* x1162);
IrminConfig* irmin_config_fs(char* x1164, char* x1163);
IrminConfig* irmin_config_mem(char* x1166, char* x1165);
void irmin_config_free(IrminConfig* x1167);
_Bool irmin_config_set(IrminConfig* x1171, char* x1170, IrminType* x1169,
                       IrminValue* x1168);
IrminPath* irmin_path(IrminRepo* x1173, char** x1172);
IrminPath* irmin_path_of_string(IrminRepo* x1176, char* x1175, int x1174);
char* irmin_path_to_string(IrminRepo* x1179, IrminPath* x1178, int* x1177);
IrminPath* irmin_path_parent(IrminRepo* x1181, IrminPath* x1180);
IrminPath* irmin_path_append(IrminRepo* x1185, IrminPath* x1184, char* x1183,
                             int x1182);
_Bool irmin_path_equal(IrminRepo* x1188, IrminPath* x1187, IrminPath* x1186);
void irmin_path_free(IrminPath* x1189);
void irmin_hash_free(IrminHash* x1190);
_Bool irmin_hash_equal(IrminRepo* x1193, IrminHash* x1192, IrminHash* x1191);
IrminHash* irmin_contents_hash(IrminRepo* x1195, IrminValue* x1194);
IrminValue* irmin_contents_of_hash(IrminRepo* x1197, IrminHash* x1196);
char* irmin_hash_to_string(IrminRepo* x1200, IrminHash* x1199, int* x1198);
IrminHash* irmin_hash_of_string(IrminRepo* x1203, char* x1202, int x1201);
Irmin* irmin_main(IrminRepo* x1204);
Irmin* irmin_of_branch(IrminRepo* x1206, char* x1205);
IrminCommit* irmin_get_head(Irmin* x1207);
void irmin_set_head(Irmin* x1209, IrminCommit* x1208);
_Bool irmin_fast_forward(Irmin* x1211, IrminCommit* x1210);
_Bool irmin_merge_with_branch(Irmin* x1214, char* x1213, IrminInfo* x1212);
_Bool irmin_merge_with_commit(Irmin* x1217, IrminCommit* x1216,
                              IrminInfo* x1215);
_Bool irmin_set(Irmin* x1221, IrminPath* x1220, IrminValue* x1219,
                IrminInfo* x1218);
_Bool irmin_test_and_set(Irmin* x1226, IrminPath* x1225, IrminValue* x1224,
                         IrminValue* x1223, IrminInfo* x1222);
_Bool irmin_test_and_set_tree(Irmin* x1231, IrminPath* x1230,
                              IrminTree* x1229, IrminTree* x1228,
                              IrminInfo* x1227);
_Bool irmin_set_tree(Irmin* x1235, IrminPath* x1234, IrminTree* x1233,
                     IrminInfo* x1232);
IrminValue* irmin_find(Irmin* x1237, IrminPath* x1236);
IrminTree* irmin_find_tree(Irmin* x1239, IrminPath* x1238);
void irmin_remove(Irmin* x1242, IrminPath* x1241, IrminInfo* x1240);
_Bool irmin_mem(Irmin* x1244, IrminPath* x1243);
_Bool irmin_mem_tree(Irmin* x1246, IrminPath* x1245);
void irmin_free(Irmin* x1247);
IrminTree* irmin_tree_new(IrminRepo* x1248);
IrminTree* irmin_tree_clone(IrminRepo* x1250, IrminTree* x1249);
_Bool irmin_tree_mem(IrminRepo* x1253, IrminTree* x1252, IrminPath* x1251);
_Bool irmin_tree_mem_tree(IrminRepo* x1256, IrminTree* x1255,
                          IrminPath* x1254);
IrminValue* irmin_tree_find(IrminRepo* x1259, IrminTree* x1258,
                            IrminPath* x1257);
IrminTree* irmin_tree_find_tree(IrminRepo* x1262, IrminTree* x1261,
                                IrminPath* x1260);
void irmin_tree_add(IrminRepo* x1266, IrminTree* x1265, IrminPath* x1264,
                    IrminValue* x1263);
void irmin_tree_add_tree(IrminRepo* x1270, IrminTree* x1269,
                         IrminPath* x1268, IrminTree* x1267);
void irmin_tree_remove(IrminRepo* x1273, IrminTree* x1272, IrminPath* x1271);
_Bool irmin_tree_equal(IrminRepo* x1276, IrminTree* x1275, IrminTree* x1274);
void irmin_tree_free(IrminTree* x1277);
IrminRepo* irmin_repo_new(IrminConfig* x1278);
void irmin_repo_free(IrminRepo* x1279);
IrminInfo* irmin_commit_info(IrminRepo* x1281, IrminCommit* x1280);
IrminHash* irmin_commit_hash(IrminRepo* x1283, IrminCommit* x1282);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1285, IrminHash* x1284);
IrminCommit* irmin_commit_new(IrminRepo* x1289, IrminCommit* x1288,
                              IrminTree* x1287, IrminInfo* x1286);
int irmin_commit_parents_length(IrminRepo* x1291, IrminCommit* x1290);
IrminCommit* irmin_commit_parent(IrminRepo* x1294, IrminCommit* x1293,
                                 int x1292);
_Bool irmin_commit_equal(IrminRepo* x1297, IrminCommit* x1296,
                         IrminCommit* x1295);
void irmin_commit_free(IrminCommit* x1298);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
