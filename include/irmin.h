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
IrminType* irmin_type_list(IrminType* x1172);
IrminType* irmin_type_array(IrminType* x1173);
IrminType* irmin_type_option(IrminType* x1174);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1177);
IrminType* irmin_type_commit(IrminRepo* x1178);
IrminType* irmin_type_tree(IrminRepo* x1179);
IrminType* irmin_type_hash(IrminRepo* x1180);
IrminType* irmin_type_contents(IrminRepo* x1181);
IrminType* irmin_type_pair(IrminType* x1183, IrminType* x1182);
IrminType* irmin_type_triple(IrminType* x1186, IrminType* x1185,
                             IrminType* x1184);
IrminString* irmin_type_name(IrminType* x1187);
void irmin_type_free(IrminType* x1188);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int64_t x1190);
IrminValue* irmin_value_float(double x1191);
IrminValue* irmin_value_bool(_Bool x1192);
IrminValue* irmin_value_clone(IrminValue* x1193);
IrminString* irmin_value_get_string(IrminValue* x1194);
int64_t irmin_value_get_int(IrminValue* x1195);
_Bool irmin_value_get_bool(IrminValue* x1196);
double irmin_value_get_float(IrminValue* x1197);
IrminValue* irmin_value_bytes(char* x1199, int64_t x1198);
IrminValue* irmin_value_string(char* x1201, int64_t x1200);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1204, IrminValue* x1203);
IrminValue* irmin_value_list_hd(IrminValue* x1205);
IrminValue* irmin_value_list_tl(IrminValue* x1206);
IrminValue* irmin_value_list_get(IrminValue* x1208, uint64_t x1207);
uint64_t irmin_value_list_length(IrminValue* x1209);
IrminValue* irmin_value_array_new(uint64_t x1211, IrminValue* x1210);
void irmin_value_array_set(IrminValue* x1214, uint64_t x1213,
                           IrminValue* x1212);
IrminValue* irmin_value_array_get(IrminValue* x1216, uint64_t x1215);
uint64_t irmin_value_array_length(IrminValue* x1217);
IrminValue* irmin_value_option(IrminValue* x1218);
IrminValue* irmin_value_pair(IrminValue* x1220, IrminValue* x1219);
IrminValue* irmin_value_triple(IrminValue* x1223, IrminValue* x1222,
                               IrminValue* x1221);
IrminString* irmin_value_to_string(IrminType* x1225, IrminValue* x1224);
IrminValue* irmin_value_of_string(IrminType* x1228, char* x1227,
                                  int64_t x1226);
IrminString* irmin_value_to_bin(IrminType* x1230, IrminValue* x1229);
IrminValue* irmin_value_of_bin(IrminType* x1233, char* x1232, int64_t x1231);
IrminString* irmin_value_to_json(IrminType* x1235, IrminValue* x1234);
IrminValue* irmin_value_of_json(IrminType* x1238, char* x1237, int64_t x1236);
_Bool irmin_value_equal(IrminType* x1241, IrminValue* x1240,
                        IrminValue* x1239);
int irmin_value_compare(IrminType* x1244, IrminValue* x1243,
                        IrminValue* x1242);
void irmin_value_free(IrminValue* x1245);
IrminString* irmin_string_new(char* x1247, int64_t x1246);
char* irmin_string_data(IrminString* x1248);
uint64_t irmin_string_length(IrminString* x1249);
void irmin_string_free(IrminString* x1250);
IrminInfo* irmin_info_new(IrminRepo* x1253, char* x1252, char* x1251);
void irmin_info_update(IrminRepo* x1257, IrminInfo* x1256, char* x1255,
                       char* x1254);
IrminString* irmin_info_message(IrminRepo* x1259, IrminInfo* x1258);
IrminString* irmin_info_author(IrminRepo* x1261, IrminInfo* x1260);
int64_t irmin_info_date(IrminRepo* x1263, IrminInfo* x1262);
void irmin_info_free(IrminInfo* x1264);
void irmin_log_level(char* x1265);
IrminConfig* irmin_config_pack(char* x1267, char* x1266);
IrminConfig* irmin_config_tezos(void);
IrminConfig* irmin_config_git(char* x1269);
IrminConfig* irmin_config_git_mem(char* x1270);
IrminConfig* irmin_config_fs(char* x1272, char* x1271);
IrminConfig* irmin_config_mem(char* x1274, char* x1273);
void irmin_config_free(IrminConfig* x1275);
_Bool irmin_config_set(IrminConfig* x1279, char* x1278, IrminType* x1277,
                       IrminValue* x1276);
IrminPath* irmin_path(IrminRepo* x1281, char** x1280);
IrminPath* irmin_path_of_string(IrminRepo* x1284, char* x1283, int64_t x1282);
IrminString* irmin_path_to_string(IrminRepo* x1286, IrminPath* x1285);
IrminPath* irmin_path_parent(IrminRepo* x1288, IrminPath* x1287);
IrminPath* irmin_path_append(IrminRepo* x1292, IrminPath* x1291, char* x1290,
                             int64_t x1289);
