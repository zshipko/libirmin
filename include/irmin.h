#pragma once
#include <stdbool.h>
#include <stdint.h>
typedef struct IrminType IrminType;
typedef struct IrminValue IrminValue;
typedef struct IrminConfig IrminConfig;
typedef struct IrminRepo IrminRepo;
typedef struct Irmin Irmin;
typedef struct IrminPath IrminPath;
typedef struct IrminCommitKey IrminCommitKey;
typedef struct IrminContentsKey IrminContentsKey;
typedef struct IrminNodeKey IrminNodeKey;
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
IrminType* irmin_type_list(IrminType* x1386);
IrminType* irmin_type_array(IrminType* x1387);
IrminType* irmin_type_option(IrminType* x1388);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1391);
IrminType* irmin_type_commit(IrminRepo* x1392);
IrminType* irmin_type_tree(IrminRepo* x1393);
IrminType* irmin_type_hash(IrminRepo* x1394);
IrminType* irmin_type_commit_key(IrminRepo* x1395);
IrminType* irmin_type_contents_key(IrminRepo* x1396);
IrminType* irmin_type_node_key(IrminRepo* x1397);
IrminType* irmin_type_contents(IrminRepo* x1398);
IrminType* irmin_type_pair(IrminType* x1400, IrminType* x1399);
IrminType* irmin_type_triple(IrminType* x1403, IrminType* x1402,
                             IrminType* x1401);
IrminString* irmin_type_name(IrminType* x1404);
IrminType* irmin_type_diff(IrminType* x1405);
void irmin_type_free(IrminType* x1406);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int64_t x1408);
IrminValue* irmin_value_float(double x1409);
IrminValue* irmin_value_bool(_Bool x1410);
IrminValue* irmin_value_clone(IrminValue* x1411);
IrminString* irmin_value_get_string(IrminValue* x1412);
int64_t irmin_value_get_int(IrminValue* x1413);
_Bool irmin_value_get_bool(IrminValue* x1414);
double irmin_value_get_float(IrminValue* x1415);
IrminValue* irmin_value_bytes(char* x1417, int64_t x1416);
IrminValue* irmin_value_string(char* x1419, int64_t x1418);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1422, IrminValue* x1421);
IrminValue* irmin_value_list_hd(IrminValue* x1423);
IrminValue* irmin_value_list_tl(IrminValue* x1424);
IrminValue* irmin_value_list_get(IrminValue* x1426, uint64_t x1425);
uint64_t irmin_value_list_length(IrminValue* x1427);
IrminValue* irmin_value_array_new(uint64_t x1429, IrminValue* x1428);
void irmin_value_array_set(IrminValue* x1432, uint64_t x1431,
                           IrminValue* x1430);
IrminValue* irmin_value_array_get(IrminValue* x1434, uint64_t x1433);
uint64_t irmin_value_array_length(IrminValue* x1435);
IrminValue* irmin_value_option(IrminValue* x1436);
IrminValue* irmin_value_pair(IrminValue* x1438, IrminValue* x1437);
IrminValue* irmin_value_triple(IrminValue* x1441, IrminValue* x1440,
                               IrminValue* x1439);
IrminString* irmin_value_to_string(IrminType* x1443, IrminValue* x1442);
IrminValue* irmin_value_of_string(IrminType* x1446, char* x1445,
                                  int64_t x1444);
IrminString* irmin_value_to_bin(IrminType* x1448, IrminValue* x1447);
IrminValue* irmin_value_of_bin(IrminType* x1451, char* x1450, int64_t x1449);
IrminString* irmin_value_to_json(IrminType* x1453, IrminValue* x1452);
IrminValue* irmin_value_of_json(IrminType* x1456, char* x1455, int64_t x1454);
_Bool irmin_value_equal(IrminType* x1459, IrminValue* x1458,
                        IrminValue* x1457);
int irmin_value_compare(IrminType* x1462, IrminValue* x1461,
                        IrminValue* x1460);
