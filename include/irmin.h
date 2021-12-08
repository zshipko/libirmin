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
void caml_startup(char *argv[]);
void caml_shutdown();
IrminType* irmin_type_unit(void);
IrminType* irmin_type_bool(void);
IrminType* irmin_type_int(void);
IrminType* irmin_type_float(void);
IrminType* irmin_type_string(void);
IrminType* irmin_type_bytes(void);
IrminType* irmin_type_list(IrminType* x1105);
IrminType* irmin_type_array(IrminType* x1106);
IrminType* irmin_type_option(IrminType* x1107);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1110);
IrminType* irmin_type_commit(IrminRepo* x1111);
IrminType* irmin_type_tree(IrminRepo* x1112);
IrminType* irmin_type_hash(IrminRepo* x1113);
IrminType* irmin_type_contents(IrminRepo* x1114);
IrminType* irmin_type_pair(IrminType* x1116, IrminType* x1115);
IrminType* irmin_type_triple(IrminType* x1119, IrminType* x1118,
                             IrminType* x1117);
char* irmin_type_name(IrminType* x1121, uint64_t* x1120);
void irmin_type_free(IrminType* x1122);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int64_t x1124);
IrminValue* irmin_value_float(double x1125);
IrminValue* irmin_value_bool(_Bool x1126);
IrminValue* irmin_value_make(void* x1127);
IrminValue* irmin_value_string(char* x1129, int64_t x1128);
char* irmin_value_get_string(IrminValue* x1131, uint64_t* x1130);
int64_t irmin_value_get_int(IrminValue* x1132);
_Bool irmin_value_get_bool(IrminValue* x1133);
double irmin_value_get_float(IrminValue* x1134);
IrminValue* irmin_value_bytes(char* x1136, int64_t x1135);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1139, IrminValue* x1138);
IrminValue* irmin_value_list_hd(IrminValue* x1140);
IrminValue* irmin_value_list_tl(IrminValue* x1141);
IrminValue* irmin_value_array_new(uint64_t x1143, IrminValue* x1142);
void irmin_value_array_set(IrminValue* x1146, uint64_t x1145,
                           IrminValue* x1144);
IrminValue* irmin_value_array_get(IrminValue* x1148, uint64_t x1147);
IrminValue* irmin_value_option(IrminValue* x1149);
IrminValue* irmin_value_pair(IrminValue* x1151, IrminValue* x1150);
IrminValue* irmin_value_triple(IrminValue* x1154, IrminValue* x1153,
                               IrminValue* x1152);
char* irmin_value_to_string(IrminType* x1157, IrminValue* x1156,
                            uint64_t* x1155);
IrminValue* irmin_value_of_string(IrminType* x1160, char* x1159,
                                  int64_t x1158);
char* irmin_value_to_bin(IrminType* x1163, IrminValue* x1162,
                         uint64_t* x1161);
IrminValue* irmin_value_of_bin(IrminType* x1166, char* x1165, int64_t x1164);
char* irmin_value_to_json(IrminType* x1169, IrminValue* x1168,
                          uint64_t* x1167);
IrminValue* irmin_value_of_json(IrminType* x1172, char* x1171, int64_t x1170);
_Bool irmin_value_equal(IrminType* x1175, IrminValue* x1174,
                        IrminValue* x1173);
int irmin_value_compare(IrminType* x1178, IrminValue* x1177,
                        IrminValue* x1176);
void irmin_value_free(IrminValue* x1179);
IrminInfo* irmin_info_new(IrminRepo* x1182, char* x1181, char* x1180);
IrminInfo* irmin_info_update(IrminRepo* x1186, char* x1185, char* x1184,
                             IrminInfo* x1183);
char* irmin_info_message(IrminRepo* x1189, IrminInfo* x1188, uint64_t* x1187);
char* irmin_info_author(IrminRepo* x1192, IrminInfo* x1191, uint64_t* x1190);
int64_t irmin_info_date(IrminRepo* x1194, IrminInfo* x1193);
void irmin_info_free(IrminInfo* x1195);
void irmin_log_level(char* x1196);
IrminConfig* irmin_config_pack(char* x1198, char* x1197);
IrminConfig* irmin_config_tezos(void);
IrminConfig* irmin_config_git(char* x1200);
IrminConfig* irmin_config_git_mem(char* x1201);
IrminConfig* irmin_config_fs(char* x1203, char* x1202);
IrminConfig* irmin_config_mem(char* x1205, char* x1204);
void irmin_config_free(IrminConfig* x1206);
_Bool irmin_config_set(IrminConfig* x1210, char* x1209, IrminType* x1208,
                       IrminValue* x1207);
IrminPath* irmin_path(IrminRepo* x1212, char** x1211);
IrminPath* irmin_path_of_string(IrminRepo* x1215, char* x1214, int64_t x1213);
char* irmin_path_to_string(IrminRepo* x1218, IrminPath* x1217,
                           uint64_t* x1216);
