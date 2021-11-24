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
IrminType* irmin_type_list(IrminType* x1087);
IrminType* irmin_type_array(IrminType* x1088);
IrminType* irmin_type_option(IrminType* x1089);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1092);
IrminType* irmin_type_commit(IrminRepo* x1093);
IrminType* irmin_type_tree(IrminRepo* x1094);
IrminType* irmin_type_hash(IrminRepo* x1095);
IrminType* irmin_type_contents(IrminRepo* x1096);
IrminType* irmin_type_pair(IrminType* x1098, IrminType* x1097);
IrminType* irmin_type_triple(IrminType* x1101, IrminType* x1100,
                             IrminType* x1099);
char* irmin_type_name(IrminType* x1103, int* x1102);
void irmin_type_free(IrminType* x1104);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int x1106);
IrminValue* irmin_value_float(float x1107);
IrminValue* irmin_value_bool(_Bool x1108);
IrminValue* irmin_value_make(void* x1109);
IrminValue* irmin_value_string(char* x1111, int x1110);
char* irmin_value_get_string(IrminValue* x1113, int* x1112);
int irmin_value_get_int(IrminValue* x1114);
_Bool irmin_value_get_bool(IrminValue* x1115);
IrminValue* irmin_value_bytes(char* x1117, int x1116);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1120, IrminValue* x1119);
IrminValue* irmin_value_list_hd(IrminValue* x1121);
IrminValue* irmin_value_list_tl(IrminValue* x1122);
IrminValue* irmin_value_array_new(int x1124, IrminValue* x1123);
void irmin_value_array_set(IrminValue* x1127, int x1126, IrminValue* x1125);
IrminValue* irmin_value_array_get(IrminValue* x1129, int x1128);
IrminValue* irmin_value_option(IrminValue* x1130);
IrminValue* irmin_value_pair(IrminValue* x1132, IrminValue* x1131);
IrminValue* irmin_value_triple(IrminValue* x1135, IrminValue* x1134,
                               IrminValue* x1133);
char* irmin_value_to_string(IrminType* x1138, IrminValue* x1137, int* x1136);
IrminValue* irmin_value_of_string(IrminType* x1141, char* x1140, int x1139);
char* irmin_value_to_bin(IrminType* x1144, IrminValue* x1143, int* x1142);
IrminValue* irmin_value_of_bin(IrminType* x1147, char* x1146, int x1145);
char* irmin_value_to_json(IrminType* x1150, IrminValue* x1149, int* x1148);
IrminValue* irmin_value_of_json(IrminType* x1153, char* x1152, int x1151);
_Bool irmin_value_equal(IrminType* x1156, IrminValue* x1155,
                        IrminValue* x1154);
int irmin_value_compare(IrminType* x1159, IrminValue* x1158,
                        IrminValue* x1157);
void irmin_value_free(IrminValue* x1160);
IrminInfo* irmin_info_new(IrminRepo* x1163, char* x1162, char* x1161);
IrminInfo* irmin_info_update(IrminRepo* x1167, char* x1166, char* x1165,
                             IrminInfo* x1164);
char* irmin_info_message(IrminRepo* x1170, IrminInfo* x1169, int* x1168);
char* irmin_info_author(IrminRepo* x1173, IrminInfo* x1172, int* x1171);
int64_t irmin_info_date(IrminRepo* x1175, IrminInfo* x1174);
void irmin_info_free(IrminInfo* x1176);
void irmin_log_level(char* x1177);
IrminConfig* irmin_config_pack(char* x1179, char* x1178);
IrminConfig* irmin_config_git(char* x1180);
IrminConfig* irmin_config_git_mem(char* x1181);
IrminConfig* irmin_config_fs(char* x1183, char* x1182);
IrminConfig* irmin_config_mem(char* x1185, char* x1184);
void irmin_config_free(IrminConfig* x1186);
_Bool irmin_config_set(IrminConfig* x1190, char* x1189, IrminType* x1188,
                       IrminValue* x1187);
IrminPath* irmin_path(IrminRepo* x1192, char** x1191);
IrminPath* irmin_path_of_string(IrminRepo* x1195, char* x1194, int x1193);
char* irmin_path_to_string(IrminRepo* x1198, IrminPath* x1197, int* x1196);
IrminPath* irmin_path_parent(IrminRepo* x1200, IrminPath* x1199);
IrminPath* irmin_path_append(IrminRepo* x1204, IrminPath* x1203, char* x1202,
                             int x1201);
