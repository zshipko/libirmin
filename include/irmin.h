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
typedef struct IrminBranchList IrminBranchList;
void caml_startup(char *argv[]);
void caml_shutdown();
IrminType* irmin_type_unit(void);
IrminType* irmin_type_bool(void);
IrminType* irmin_type_int(void);
IrminType* irmin_type_float(void);
IrminType* irmin_type_string(void);
IrminType* irmin_type_bytes(void);
IrminType* irmin_type_list(IrminType* x1312);
IrminType* irmin_type_array(IrminType* x1313);
IrminType* irmin_type_option(IrminType* x1314);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1317);
IrminType* irmin_type_commit(IrminRepo* x1318);
IrminType* irmin_type_tree(IrminRepo* x1319);
IrminType* irmin_type_hash(IrminRepo* x1320);
IrminType* irmin_type_contents(IrminRepo* x1321);
IrminType* irmin_type_pair(IrminType* x1323, IrminType* x1322);
IrminType* irmin_type_triple(IrminType* x1326, IrminType* x1325,
                             IrminType* x1324);
IrminString* irmin_type_name(IrminType* x1327);
void irmin_type_free(IrminType* x1328);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int64_t x1330);
IrminValue* irmin_value_float(double x1331);
IrminValue* irmin_value_bool(_Bool x1332);
IrminValue* irmin_value_clone(IrminValue* x1333);
IrminString* irmin_value_get_string(IrminValue* x1334);
int64_t irmin_value_get_int(IrminValue* x1335);
_Bool irmin_value_get_bool(IrminValue* x1336);
double irmin_value_get_float(IrminValue* x1337);
IrminValue* irmin_value_bytes(char* x1339, int64_t x1338);
IrminValue* irmin_value_string(char* x1341, int64_t x1340);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1344, IrminValue* x1343);
IrminValue* irmin_value_list_hd(IrminValue* x1345);
IrminValue* irmin_value_list_tl(IrminValue* x1346);
IrminValue* irmin_value_list_get(IrminValue* x1348, uint64_t x1347);
uint64_t irmin_value_list_length(IrminValue* x1349);
IrminValue* irmin_value_array_new(uint64_t x1351, IrminValue* x1350);
void irmin_value_array_set(IrminValue* x1354, uint64_t x1353,
                           IrminValue* x1352);
IrminValue* irmin_value_array_get(IrminValue* x1356, uint64_t x1355);
uint64_t irmin_value_array_length(IrminValue* x1357);
IrminValue* irmin_value_option(IrminValue* x1358);
IrminValue* irmin_value_pair(IrminValue* x1360, IrminValue* x1359);
IrminValue* irmin_value_triple(IrminValue* x1363, IrminValue* x1362,
                               IrminValue* x1361);
IrminString* irmin_value_to_string(IrminType* x1365, IrminValue* x1364);
IrminValue* irmin_value_of_string(IrminType* x1368, char* x1367,
                                  int64_t x1366);
IrminString* irmin_value_to_bin(IrminType* x1370, IrminValue* x1369);
IrminValue* irmin_value_of_bin(IrminType* x1373, char* x1372, int64_t x1371);
IrminString* irmin_value_to_json(IrminType* x1375, IrminValue* x1374);
IrminValue* irmin_value_of_json(IrminType* x1378, char* x1377, int64_t x1376);
_Bool irmin_value_equal(IrminType* x1381, IrminValue* x1380,
                        IrminValue* x1379);
int irmin_value_compare(IrminType* x1384, IrminValue* x1383,
                        IrminValue* x1382);
void irmin_value_free(IrminValue* x1385);
IrminString* irmin_string_new(char* x1387, int64_t x1386);
char* irmin_string_data(IrminString* x1388);
uint64_t irmin_string_length(IrminString* x1389);
void irmin_string_free(IrminString* x1390);
IrminInfo* irmin_info_new(IrminRepo* x1393, char* x1392, char* x1391);
void irmin_info_update(IrminRepo* x1397, IrminInfo* x1396, char* x1395,
                       char* x1394);
IrminString* irmin_info_message(IrminRepo* x1399, IrminInfo* x1398);
IrminString* irmin_info_author(IrminRepo* x1401, IrminInfo* x1400);
int64_t irmin_info_date(IrminRepo* x1403, IrminInfo* x1402);
void irmin_info_free(IrminInfo* x1404);
void irmin_log_level(char* x1405);
IrminString* irmin_error_msg(void);
_Bool irmin_error_msg_is_set(void);
IrminConfig* irmin_config_pack(char* x1409, char* x1408);
IrminConfig* irmin_config_tezos(void);
IrminConfig* irmin_config_git(char* x1411);
IrminConfig* irmin_config_git_mem(char* x1412);
IrminConfig* irmin_config_fs(char* x1414, char* x1413);
IrminConfig* irmin_config_mem(char* x1416, char* x1415);
void irmin_config_free(IrminConfig* x1417);
_Bool irmin_config_set(IrminConfig* x1421, char* x1420, IrminType* x1419,
                       IrminValue* x1418);
IrminPath* irmin_path(IrminRepo* x1423, char** x1422);
IrminPath* irmin_path_of_string(IrminRepo* x1426, char* x1425, int64_t x1424);
IrminPath* irmin_path_empty(IrminRepo* x1427);
IrminString* irmin_path_to_string(IrminRepo* x1429, IrminPath* x1428);
IrminPath* irmin_path_parent(IrminRepo* x1431, IrminPath* x1430);
IrminPath* irmin_path_append(IrminRepo* x1435, IrminPath* x1434, char* x1433,
                             int64_t x1432);
IrminPath* irmin_path_append_path(IrminRepo* x1438, IrminPath* x1437,
                                  IrminPath* x1436);
