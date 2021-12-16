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
IrminType* irmin_type_list(IrminType* x1306);
IrminType* irmin_type_array(IrminType* x1307);
IrminType* irmin_type_option(IrminType* x1308);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1311);
IrminType* irmin_type_commit(IrminRepo* x1312);
IrminType* irmin_type_tree(IrminRepo* x1313);
IrminType* irmin_type_hash(IrminRepo* x1314);
IrminType* irmin_type_contents(IrminRepo* x1315);
IrminType* irmin_type_pair(IrminType* x1317, IrminType* x1316);
IrminType* irmin_type_triple(IrminType* x1320, IrminType* x1319,
                             IrminType* x1318);
IrminString* irmin_type_name(IrminType* x1321);
void irmin_type_free(IrminType* x1322);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int64_t x1324);
IrminValue* irmin_value_float(double x1325);
IrminValue* irmin_value_bool(_Bool x1326);
IrminValue* irmin_value_clone(IrminValue* x1327);
IrminString* irmin_value_get_string(IrminValue* x1328);
int64_t irmin_value_get_int(IrminValue* x1329);
_Bool irmin_value_get_bool(IrminValue* x1330);
double irmin_value_get_float(IrminValue* x1331);
IrminValue* irmin_value_bytes(char* x1333, int64_t x1332);
IrminValue* irmin_value_string(char* x1335, int64_t x1334);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1338, IrminValue* x1337);
IrminValue* irmin_value_list_hd(IrminValue* x1339);
IrminValue* irmin_value_list_tl(IrminValue* x1340);
IrminValue* irmin_value_list_get(IrminValue* x1342, uint64_t x1341);
uint64_t irmin_value_list_length(IrminValue* x1343);
IrminValue* irmin_value_array_new(uint64_t x1345, IrminValue* x1344);
void irmin_value_array_set(IrminValue* x1348, uint64_t x1347,
                           IrminValue* x1346);
IrminValue* irmin_value_array_get(IrminValue* x1350, uint64_t x1349);
uint64_t irmin_value_array_length(IrminValue* x1351);
IrminValue* irmin_value_option(IrminValue* x1352);
IrminValue* irmin_value_pair(IrminValue* x1354, IrminValue* x1353);
IrminValue* irmin_value_triple(IrminValue* x1357, IrminValue* x1356,
                               IrminValue* x1355);
IrminString* irmin_value_to_string(IrminType* x1359, IrminValue* x1358);
IrminValue* irmin_value_of_string(IrminType* x1362, char* x1361,
                                  int64_t x1360);
IrminString* irmin_value_to_bin(IrminType* x1364, IrminValue* x1363);
IrminValue* irmin_value_of_bin(IrminType* x1367, char* x1366, int64_t x1365);
IrminString* irmin_value_to_json(IrminType* x1369, IrminValue* x1368);
IrminValue* irmin_value_of_json(IrminType* x1372, char* x1371, int64_t x1370);
_Bool irmin_value_equal(IrminType* x1375, IrminValue* x1374,
                        IrminValue* x1373);
int irmin_value_compare(IrminType* x1378, IrminValue* x1377,
                        IrminValue* x1376);
void irmin_value_free(IrminValue* x1379);
IrminString* irmin_string_new(char* x1381, int64_t x1380);
char* irmin_string_data(IrminString* x1382);
uint64_t irmin_string_length(IrminString* x1383);
void irmin_string_free(IrminString* x1384);
IrminInfo* irmin_info_new(IrminRepo* x1387, char* x1386, char* x1385);
void irmin_info_update(IrminRepo* x1391, IrminInfo* x1390, char* x1389,
                       char* x1388);
IrminString* irmin_info_message(IrminRepo* x1393, IrminInfo* x1392);
IrminString* irmin_info_author(IrminRepo* x1395, IrminInfo* x1394);
int64_t irmin_info_date(IrminRepo* x1397, IrminInfo* x1396);
void irmin_info_free(IrminInfo* x1398);
void irmin_log_level(char* x1399);
IrminString* irmin_error_msg(void);
_Bool irmin_error_msg_is_set(void);
IrminConfig* irmin_config_pack(char* x1403, char* x1402);
IrminConfig* irmin_config_tezos(void);
IrminConfig* irmin_config_git(char* x1405);
IrminConfig* irmin_config_git_mem(char* x1406);
IrminConfig* irmin_config_fs(char* x1408, char* x1407);
IrminConfig* irmin_config_mem(char* x1410, char* x1409);
void irmin_config_free(IrminConfig* x1411);
_Bool irmin_config_set(IrminConfig* x1415, char* x1414, IrminType* x1413,
                       IrminValue* x1412);
IrminPath* irmin_path(IrminRepo* x1417, char** x1416);
IrminPath* irmin_path_of_string(IrminRepo* x1420, char* x1419, int64_t x1418);
IrminPath* irmin_path_empty(IrminRepo* x1421);
IrminString* irmin_path_to_string(IrminRepo* x1423, IrminPath* x1422);
IrminPath* irmin_path_parent(IrminRepo* x1425, IrminPath* x1424);
IrminPath* irmin_path_append(IrminRepo* x1429, IrminPath* x1428, char* x1427,
                             int64_t x1426);
IrminPath* irmin_path_append_path(IrminRepo* x1432, IrminPath* x1431,
                                  IrminPath* x1430);