_Bool irmin_path_equal(IrminRepo* x1207, IrminPath* x1206, IrminPath* x1205);
void irmin_path_free(IrminPath* x1208);
void irmin_hash_free(IrminHash* x1209);
_Bool irmin_hash_equal(IrminRepo* x1212, IrminHash* x1211, IrminHash* x1210);
IrminHash* irmin_contents_hash(IrminRepo* x1214, IrminValue* x1213);
IrminValue* irmin_contents_of_hash(IrminRepo* x1216, IrminHash* x1215);
char* irmin_hash_to_string(IrminRepo* x1219, IrminHash* x1218, int* x1217);
IrminHash* irmin_hash_of_string(IrminRepo* x1222, char* x1221, int x1220);
Irmin* irmin_main(IrminRepo* x1223);
Irmin* irmin_of_branch(IrminRepo* x1225, char* x1224);
IrminCommit* irmin_get_head(Irmin* x1226);
void irmin_set_head(Irmin* x1228, IrminCommit* x1227);
_Bool irmin_fast_forward(Irmin* x1230, IrminCommit* x1229);
_Bool irmin_merge_with_branch(Irmin* x1233, char* x1232, IrminInfo* x1231);
_Bool irmin_merge_with_commit(Irmin* x1236, IrminCommit* x1235,
                              IrminInfo* x1234);
_Bool irmin_set(Irmin* x1240, IrminPath* x1239, IrminValue* x1238,
                IrminInfo* x1237);
_Bool irmin_test_and_set(Irmin* x1245, IrminPath* x1244, IrminValue* x1243,
                         IrminValue* x1242, IrminInfo* x1241);
_Bool irmin_test_and_set_tree(Irmin* x1250, IrminPath* x1249,
                              IrminTree* x1248, IrminTree* x1247,
                              IrminInfo* x1246);
_Bool irmin_set_tree(Irmin* x1254, IrminPath* x1253, IrminTree* x1252,
                     IrminInfo* x1251);
IrminValue* irmin_find(Irmin* x1256, IrminPath* x1255);
IrminTree* irmin_find_tree(Irmin* x1258, IrminPath* x1257);
void irmin_remove(Irmin* x1261, IrminPath* x1260, IrminInfo* x1259);
_Bool irmin_mem(Irmin* x1263, IrminPath* x1262);
_Bool irmin_mem_tree(Irmin* x1265, IrminPath* x1264);
void irmin_free(Irmin* x1266);
IrminTree* irmin_tree_new(IrminRepo* x1267);
IrminTree* irmin_tree_clone(IrminRepo* x1269, IrminTree* x1268);
_Bool irmin_tree_mem(IrminRepo* x1272, IrminTree* x1271, IrminPath* x1270);
_Bool irmin_tree_mem_tree(IrminRepo* x1275, IrminTree* x1274,
                          IrminPath* x1273);
IrminValue* irmin_tree_find(IrminRepo* x1278, IrminTree* x1277,
                            IrminPath* x1276);
IrminTree* irmin_tree_find_tree(IrminRepo* x1281, IrminTree* x1280,
                                IrminPath* x1279);
void irmin_tree_add(IrminRepo* x1285, IrminTree* x1284, IrminPath* x1283,
                    IrminValue* x1282);
void irmin_tree_add_tree(IrminRepo* x1289, IrminTree* x1288,
                         IrminPath* x1287, IrminTree* x1286);
void irmin_tree_remove(IrminRepo* x1292, IrminTree* x1291, IrminPath* x1290);
_Bool irmin_tree_equal(IrminRepo* x1295, IrminTree* x1294, IrminTree* x1293);
void irmin_tree_free(IrminTree* x1296);
IrminRepo* irmin_repo_new(IrminConfig* x1297);
void irmin_repo_free(IrminRepo* x1298);
IrminInfo* irmin_commit_info(IrminRepo* x1300, IrminCommit* x1299);
IrminHash* irmin_commit_hash(IrminRepo* x1302, IrminCommit* x1301);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1304, IrminHash* x1303);
IrminCommit* irmin_commit_new(IrminRepo* x1309, IrminCommit** x1308,
                              int x1307, IrminTree* x1306, IrminInfo* x1305);
int irmin_commit_parents_length(IrminRepo* x1311, IrminCommit* x1310);
IrminCommit* irmin_commit_parent(IrminRepo* x1314, IrminCommit* x1313,
                                 int x1312);
_Bool irmin_commit_equal(IrminRepo* x1317, IrminCommit* x1316,
                         IrminCommit* x1315);
void irmin_commit_free(IrminCommit* x1318);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
