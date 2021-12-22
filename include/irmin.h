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
Irmin* irmin_main(IrminRepo* x1422);
Irmin* irmin_of_branch(IrminRepo* x1424, char* x1423);
IrminCommit* irmin_get_head(Irmin* x1425);
void irmin_set_head(Irmin* x1427, IrminCommit* x1426);
_Bool irmin_fast_forward(Irmin* x1429, IrminCommit* x1428);
_Bool irmin_merge_with_branch(Irmin* x1432, char* x1431, IrminInfo* x1430);
_Bool irmin_merge_with_commit(Irmin* x1435, IrminCommit* x1434,
                              IrminInfo* x1433);
_Bool irmin_merge_into(Irmin* x1438, Irmin* x1437, IrminInfo* x1436);
_Bool irmin_set(Irmin* x1442, IrminPath* x1441, IrminValue* x1440,
                IrminInfo* x1439);
_Bool irmin_test_and_set(Irmin* x1447, IrminPath* x1446, IrminValue* x1445,
                         IrminValue* x1444, IrminInfo* x1443);
_Bool irmin_test_and_set_tree(Irmin* x1452, IrminPath* x1451,
                              IrminTree* x1450, IrminTree* x1449,
                              IrminInfo* x1448);
_Bool irmin_set_tree(Irmin* x1456, IrminPath* x1455, IrminTree* x1454,
                     IrminInfo* x1453);
IrminValue* irmin_find(Irmin* x1458, IrminPath* x1457);
IrminTree* irmin_find_tree(Irmin* x1460, IrminPath* x1459);
_Bool irmin_remove(Irmin* x1463, IrminPath* x1462, IrminInfo* x1461);
_Bool irmin_mem(Irmin* x1465, IrminPath* x1464);
_Bool irmin_mem_tree(Irmin* x1467, IrminPath* x1466);
IrminPathList* irmin_list(Irmin* x1469, IrminPath* x1468);
uint64_t irmin_path_list_length(IrminRepo* x1471, IrminPathList* x1470);
uint64_t irmin_commit_list_length(IrminRepo* x1473, IrminCommitList* x1472);
IrminPath* irmin_path_list_get(IrminRepo* x1476, IrminPathList* x1475,
                               uint64_t x1474);
IrminCommit* irmin_commit_list_get(IrminRepo* x1479, IrminCommitList* x1478,
                                   uint64_t x1477);
void irmin_path_list_free(IrminPathList* x1480);
void irmin_commit_list_free(IrminCommitList* x1481);
void irmin_free(Irmin* x1482);
IrminTree* irmin_tree_new(IrminRepo* x1483);
IrminTree* irmin_tree_clone(IrminRepo* x1485, IrminTree* x1484);
_Bool irmin_tree_mem(IrminRepo* x1488, IrminTree* x1487, IrminPath* x1486);
_Bool irmin_tree_mem_tree(IrminRepo* x1491, IrminTree* x1490,
                          IrminPath* x1489);
IrminValue* irmin_tree_find(IrminRepo* x1494, IrminTree* x1493,
                            IrminPath* x1492);
IrminTree* irmin_tree_find_tree(IrminRepo* x1497, IrminTree* x1496,
                                IrminPath* x1495);
void irmin_tree_add(IrminRepo* x1501, IrminTree* x1500, IrminPath* x1499,
                    IrminValue* x1498);
void irmin_tree_add_tree(IrminRepo* x1505, IrminTree* x1504,
                         IrminPath* x1503, IrminTree* x1502);
void irmin_tree_remove(IrminRepo* x1508, IrminTree* x1507, IrminPath* x1506);
_Bool irmin_tree_equal(IrminRepo* x1511, IrminTree* x1510, IrminTree* x1509);
IrminPathList* irmin_tree_list(IrminRepo* x1514, IrminTree* x1513,
                               IrminPath* x1512);
void irmin_tree_free(IrminTree* x1515);
IrminRepo* irmin_repo_new(IrminConfig* x1516);
IrminBranchList* irmin_repo_branches(IrminRepo* x1517);
uint64_t irmin_branch_list_length(IrminRepo* x1519, IrminBranchList* x1518);
IrminString* irmin_branch_list_get(IrminRepo* x1522, IrminBranchList* x1521,
                                   uint64_t x1520);
_Bool irmin_hash_equal(IrminRepo* x1525, IrminHash* x1524, IrminHash* x1523);
IrminHash* irmin_contents_hash(IrminRepo* x1527, IrminValue* x1526);
IrminValue* irmin_contents_of_hash(IrminRepo* x1529, IrminHash* x1528);
IrminString* irmin_hash_to_string(IrminRepo* x1531, IrminHash* x1530);
IrminHash* irmin_hash_of_string(IrminRepo* x1534, char* x1533, int64_t x1532);
void irmin_hash_free(IrminHash* x1535);
void irmin_branch_list_free(IrminBranchList* x1536);
void irmin_repo_free(IrminRepo* x1537);
IrminInfo* irmin_commit_info(IrminRepo* x1539, IrminCommit* x1538);
IrminHash* irmin_commit_hash(IrminRepo* x1541, IrminCommit* x1540);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1543, IrminHash* x1542);
IrminCommit* irmin_commit_new(IrminRepo* x1548, IrminCommit** x1547,
                              uint64_t x1546, IrminTree* x1545,
                              IrminInfo* x1544);
IrminCommitList* irmin_commit_parents(IrminRepo* x1550, IrminCommit* x1549);
_Bool irmin_commit_equal(IrminRepo* x1553, IrminCommit* x1552,
                         IrminCommit* x1551);
void irmin_commit_free(IrminCommit* x1554);
IrminPath* irmin_path(IrminRepo* x1556, char** x1555);
IrminPath* irmin_path_of_string(IrminRepo* x1559, char* x1558, int64_t x1557);
IrminPath* irmin_path_empty(IrminRepo* x1560);
IrminString* irmin_path_to_string(IrminRepo* x1562, IrminPath* x1561);
IrminPath* irmin_path_parent(IrminRepo* x1564, IrminPath* x1563);
IrminPath* irmin_path_append(IrminRepo* x1568, IrminPath* x1567, char* x1566,
                             int64_t x1565);
IrminPath* irmin_path_append_path(IrminRepo* x1571, IrminPath* x1570,
                                  IrminPath* x1569);
_Bool irmin_path_equal(IrminRepo* x1574, IrminPath* x1573, IrminPath* x1572);
void irmin_path_free(IrminPath* x1575);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