IrminPath* irmin_path_parent(IrminRepo* x1220, IrminPath* x1219);
IrminPath* irmin_path_append(IrminRepo* x1224, IrminPath* x1223, char* x1222,
                             int64_t x1221);
_Bool irmin_path_equal(IrminRepo* x1227, IrminPath* x1226, IrminPath* x1225);
void irmin_path_free(IrminPath* x1228);
void irmin_hash_free(IrminHash* x1229);
_Bool irmin_hash_equal(IrminRepo* x1232, IrminHash* x1231, IrminHash* x1230);
IrminHash* irmin_contents_hash(IrminRepo* x1234, IrminValue* x1233);
IrminValue* irmin_contents_of_hash(IrminRepo* x1236, IrminHash* x1235);
char* irmin_hash_to_string(IrminRepo* x1239, IrminHash* x1238,
                           uint64_t* x1237);
IrminHash* irmin_hash_of_string(IrminRepo* x1242, char* x1241, int64_t x1240);
Irmin* irmin_main(IrminRepo* x1243);
Irmin* irmin_of_branch(IrminRepo* x1245, char* x1244);
IrminCommit* irmin_get_head(Irmin* x1246);
void irmin_set_head(Irmin* x1248, IrminCommit* x1247);
_Bool irmin_fast_forward(Irmin* x1250, IrminCommit* x1249);
_Bool irmin_merge_with_branch(Irmin* x1253, char* x1252, IrminInfo* x1251);
_Bool irmin_merge_with_commit(Irmin* x1256, IrminCommit* x1255,
                              IrminInfo* x1254);
_Bool irmin_set(Irmin* x1260, IrminPath* x1259, IrminValue* x1258,
                IrminInfo* x1257);
_Bool irmin_test_and_set(Irmin* x1265, IrminPath* x1264, IrminValue* x1263,
                         IrminValue* x1262, IrminInfo* x1261);
_Bool irmin_test_and_set_tree(Irmin* x1270, IrminPath* x1269,
                              IrminTree* x1268, IrminTree* x1267,
                              IrminInfo* x1266);
_Bool irmin_set_tree(Irmin* x1274, IrminPath* x1273, IrminTree* x1272,
                     IrminInfo* x1271);
IrminValue* irmin_find(Irmin* x1276, IrminPath* x1275);
IrminTree* irmin_find_tree(Irmin* x1278, IrminPath* x1277);
void irmin_remove(Irmin* x1281, IrminPath* x1280, IrminInfo* x1279);
_Bool irmin_mem(Irmin* x1283, IrminPath* x1282);
_Bool irmin_mem_tree(Irmin* x1285, IrminPath* x1284);
void irmin_free(Irmin* x1286);
IrminTree* irmin_tree_new(IrminRepo* x1287);
IrminTree* irmin_tree_clone(IrminRepo* x1289, IrminTree* x1288);
_Bool irmin_tree_mem(IrminRepo* x1292, IrminTree* x1291, IrminPath* x1290);
_Bool irmin_tree_mem_tree(IrminRepo* x1295, IrminTree* x1294,
                          IrminPath* x1293);
IrminValue* irmin_tree_find(IrminRepo* x1298, IrminTree* x1297,
                            IrminPath* x1296);
IrminTree* irmin_tree_find_tree(IrminRepo* x1301, IrminTree* x1300,
                                IrminPath* x1299);
void irmin_tree_add(IrminRepo* x1305, IrminTree* x1304, IrminPath* x1303,
                    IrminValue* x1302);
void irmin_tree_add_tree(IrminRepo* x1309, IrminTree* x1308,
                         IrminPath* x1307, IrminTree* x1306);
void irmin_tree_remove(IrminRepo* x1312, IrminTree* x1311, IrminPath* x1310);
_Bool irmin_tree_equal(IrminRepo* x1315, IrminTree* x1314, IrminTree* x1313);
void irmin_tree_free(IrminTree* x1316);
IrminRepo* irmin_repo_new(IrminConfig* x1317);
void irmin_repo_free(IrminRepo* x1318);
IrminInfo* irmin_commit_info(IrminRepo* x1320, IrminCommit* x1319);
IrminHash* irmin_commit_hash(IrminRepo* x1322, IrminCommit* x1321);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1324, IrminHash* x1323);
IrminCommit* irmin_commit_new(IrminRepo* x1329, IrminCommit** x1328,
                              uint64_t x1327, IrminTree* x1326,
                              IrminInfo* x1325);
uint64_t irmin_commit_parents_length(IrminRepo* x1331, IrminCommit* x1330);
IrminCommit* irmin_commit_parent(IrminRepo* x1334, IrminCommit* x1333,
                                 uint64_t x1332);
_Bool irmin_commit_equal(IrminRepo* x1337, IrminCommit* x1336,
                         IrminCommit* x1335);
void irmin_commit_free(IrminCommit* x1338);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
