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
IrminType* irmin_type_list(IrminType* x1160);
IrminType* irmin_type_array(IrminType* x1161);
IrminType* irmin_type_option(IrminType* x1162);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1165);
IrminType* irmin_type_commit(IrminRepo* x1166);
IrminType* irmin_type_tree(IrminRepo* x1167);
IrminType* irmin_type_hash(IrminRepo* x1168);
IrminType* irmin_type_contents(IrminRepo* x1169);
IrminType* irmin_type_pair(IrminType* x1171, IrminType* x1170);
IrminType* irmin_type_triple(IrminType* x1174, IrminType* x1173,
                             IrminType* x1172);
IrminString* irmin_type_name(IrminType* x1175);
void irmin_type_free(IrminType* x1176);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int64_t x1178);
IrminValue* irmin_value_float(double x1179);
IrminValue* irmin_value_bool(_Bool x1180);
IrminValue* irmin_value_clone(IrminValue* x1181);
IrminString* irmin_value_get_string(IrminValue* x1182);
int64_t irmin_value_get_int(IrminValue* x1183);
_Bool irmin_value_get_bool(IrminValue* x1184);
double irmin_value_get_float(IrminValue* x1185);
IrminValue* irmin_value_bytes(char* x1187, int64_t x1186);
IrminValue* irmin_value_string(char* x1189, int64_t x1188);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1192, IrminValue* x1191);
IrminValue* irmin_value_list_hd(IrminValue* x1193);
IrminValue* irmin_value_list_tl(IrminValue* x1194);
IrminValue* irmin_value_list_get(IrminValue* x1196, uint64_t x1195);
uint64_t irmin_value_list_length(IrminValue* x1197);
IrminValue* irmin_value_array_new(uint64_t x1199, IrminValue* x1198);
void irmin_value_array_set(IrminValue* x1202, uint64_t x1201,
                           IrminValue* x1200);
IrminValue* irmin_value_array_get(IrminValue* x1204, uint64_t x1203);
uint64_t irmin_value_array_length(IrminValue* x1205);
IrminValue* irmin_value_option(IrminValue* x1206);
IrminValue* irmin_value_pair(IrminValue* x1208, IrminValue* x1207);
IrminValue* irmin_value_triple(IrminValue* x1211, IrminValue* x1210,
                               IrminValue* x1209);
IrminString* irmin_value_to_string(IrminType* x1213, IrminValue* x1212);
IrminValue* irmin_value_of_string(IrminType* x1216, char* x1215,
                                  int64_t x1214);
IrminString* irmin_value_to_bin(IrminType* x1218, IrminValue* x1217);
IrminValue* irmin_value_of_bin(IrminType* x1221, char* x1220, int64_t x1219);
IrminString* irmin_value_to_json(IrminType* x1223, IrminValue* x1222);
IrminValue* irmin_value_of_json(IrminType* x1226, char* x1225, int64_t x1224);
_Bool irmin_value_equal(IrminType* x1229, IrminValue* x1228,
                        IrminValue* x1227);
int irmin_value_compare(IrminType* x1232, IrminValue* x1231,
                        IrminValue* x1230);
void irmin_value_free(IrminValue* x1233);
IrminString* irmin_string_new(char* x1235, int64_t x1234);
char* irmin_string_data(IrminString* x1236);
uint64_t irmin_string_length(IrminString* x1237);
void irmin_string_free(IrminString* x1238);
IrminInfo* irmin_info_new(IrminRepo* x1241, char* x1240, char* x1239);
void irmin_info_update(IrminRepo* x1245, IrminInfo* x1244, char* x1243,
                       char* x1242);
IrminString* irmin_info_message(IrminRepo* x1247, IrminInfo* x1246);
IrminString* irmin_info_author(IrminRepo* x1249, IrminInfo* x1248);
int64_t irmin_info_date(IrminRepo* x1251, IrminInfo* x1250);
void irmin_info_free(IrminInfo* x1252);
void irmin_log_level(char* x1253);
IrminConfig* irmin_config_pack(char* x1255, char* x1254);
IrminConfig* irmin_config_tezos(void);
IrminConfig* irmin_config_git(char* x1257);
IrminConfig* irmin_config_git_mem(char* x1258);
IrminConfig* irmin_config_fs(char* x1260, char* x1259);
IrminConfig* irmin_config_mem(char* x1262, char* x1261);
void irmin_config_free(IrminConfig* x1263);
_Bool irmin_config_set(IrminConfig* x1267, char* x1266, IrminType* x1265,
                       IrminValue* x1264);
IrminPath* irmin_path(IrminRepo* x1269, char** x1268);
IrminPath* irmin_path_of_string(IrminRepo* x1272, char* x1271, int64_t x1270);
IrminString* irmin_path_to_string(IrminRepo* x1274, IrminPath* x1273);
IrminPath* irmin_path_parent(IrminRepo* x1276, IrminPath* x1275);
IrminPath* irmin_path_append(IrminRepo* x1280, IrminPath* x1279, char* x1278,
                             int64_t x1277);
