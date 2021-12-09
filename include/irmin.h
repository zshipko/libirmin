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
typedef struct IrminList IrminList;
typedef struct IrminArray IrminArray;
void caml_startup(char *argv[]);
void caml_shutdown();
IrminType* irmin_type_unit(void);
IrminType* irmin_type_bool(void);
IrminType* irmin_type_int(void);
IrminType* irmin_type_float(void);
IrminType* irmin_type_string(void);
IrminType* irmin_type_bytes(void);
IrminType* irmin_type_list(IrminType* x1183);
IrminType* irmin_type_array(IrminType* x1184);
IrminType* irmin_type_option(IrminType* x1185);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1188);
IrminType* irmin_type_commit(IrminRepo* x1189);
IrminType* irmin_type_tree(IrminRepo* x1190);
IrminType* irmin_type_hash(IrminRepo* x1191);
IrminType* irmin_type_contents(IrminRepo* x1192);
IrminType* irmin_type_pair(IrminType* x1194, IrminType* x1193);
IrminType* irmin_type_triple(IrminType* x1197, IrminType* x1196,
                             IrminType* x1195);
IrminString* irmin_type_name(IrminType* x1198);
void irmin_type_free(IrminType* x1199);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int64_t x1201);
IrminValue* irmin_value_float(double x1202);
IrminValue* irmin_value_bool(_Bool x1203);
IrminValue* irmin_value_make(void* x1204);
IrminString* irmin_value_get_string(IrminValue* x1205);
int64_t irmin_value_get_int(IrminValue* x1206);
_Bool irmin_value_get_bool(IrminValue* x1207);
double irmin_value_get_float(IrminValue* x1208);
IrminValue* irmin_value_bytes(char* x1210, int64_t x1209);
IrminValue* irmin_list_new(void);
void irmin_list_free(IrminList* x1212);
void irmin_list_add(IrminValue* x1214, IrminValue* x1213);
IrminValue* irmin_list_hd(IrminValue* x1215);
IrminValue* irmin_list_tl(IrminValue* x1216);
uint64_t irmin_list_length(IrminList* x1217);
IrminArray* irmin_array_new(uint64_t x1219, IrminValue* x1218);
void irmin_array_free(IrminArray* x1220);
void irmin_array_set(IrminArray* x1223, uint64_t x1222, IrminValue* x1221);
IrminValue* irmin_array_get(IrminArray* x1225, uint64_t x1224);
uint64_t irmin_array_length(IrminArray* x1226);
IrminList* irmin_array_to_list(IrminArray* x1227);
IrminArray* irmin_array_of_list(IrminList* x1228);
IrminValue* irmin_value_option(IrminValue* x1229);
IrminValue* irmin_value_pair(IrminValue* x1231, IrminValue* x1230);
IrminValue* irmin_value_triple(IrminValue* x1234, IrminValue* x1233,
                               IrminValue* x1232);
IrminString* irmin_value_to_string(IrminType* x1236, IrminValue* x1235);
IrminValue* irmin_value_of_string(IrminType* x1239, char* x1238,
                                  int64_t x1237);
IrminString* irmin_value_to_bin(IrminType* x1241, IrminValue* x1240);
IrminValue* irmin_value_of_bin(IrminType* x1244, char* x1243, int64_t x1242);
IrminString* irmin_value_to_json(IrminType* x1246, IrminValue* x1245);
IrminValue* irmin_value_of_json(IrminType* x1249, char* x1248, int64_t x1247);
_Bool irmin_value_equal(IrminType* x1252, IrminValue* x1251,
                        IrminValue* x1250);
int irmin_value_compare(IrminType* x1255, IrminValue* x1254,
                        IrminValue* x1253);
void irmin_value_free(IrminValue* x1256);
IrminString* irmin_string_new(char* x1258, int64_t x1257);
char* irmin_string_data(IrminString* x1259);
uint64_t irmin_string_length(IrminString* x1260);
void irmin_string_free(IrminString* x1261);
IrminInfo* irmin_info_new(IrminRepo* x1264, char* x1263, char* x1262);
void irmin_info_update(IrminRepo* x1268, IrminInfo* x1267, char* x1266,
                       char* x1265);
IrminString* irmin_info_message(IrminRepo* x1270, IrminInfo* x1269);
IrminString* irmin_info_author(IrminRepo* x1272, IrminInfo* x1271);
int64_t irmin_info_date(IrminRepo* x1274, IrminInfo* x1273);
void irmin_info_free(IrminInfo* x1275);
void irmin_log_level(char* x1276);
IrminConfig* irmin_config_pack(char* x1278, char* x1277);
IrminConfig* irmin_config_tezos(void);
IrminConfig* irmin_config_git(char* x1280);
IrminConfig* irmin_config_git_mem(char* x1281);
IrminConfig* irmin_config_fs(char* x1283, char* x1282);
IrminConfig* irmin_config_mem(char* x1285, char* x1284);
void irmin_config_free(IrminConfig* x1286);
_Bool irmin_config_set(IrminConfig* x1290, char* x1289, IrminType* x1288,
                       IrminValue* x1287);
