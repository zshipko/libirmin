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
IrminType* irmin_type_string(void);
IrminType* irmin_type_bytes(void);
IrminType* irmin_type_list(IrminType* x1070);
IrminType* irmin_type_array(IrminType* x1071);
IrminType* irmin_type_option(IrminType* x1072);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1075);
IrminType* irmin_type_commit(IrminRepo* x1076);
IrminType* irmin_type_tree(IrminRepo* x1077);
IrminType* irmin_type_hash(IrminRepo* x1078);
IrminType* irmin_type_contents(IrminRepo* x1079);
IrminType* irmin_type_pair(IrminType* x1081, IrminType* x1080);
IrminType* irmin_type_triple(IrminType* x1084, IrminType* x1083,
                             IrminType* x1082);
char* irmin_type_name(IrminType* x1086, int* x1085);
void irmin_type_free(IrminType* x1087);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int x1089);
IrminValue* irmin_value_bool(_Bool x1090);
IrminValue* irmin_value_make(void* x1091);
IrminValue* irmin_value_string(char* x1093, int x1092);
char* irmin_value_get_string(IrminValue* x1095, int* x1094);
int irmin_value_get_int(IrminValue* x1096);
_Bool irmin_value_get_bool(IrminValue* x1097);
IrminValue* irmin_value_bytes(char* x1099, int x1098);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1102, IrminValue* x1101);
IrminValue* irmin_value_list_hd(IrminValue* x1103);
IrminValue* irmin_value_list_tl(IrminValue* x1104);
IrminValue* irmin_value_array_new(int x1106, IrminValue* x1105);
void irmin_value_array_set(IrminValue* x1109, int x1108, IrminValue* x1107);
IrminValue* irmin_value_array_get(IrminValue* x1111, int x1110);
IrminValue* irmin_value_option(IrminValue* x1112);
IrminValue* irmin_value_pair(IrminValue* x1114, IrminValue* x1113);
IrminValue* irmin_value_triple(IrminValue* x1117, IrminValue* x1116,
                               IrminValue* x1115);
char* irmin_value_to_string(IrminType* x1120, IrminValue* x1119, int* x1118);
IrminValue* irmin_value_of_string(IrminType* x1123, char* x1122, int x1121);
char* irmin_value_to_bin(IrminType* x1126, IrminValue* x1125, int* x1124);
IrminValue* irmin_value_of_bin(IrminType* x1129, char* x1128, int x1127);
char* irmin_value_to_json(IrminType* x1132, IrminValue* x1131, int* x1130);
IrminValue* irmin_value_of_json(IrminType* x1135, char* x1134, int x1133);
_Bool irmin_value_equal(IrminType* x1138, IrminValue* x1137,
                        IrminValue* x1136);
int irmin_value_compare(IrminType* x1141, IrminValue* x1140,
                        IrminValue* x1139);
void irmin_value_free(IrminValue* x1142);
IrminInfo* irmin_info_new(IrminRepo* x1145, char* x1144, char* x1143);
IrminInfo* irmin_info_update(IrminRepo* x1149, char* x1148, char* x1147,
                             IrminInfo* x1146);
char* irmin_info_message(IrminRepo* x1152, IrminInfo* x1151, int* x1150);
char* irmin_info_author(IrminRepo* x1155, IrminInfo* x1154, int* x1153);
int64_t irmin_info_date(IrminRepo* x1157, IrminInfo* x1156);
void irmin_info_free(IrminInfo* x1158);
void irmin_log_level(char* x1159);
IrminConfig* irmin_config_pack(char* x1161, char* x1160);
IrminConfig* irmin_config_git(char* x1162);
IrminConfig* irmin_config_git_mem(char* x1163);
IrminConfig* irmin_config_fs(char* x1165, char* x1164);
IrminConfig* irmin_config_mem(char* x1167, char* x1166);
void irmin_config_free(IrminConfig* x1168);
_Bool irmin_config_set(IrminConfig* x1172, char* x1171, IrminType* x1170,
                       IrminValue* x1169);
IrminPath* irmin_path(IrminRepo* x1174, char** x1173);
IrminPath* irmin_path_of_string(IrminRepo* x1177, char* x1176, int x1175);
char* irmin_path_to_string(IrminRepo* x1180, IrminPath* x1179, int* x1178);
IrminPath* irmin_path_parent(IrminRepo* x1182, IrminPath* x1181);
IrminPath* irmin_path_append(IrminRepo* x1186, IrminPath* x1185, char* x1184,
                             int x1183);
