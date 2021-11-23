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
IrminType* irmin_type_list(IrminType* x1058);
IrminType* irmin_type_array(IrminType* x1059);
IrminType* irmin_type_option(IrminType* x1060);
IrminType* irmin_type_json(void);
IrminType* irmin_type_json_value(void);
IrminType* irmin_type_path(IrminRepo* x1063);
IrminType* irmin_type_commit(IrminRepo* x1064);
IrminType* irmin_type_tree(IrminRepo* x1065);
IrminType* irmin_type_hash(IrminRepo* x1066);
IrminType* irmin_type_contents(IrminRepo* x1067);
IrminType* irmin_type_pair(IrminType* x1069, IrminType* x1068);
IrminType* irmin_type_triple(IrminType* x1072, IrminType* x1071,
                             IrminType* x1070);
char* irmin_type_name(IrminType* x1074, int* x1073);
void irmin_type_free(IrminType* x1075);
IrminValue* irmin_value_unit(void);
IrminValue* irmin_value_int(int x1077);
IrminValue* irmin_value_bool(_Bool x1078);
IrminValue* irmin_value_make(void* x1079);
IrminValue* irmin_value_string(char* x1081, int x1080);
char* irmin_value_get_string(IrminValue* x1083, int* x1082);
int irmin_value_get_int(IrminValue* x1084);
_Bool irmin_value_get_bool(IrminValue* x1085);
IrminValue* irmin_value_bytes(char* x1087, int x1086);
IrminValue* irmin_value_list_new(void);
void irmin_value_list_add(IrminValue* x1090, IrminValue* x1089);
IrminValue* irmin_value_list_hd(IrminValue* x1091);
IrminValue* irmin_value_list_tl(IrminValue* x1092);
IrminValue* irmin_value_array_new(int x1094, IrminValue* x1093);
void irmin_value_array_set(IrminValue* x1097, int x1096, IrminValue* x1095);
IrminValue* irmin_value_array_get(IrminValue* x1099, int x1098);
IrminValue* irmin_value_option(IrminValue* x1100);
IrminValue* irmin_value_pair(IrminValue* x1102, IrminValue* x1101);
IrminValue* irmin_value_triple(IrminValue* x1105, IrminValue* x1104,
                               IrminValue* x1103);
char* irmin_value_to_string(IrminType* x1108, IrminValue* x1107, int* x1106);
IrminValue* irmin_value_of_string(IrminType* x1111, char* x1110, int x1109);
char* irmin_value_to_bin(IrminType* x1114, IrminValue* x1113, int* x1112);
IrminValue* irmin_value_of_bin(IrminType* x1117, char* x1116, int x1115);
char* irmin_value_to_json(IrminType* x1120, IrminValue* x1119, int* x1118);
IrminValue* irmin_value_of_json(IrminType* x1123, char* x1122, int x1121);
_Bool irmin_value_equal(IrminType* x1126, IrminValue* x1125,
                        IrminValue* x1124);
int irmin_value_compare(IrminType* x1129, IrminValue* x1128,
                        IrminValue* x1127);
void irmin_value_free(IrminValue* x1130);
IrminInfo* irmin_info_new(IrminRepo* x1133, char* x1132, char* x1131);
IrminInfo* irmin_info_update(IrminRepo* x1137, char* x1136, char* x1135,
                             IrminInfo* x1134);
char* irmin_info_message(IrminRepo* x1140, IrminInfo* x1139, int* x1138);
char* irmin_info_author(IrminRepo* x1143, IrminInfo* x1142, int* x1141);
int64_t irmin_info_date(IrminRepo* x1145, IrminInfo* x1144);
void irmin_info_free(IrminInfo* x1146);
void irmin_log_level(char* x1147);
IrminConfig* irmin_config_pack(char* x1149, char* x1148);
IrminConfig* irmin_config_git(char* x1150);
IrminConfig* irmin_config_git_mem(char* x1151);
IrminConfig* irmin_config_fs(char* x1153, char* x1152);
IrminConfig* irmin_config_mem(char* x1155, char* x1154);
void irmin_config_free(IrminConfig* x1156);
_Bool irmin_config_set(IrminConfig* x1160, char* x1159, IrminType* x1158,
                       IrminValue* x1157);
IrminPath* irmin_path(IrminRepo* x1162, char** x1161);
IrminPath* irmin_path_of_string(IrminRepo* x1165, char* x1164, int x1163);
char* irmin_path_to_string(IrminRepo* x1168, IrminPath* x1167, int* x1166);
IrminPath* irmin_path_parent(IrminRepo* x1170, IrminPath* x1169);
IrminPath* irmin_path_append(IrminRepo* x1174, IrminPath* x1173, char* x1172,
                             int x1171);