_Bool irmin_path_equal(IrminRepo* x1441, IrminPath* x1440, IrminPath* x1439);
void irmin_path_free(IrminPath* x1442);
void irmin_hash_free(IrminHash* x1443);
_Bool irmin_hash_equal(IrminRepo* x1446, IrminHash* x1445, IrminHash* x1444);
IrminHash* irmin_contents_hash(IrminRepo* x1448, IrminValue* x1447);
IrminValue* irmin_contents_of_hash(IrminRepo* x1450, IrminHash* x1449);
IrminString* irmin_hash_to_string(IrminRepo* x1452, IrminHash* x1451);
IrminHash* irmin_hash_of_string(IrminRepo* x1455, char* x1454, int64_t x1453);
Irmin* irmin_main(IrminRepo* x1456);
Irmin* irmin_of_branch(IrminRepo* x1458, char* x1457);
IrminCommit* irmin_get_head(Irmin* x1459);
void irmin_set_head(Irmin* x1461, IrminCommit* x1460);
_Bool irmin_fast_forward(Irmin* x1463, IrminCommit* x1462);
_Bool irmin_merge_with_branch(Irmin* x1466, char* x1465, IrminInfo* x1464);
_Bool irmin_merge_with_commit(Irmin* x1469, IrminCommit* x1468,
                              IrminInfo* x1467);
_Bool irmin_merge_into(Irmin* x1472, Irmin* x1471, IrminInfo* x1470);
_Bool irmin_set(Irmin* x1476, IrminPath* x1475, IrminValue* x1474,
                IrminInfo* x1473);
_Bool irmin_test_and_set(Irmin* x1481, IrminPath* x1480, IrminValue* x1479,
                         IrminValue* x1478, IrminInfo* x1477);
_Bool irmin_test_and_set_tree(Irmin* x1486, IrminPath* x1485,
                              IrminTree* x1484, IrminTree* x1483,
                              IrminInfo* x1482);
_Bool irmin_set_tree(Irmin* x1490, IrminPath* x1489, IrminTree* x1488,
                     IrminInfo* x1487);
IrminValue* irmin_find(Irmin* x1492, IrminPath* x1491);
IrminTree* irmin_find_tree(Irmin* x1494, IrminPath* x1493);
_Bool irmin_remove(Irmin* x1497, IrminPath* x1496, IrminInfo* x1495);
_Bool irmin_mem(Irmin* x1499, IrminPath* x1498);
_Bool irmin_mem_tree(Irmin* x1501, IrminPath* x1500);
IrminPathList* irmin_list(Irmin* x1503, IrminPath* x1502);
uint64_t irmin_path_list_length(IrminRepo* x1505, IrminPathList* x1504);
uint64_t irmin_commit_list_length(IrminRepo* x1507, IrminCommitList* x1506);
IrminPath* irmin_path_list_get(IrminRepo* x1510, IrminPathList* x1509,
                               uint64_t x1508);
IrminCommit* irmin_commit_list_get(IrminRepo* x1513, IrminCommitList* x1512,
                                   uint64_t x1511);
void irmin_path_list_free(IrminPathList* x1514);
void irmin_commit_list_free(IrminCommitList* x1515);
void irmin_free(Irmin* x1516);
IrminTree* irmin_tree_new(IrminRepo* x1517);
IrminTree* irmin_tree_clone(IrminRepo* x1519, IrminTree* x1518);
_Bool irmin_tree_mem(IrminRepo* x1522, IrminTree* x1521, IrminPath* x1520);
_Bool irmin_tree_mem_tree(IrminRepo* x1525, IrminTree* x1524,
                          IrminPath* x1523);
IrminValue* irmin_tree_find(IrminRepo* x1528, IrminTree* x1527,
                            IrminPath* x1526);
IrminTree* irmin_tree_find_tree(IrminRepo* x1531, IrminTree* x1530,
                                IrminPath* x1529);
void irmin_tree_add(IrminRepo* x1535, IrminTree* x1534, IrminPath* x1533,
                    IrminValue* x1532);
void irmin_tree_add_tree(IrminRepo* x1539, IrminTree* x1538,
                         IrminPath* x1537, IrminTree* x1536);
void irmin_tree_remove(IrminRepo* x1542, IrminTree* x1541, IrminPath* x1540);
_Bool irmin_tree_equal(IrminRepo* x1545, IrminTree* x1544, IrminTree* x1543);
IrminPathList* irmin_tree_list(IrminRepo* x1548, IrminTree* x1547,
                               IrminPath* x1546);
void irmin_tree_free(IrminTree* x1549);
IrminRepo* irmin_repo_new(IrminConfig* x1550);
IrminBranchList* irmin_repo_branches(IrminRepo* x1551);
uint64_t irmin_branch_list_length(IrminRepo* x1553, IrminBranchList* x1552);
IrminString* irmin_branch_list_get(IrminRepo* x1556, IrminBranchList* x1555,
                                   uint64_t x1554);
void irmin_branch_list_free(IrminBranchList* x1557);
void irmin_repo_free(IrminRepo* x1558);
IrminInfo* irmin_commit_info(IrminRepo* x1560, IrminCommit* x1559);
IrminHash* irmin_commit_hash(IrminRepo* x1562, IrminCommit* x1561);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1564, IrminHash* x1563);
IrminCommit* irmin_commit_new(IrminRepo* x1569, IrminCommit** x1568,
                              uint64_t x1567, IrminTree* x1566,
                              IrminInfo* x1565);
IrminCommitList* irmin_commit_parents(IrminRepo* x1571, IrminCommit* x1570);
_Bool irmin_commit_equal(IrminRepo* x1574, IrminCommit* x1573,
                         IrminCommit* x1572);
void irmin_commit_free(IrminCommit* x1575);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
