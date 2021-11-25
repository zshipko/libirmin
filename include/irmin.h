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
IrminType* irmin_type_float(void);
IrminType* irmin_type_string(void);
IrminType* irmin_type_bytes(void);
IrminType* irmin_type_list(IrminType* x1097);
IrminType* irmin_type_array(IrminType* x1098);
IrminType* irmin_type_option(IrminType* x1099);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1102);
IrminType* irmin_type_commit(IrminRepo* x1103);
IrminType* irmin_type_tree(IrminRepo* x1104);
IrminType* irmin_type_hash(IrminRepo* x1105);
IrminType* irmin_type_contents(IrminRepo* x1106);
IrminType* irmin_type_pair(IrminType* x1108, IrminType* x1107);
IrminType* irmin_type_triple(IrminType* x1111, IrminType* x1110,
                             IrminType* x1109);
char* irmin_type_name(IrminType* x1113, int* x1112);
void irmin_type_free(IrminType* x1114);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int x1116);
IrminValue* irmin_value_float(float x1117);
IrminValue* irmin_value_bool(_Bool x1118);
IrminValue* irmin_value_make(void* x1119);
IrminValue* irmin_value_string(char* x1121, int x1120);
char* irmin_value_get_string(IrminValue* x1123, int* x1122);
int irmin_value_get_int(IrminValue* x1124);
_Bool irmin_value_get_bool(IrminValue* x1125);
float irmin_value_get_float(IrminValue* x1126);
IrminValue* irmin_value_bytes(char* x1128, int x1127);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1131, IrminValue* x1130);
IrminValue* irmin_value_list_hd(IrminValue* x1132);
IrminValue* irmin_value_list_tl(IrminValue* x1133);
IrminValue* irmin_value_array_new(int x1135, IrminValue* x1134);
void irmin_value_array_set(IrminValue* x1138, int x1137, IrminValue* x1136);
IrminValue* irmin_value_array_get(IrminValue* x1140, int x1139);
IrminValue* irmin_value_option(IrminValue* x1141);
IrminValue* irmin_value_pair(IrminValue* x1143, IrminValue* x1142);
IrminValue* irmin_value_triple(IrminValue* x1146, IrminValue* x1145,
                               IrminValue* x1144);
char* irmin_value_to_string(IrminType* x1149, IrminValue* x1148, int* x1147);
IrminValue* irmin_value_of_string(IrminType* x1152, char* x1151, int x1150);
char* irmin_value_to_bin(IrminType* x1155, IrminValue* x1154, int* x1153);
IrminValue* irmin_value_of_bin(IrminType* x1158, char* x1157, int x1156);
char* irmin_value_to_json(IrminType* x1161, IrminValue* x1160, int* x1159);
IrminValue* irmin_value_of_json(IrminType* x1164, char* x1163, int x1162);
_Bool irmin_value_equal(IrminType* x1167, IrminValue* x1166,
                        IrminValue* x1165);
int irmin_value_compare(IrminType* x1170, IrminValue* x1169,
                        IrminValue* x1168);
void irmin_value_free(IrminValue* x1171);
IrminInfo* irmin_info_new(IrminRepo* x1174, char* x1173, char* x1172);
IrminInfo* irmin_info_update(IrminRepo* x1178, char* x1177, char* x1176,
                             IrminInfo* x1175);
char* irmin_info_message(IrminRepo* x1181, IrminInfo* x1180, int* x1179);
char* irmin_info_author(IrminRepo* x1184, IrminInfo* x1183, int* x1182);
int64_t irmin_info_date(IrminRepo* x1186, IrminInfo* x1185);
void irmin_info_free(IrminInfo* x1187);
void irmin_log_level(char* x1188);
IrminConfig* irmin_config_pack(char* x1190, char* x1189);
IrminConfig* irmin_config_git(char* x1191);
IrminConfig* irmin_config_git_mem(char* x1192);
IrminConfig* irmin_config_fs(char* x1194, char* x1193);
IrminConfig* irmin_config_mem(char* x1196, char* x1195);
void irmin_config_free(IrminConfig* x1197);
_Bool irmin_config_set(IrminConfig* x1201, char* x1200, IrminType* x1199,
                       IrminValue* x1198);
IrminPath* irmin_path(IrminRepo* x1203, char** x1202);
IrminPath* irmin_path_of_string(IrminRepo* x1206, char* x1205, int x1204);
char* irmin_path_to_string(IrminRepo* x1209, IrminPath* x1208, int* x1207);
IrminPath* irmin_path_parent(IrminRepo* x1211, IrminPath* x1210);
IrminPath* irmin_path_append(IrminRepo* x1215, IrminPath* x1214, char* x1213,
                             int x1212);
