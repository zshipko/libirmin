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
IrminType* irmin_type_list(IrminType* x1271);
IrminType* irmin_type_array(IrminType* x1272);
IrminType* irmin_type_option(IrminType* x1273);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1276);
IrminType* irmin_type_commit(IrminRepo* x1277);
IrminType* irmin_type_tree(IrminRepo* x1278);
IrminType* irmin_type_hash(IrminRepo* x1279);
IrminType* irmin_type_contents(IrminRepo* x1280);
IrminType* irmin_type_pair(IrminType* x1282, IrminType* x1281);
IrminType* irmin_type_triple(IrminType* x1285, IrminType* x1284,
                             IrminType* x1283);
IrminString* irmin_type_name(IrminType* x1286);
void irmin_type_free(IrminType* x1287);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int64_t x1289);
IrminValue* irmin_value_float(double x1290);
IrminValue* irmin_value_bool(_Bool x1291);
IrminValue* irmin_value_clone(IrminValue* x1292);
IrminString* irmin_value_get_string(IrminValue* x1293);
int64_t irmin_value_get_int(IrminValue* x1294);
_Bool irmin_value_get_bool(IrminValue* x1295);
double irmin_value_get_float(IrminValue* x1296);
IrminValue* irmin_value_bytes(char* x1298, int64_t x1297);
IrminValue* irmin_value_string(char* x1300, int64_t x1299);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1303, IrminValue* x1302);
IrminValue* irmin_value_list_hd(IrminValue* x1304);
IrminValue* irmin_value_list_tl(IrminValue* x1305);
IrminValue* irmin_value_list_get(IrminValue* x1307, uint64_t x1306);
uint64_t irmin_value_list_length(IrminValue* x1308);
IrminValue* irmin_value_array_new(uint64_t x1310, IrminValue* x1309);
void irmin_value_array_set(IrminValue* x1313, uint64_t x1312,
                           IrminValue* x1311);
IrminValue* irmin_value_array_get(IrminValue* x1315, uint64_t x1314);
uint64_t irmin_value_array_length(IrminValue* x1316);
IrminValue* irmin_value_option(IrminValue* x1317);
IrminValue* irmin_value_pair(IrminValue* x1319, IrminValue* x1318);
IrminValue* irmin_value_triple(IrminValue* x1322, IrminValue* x1321,
                               IrminValue* x1320);
IrminString* irmin_value_to_string(IrminType* x1324, IrminValue* x1323);
IrminValue* irmin_value_of_string(IrminType* x1327, char* x1326,
                                  int64_t x1325);
IrminString* irmin_value_to_bin(IrminType* x1329, IrminValue* x1328);
IrminValue* irmin_value_of_bin(IrminType* x1332, char* x1331, int64_t x1330);
IrminString* irmin_value_to_json(IrminType* x1334, IrminValue* x1333);
IrminValue* irmin_value_of_json(IrminType* x1337, char* x1336, int64_t x1335);
_Bool irmin_value_equal(IrminType* x1340, IrminValue* x1339,
                        IrminValue* x1338);
int irmin_value_compare(IrminType* x1343, IrminValue* x1342,
                        IrminValue* x1341);
void irmin_value_free(IrminValue* x1344);
IrminString* irmin_string_new(char* x1346, int64_t x1345);
char* irmin_string_data(IrminString* x1347);
uint64_t irmin_string_length(IrminString* x1348);
void irmin_string_free(IrminString* x1349);
IrminInfo* irmin_info_new(IrminRepo* x1352, char* x1351, char* x1350);
void irmin_info_update(IrminRepo* x1356, IrminInfo* x1355, char* x1354,
                       char* x1353);
IrminString* irmin_info_message(IrminRepo* x1358, IrminInfo* x1357);
IrminString* irmin_info_author(IrminRepo* x1360, IrminInfo* x1359);
int64_t irmin_info_date(IrminRepo* x1362, IrminInfo* x1361);
void irmin_info_free(IrminInfo* x1363);
void irmin_log_level(char* x1364);
IrminString* irmin_error_msg(void);
_Bool irmin_error_msg_is_set(void);
IrminConfig* irmin_config_pack(char* x1368, char* x1367);
IrminConfig* irmin_config_tezos(void);
IrminConfig* irmin_config_git(char* x1370);
IrminConfig* irmin_config_git_mem(char* x1371);
IrminConfig* irmin_config_fs(char* x1373, char* x1372);
IrminConfig* irmin_config_mem(char* x1375, char* x1374);
void irmin_config_free(IrminConfig* x1376);
_Bool irmin_config_set(IrminConfig* x1380, char* x1379, IrminType* x1378,
                       IrminValue* x1377);
IrminPath* irmin_path(IrminRepo* x1382, char** x1381);
IrminPath* irmin_path_of_string(IrminRepo* x1385, char* x1384, int64_t x1383);
IrminPath* irmin_path_empty(IrminRepo* x1386);
IrminString* irmin_path_to_string(IrminRepo* x1388, IrminPath* x1387);
IrminPath* irmin_path_parent(IrminRepo* x1390, IrminPath* x1389);
IrminPath* irmin_path_append(IrminRepo* x1394, IrminPath* x1393, char* x1392,
                             int64_t x1391);
IrminPath* irmin_path_append_path(IrminRepo* x1397, IrminPath* x1396,
                                  IrminPath* x1395);