void irmin_value_free(IrminValue* x1463);
IrminString* irmin_string_new(char* x1465, int64_t x1464);
char* irmin_string_data(IrminString* x1466);
uint64_t irmin_string_length(IrminString* x1467);
void irmin_string_free(IrminString* x1468);
IrminInfo* irmin_info_new(IrminRepo* x1471, char* x1470, char* x1469);
void irmin_info_update(IrminRepo* x1475, IrminInfo* x1474, char* x1473,
                       char* x1472);
IrminString* irmin_info_message(IrminRepo* x1477, IrminInfo* x1476);
IrminString* irmin_info_author(IrminRepo* x1479, IrminInfo* x1478);
int64_t irmin_info_date(IrminRepo* x1481, IrminInfo* x1480);
void irmin_info_free(IrminInfo* x1482);
void irmin_log_level(char* x1483);
IrminString* irmin_error_msg(void);
_Bool irmin_error_msg_is_set(void);
IrminConfig* irmin_config_pack(char* x1487, char* x1486);
IrminConfig* irmin_config_tezos(void);
IrminConfig* irmin_config_git(char* x1489);
IrminConfig* irmin_config_git_mem(char* x1490);
IrminConfig* irmin_config_fs(char* x1492, char* x1491);
IrminConfig* irmin_config_mem(char* x1494, char* x1493);
void irmin_config_free(IrminConfig* x1495);
_Bool irmin_config_set(IrminConfig* x1499, char* x1498, IrminType* x1497,
                       IrminValue* x1496);
Irmin* irmin_main(IrminRepo* x1500);
Irmin* irmin_of_branch(IrminRepo* x1502, char* x1501);
IrminCommit* irmin_get_head(Irmin* x1503);
void irmin_set_head(Irmin* x1505, IrminCommit* x1504);
_Bool irmin_fast_forward(Irmin* x1507, IrminCommit* x1506);
_Bool irmin_merge_with_branch(Irmin* x1510, char* x1509, IrminInfo* x1508);
_Bool irmin_merge_with_commit(Irmin* x1513, IrminCommit* x1512,
                              IrminInfo* x1511);
_Bool irmin_merge_into(Irmin* x1516, Irmin* x1515, IrminInfo* x1514);
_Bool irmin_set(Irmin* x1520, IrminPath* x1519, IrminValue* x1518,
                IrminInfo* x1517);
_Bool irmin_test_and_set(Irmin* x1525, IrminPath* x1524, IrminValue* x1523,
                         IrminValue* x1522, IrminInfo* x1521);
_Bool irmin_test_and_set_tree(Irmin* x1530, IrminPath* x1529,
                              IrminTree* x1528, IrminTree* x1527,
                              IrminInfo* x1526);
_Bool irmin_set_tree(Irmin* x1534, IrminPath* x1533, IrminTree* x1532,
                     IrminInfo* x1531);
IrminValue* irmin_find(Irmin* x1536, IrminPath* x1535);
IrminTree* irmin_find_tree(Irmin* x1538, IrminPath* x1537);
_Bool irmin_remove(Irmin* x1541, IrminPath* x1540, IrminInfo* x1539);
_Bool irmin_mem(Irmin* x1543, IrminPath* x1542);
_Bool irmin_mem_tree(Irmin* x1545, IrminPath* x1544);
IrminPathList* irmin_list(Irmin* x1547, IrminPath* x1546);
uint64_t irmin_path_list_length(IrminRepo* x1549, IrminPathList* x1548);
uint64_t irmin_commit_list_length(IrminRepo* x1551, IrminCommitList* x1550);
IrminPath* irmin_path_list_get(IrminRepo* x1554, IrminPathList* x1553,
                               uint64_t x1552);
IrminCommit* irmin_commit_list_get(IrminRepo* x1557, IrminCommitList* x1556,
                                   uint64_t x1555);
void irmin_path_list_free(IrminPathList* x1558);
void irmin_commit_list_free(IrminCommitList* x1559);
void irmin_free(Irmin* x1560);
IrminTree* irmin_tree_new(IrminRepo* x1561);
IrminTree* irmin_tree_clone(IrminRepo* x1563, IrminTree* x1562);
_Bool irmin_tree_mem(IrminRepo* x1566, IrminTree* x1565, IrminPath* x1564);
_Bool irmin_tree_mem_tree(IrminRepo* x1569, IrminTree* x1568,
                          IrminPath* x1567);
