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
typedef struct IrminString IrminString;
void caml_startup(char *argv[]);
void caml_shutdown();
IrminType* irmin_type_unit(void);
IrminType* irmin_type_bool(void);
IrminType* irmin_type_int(void);
IrminType* irmin_type_float(void);
IrminType* irmin_type_string(void);
IrminType* irmin_type_bytes(void);
IrminType* irmin_type_list(IrminType* x1159);
IrminType* irmin_type_array(IrminType* x1160);
IrminType* irmin_type_option(IrminType* x1161);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1164);
IrminType* irmin_type_commit(IrminRepo* x1165);
IrminType* irmin_type_tree(IrminRepo* x1166);
IrminType* irmin_type_hash(IrminRepo* x1167);
IrminType* irmin_type_contents(IrminRepo* x1168);
IrminType* irmin_type_pair(IrminType* x1170, IrminType* x1169);
IrminType* irmin_type_triple(IrminType* x1173, IrminType* x1172,
                             IrminType* x1171);
IrminString* irmin_type_name(IrminType* x1174);
void irmin_type_free(IrminType* x1175);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int64_t x1177);
IrminValue* irmin_value_float(double x1178);
IrminValue* irmin_value_bool(_Bool x1179);
IrminValue* irmin_value_clone(IrminValue* x1180);
IrminValue* irmin_value_string(IrminString* x1181);
IrminString* irmin_value_get_string(IrminValue* x1182);
int64_t irmin_value_get_int(IrminValue* x1183);
_Bool irmin_value_get_bool(IrminValue* x1184);
double irmin_value_get_float(IrminValue* x1185);
IrminValue* irmin_value_bytes(char* x1187, int64_t x1186);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1190, IrminValue* x1189);
IrminValue* irmin_value_list_hd(IrminValue* x1191);
IrminValue* irmin_value_list_tl(IrminValue* x1192);
IrminValue* irmin_value_list_get(IrminValue* x1194, uint64_t x1193);
uint64_t irmin_value_list_length(IrminValue* x1195);
IrminValue* irmin_value_array_new(uint64_t x1197, IrminValue* x1196);
void irmin_value_array_set(IrminValue* x1200, uint64_t x1199,
                           IrminValue* x1198);
IrminValue* irmin_value_array_get(IrminValue* x1202, uint64_t x1201);
uint64_t irmin_value_array_length(IrminValue* x1203);
IrminValue* irmin_value_option(IrminValue* x1204);
IrminValue* irmin_value_pair(IrminValue* x1206, IrminValue* x1205);
IrminValue* irmin_value_triple(IrminValue* x1209, IrminValue* x1208,
                               IrminValue* x1207);
IrminString* irmin_value_to_string(IrminType* x1211, IrminValue* x1210);
IrminValue* irmin_value_of_string(IrminType* x1214, char* x1213,
                                  int64_t x1212);
IrminString* irmin_value_to_bin(IrminType* x1216, IrminValue* x1215);
IrminValue* irmin_value_of_bin(IrminType* x1219, char* x1218, int64_t x1217);
IrminString* irmin_value_to_json(IrminType* x1221, IrminValue* x1220);
IrminValue* irmin_value_of_json(IrminType* x1224, char* x1223, int64_t x1222);
_Bool irmin_value_equal(IrminType* x1227, IrminValue* x1226,
                        IrminValue* x1225);
int irmin_value_compare(IrminType* x1230, IrminValue* x1229,
                        IrminValue* x1228);
void irmin_value_free(IrminValue* x1231);
IrminString* irmin_string_new(char* x1233, int64_t x1232);
char* irmin_string_data(IrminString* x1234);
uint64_t irmin_string_length(IrminString* x1235);
void irmin_string_free(IrminString* x1236);
IrminInfo* irmin_info_new(IrminRepo* x1239, char* x1238, char* x1237);
void irmin_info_update(IrminRepo* x1243, IrminInfo* x1242, char* x1241,
                       char* x1240);
IrminString* irmin_info_message(IrminRepo* x1245, IrminInfo* x1244);
IrminString* irmin_info_author(IrminRepo* x1247, IrminInfo* x1246);
int64_t irmin_info_date(IrminRepo* x1249, IrminInfo* x1248);
void irmin_info_free(IrminInfo* x1250);
void irmin_log_level(char* x1251);
IrminConfig* irmin_config_pack(char* x1253, char* x1252);
IrminConfig* irmin_config_tezos(void);
IrminConfig* irmin_config_git(char* x1255);
IrminConfig* irmin_config_git_mem(char* x1256);
IrminConfig* irmin_config_fs(char* x1258, char* x1257);
IrminConfig* irmin_config_mem(char* x1260, char* x1259);
void irmin_config_free(IrminConfig* x1261);
_Bool irmin_config_set(IrminConfig* x1265, char* x1264, IrminType* x1263,
                       IrminValue* x1262);