IrminPath* irmin_path(IrminRepo* x1292, char** x1291);
IrminPath* irmin_path_of_string(IrminRepo* x1295, char* x1294, int64_t x1293);
IrminString* irmin_path_to_string(IrminRepo* x1297, IrminPath* x1296);
IrminPath* irmin_path_parent(IrminRepo* x1299, IrminPath* x1298);
IrminPath* irmin_path_append(IrminRepo* x1303, IrminPath* x1302, char* x1301,
                             int64_t x1300);
_Bool irmin_path_equal(IrminRepo* x1306, IrminPath* x1305, IrminPath* x1304);
void irmin_path_free(IrminPath* x1307);
void irmin_hash_free(IrminHash* x1308);
_Bool irmin_hash_equal(IrminRepo* x1311, IrminHash* x1310, IrminHash* x1309);
IrminHash* irmin_contents_hash(IrminRepo* x1313, IrminValue* x1312);
IrminValue* irmin_contents_of_hash(IrminRepo* x1315, IrminHash* x1314);
IrminString* irmin_hash_to_string(IrminRepo* x1317, IrminHash* x1316);
IrminHash* irmin_hash_of_string(IrminRepo* x1320, char* x1319, int64_t x1318);
Irmin* irmin_main(IrminRepo* x1321);
Irmin* irmin_of_branch(IrminRepo* x1323, char* x1322);
IrminCommit* irmin_get_head(Irmin* x1324);
void irmin_set_head(Irmin* x1326, IrminCommit* x1325);
_Bool irmin_fast_forward(Irmin* x1328, IrminCommit* x1327);
_Bool irmin_merge_with_branch(Irmin* x1331, char* x1330, IrminInfo* x1329);
_Bool irmin_merge_with_commit(Irmin* x1334, IrminCommit* x1333,
                              IrminInfo* x1332);
_Bool irmin_set(Irmin* x1338, IrminPath* x1337, IrminValue* x1336,
                IrminInfo* x1335);
_Bool irmin_test_and_set(Irmin* x1343, IrminPath* x1342, IrminValue* x1341,
                         IrminValue* x1340, IrminInfo* x1339);
_Bool irmin_test_and_set_tree(Irmin* x1348, IrminPath* x1347,
                              IrminTree* x1346, IrminTree* x1345,
                              IrminInfo* x1344);
_Bool irmin_set_tree(Irmin* x1352, IrminPath* x1351, IrminTree* x1350,
                     IrminInfo* x1349);
IrminValue* irmin_find(Irmin* x1354, IrminPath* x1353);
IrminTree* irmin_find_tree(Irmin* x1356, IrminPath* x1355);
void irmin_remove(Irmin* x1359, IrminPath* x1358, IrminInfo* x1357);
_Bool irmin_mem(Irmin* x1361, IrminPath* x1360);
_Bool irmin_mem_tree(Irmin* x1363, IrminPath* x1362);
void irmin_free(Irmin* x1364);
IrminTree* irmin_tree_new(IrminRepo* x1365);
IrminTree* irmin_tree_clone(IrminRepo* x1367, IrminTree* x1366);
_Bool irmin_tree_mem(IrminRepo* x1370, IrminTree* x1369, IrminPath* x1368);
_Bool irmin_tree_mem_tree(IrminRepo* x1373, IrminTree* x1372,
                          IrminPath* x1371);
IrminValue* irmin_tree_find(IrminRepo* x1376, IrminTree* x1375,
                            IrminPath* x1374);
IrminTree* irmin_tree_find_tree(IrminRepo* x1379, IrminTree* x1378,
                                IrminPath* x1377);
void irmin_tree_add(IrminRepo* x1383, IrminTree* x1382, IrminPath* x1381,
                    IrminValue* x1380);
void irmin_tree_add_tree(IrminRepo* x1387, IrminTree* x1386,
                         IrminPath* x1385, IrminTree* x1384);
void irmin_tree_remove(IrminRepo* x1390, IrminTree* x1389, IrminPath* x1388);
_Bool irmin_tree_equal(IrminRepo* x1393, IrminTree* x1392, IrminTree* x1391);
void irmin_tree_free(IrminTree* x1394);
IrminRepo* irmin_repo_new(IrminConfig* x1395);
void irmin_repo_free(IrminRepo* x1396);
IrminInfo* irmin_commit_info(IrminRepo* x1398, IrminCommit* x1397);
IrminHash* irmin_commit_hash(IrminRepo* x1400, IrminCommit* x1399);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1402, IrminHash* x1401);
IrminCommit* irmin_commit_new(IrminRepo* x1407, IrminCommit** x1406,
                              uint64_t x1405, IrminTree* x1404,
                              IrminInfo* x1403);
IrminList* irmin_commit_parents(IrminRepo* x1409, IrminCommit* x1408);
uint64_t irmin_commit_parents_length(IrminRepo* x1411, IrminCommit* x1410);
IrminCommit* irmin_commit_parent(IrminRepo* x1414, IrminCommit* x1413,
                                 uint64_t x1412);
_Bool irmin_commit_equal(IrminRepo* x1417, IrminCommit* x1416,
                         IrminCommit* x1415);
void irmin_commit_free(IrminCommit* x1418);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