_Bool irmin_path_equal(IrminRepo* x1435, IrminPath* x1434, IrminPath* x1433);
void irmin_path_free(IrminPath* x1436);
void irmin_hash_free(IrminHash* x1437);
_Bool irmin_hash_equal(IrminRepo* x1440, IrminHash* x1439, IrminHash* x1438);
IrminHash* irmin_contents_hash(IrminRepo* x1442, IrminValue* x1441);
IrminValue* irmin_contents_of_hash(IrminRepo* x1444, IrminHash* x1443);
IrminString* irmin_hash_to_string(IrminRepo* x1446, IrminHash* x1445);
IrminHash* irmin_hash_of_string(IrminRepo* x1449, char* x1448, int64_t x1447);
Irmin* irmin_main(IrminRepo* x1450);
Irmin* irmin_of_branch(IrminRepo* x1452, char* x1451);
IrminCommit* irmin_get_head(Irmin* x1453);
void irmin_set_head(Irmin* x1455, IrminCommit* x1454);
_Bool irmin_fast_forward(Irmin* x1457, IrminCommit* x1456);
_Bool irmin_merge_with_branch(Irmin* x1460, char* x1459, IrminInfo* x1458);
_Bool irmin_merge_with_commit(Irmin* x1463, IrminCommit* x1462,
                              IrminInfo* x1461);
_Bool irmin_merge_into(Irmin* x1466, Irmin* x1465, IrminInfo* x1464);
_Bool irmin_set(Irmin* x1470, IrminPath* x1469, IrminValue* x1468,
                IrminInfo* x1467);
_Bool irmin_test_and_set(Irmin* x1475, IrminPath* x1474, IrminValue* x1473,
                         IrminValue* x1472, IrminInfo* x1471);
_Bool irmin_test_and_set_tree(Irmin* x1480, IrminPath* x1479,
                              IrminTree* x1478, IrminTree* x1477,
                              IrminInfo* x1476);
_Bool irmin_set_tree(Irmin* x1484, IrminPath* x1483, IrminTree* x1482,
                     IrminInfo* x1481);
IrminValue* irmin_find(Irmin* x1486, IrminPath* x1485);
IrminTree* irmin_find_tree(Irmin* x1488, IrminPath* x1487);
_Bool irmin_remove(Irmin* x1491, IrminPath* x1490, IrminInfo* x1489);
_Bool irmin_mem(Irmin* x1493, IrminPath* x1492);
_Bool irmin_mem_tree(Irmin* x1495, IrminPath* x1494);
IrminPathList* irmin_list(Irmin* x1497, IrminPath* x1496);
uint64_t irmin_path_list_length(IrminPathList* x1498);
uint64_t irmin_commit_list_length(IrminCommitList* x1499);
IrminPath* irmin_path_list_get(IrminPathList* x1501, uint64_t x1500);
IrminCommit* irmin_commit_list_get(IrminCommitList* x1503, uint64_t x1502);
void irmin_path_list_free(IrminPathList* x1504);
void irmin_commit_list_free(IrminCommitList* x1505);
void irmin_free(Irmin* x1506);
IrminTree* irmin_tree_new(IrminRepo* x1507);
IrminTree* irmin_tree_clone(IrminRepo* x1509, IrminTree* x1508);
_Bool irmin_tree_mem(IrminRepo* x1512, IrminTree* x1511, IrminPath* x1510);
_Bool irmin_tree_mem_tree(IrminRepo* x1515, IrminTree* x1514,
                          IrminPath* x1513);
IrminValue* irmin_tree_find(IrminRepo* x1518, IrminTree* x1517,
                            IrminPath* x1516);
IrminTree* irmin_tree_find_tree(IrminRepo* x1521, IrminTree* x1520,
                                IrminPath* x1519);
void irmin_tree_add(IrminRepo* x1525, IrminTree* x1524, IrminPath* x1523,
                    IrminValue* x1522);
void irmin_tree_add_tree(IrminRepo* x1529, IrminTree* x1528,
                         IrminPath* x1527, IrminTree* x1526);
void irmin_tree_remove(IrminRepo* x1532, IrminTree* x1531, IrminPath* x1530);
_Bool irmin_tree_equal(IrminRepo* x1535, IrminTree* x1534, IrminTree* x1533);
IrminPathList* irmin_tree_list(IrminRepo* x1538, IrminTree* x1537,
                               IrminPath* x1536);
void irmin_tree_free(IrminTree* x1539);
IrminRepo* irmin_repo_new(IrminConfig* x1540);
IrminBranchList* irmin_repo_branches(IrminRepo* x1541);
uint64_t irmin_branch_list_length(IrminBranchList* x1542);
IrminString* irmin_branch_list_get(IrminBranchList* x1544, uint64_t x1543);
void irmin_branch_list_free(IrminBranchList* x1545);
void irmin_repo_free(IrminRepo* x1546);
IrminInfo* irmin_commit_info(IrminRepo* x1548, IrminCommit* x1547);
IrminHash* irmin_commit_hash(IrminRepo* x1550, IrminCommit* x1549);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1552, IrminHash* x1551);
IrminCommit* irmin_commit_new(IrminRepo* x1557, IrminCommit** x1556,
                              uint64_t x1555, IrminTree* x1554,
                              IrminInfo* x1553);
IrminCommitList* irmin_commit_parents(IrminRepo* x1559, IrminCommit* x1558);
_Bool irmin_commit_equal(IrminRepo* x1562, IrminCommit* x1561,
                         IrminCommit* x1560);
void irmin_commit_free(IrminCommit* x1563);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