_Bool irmin_path_equal(IrminRepo* x1400, IrminPath* x1399, IrminPath* x1398);
void irmin_path_free(IrminPath* x1401);
void irmin_hash_free(IrminHash* x1402);
_Bool irmin_hash_equal(IrminRepo* x1405, IrminHash* x1404, IrminHash* x1403);
IrminHash* irmin_contents_hash(IrminRepo* x1407, IrminValue* x1406);
IrminValue* irmin_contents_of_hash(IrminRepo* x1409, IrminHash* x1408);
IrminString* irmin_hash_to_string(IrminRepo* x1411, IrminHash* x1410);
IrminHash* irmin_hash_of_string(IrminRepo* x1414, char* x1413, int64_t x1412);
Irmin* irmin_main(IrminRepo* x1415);
Irmin* irmin_of_branch(IrminRepo* x1417, char* x1416);
IrminCommit* irmin_get_head(Irmin* x1418);
void irmin_set_head(Irmin* x1420, IrminCommit* x1419);
_Bool irmin_fast_forward(Irmin* x1422, IrminCommit* x1421);
_Bool irmin_merge_with_branch(Irmin* x1425, char* x1424, IrminInfo* x1423);
_Bool irmin_merge_with_commit(Irmin* x1428, IrminCommit* x1427,
                              IrminInfo* x1426);
_Bool irmin_merge_into(Irmin* x1431, Irmin* x1430, IrminInfo* x1429);
_Bool irmin_set(Irmin* x1435, IrminPath* x1434, IrminValue* x1433,
                IrminInfo* x1432);
_Bool irmin_test_and_set(Irmin* x1440, IrminPath* x1439, IrminValue* x1438,
                         IrminValue* x1437, IrminInfo* x1436);
_Bool irmin_test_and_set_tree(Irmin* x1445, IrminPath* x1444,
                              IrminTree* x1443, IrminTree* x1442,
                              IrminInfo* x1441);
_Bool irmin_set_tree(Irmin* x1449, IrminPath* x1448, IrminTree* x1447,
                     IrminInfo* x1446);
IrminValue* irmin_find(Irmin* x1451, IrminPath* x1450);
IrminTree* irmin_find_tree(Irmin* x1453, IrminPath* x1452);
_Bool irmin_remove(Irmin* x1456, IrminPath* x1455, IrminInfo* x1454);
_Bool irmin_mem(Irmin* x1458, IrminPath* x1457);
_Bool irmin_mem_tree(Irmin* x1460, IrminPath* x1459);
IrminPathList* irmin_list(Irmin* x1462, IrminPath* x1461);
uint64_t irmin_path_list_length(IrminPathList* x1463);
uint64_t irmin_commit_list_length(IrminCommitList* x1464);
IrminPath* irmin_path_list_get(IrminPathList* x1466, uint64_t x1465);
IrminCommit* irmin_commit_list_get(IrminCommitList* x1468, uint64_t x1467);
void irmin_path_list_free(IrminPathList* x1469);
void irmin_commit_list_free(IrminCommitList* x1470);
void irmin_free(Irmin* x1471);
IrminTree* irmin_tree_new(IrminRepo* x1472);
IrminTree* irmin_tree_clone(IrminRepo* x1474, IrminTree* x1473);
_Bool irmin_tree_mem(IrminRepo* x1477, IrminTree* x1476, IrminPath* x1475);
_Bool irmin_tree_mem_tree(IrminRepo* x1480, IrminTree* x1479,
                          IrminPath* x1478);
IrminValue* irmin_tree_find(IrminRepo* x1483, IrminTree* x1482,
                            IrminPath* x1481);
IrminTree* irmin_tree_find_tree(IrminRepo* x1486, IrminTree* x1485,
                                IrminPath* x1484);
void irmin_tree_add(IrminRepo* x1490, IrminTree* x1489, IrminPath* x1488,
                    IrminValue* x1487);
void irmin_tree_add_tree(IrminRepo* x1494, IrminTree* x1493,
                         IrminPath* x1492, IrminTree* x1491);
void irmin_tree_remove(IrminRepo* x1497, IrminTree* x1496, IrminPath* x1495);
_Bool irmin_tree_equal(IrminRepo* x1500, IrminTree* x1499, IrminTree* x1498);
IrminPathList* irmin_tree_list(IrminRepo* x1503, IrminTree* x1502,
                               IrminPath* x1501);
void irmin_tree_free(IrminTree* x1504);
IrminRepo* irmin_repo_new(IrminConfig* x1505);
void irmin_repo_free(IrminRepo* x1506);
IrminInfo* irmin_commit_info(IrminRepo* x1508, IrminCommit* x1507);
IrminHash* irmin_commit_hash(IrminRepo* x1510, IrminCommit* x1509);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1512, IrminHash* x1511);
IrminCommit* irmin_commit_new(IrminRepo* x1517, IrminCommit** x1516,
                              uint64_t x1515, IrminTree* x1514,
                              IrminInfo* x1513);
IrminCommitList* irmin_commit_parents(IrminRepo* x1519, IrminCommit* x1518);
_Bool irmin_commit_equal(IrminRepo* x1522, IrminCommit* x1521,
                         IrminCommit* x1520);
void irmin_commit_free(IrminCommit* x1523);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