_Bool irmin_path_equal(IrminRepo* x1283, IrminPath* x1282, IrminPath* x1281);
void irmin_path_free(IrminPath* x1284);
void irmin_hash_free(IrminHash* x1285);
_Bool irmin_hash_equal(IrminRepo* x1288, IrminHash* x1287, IrminHash* x1286);
IrminHash* irmin_contents_hash(IrminRepo* x1290, IrminValue* x1289);
IrminValue* irmin_contents_of_hash(IrminRepo* x1292, IrminHash* x1291);
IrminString* irmin_hash_to_string(IrminRepo* x1294, IrminHash* x1293);
IrminHash* irmin_hash_of_string(IrminRepo* x1297, char* x1296, int64_t x1295);
Irmin* irmin_main(IrminRepo* x1298);
Irmin* irmin_of_branch(IrminRepo* x1300, char* x1299);
IrminCommit* irmin_get_head(Irmin* x1301);
void irmin_set_head(Irmin* x1303, IrminCommit* x1302);
_Bool irmin_fast_forward(Irmin* x1305, IrminCommit* x1304);
_Bool irmin_merge_with_branch(Irmin* x1308, char* x1307, IrminInfo* x1306);
_Bool irmin_merge_with_commit(Irmin* x1311, IrminCommit* x1310,
                              IrminInfo* x1309);
_Bool irmin_set(Irmin* x1315, IrminPath* x1314, IrminValue* x1313,
                IrminInfo* x1312);
_Bool irmin_test_and_set(Irmin* x1320, IrminPath* x1319, IrminValue* x1318,
                         IrminValue* x1317, IrminInfo* x1316);
_Bool irmin_test_and_set_tree(Irmin* x1325, IrminPath* x1324,
                              IrminTree* x1323, IrminTree* x1322,
                              IrminInfo* x1321);
_Bool irmin_set_tree(Irmin* x1329, IrminPath* x1328, IrminTree* x1327,
                     IrminInfo* x1326);
IrminValue* irmin_find(Irmin* x1331, IrminPath* x1330);
IrminTree* irmin_find_tree(Irmin* x1333, IrminPath* x1332);
void irmin_remove(Irmin* x1336, IrminPath* x1335, IrminInfo* x1334);
_Bool irmin_mem(Irmin* x1338, IrminPath* x1337);
_Bool irmin_mem_tree(Irmin* x1340, IrminPath* x1339);
void irmin_free(Irmin* x1341);
IrminTree* irmin_tree_new(IrminRepo* x1342);
IrminTree* irmin_tree_clone(IrminRepo* x1344, IrminTree* x1343);
_Bool irmin_tree_mem(IrminRepo* x1347, IrminTree* x1346, IrminPath* x1345);
_Bool irmin_tree_mem_tree(IrminRepo* x1350, IrminTree* x1349,
                          IrminPath* x1348);
IrminValue* irmin_tree_find(IrminRepo* x1353, IrminTree* x1352,
                            IrminPath* x1351);
IrminTree* irmin_tree_find_tree(IrminRepo* x1356, IrminTree* x1355,
                                IrminPath* x1354);
void irmin_tree_add(IrminRepo* x1360, IrminTree* x1359, IrminPath* x1358,
                    IrminValue* x1357);
void irmin_tree_add_tree(IrminRepo* x1364, IrminTree* x1363,
                         IrminPath* x1362, IrminTree* x1361);
void irmin_tree_remove(IrminRepo* x1367, IrminTree* x1366, IrminPath* x1365);
_Bool irmin_tree_equal(IrminRepo* x1370, IrminTree* x1369, IrminTree* x1368);
void irmin_tree_free(IrminTree* x1371);
IrminRepo* irmin_repo_new(IrminConfig* x1372);
void irmin_repo_free(IrminRepo* x1373);
IrminInfo* irmin_commit_info(IrminRepo* x1375, IrminCommit* x1374);
IrminHash* irmin_commit_hash(IrminRepo* x1377, IrminCommit* x1376);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1379, IrminHash* x1378);
IrminCommit* irmin_commit_new(IrminRepo* x1384, IrminCommit** x1383,
                              uint64_t x1382, IrminTree* x1381,
                              IrminInfo* x1380);
uint64_t irmin_commit_parents_length(IrminRepo* x1386, IrminCommit* x1385);
IrminCommit* irmin_commit_parent(IrminRepo* x1389, IrminCommit* x1388,
                                 uint64_t x1387);
_Bool irmin_commit_equal(IrminRepo* x1392, IrminCommit* x1391,
                         IrminCommit* x1390);
void irmin_commit_free(IrminCommit* x1393);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
