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
typedef struct IrminPathList IrminPathList;
typedef struct IrminCommitList IrminCommitList;
void caml_startup(char *argv[]);
void caml_shutdown();
IrminType* irmin_type_unit(void);
IrminType* irmin_type_bool(void);
IrminType* irmin_type_int(void);
IrminType* irmin_type_float(void);
IrminType* irmin_type_string(void);
IrminType* irmin_type_bytes(void);
IrminType* irmin_type_list(IrminType* x1261);
IrminType* irmin_type_array(IrminType* x1262);
IrminType* irmin_type_option(IrminType* x1263);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1266);
IrminType* irmin_type_commit(IrminRepo* x1267);
IrminType* irmin_type_tree(IrminRepo* x1268);
IrminType* irmin_type_hash(IrminRepo* x1269);
IrminType* irmin_type_contents(IrminRepo* x1270);
IrminType* irmin_type_pair(IrminType* x1272, IrminType* x1271);
IrminType* irmin_type_triple(IrminType* x1275, IrminType* x1274,
                             IrminType* x1273);
IrminString* irmin_type_name(IrminType* x1276);
void irmin_type_free(IrminType* x1277);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int64_t x1279);
IrminValue* irmin_value_float(double x1280);
IrminValue* irmin_value_bool(_Bool x1281);
IrminValue* irmin_value_clone(IrminValue* x1282);
IrminString* irmin_value_get_string(IrminValue* x1283);
int64_t irmin_value_get_int(IrminValue* x1284);
_Bool irmin_value_get_bool(IrminValue* x1285);
double irmin_value_get_float(IrminValue* x1286);
IrminValue* irmin_value_bytes(char* x1288, int64_t x1287);
IrminValue* irmin_value_string(char* x1290, int64_t x1289);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1293, IrminValue* x1292);
IrminValue* irmin_value_list_hd(IrminValue* x1294);
IrminValue* irmin_value_list_tl(IrminValue* x1295);
IrminValue* irmin_value_list_get(IrminValue* x1297, uint64_t x1296);
uint64_t irmin_value_list_length(IrminValue* x1298);
IrminValue* irmin_value_array_new(uint64_t x1300, IrminValue* x1299);
void irmin_value_array_set(IrminValue* x1303, uint64_t x1302,
                           IrminValue* x1301);
IrminValue* irmin_value_array_get(IrminValue* x1305, uint64_t x1304);
uint64_t irmin_value_array_length(IrminValue* x1306);
IrminValue* irmin_value_option(IrminValue* x1307);
IrminValue* irmin_value_pair(IrminValue* x1309, IrminValue* x1308);
IrminValue* irmin_value_triple(IrminValue* x1312, IrminValue* x1311,
                               IrminValue* x1310);
IrminString* irmin_value_to_string(IrminType* x1314, IrminValue* x1313);
IrminValue* irmin_value_of_string(IrminType* x1317, char* x1316,
                                  int64_t x1315);
IrminString* irmin_value_to_bin(IrminType* x1319, IrminValue* x1318);
IrminValue* irmin_value_of_bin(IrminType* x1322, char* x1321, int64_t x1320);
IrminString* irmin_value_to_json(IrminType* x1324, IrminValue* x1323);
IrminValue* irmin_value_of_json(IrminType* x1327, char* x1326, int64_t x1325);
_Bool irmin_value_equal(IrminType* x1330, IrminValue* x1329,
                        IrminValue* x1328);
int irmin_value_compare(IrminType* x1333, IrminValue* x1332,
                        IrminValue* x1331);
void irmin_value_free(IrminValue* x1334);
IrminString* irmin_string_new(char* x1336, int64_t x1335);
char* irmin_string_data(IrminString* x1337);
uint64_t irmin_string_length(IrminString* x1338);
void irmin_string_free(IrminString* x1339);
IrminInfo* irmin_info_new(IrminRepo* x1342, char* x1341, char* x1340);
void irmin_info_update(IrminRepo* x1346, IrminInfo* x1345, char* x1344,
                       char* x1343);
IrminString* irmin_info_message(IrminRepo* x1348, IrminInfo* x1347);
IrminString* irmin_info_author(IrminRepo* x1350, IrminInfo* x1349);
int64_t irmin_info_date(IrminRepo* x1352, IrminInfo* x1351);
void irmin_info_free(IrminInfo* x1353);
void irmin_log_level(char* x1354);
IrminString* irmin_error_msg(void);
IrminConfig* irmin_config_pack(char* x1357, char* x1356);
IrminConfig* irmin_config_tezos(void);
IrminConfig* irmin_config_git(char* x1359);
IrminConfig* irmin_config_git_mem(char* x1360);
IrminConfig* irmin_config_fs(char* x1362, char* x1361);
IrminConfig* irmin_config_mem(char* x1364, char* x1363);
void irmin_config_free(IrminConfig* x1365);
_Bool irmin_config_set(IrminConfig* x1369, char* x1368, IrminType* x1367,
                       IrminValue* x1366);
IrminPath* irmin_path(IrminRepo* x1371, char** x1370);
IrminPath* irmin_path_of_string(IrminRepo* x1374, char* x1373, int64_t x1372);
IrminPath* irmin_path_empty(IrminRepo* x1375);
IrminString* irmin_path_to_string(IrminRepo* x1377, IrminPath* x1376);
IrminPath* irmin_path_parent(IrminRepo* x1379, IrminPath* x1378);
IrminPath* irmin_path_append(IrminRepo* x1383, IrminPath* x1382, char* x1381,
                             int64_t x1380);