_Bool irmin_path_equal(IrminRepo* x1177, IrminPath* x1176, IrminPath* x1175);
void irmin_path_free(IrminPath* x1178);
void irmin_hash_free(IrminHash* x1179);
_Bool irmin_hash_equal(IrminRepo* x1182, IrminHash* x1181, IrminHash* x1180);
IrminHash* irmin_contents_hash(IrminRepo* x1184, IrminValue* x1183);
IrminValue* irmin_contents_of_hash(IrminRepo* x1186, IrminHash* x1185);
char* irmin_hash_to_string(IrminRepo* x1189, IrminHash* x1188, int* x1187);
IrminHash* irmin_hash_of_string(IrminRepo* x1192, char* x1191, int x1190);
Irmin* irmin_main(IrminRepo* x1193);
Irmin* irmin_of_branch(IrminRepo* x1195, char* x1194);
IrminCommit* irmin_get_head(Irmin* x1196);
void irmin_set_head(Irmin* x1198, IrminCommit* x1197);
_Bool irmin_fast_forward(Irmin* x1200, IrminCommit* x1199);
_Bool irmin_merge_with_branch(Irmin* x1203, char* x1202, IrminInfo* x1201);
_Bool irmin_merge_with_commit(Irmin* x1206, IrminCommit* x1205,
                              IrminInfo* x1204);
_Bool irmin_set(Irmin* x1210, IrminPath* x1209, IrminValue* x1208,
                IrminInfo* x1207);
_Bool irmin_test_and_set(Irmin* x1215, IrminPath* x1214, IrminValue* x1213,
                         IrminValue* x1212, IrminInfo* x1211);
_Bool irmin_test_and_set_tree(Irmin* x1220, IrminPath* x1219,
                              IrminTree* x1218, IrminTree* x1217,
                              IrminInfo* x1216);
_Bool irmin_set_tree(Irmin* x1224, IrminPath* x1223, IrminTree* x1222,
                     IrminInfo* x1221);
IrminValue* irmin_find(Irmin* x1226, IrminPath* x1225);
IrminTree* irmin_find_tree(Irmin* x1228, IrminPath* x1227);
void irmin_remove(Irmin* x1231, IrminPath* x1230, IrminInfo* x1229);
_Bool irmin_mem(Irmin* x1233, IrminPath* x1232);
_Bool irmin_mem_tree(Irmin* x1235, IrminPath* x1234);
void irmin_free(Irmin* x1236);
IrminTree* irmin_tree_new(IrminRepo* x1237);
IrminTree* irmin_tree_clone(IrminRepo* x1239, IrminTree* x1238);
_Bool irmin_tree_mem(IrminRepo* x1242, IrminTree* x1241, IrminPath* x1240);
_Bool irmin_tree_mem_tree(IrminRepo* x1245, IrminTree* x1244,
                          IrminPath* x1243);
IrminValue* irmin_tree_find(IrminRepo* x1248, IrminTree* x1247,
                            IrminPath* x1246);
IrminTree* irmin_tree_find_tree(IrminRepo* x1251, IrminTree* x1250,
                                IrminPath* x1249);
void irmin_tree_add(IrminRepo* x1255, IrminTree* x1254, IrminPath* x1253,
                    IrminValue* x1252);
void irmin_tree_add_tree(IrminRepo* x1259, IrminTree* x1258,
                         IrminPath* x1257, IrminTree* x1256);
void irmin_tree_remove(IrminRepo* x1262, IrminTree* x1261, IrminPath* x1260);
_Bool irmin_tree_equal(IrminRepo* x1265, IrminTree* x1264, IrminTree* x1263);
void irmin_tree_free(IrminTree* x1266);
IrminRepo* irmin_repo_new(IrminConfig* x1267);
void irmin_repo_free(IrminRepo* x1268);
IrminInfo* irmin_commit_info(IrminRepo* x1270, IrminCommit* x1269);
IrminHash* irmin_commit_hash(IrminRepo* x1272, IrminCommit* x1271);
IrminCommit* irmin_commit_of_hash(IrminRepo* x1274, IrminHash* x1273);
int irmin_commit_parents_length(IrminRepo* x1276, IrminCommit* x1275);
IrminCommit* irmin_commit_parent(IrminRepo* x1279, IrminCommit* x1278,
                                 int x1277);
_Bool irmin_commit_equal(IrminRepo* x1282, IrminCommit* x1281,
                         IrminCommit* x1280);
void irmin_commit_free(IrminCommit* x1283);


static void _irmin_cleanup(void *p) { if (p) { irmin_free(*(Irmin**)p); p = (void*)0;} };
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
    