IrminValue* irmin_tree_find(IrminRepo* x1572, IrminTree* x1571,
                            IrminPath* x1570);
IrminTree* irmin_tree_find_tree(IrminRepo* x1575, IrminTree* x1574,
                                IrminPath* x1573);
void irmin_tree_add(IrminRepo* x1579, IrminTree* x1578, IrminPath* x1577,
                    IrminValue* x1576);
void irmin_tree_add_tree(IrminRepo* x1583, IrminTree* x1582,
                         IrminPath* x1581, IrminTree* x1580);
void irmin_tree_remove(IrminRepo* x1586, IrminTree* x1585, IrminPath* x1584);
_Bool irmin_tree_equal(IrminRepo* x1589, IrminTree* x1588, IrminTree* x1587);
IrminPathList* irmin_tree_list(IrminRepo* x1592, IrminTree* x1591,
                               IrminPath* x1590);
void irmin_tree_free(IrminTree* x1593);
IrminRepo* irmin_repo_new(IrminConfig* x1594);
IrminBranchList* irmin_repo_branches(IrminRepo* x1595);
uint64_t irmin_branch_list_length(IrminRepo* x1597, IrminBranchList* x1596);
IrminString* irmin_branch_list_get(IrminRepo* x1600, IrminBranchList* x1599,
                                   uint64_t x1598);
_Bool irmin_hash_equal(IrminRepo* x1603, IrminHash* x1602, IrminHash* x1601);
IrminHash* irmin_contents_hash(IrminRepo* x1605, IrminValue* x1604);
IrminValue* irmin_contents_of_hash(IrminRepo* x1607, IrminHash* x1606);
IrminString* irmin_hash_to_string(IrminRepo* x1609, IrminHash* x1608);
IrminHash* irmin_hash_of_string(IrminRepo* x1612, char* x1611, int64_t x1610);
void irmin_hash_free(IrminHash* x1613);
void irmin_branch_list_free(IrminBranchList* x1614);
void irmin_commit_key_free(IrminCommitKey* x1615);
void irmin_node_key_free(IrminNodeKey* x1616);
void irmin_contents_key_free(IrminContentsKey* x1617);
void irmin_repo_free(IrminRepo* x1618);
IrminInfo* irmin_commit_info(IrminRepo* x1620, IrminCommit* x1619);
IrminHash* irmin_commit_hash(IrminRepo* x1622, IrminCommit* x1621);
IrminHash* irmin_commit_key(IrminRepo* x1624, IrminCommit* x1623);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1626, IrminHash* x1625);
IrminCommit* irmin_commit_of_key(IrminRepo* x1628, IrminCommitKey* x1627);
IrminCommit* irmin_commit_new(IrminRepo* x1633, IrminCommit** x1632,
                              uint64_t x1631, IrminTree* x1630,
                              IrminInfo* x1629);
IrminCommitList* irmin_commit_parents(IrminRepo* x1635, IrminCommit* x1634);
_Bool irmin_commit_equal(IrminRepo* x1638, IrminCommit* x1637,
                         IrminCommit* x1636);
void irmin_commit_free(IrminCommit* x1639);
IrminPath* irmin_path(IrminRepo* x1641, char** x1640);
IrminPath* irmin_path_of_string(IrminRepo* x1644, char* x1643, int64_t x1642);
IrminPath* irmin_path_empty(IrminRepo* x1645);
IrminString* irmin_path_to_string(IrminRepo* x1647, IrminPath* x1646);
IrminPath* irmin_path_parent(IrminRepo* x1649, IrminPath* x1648);
IrminPath* irmin_path_append(IrminRepo* x1653, IrminPath* x1652, char* x1651,
                             int64_t x1650);
IrminPath* irmin_path_append_path(IrminRepo* x1656, IrminPath* x1655,
                                  IrminPath* x1654);
_Bool irmin_path_equal(IrminRepo* x1659, IrminPath* x1658, IrminPath* x1657);
void irmin_path_free(IrminPath* x1660);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