IrminPath* irmin_path_append_path(IrminRepo* x1386, IrminPath* x1385,
                                  IrminPath* x1384);
_Bool irmin_path_equal(IrminRepo* x1389, IrminPath* x1388, IrminPath* x1387);
void irmin_path_free(IrminPath* x1390);
void irmin_hash_free(IrminHash* x1391);
_Bool irmin_hash_equal(IrminRepo* x1394, IrminHash* x1393, IrminHash* x1392);
IrminHash* irmin_contents_hash(IrminRepo* x1396, IrminValue* x1395);
IrminValue* irmin_contents_of_hash(IrminRepo* x1398, IrminHash* x1397);
IrminString* irmin_hash_to_string(IrminRepo* x1400, IrminHash* x1399);
IrminHash* irmin_hash_of_string(IrminRepo* x1403, char* x1402, int64_t x1401);
Irmin* irmin_main(IrminRepo* x1404);
Irmin* irmin_of_branch(IrminRepo* x1406, char* x1405);
IrminCommit* irmin_get_head(Irmin* x1407);
void irmin_set_head(Irmin* x1409, IrminCommit* x1408);
_Bool irmin_fast_forward(Irmin* x1411, IrminCommit* x1410);
_Bool irmin_merge_with_branch(Irmin* x1414, char* x1413, IrminInfo* x1412);
_Bool irmin_merge_with_commit(Irmin* x1417, IrminCommit* x1416,
                              IrminInfo* x1415);
_Bool irmin_merge_into(Irmin* x1420, Irmin* x1419, IrminInfo* x1418);
_Bool irmin_set(Irmin* x1424, IrminPath* x1423, IrminValue* x1422,
                IrminInfo* x1421);
_Bool irmin_test_and_set(Irmin* x1429, IrminPath* x1428, IrminValue* x1427,
                         IrminValue* x1426, IrminInfo* x1425);
_Bool irmin_test_and_set_tree(Irmin* x1434, IrminPath* x1433,
                              IrminTree* x1432, IrminTree* x1431,
                              IrminInfo* x1430);
_Bool irmin_set_tree(Irmin* x1438, IrminPath* x1437, IrminTree* x1436,
                     IrminInfo* x1435);
IrminValue* irmin_find(Irmin* x1440, IrminPath* x1439);
IrminTree* irmin_find_tree(Irmin* x1442, IrminPath* x1441);
_Bool irmin_remove(Irmin* x1445, IrminPath* x1444, IrminInfo* x1443);
_Bool irmin_mem(Irmin* x1447, IrminPath* x1446);
_Bool irmin_mem_tree(Irmin* x1449, IrminPath* x1448);
IrminPathList* irmin_list(Irmin* x1451, IrminPath* x1450);
uint64_t irmin_path_list_length(IrminPathList* x1452);
uint64_t irmin_commit_list_length(IrminCommitList* x1453);
IrminPath* irmin_path_list_get(IrminPathList* x1455, uint64_t x1454);
IrminCommit* irmin_commit_list_get(IrminCommitList* x1457, uint64_t x1456);
void irmin_path_list_free(IrminPathList* x1458);
void irmin_commit_list_free(IrminCommitList* x1459);
void irmin_free(Irmin* x1460);
IrminTree* irmin_tree_new(IrminRepo* x1461);
IrminTree* irmin_tree_clone(IrminRepo* x1463, IrminTree* x1462);
_Bool irmin_tree_mem(IrminRepo* x1466, IrminTree* x1465, IrminPath* x1464);
_Bool irmin_tree_mem_tree(IrminRepo* x1469, IrminTree* x1468,
                          IrminPath* x1467);
IrminValue* irmin_tree_find(IrminRepo* x1472, IrminTree* x1471,
                            IrminPath* x1470);
IrminTree* irmin_tree_find_tree(IrminRepo* x1475, IrminTree* x1474,
                                IrminPath* x1473);
void irmin_tree_add(IrminRepo* x1479, IrminTree* x1478, IrminPath* x1477,
                    IrminValue* x1476);
void irmin_tree_add_tree(IrminRepo* x1483, IrminTree* x1482,
                         IrminPath* x1481, IrminTree* x1480);
void irmin_tree_remove(IrminRepo* x1486, IrminTree* x1485, IrminPath* x1484);
_Bool irmin_tree_equal(IrminRepo* x1489, IrminTree* x1488, IrminTree* x1487);
IrminPathList* irmin_tree_list(IrminRepo* x1492, IrminTree* x1491,
                               IrminPath* x1490);
void irmin_tree_free(IrminTree* x1493);
IrminRepo* irmin_repo_new(IrminConfig* x1494);
void irmin_repo_free(IrminRepo* x1495);
IrminInfo* irmin_commit_info(IrminRepo* x1497, IrminCommit* x1496);
IrminHash* irmin_commit_hash(IrminRepo* x1499, IrminCommit* x1498);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1501, IrminHash* x1500);
IrminCommit* irmin_commit_new(IrminRepo* x1506, IrminCommit** x1505,
                              uint64_t x1504, IrminTree* x1503,
                              IrminInfo* x1502);
IrminCommitList* irmin_commit_parents(IrminRepo* x1508, IrminCommit* x1507);
_Bool irmin_commit_equal(IrminRepo* x1511, IrminCommit* x1510,
                         IrminCommit* x1509);
void irmin_commit_free(IrminCommit* x1512);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