IrminPath* irmin_path(IrminRepo* x1267, char** x1266);
IrminPath* irmin_path_of_string(IrminRepo* x1270, char* x1269, int64_t x1268);
IrminString* irmin_path_to_string(IrminRepo* x1272, IrminPath* x1271);
IrminPath* irmin_path_parent(IrminRepo* x1274, IrminPath* x1273);
IrminPath* irmin_path_append(IrminRepo* x1278, IrminPath* x1277, char* x1276,
                             int64_t x1275);
_Bool irmin_path_equal(IrminRepo* x1281, IrminPath* x1280, IrminPath* x1279);
void irmin_path_free(IrminPath* x1282);
void irmin_hash_free(IrminHash* x1283);
_Bool irmin_hash_equal(IrminRepo* x1286, IrminHash* x1285, IrminHash* x1284);
IrminHash* irmin_contents_hash(IrminRepo* x1288, IrminValue* x1287);
IrminValue* irmin_contents_of_hash(IrminRepo* x1290, IrminHash* x1289);
IrminString* irmin_hash_to_string(IrminRepo* x1292, IrminHash* x1291);
IrminHash* irmin_hash_of_string(IrminRepo* x1295, char* x1294, int64_t x1293);
Irmin* irmin_main(IrminRepo* x1296);
Irmin* irmin_of_branch(IrminRepo* x1298, char* x1297);
IrminCommit* irmin_get_head(Irmin* x1299);
void irmin_set_head(Irmin* x1301, IrminCommit* x1300);
_Bool irmin_fast_forward(Irmin* x1303, IrminCommit* x1302);
_Bool irmin_merge_with_branch(Irmin* x1306, char* x1305, IrminInfo* x1304);
_Bool irmin_merge_with_commit(Irmin* x1309, IrminCommit* x1308,
                              IrminInfo* x1307);
_Bool irmin_set(Irmin* x1313, IrminPath* x1312, IrminValue* x1311,
                IrminInfo* x1310);
_Bool irmin_test_and_set(Irmin* x1318, IrminPath* x1317, IrminValue* x1316,
                         IrminValue* x1315, IrminInfo* x1314);
_Bool irmin_test_and_set_tree(Irmin* x1323, IrminPath* x1322,
                              IrminTree* x1321, IrminTree* x1320,
                              IrminInfo* x1319);
_Bool irmin_set_tree(Irmin* x1327, IrminPath* x1326, IrminTree* x1325,
                     IrminInfo* x1324);
IrminValue* irmin_find(Irmin* x1329, IrminPath* x1328);
IrminTree* irmin_find_tree(Irmin* x1331, IrminPath* x1330);
void irmin_remove(Irmin* x1334, IrminPath* x1333, IrminInfo* x1332);
_Bool irmin_mem(Irmin* x1336, IrminPath* x1335);
_Bool irmin_mem_tree(Irmin* x1338, IrminPath* x1337);
void irmin_free(Irmin* x1339);
IrminTree* irmin_tree_new(IrminRepo* x1340);
IrminTree* irmin_tree_clone(IrminRepo* x1342, IrminTree* x1341);
_Bool irmin_tree_mem(IrminRepo* x1345, IrminTree* x1344, IrminPath* x1343);
_Bool irmin_tree_mem_tree(IrminRepo* x1348, IrminTree* x1347,
                          IrminPath* x1346);
IrminValue* irmin_tree_find(IrminRepo* x1351, IrminTree* x1350,
                            IrminPath* x1349);
IrminTree* irmin_tree_find_tree(IrminRepo* x1354, IrminTree* x1353,
                                IrminPath* x1352);
void irmin_tree_add(IrminRepo* x1358, IrminTree* x1357, IrminPath* x1356,
                    IrminValue* x1355);
void irmin_tree_add_tree(IrminRepo* x1362, IrminTree* x1361,
                         IrminPath* x1360, IrminTree* x1359);
void irmin_tree_remove(IrminRepo* x1365, IrminTree* x1364, IrminPath* x1363);
_Bool irmin_tree_equal(IrminRepo* x1368, IrminTree* x1367, IrminTree* x1366);
void irmin_tree_free(IrminTree* x1369);
IrminRepo* irmin_repo_new(IrminConfig* x1370);
void irmin_repo_free(IrminRepo* x1371);
IrminInfo* irmin_commit_info(IrminRepo* x1373, IrminCommit* x1372);
IrminHash* irmin_commit_hash(IrminRepo* x1375, IrminCommit* x1374);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1377, IrminHash* x1376);
IrminCommit* irmin_commit_new(IrminRepo* x1382, IrminCommit** x1381,
                              uint64_t x1380, IrminTree* x1379,
                              IrminInfo* x1378);
uint64_t irmin_commit_parents_length(IrminRepo* x1384, IrminCommit* x1383);
IrminCommit* irmin_commit_parent(IrminRepo* x1387, IrminCommit* x1386,
                                 uint64_t x1385);
_Bool irmin_commit_equal(IrminRepo* x1390, IrminCommit* x1389,
                         IrminCommit* x1388);
void irmin_commit_free(IrminCommit* x1391);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
