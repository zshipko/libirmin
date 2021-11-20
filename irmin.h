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
IrminType *irmin_type_unit(void);
IrminType *irmin_type_bool(void);
IrminType *irmin_type_int(void);
IrminType *irmin_type_string(void);
IrminType *irmin_type_bytes(void);
IrminType *irmin_type_list(IrminType *x1026);
IrminType *irmin_type_array(IrminType *x1027);
IrminType *irmin_type_option(IrminType *x1028);
IrminType *irmin_type_json(void);
IrminType *irmin_type_json_value(void);
IrminType *irmin_type_path(IrminRepo *x1031);
IrminType *irmin_type_commit(IrminRepo *x1032);
IrminType *irmin_type_tree(IrminRepo *x1033);
IrminType *irmin_type_hash(IrminRepo *x1034);
IrminType *irmin_type_contents(IrminRepo *x1035);
IrminType *irmin_type_pair(IrminType *x1037, IrminType *x1036);
IrminType *irmin_type_triple(IrminType *x1040, IrminType *x1039,
                             IrminType *x1038);
char *irmin_type_name(IrminType *x1042, int *x1041);
void irmin_type_free(IrminType *x1043);
IrminValue *irmin_value_unit(void);
IrminValue *irmin_value_int(int x1045);
IrminValue *irmin_value_bool(_Bool x1046);
IrminValue *irmin_value_string(char *x1047);
IrminValue *irmin_value_string_len(char *x1049, int x1048);
char *irmin_value_get_string(IrminValue *x1051, int *x1050);
int irmin_value_get_int(IrminValue *x1052);
_Bool irmin_value_get_bool(IrminValue *x1053);
IrminValue *irmin_value_bytes(char *x1054);
IrminValue *irmin_value_bytes_len(char *x1056, int x1055);
IrminValue *irmin_value_list_new(void);
void irmin_value_list_add(IrminValue *x1059, IrminValue *x1058);
IrminValue *irmin_value_list_hd(IrminValue *x1060);
IrminValue *irmin_value_list_tl(IrminValue *x1061);
IrminValue *irmin_value_array_new(int x1063, IrminValue *x1062);
void irmin_value_array_set(IrminValue *x1066, int x1065, IrminValue *x1064);
IrminValue *irmin_value_array_get(IrminValue *x1068, int x1067);
IrminValue *irmin_value_option(IrminValue *x1069);
IrminValue *irmin_value_pair(IrminValue *x1071, IrminValue *x1070);
IrminValue *irmin_value_triple(IrminValue *x1074, IrminValue *x1073,
                               IrminValue *x1072);
char *irmin_value_to_string(IrminType *x1077, IrminValue *x1076, int *x1075);
IrminValue *irmin_value_of_string(IrminType *x1080, char *x1079, int x1078);
char *irmin_value_to_bin(IrminValue *x1082, int *x1081);
IrminValue *irmin_value_of_bin(IrminType *x1085, char *x1084, int x1083);
char *irmin_value_to_json(IrminValue *x1087, int *x1086);
IrminValue *irmin_value_of_json(IrminType *x1090, char *x1089, int x1088);
_Bool irmin_value_equal(IrminType *x1093, IrminValue *x1092, IrminValue *x1091);
int irmin_value_compare(IrminType *x1096, IrminValue *x1095, IrminValue *x1094);
void irmin_value_free(IrminValue *x1097);
IrminInfo *irmin_info_new(IrminRepo *x1100, char *x1099, char *x1098);
IrminInfo *irmin_info_update(IrminRepo *x1104, char *x1103, char *x1102,
                             IrminInfo *x1101);
char *irmin_info_message(IrminRepo *x1107, IrminInfo *x1106, int *x1105);
char *irmin_info_author(IrminRepo *x1110, IrminInfo *x1109, int *x1108);
int64_t irmin_info_date(IrminRepo *x1112, IrminInfo *x1111);
void irmin_info_free(IrminInfo *x1113);
void irmin_log_level(char *x1114);
IrminConfig *irmin_config_pack(char *x1116, char *x1115);
IrminConfig *irmin_config_git(char *x1117);
IrminConfig *irmin_config_git_mem(char *x1118);
IrminConfig *irmin_config_fs(char *x1120, char *x1119);
IrminConfig *irmin_config_mem(char *x1122, char *x1121);
void irmin_config_free(IrminConfig *x1123);
_Bool irmin_config_set(IrminConfig *x1127, char *x1126, IrminType *x1125,
                       IrminValue *x1124);