_Bool irmin_path_equal(IrminRepo* x1189, IrminPath* x1188, IrminPath* x1187);
void irmin_path_free(IrminPath* x1190);
void irmin_hash_free(IrminHash* x1191);
_Bool irmin_hash_equal(IrminRepo* x1194, IrminHash* x1193, IrminHash* x1192);
IrminHash* irmin_contents_hash(IrminRepo* x1196, IrminValue* x1195);
IrminValue* irmin_contents_of_hash(IrminRepo* x1198, IrminHash* x1197);
char* irmin_hash_to_string(IrminRepo* x1201, IrminHash* x1200, int* x1199);
IrminHash* irmin_hash_of_string(IrminRepo* x1204, char* x1203, int x1202);
Irmin* irmin_main(IrminRepo* x1205);
Irmin* irmin_of_branch(IrminRepo* x1207, char* x1206);
IrminCommit* irmin_get_head(Irmin* x1208);
void irmin_set_head(Irmin* x1210, IrminCommit* x1209);
_Bool irmin_fast_forward(Irmin* x1212, IrminCommit* x1211);
_Bool irmin_merge_with_branch(Irmin* x1215, char* x1214, IrminInfo* x1213);
_Bool irmin_merge_with_commit(Irmin* x1218, IrminCommit* x1217,
                              IrminInfo* x1216);
_Bool irmin_set(Irmin* x1222, IrminPath* x1221, IrminValue* x1220,
                IrminInfo* x1219);
_Bool irmin_test_and_set(Irmin* x1227, IrminPath* x1226, IrminValue* x1225,
                         IrminValue* x1224, IrminInfo* x1223);
_Bool irmin_test_and_set_tree(Irmin* x1232, IrminPath* x1231,
                              IrminTree* x1230, IrminTree* x1229,
                              IrminInfo* x1228);
_Bool irmin_set_tree(Irmin* x1236, IrminPath* x1235, IrminTree* x1234,
                     IrminInfo* x1233);
IrminValue* irmin_find(Irmin* x1238, IrminPath* x1237);
IrminTree* irmin_find_tree(Irmin* x1240, IrminPath* x1239);
void irmin_remove(Irmin* x1243, IrminPath* x1242, IrminInfo* x1241);
_Bool irmin_mem(Irmin* x1245, IrminPath* x1244);
_Bool irmin_mem_tree(Irmin* x1247, IrminPath* x1246);
void irmin_free(Irmin* x1248);
IrminTree* irmin_tree_new(IrminRepo* x1249);
IrminTree* irmin_tree_clone(IrminRepo* x1251, IrminTree* x1250);
_Bool irmin_tree_mem(IrminRepo* x1254, IrminTree* x1253, IrminPath* x1252);
_Bool irmin_tree_mem_tree(IrminRepo* x1257, IrminTree* x1256,
                          IrminPath* x1255);
IrminValue* irmin_tree_find(IrminRepo* x1260, IrminTree* x1259,
                            IrminPath* x1258);
IrminTree* irmin_tree_find_tree(IrminRepo* x1263, IrminTree* x1262,
                                IrminPath* x1261);
void irmin_tree_add(IrminRepo* x1267, IrminTree* x1266, IrminPath* x1265,
                    IrminValue* x1264);
void irmin_tree_add_tree(IrminRepo* x1271, IrminTree* x1270,
                         IrminPath* x1269, IrminTree* x1268);
void irmin_tree_remove(IrminRepo* x1274, IrminTree* x1273, IrminPath* x1272);
_Bool irmin_tree_equal(IrminRepo* x1277, IrminTree* x1276, IrminTree* x1275);
void irmin_tree_free(IrminTree* x1278);
IrminRepo* irmin_repo_new(IrminConfig* x1279);
void irmin_repo_free(IrminRepo* x1280);
IrminInfo* irmin_commit_info(IrminRepo* x1282, IrminCommit* x1281);
IrminHash* irmin_commit_hash(IrminRepo* x1284, IrminCommit* x1283);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1286, IrminHash* x1285);
IrminCommit* irmin_commit_new(IrminRepo* x1291, IrminCommit** x1290,
                              int x1289, IrminTree* x1288, IrminInfo* x1287);
int irmin_commit_parents_length(IrminRepo* x1293, IrminCommit* x1292);
IrminCommit* irmin_commit_parent(IrminRepo* x1296, IrminCommit* x1295,
                                 int x1294);
_Bool irmin_commit_equal(IrminRepo* x1299, IrminCommit* x1298,
                         IrminCommit* x1297);
void irmin_commit_free(IrminCommit* x1300);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