_Bool irmin_path_equal(IrminRepo* x1295, IrminPath* x1294, IrminPath* x1293);
void irmin_path_free(IrminPath* x1296);
void irmin_hash_free(IrminHash* x1297);
_Bool irmin_hash_equal(IrminRepo* x1300, IrminHash* x1299, IrminHash* x1298);
IrminHash* irmin_contents_hash(IrminRepo* x1302, IrminValue* x1301);
IrminValue* irmin_contents_of_hash(IrminRepo* x1304, IrminHash* x1303);
IrminString* irmin_hash_to_string(IrminRepo* x1306, IrminHash* x1305);
IrminHash* irmin_hash_of_string(IrminRepo* x1309, char* x1308, int64_t x1307);
Irmin* irmin_main(IrminRepo* x1310);
Irmin* irmin_of_branch(IrminRepo* x1312, char* x1311);
IrminCommit* irmin_get_head(Irmin* x1313);
void irmin_set_head(Irmin* x1315, IrminCommit* x1314);
_Bool irmin_fast_forward(Irmin* x1317, IrminCommit* x1316);
_Bool irmin_merge_with_branch(Irmin* x1320, char* x1319, IrminInfo* x1318);
_Bool irmin_merge_with_commit(Irmin* x1323, IrminCommit* x1322,
                              IrminInfo* x1321);
_Bool irmin_merge_into(Irmin* x1326, Irmin* x1325, IrminInfo* x1324);
_Bool irmin_set(Irmin* x1330, IrminPath* x1329, IrminValue* x1328,
                IrminInfo* x1327);
_Bool irmin_test_and_set(Irmin* x1335, IrminPath* x1334, IrminValue* x1333,
                         IrminValue* x1332, IrminInfo* x1331);
_Bool irmin_test_and_set_tree(Irmin* x1340, IrminPath* x1339,
                              IrminTree* x1338, IrminTree* x1337,
                              IrminInfo* x1336);
_Bool irmin_set_tree(Irmin* x1344, IrminPath* x1343, IrminTree* x1342,
                     IrminInfo* x1341);
IrminValue* irmin_find(Irmin* x1346, IrminPath* x1345);
IrminTree* irmin_find_tree(Irmin* x1348, IrminPath* x1347);
void irmin_remove(Irmin* x1351, IrminPath* x1350, IrminInfo* x1349);
_Bool irmin_mem(Irmin* x1353, IrminPath* x1352);
_Bool irmin_mem_tree(Irmin* x1355, IrminPath* x1354);
void irmin_free(Irmin* x1356);
IrminTree* irmin_tree_new(IrminRepo* x1357);
IrminTree* irmin_tree_clone(IrminRepo* x1359, IrminTree* x1358);
_Bool irmin_tree_mem(IrminRepo* x1362, IrminTree* x1361, IrminPath* x1360);
_Bool irmin_tree_mem_tree(IrminRepo* x1365, IrminTree* x1364,
                          IrminPath* x1363);
IrminValue* irmin_tree_find(IrminRepo* x1368, IrminTree* x1367,
                            IrminPath* x1366);
IrminTree* irmin_tree_find_tree(IrminRepo* x1371, IrminTree* x1370,
                                IrminPath* x1369);
void irmin_tree_add(IrminRepo* x1375, IrminTree* x1374, IrminPath* x1373,
                    IrminValue* x1372);
void irmin_tree_add_tree(IrminRepo* x1379, IrminTree* x1378,
                         IrminPath* x1377, IrminTree* x1376);
void irmin_tree_remove(IrminRepo* x1382, IrminTree* x1381, IrminPath* x1380);
_Bool irmin_tree_equal(IrminRepo* x1385, IrminTree* x1384, IrminTree* x1383);
void irmin_tree_free(IrminTree* x1386);
IrminRepo* irmin_repo_new(IrminConfig* x1387);
void irmin_repo_free(IrminRepo* x1388);
IrminInfo* irmin_commit_info(IrminRepo* x1390, IrminCommit* x1389);
IrminHash* irmin_commit_hash(IrminRepo* x1392, IrminCommit* x1391);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1394, IrminHash* x1393);
IrminCommit* irmin_commit_new(IrminRepo* x1399, IrminCommit** x1398,
                              uint64_t x1397, IrminTree* x1396,
                              IrminInfo* x1395);
uint64_t irmin_commit_parents_length(IrminRepo* x1401, IrminCommit* x1400);
IrminCommit* irmin_commit_parent(IrminRepo* x1404, IrminCommit* x1403,
                                 uint64_t x1402);
_Bool irmin_commit_equal(IrminRepo* x1407, IrminCommit* x1406,
                         IrminCommit* x1405);
void irmin_commit_free(IrminCommit* x1408);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