_Bool irmin_path_equal(IrminRepo* x1218, IrminPath* x1217, IrminPath* x1216);
void irmin_path_free(IrminPath* x1219);
void irmin_hash_free(IrminHash* x1220);
_Bool irmin_hash_equal(IrminRepo* x1223, IrminHash* x1222, IrminHash* x1221);
IrminHash* irmin_contents_hash(IrminRepo* x1225, IrminValue* x1224);
IrminValue* irmin_contents_of_hash(IrminRepo* x1227, IrminHash* x1226);
char* irmin_hash_to_string(IrminRepo* x1230, IrminHash* x1229, int* x1228);
IrminHash* irmin_hash_of_string(IrminRepo* x1233, char* x1232, int x1231);
Irmin* irmin_main(IrminRepo* x1234);
Irmin* irmin_of_branch(IrminRepo* x1236, char* x1235);
IrminCommit* irmin_get_head(Irmin* x1237);
void irmin_set_head(Irmin* x1239, IrminCommit* x1238);
_Bool irmin_fast_forward(Irmin* x1241, IrminCommit* x1240);
_Bool irmin_merge_with_branch(Irmin* x1244, char* x1243, IrminInfo* x1242);
_Bool irmin_merge_with_commit(Irmin* x1247, IrminCommit* x1246,
                              IrminInfo* x1245);
_Bool irmin_set(Irmin* x1251, IrminPath* x1250, IrminValue* x1249,
                IrminInfo* x1248);
_Bool irmin_test_and_set(Irmin* x1256, IrminPath* x1255, IrminValue* x1254,
                         IrminValue* x1253, IrminInfo* x1252);
_Bool irmin_test_and_set_tree(Irmin* x1261, IrminPath* x1260,
                              IrminTree* x1259, IrminTree* x1258,
                              IrminInfo* x1257);
_Bool irmin_set_tree(Irmin* x1265, IrminPath* x1264, IrminTree* x1263,
                     IrminInfo* x1262);
IrminValue* irmin_find(Irmin* x1267, IrminPath* x1266);
IrminTree* irmin_find_tree(Irmin* x1269, IrminPath* x1268);
void irmin_remove(Irmin* x1272, IrminPath* x1271, IrminInfo* x1270);
_Bool irmin_mem(Irmin* x1274, IrminPath* x1273);
_Bool irmin_mem_tree(Irmin* x1276, IrminPath* x1275);
void irmin_free(Irmin* x1277);
IrminTree* irmin_tree_new(IrminRepo* x1278);
IrminTree* irmin_tree_clone(IrminRepo* x1280, IrminTree* x1279);
_Bool irmin_tree_mem(IrminRepo* x1283, IrminTree* x1282, IrminPath* x1281);
_Bool irmin_tree_mem_tree(IrminRepo* x1286, IrminTree* x1285,
                          IrminPath* x1284);
IrminValue* irmin_tree_find(IrminRepo* x1289, IrminTree* x1288,
                            IrminPath* x1287);
IrminTree* irmin_tree_find_tree(IrminRepo* x1292, IrminTree* x1291,
                                IrminPath* x1290);
void irmin_tree_add(IrminRepo* x1296, IrminTree* x1295, IrminPath* x1294,
                    IrminValue* x1293);
void irmin_tree_add_tree(IrminRepo* x1300, IrminTree* x1299,
                         IrminPath* x1298, IrminTree* x1297);
void irmin_tree_remove(IrminRepo* x1303, IrminTree* x1302, IrminPath* x1301);
_Bool irmin_tree_equal(IrminRepo* x1306, IrminTree* x1305, IrminTree* x1304);
void irmin_tree_free(IrminTree* x1307);
IrminRepo* irmin_repo_new(IrminConfig* x1308);
void irmin_repo_free(IrminRepo* x1309);
IrminInfo* irmin_commit_info(IrminRepo* x1311, IrminCommit* x1310);
IrminHash* irmin_commit_hash(IrminRepo* x1313, IrminCommit* x1312);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1315, IrminHash* x1314);
IrminCommit* irmin_commit_new(IrminRepo* x1320, IrminCommit** x1319,
                              int x1318, IrminTree* x1317, IrminInfo* x1316);
int irmin_commit_parents_length(IrminRepo* x1322, IrminCommit* x1321);
IrminCommit* irmin_commit_parent(IrminRepo* x1325, IrminCommit* x1324,
                                 int x1323);
_Bool irmin_commit_equal(IrminRepo* x1328, IrminCommit* x1327,
                         IrminCommit* x1326);
void irmin_commit_free(IrminCommit* x1329);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