IrminPath *irmin_path(IrminRepo *x1129, char **x1128);
IrminPath *irmin_path_of_string(IrminRepo *x1132, char *x1131, int x1130);
char *irmin_path_to_string(IrminRepo *x1135, IrminPath *x1134, int *x1133);
_Bool irmin_path_equal(IrminRepo *x1138, IrminPath *x1137, IrminPath *x1136);
void irmin_path_free(IrminPath *x1139);
void irmin_hash_free(IrminHash *x1140);
_Bool irmin_hash_equal(IrminRepo *x1143, IrminHash *x1142, IrminHash *x1141);
char *irmin_hash_to_string(IrminRepo *x1146, IrminHash *x1145, int *x1144);
IrminHash *irmin_hash_of_string(IrminRepo *x1149, char *x1148, int x1147);
Irmin *irmin_main(IrminRepo *x1150);
Irmin *irmin_of_branch(IrminRepo *x1152, char *x1151);
IrminCommit *irmin_get_head(Irmin *x1153);
void irmin_set_head(Irmin *x1155, IrminCommit *x1154);
_Bool irmin_fast_forward(Irmin *x1157, IrminCommit *x1156);
_Bool irmin_merge_with_branch(Irmin *x1160, char *x1159, IrminInfo *x1158);
_Bool irmin_merge_with_commit(Irmin *x1163, IrminCommit *x1162,
                              IrminInfo *x1161);
_Bool irmin_set(Irmin *x1167, IrminPath *x1166, IrminValue *x1165,
                IrminInfo *x1164);
_Bool irmin_test_and_set(Irmin *x1172, IrminPath *x1171, IrminValue *x1170,
                         IrminValue *x1169, IrminInfo *x1168);
_Bool irmin_test_and_set_tree(Irmin *x1177, IrminPath *x1176, IrminTree *x1175,
                              IrminTree *x1174, IrminInfo *x1173);
_Bool irmin_set_tree(Irmin *x1181, IrminPath *x1180, IrminTree *x1179,
                     IrminInfo *x1178);
IrminValue *irmin_find(Irmin *x1183, IrminPath *x1182);
IrminTree *irmin_find_tree(Irmin *x1185, IrminPath *x1184);
void irmin_remove(Irmin *x1188, IrminPath *x1187, IrminInfo *x1186);
_Bool irmin_mem(Irmin *x1190, IrminPath *x1189);
_Bool irmin_mem_tree(Irmin *x1192, IrminPath *x1191);
void irmin_free(Irmin *x1193);
IrminTree *irmin_tree_new(IrminRepo *x1194);
IrminTree *irmin_tree_clone(IrminRepo *x1196, IrminTree *x1195);
_Bool irmin_tree_mem(IrminRepo *x1199, IrminTree *x1198, IrminPath *x1197);
_Bool irmin_tree_mem_tree(IrminRepo *x1202, IrminTree *x1201, IrminPath *x1200);
IrminValue *irmin_tree_find(IrminRepo *x1205, IrminTree *x1204,
                            IrminPath *x1203);
IrminTree *irmin_tree_find_tree(IrminRepo *x1208, IrminTree *x1207,
                                IrminPath *x1206);
void irmin_tree_add(IrminRepo *x1212, IrminTree *x1211, IrminPath *x1210,
                    IrminValue *x1209);
void irmin_tree_add_tree(IrminRepo *x1216, IrminTree *x1215, IrminPath *x1214,
                         IrminTree *x1213);
void irmin_tree_remove(IrminRepo *x1219, IrminTree *x1218, IrminPath *x1217);
_Bool irmin_tree_equal(IrminRepo *x1222, IrminTree *x1221, IrminTree *x1220);
void irmin_tree_free(IrminTree *x1223);
IrminRepo *irmin_repo_new(IrminConfig *x1224);
void irmin_repo_free(IrminRepo *x1225);
IrminInfo *irmin_commit_info(IrminRepo *x1227, IrminCommit *x1226);
IrminHash *irmin_commit_hash(IrminRepo *x1229, IrminCommit *x1228);
IrminCommit *irmin_commit_of_hash(IrminRepo *x1231, IrminHash *x1230);
int irmin_commit_parents_length(IrminRepo *x1233, IrminCommit *x1232);
IrminCommit *irmin_commit_parent(IrminRepo *x1236, IrminCommit *x1235,
                                 int x1234);
_Bool irmin_commit_equal(IrminRepo *x1239, IrminCommit *x1238,
                         IrminCommit *x1237);
void irmin_commit_free(IrminCommit *x1240);

static void _irmin_cleanup(void *p) {
  if (p) {
    irmin_free(*(Irmin **)p);
    p = (void *)0;
  }
};
#define AUTO __attribute__((cleanup(_irmin_cleanup)))
