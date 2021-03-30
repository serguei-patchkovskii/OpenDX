# Initial spec file created by autospec ver. 0.3
# This spec file will build the rpm installation from a tarball version
# of the binaries: to create bins:
#     tar -zcvf opendx-4.1.0.tar.gz /usr/local/dx /usr/local/bin/dx
Summary: OpenDX is a system of tools for vizualizing data.
# The Summary: line should be expanded to about here -----^
Name: opendx
%define version 4.1.0
Version: %{version}
Release: 1
Group: Applications/Graphics
Copyright: IBM Public License - Open Visualization Data Explorer VERSION 1.0
Source: opendx-%{version}-bin.tar.gz
BuildRoot: /usr/src/redhat/BUILD/opendx-%{version}-root
# Following are optional fields
URL: http://www.opendx.org/
Distribution: OpenDX Organization
#Patch: opendx-%{version}.patch
#Prefix: /usr/local
#BuildArchitectures: noarch
#Requires: 
#Obsoletes: 

%description
OpenDX is a uniquely powerful, full-featured software package for the visualization
of scientific, engineering and analytical data: Its open system design is built on familiar
standard interface environments. And its sophisticated data model provides users with 
great flexibility in creating visualizations.

And if you are looking to build visualization applications for your end users, OpenDX
has what you need: power to support their requirements and versatility for customized
application developement.

%prep
%setup -c opendx-%{version}
#%patch

%install
cp -aR . ${RPM_BUILD_ROOT-/}

%files
%dir /usr/
%dir /usr/local/
%dir /usr/local/dx/
%dir /usr/local/dx/lib_linux/
/usr/local/dx/lib_linux/libDXlite.a
/usr/local/dx/lib_linux/libDX.a
/usr/local/dx/lib_linux/libDXcallm.a
/usr/local/dx/lib_linux/libDXL.a
/usr/local/dx/lib_linux/arch.mak
%dir /usr/local/dx/lib/
/usr/local/dx/lib/dx.mdf
/usr/local/dx/lib/mdf2c.awk
/usr/local/dx/lib/messages
/usr/local/dx/lib/colors.txt
/usr/local/dx/lib/dxfSaveCurrentImage.net
%config /usr/local/dx/lib/dxrc
/usr/local/dx/lib/dxexec.exp
/usr/local/dx/lib/outboard.c
%dir /usr/local/dx/bin_linux/
/usr/local/dx/bin_linux/dxexec
/usr/local/dx/bin_linux/dxui
/usr/local/dx/bin_linux/prompter
/usr/local/dx/bin_linux/tutor
/usr/local/dx/bin_linux/builder
/usr/local/dx/bin_linux/startupui
%dir /usr/local/dx/ui/
/usr/local/dx/ui/icon50.dat
/usr/local/dx/ui/logo.dat
/usr/local/dx/ui/ui.mdf
/usr/local/dx/ui/Basic2D.cfg
/usr/local/dx/ui/Basic2D.net
/usr/local/dx/ui/Basic3D.cfg
/usr/local/dx/ui/Basic3D.net
/usr/local/dx/ui/FacesLoopsEdges.cfg
/usr/local/dx/ui/FacesLoopsEdges.net
/usr/local/dx/ui/GARMWName
/usr/local/dx/ui/Gridded_2D_1var_notseries.cfg
/usr/local/dx/ui/Gridded_2D_1var_notseries.net
/usr/local/dx/ui/Gridded_2D_2ormorevar_notseries.cfg
/usr/local/dx/ui/Gridded_2D_2ormorevar_notseries.net
/usr/local/dx/ui/Gridded_3D_1var_notseries.cfg
/usr/local/dx/ui/Gridded_3D_1var_notseries.net
/usr/local/dx/ui/Gridded_3D_2ormorevar_notseries.cfg
/usr/local/dx/ui/Gridded_3D_2ormorevar_notseries.net
/usr/local/dx/ui/ImportSpreadsheetMatrix.cfg
/usr/local/dx/ui/ImportSpreadsheetMatrix.net
/usr/local/dx/ui/ImportSpreadsheetTable.cfg
/usr/local/dx/ui/ImportSpreadsheetTable.net
/usr/local/dx/ui/ReadImage.cfg
/usr/local/dx/ui/ReadImage.net
/usr/local/dx/ui/UnGridded_2D_1var_notseries.cfg
/usr/local/dx/ui/UnGridded_2D_1var_notseries.net
/usr/local/dx/ui/UnGridded_2D_2ormorevar_notseries.cfg
/usr/local/dx/ui/UnGridded_2D_2ormorevar_notseries.net
/usr/local/dx/ui/UnGridded_3D_1var_notseries.cfg
/usr/local/dx/ui/UnGridded_3D_1var_notseries.net
/usr/local/dx/ui/UnGridded_3D_2ormorevar_notseries.cfg
/usr/local/dx/ui/UnGridded_3D_2ormorevar_notseries.net
/usr/local/dx/ui/date.fmt
/usr/local/dx/ui/decision.cfg
/usr/local/dx/ui/decision.net
/usr/local/dx/ui/editorWindow
/usr/local/dx/ui/help.txt
/usr/local/dx/ui/imageWindow
/usr/local/dx/ui/support.txt
/usr/local/dx/ui/syntax.txt
/usr/local/dx/ui/testimp.net
/usr/local/dx/ui/testssheet.net
/usr/local/dx/ui/viewer.net
%dir /usr/local/dx/java/
%dir /usr/local/dx/java/server/
%dir /usr/local/dx/java/server/dxmacros/
/usr/local/dx/java/server/dxmacros/gifmac.net
/usr/local/dx/java/server/dxmacros/vrmlmac.net
/usr/local/dx/java/server/dxmacros/dxmac.net
/usr/local/dx/java/server/dxmacros/weboptionsmac.net
%dir /usr/local/dx/java/server/bin/
/usr/local/dx/java/server/bin/stopserver
/usr/local/dx/java/server/bin/startserver
/usr/local/dx/java/server/bin/startserver.bat
/usr/local/dx/java/server/bin/dxserver.paths
%dir /usr/local/dx/java/server/class/
/usr/local/dx/java/server/class/dxserver.paths
/usr/local/dx/java/server/class/server.jar
%dir /usr/local/dx/java/server/lib_linux/
/usr/local/dx/java/server/lib_linux/libAnyDX.so
%dir /usr/local/dx/java/output/
%doc /usr/local/dx/java/output/README.output
%dir /usr/local/dx/java/htmlpages/
/usr/local/dx/java/htmlpages/dx.jar
%dir /usr/local/dx/include/
%dir /usr/local/dx/include/dx/
/usr/local/dx/include/dx/UserInteractors.h
/usr/local/dx/include/dx/advanced.h
/usr/local/dx/include/dx/arch.h
/usr/local/dx/include/dx/array.h
/usr/local/dx/include/dx/arrayhandles.h
/usr/local/dx/include/dx/basic.h
/usr/local/dx/include/dx/cache.h
/usr/local/dx/include/dx/camera.h
/usr/local/dx/include/dx/clipped.h
/usr/local/dx/include/dx/component.h
/usr/local/dx/include/dx/dx.h
/usr/local/dx/include/dx/error.h
/usr/local/dx/include/dx/extract.h
/usr/local/dx/include/dx/field.h
/usr/local/dx/include/dx/geometry.h
/usr/local/dx/include/dx/group.h
/usr/local/dx/include/dx/grow.h
/usr/local/dx/include/dx/hash.h
/usr/local/dx/include/dx/helper.h
/usr/local/dx/include/dx/image.h
/usr/local/dx/include/dx/import.h
/usr/local/dx/include/dx/invalid.h
/usr/local/dx/include/dx/lexical.h
/usr/local/dx/include/dx/light.h
/usr/local/dx/include/dx/memory.h
/usr/local/dx/include/dx/modflags.h
/usr/local/dx/include/dx/object.h
/usr/local/dx/include/dx/partition.h
/usr/local/dx/include/dx/pending.h
/usr/local/dx/include/dx/pick.h
/usr/local/dx/include/dx/private.h
/usr/local/dx/include/dx/rel_1_bc.h
/usr/local/dx/include/dx/render.h
/usr/local/dx/include/dx/resampling.h
/usr/local/dx/include/dx/screen.h
/usr/local/dx/include/dx/seglist.h
/usr/local/dx/include/dx/string.h
/usr/local/dx/include/dx/task.h
/usr/local/dx/include/dx/timing.h
/usr/local/dx/include/dx/version.h
/usr/local/dx/include/dx/xform.h
/usr/local/dx/include/dxl.h
/usr/local/dx/include/dxconfig.h
%dir /usr/local/dx/bin/
/usr/local/dx/bin/dxworker
/usr/local/dx/bin/mdf2c
/usr/local/dx/bin/dx
%dir /usr/local/dx/help/
%doc /usr/local/dx/help/HelpDir
%doc /usr/local/dx/help/HelpNotAvailable
%doc /usr/local/dx/help/dxall1
%doc /usr/local/dx/help/dxall10
%doc /usr/local/dx/help/dxall100
%doc /usr/local/dx/help/dxall1000
%doc /usr/local/dx/help/dxall1001
%doc /usr/local/dx/help/dxall1002
%doc /usr/local/dx/help/dxall1003
%doc /usr/local/dx/help/dxall1004
%doc /usr/local/dx/help/dxall1005
%doc /usr/local/dx/help/dxall1006
%doc /usr/local/dx/help/dxall1007
%doc /usr/local/dx/help/dxall1008
%doc /usr/local/dx/help/dxall1009
%doc /usr/local/dx/help/dxall101
%doc /usr/local/dx/help/dxall1010
%doc /usr/local/dx/help/dxall1011
%doc /usr/local/dx/help/dxall1012
%doc /usr/local/dx/help/dxall1013
%doc /usr/local/dx/help/dxall1014
%doc /usr/local/dx/help/dxall1015
%doc /usr/local/dx/help/dxall1016
%doc /usr/local/dx/help/dxall1017
%doc /usr/local/dx/help/dxall1018
%doc /usr/local/dx/help/dxall1019
%doc /usr/local/dx/help/dxall102
%doc /usr/local/dx/help/dxall1020
%doc /usr/local/dx/help/dxall1021
%doc /usr/local/dx/help/dxall1022
%doc /usr/local/dx/help/dxall1023
%doc /usr/local/dx/help/dxall1024
%doc /usr/local/dx/help/dxall1025
%doc /usr/local/dx/help/dxall1026
%doc /usr/local/dx/help/dxall1027
%doc /usr/local/dx/help/dxall1028
%doc /usr/local/dx/help/dxall1029
%doc /usr/local/dx/help/dxall103
%doc /usr/local/dx/help/dxall1030
%doc /usr/local/dx/help/dxall1031
%doc /usr/local/dx/help/dxall1032
%doc /usr/local/dx/help/dxall1033
%doc /usr/local/dx/help/dxall1034
%doc /usr/local/dx/help/dxall1035
%doc /usr/local/dx/help/dxall1036
%doc /usr/local/dx/help/dxall1037
%doc /usr/local/dx/help/dxall1038
%doc /usr/local/dx/help/dxall1039
%doc /usr/local/dx/help/dxall104
%doc /usr/local/dx/help/dxall1040
%doc /usr/local/dx/help/dxall1041
%doc /usr/local/dx/help/dxall1042
%doc /usr/local/dx/help/dxall1043
%doc /usr/local/dx/help/dxall1044
%doc /usr/local/dx/help/dxall1045
%doc /usr/local/dx/help/dxall1046
%doc /usr/local/dx/help/dxall1047
%doc /usr/local/dx/help/dxall1048
%doc /usr/local/dx/help/dxall1049
%doc /usr/local/dx/help/dxall105
%doc /usr/local/dx/help/dxall1050
%doc /usr/local/dx/help/dxall1051
%doc /usr/local/dx/help/dxall1052
%doc /usr/local/dx/help/dxall1053
%doc /usr/local/dx/help/dxall1054
%doc /usr/local/dx/help/dxall1055
%doc /usr/local/dx/help/dxall1056
%doc /usr/local/dx/help/dxall1057
%doc /usr/local/dx/help/dxall1058
%doc /usr/local/dx/help/dxall1059
%doc /usr/local/dx/help/dxall106
%doc /usr/local/dx/help/dxall1060
%doc /usr/local/dx/help/dxall1061
%doc /usr/local/dx/help/dxall1062
%doc /usr/local/dx/help/dxall1063
%doc /usr/local/dx/help/dxall1064
%doc /usr/local/dx/help/dxall1065
%doc /usr/local/dx/help/dxall1066
%doc /usr/local/dx/help/dxall1067
%doc /usr/local/dx/help/dxall1068
%doc /usr/local/dx/help/dxall1069
%doc /usr/local/dx/help/dxall107
%doc /usr/local/dx/help/dxall1070
%doc /usr/local/dx/help/dxall1071
%doc /usr/local/dx/help/dxall1072
%doc /usr/local/dx/help/dxall1073
%doc /usr/local/dx/help/dxall1074
%doc /usr/local/dx/help/dxall1075
%doc /usr/local/dx/help/dxall1076
%doc /usr/local/dx/help/dxall1077
%doc /usr/local/dx/help/dxall1078
%doc /usr/local/dx/help/dxall1079
%doc /usr/local/dx/help/dxall108
%doc /usr/local/dx/help/dxall1080
%doc /usr/local/dx/help/dxall1081
%doc /usr/local/dx/help/dxall1082
%doc /usr/local/dx/help/dxall1083
%doc /usr/local/dx/help/dxall1084
%doc /usr/local/dx/help/dxall1085
%doc /usr/local/dx/help/dxall1086
%doc /usr/local/dx/help/dxall1087
%doc /usr/local/dx/help/dxall1088
%doc /usr/local/dx/help/dxall1089
%doc /usr/local/dx/help/dxall109
%doc /usr/local/dx/help/dxall1090
%doc /usr/local/dx/help/dxall1091
%doc /usr/local/dx/help/dxall1092
%doc /usr/local/dx/help/dxall1093
%doc /usr/local/dx/help/dxall1094
%doc /usr/local/dx/help/dxall1095
%doc /usr/local/dx/help/dxall1096
%doc /usr/local/dx/help/dxall1097
%doc /usr/local/dx/help/dxall1098
%doc /usr/local/dx/help/dxall1099
%doc /usr/local/dx/help/dxall11
%doc /usr/local/dx/help/dxall110
%doc /usr/local/dx/help/dxall1100
%doc /usr/local/dx/help/dxall1101
%doc /usr/local/dx/help/dxall1102
%doc /usr/local/dx/help/dxall1103
%doc /usr/local/dx/help/dxall1104
%doc /usr/local/dx/help/dxall1105
%doc /usr/local/dx/help/dxall1106
%doc /usr/local/dx/help/dxall1107
%doc /usr/local/dx/help/dxall1108
%doc /usr/local/dx/help/dxall1109
%doc /usr/local/dx/help/dxall111
%doc /usr/local/dx/help/dxall1110
%doc /usr/local/dx/help/dxall1111
%doc /usr/local/dx/help/dxall1112
%doc /usr/local/dx/help/dxall1113
%doc /usr/local/dx/help/dxall1114
%doc /usr/local/dx/help/dxall1115
%doc /usr/local/dx/help/dxall1116
%doc /usr/local/dx/help/dxall1117
%doc /usr/local/dx/help/dxall1118
%doc /usr/local/dx/help/dxall1119
%doc /usr/local/dx/help/dxall112
%doc /usr/local/dx/help/dxall1120
%doc /usr/local/dx/help/dxall1121
%doc /usr/local/dx/help/dxall1122
%doc /usr/local/dx/help/dxall1123
%doc /usr/local/dx/help/dxall1124
%doc /usr/local/dx/help/dxall1125
%doc /usr/local/dx/help/dxall1126
%doc /usr/local/dx/help/dxall1127
%doc /usr/local/dx/help/dxall1128
%doc /usr/local/dx/help/dxall1129
%doc /usr/local/dx/help/dxall113
%doc /usr/local/dx/help/dxall1130
%doc /usr/local/dx/help/dxall1131
%doc /usr/local/dx/help/dxall1132
%doc /usr/local/dx/help/dxall1133
%doc /usr/local/dx/help/dxall1134
%doc /usr/local/dx/help/dxall1135
%doc /usr/local/dx/help/dxall1136
%doc /usr/local/dx/help/dxall1137
%doc /usr/local/dx/help/dxall1138
%doc /usr/local/dx/help/dxall1139
%doc /usr/local/dx/help/dxall114
%doc /usr/local/dx/help/dxall1140
%doc /usr/local/dx/help/dxall1141
%doc /usr/local/dx/help/dxall1142
%doc /usr/local/dx/help/dxall1143
%doc /usr/local/dx/help/dxall1144
%doc /usr/local/dx/help/dxall1145
%doc /usr/local/dx/help/dxall1146
%doc /usr/local/dx/help/dxall1147
%doc /usr/local/dx/help/dxall1148
%doc /usr/local/dx/help/dxall1149
%doc /usr/local/dx/help/dxall115
%doc /usr/local/dx/help/dxall1150
%doc /usr/local/dx/help/dxall1151
%doc /usr/local/dx/help/dxall1152
%doc /usr/local/dx/help/dxall1153
%doc /usr/local/dx/help/dxall1154
%doc /usr/local/dx/help/dxall1155
%doc /usr/local/dx/help/dxall1156
%doc /usr/local/dx/help/dxall1157
%doc /usr/local/dx/help/dxall1158
%doc /usr/local/dx/help/dxall1159
%doc /usr/local/dx/help/dxall116
%doc /usr/local/dx/help/dxall1160
%doc /usr/local/dx/help/dxall1161
%doc /usr/local/dx/help/dxall1162
%doc /usr/local/dx/help/dxall1163
%doc /usr/local/dx/help/dxall1164
%doc /usr/local/dx/help/dxall1165
%doc /usr/local/dx/help/dxall1166
%doc /usr/local/dx/help/dxall1167
%doc /usr/local/dx/help/dxall1168
%doc /usr/local/dx/help/dxall1169
%doc /usr/local/dx/help/dxall117
%doc /usr/local/dx/help/dxall1170
%doc /usr/local/dx/help/dxall1171
%doc /usr/local/dx/help/dxall1172
%doc /usr/local/dx/help/dxall1173
%doc /usr/local/dx/help/dxall1174
%doc /usr/local/dx/help/dxall1175
%doc /usr/local/dx/help/dxall1176
%doc /usr/local/dx/help/dxall1177
%doc /usr/local/dx/help/dxall1178
%doc /usr/local/dx/help/dxall1179
%doc /usr/local/dx/help/dxall118
%doc /usr/local/dx/help/dxall1180
%doc /usr/local/dx/help/dxall1181
%doc /usr/local/dx/help/dxall1182
%doc /usr/local/dx/help/dxall1183
%doc /usr/local/dx/help/dxall1184
%doc /usr/local/dx/help/dxall1185
%doc /usr/local/dx/help/dxall1186
%doc /usr/local/dx/help/dxall1187
%doc /usr/local/dx/help/dxall1188
%doc /usr/local/dx/help/dxall1189
%doc /usr/local/dx/help/dxall119
%doc /usr/local/dx/help/dxall1190
%doc /usr/local/dx/help/dxall1191
%doc /usr/local/dx/help/dxall1192
%doc /usr/local/dx/help/dxall1193
%doc /usr/local/dx/help/dxall1194
%doc /usr/local/dx/help/dxall1195
%doc /usr/local/dx/help/dxall1196
%doc /usr/local/dx/help/dxall1197
%doc /usr/local/dx/help/dxall1198
%doc /usr/local/dx/help/dxall1199
%doc /usr/local/dx/help/dxall12
%doc /usr/local/dx/help/dxall120
%doc /usr/local/dx/help/dxall1200
%doc /usr/local/dx/help/dxall1201
%doc /usr/local/dx/help/dxall1202
%doc /usr/local/dx/help/dxall1203
%doc /usr/local/dx/help/dxall1204
%doc /usr/local/dx/help/dxall1205
%doc /usr/local/dx/help/dxall1206
%doc /usr/local/dx/help/dxall1207
%doc /usr/local/dx/help/dxall1208
%doc /usr/local/dx/help/dxall1209
%doc /usr/local/dx/help/dxall121
%doc /usr/local/dx/help/dxall1210
%doc /usr/local/dx/help/dxall1211
%doc /usr/local/dx/help/dxall1212
%doc /usr/local/dx/help/dxall1213
%doc /usr/local/dx/help/dxall1214
%doc /usr/local/dx/help/dxall1215
%doc /usr/local/dx/help/dxall1216
%doc /usr/local/dx/help/dxall1217
%doc /usr/local/dx/help/dxall1218
%doc /usr/local/dx/help/dxall1219
%doc /usr/local/dx/help/dxall122
%doc /usr/local/dx/help/dxall1220
%doc /usr/local/dx/help/dxall1221
%doc /usr/local/dx/help/dxall1222
%doc /usr/local/dx/help/dxall1223
%doc /usr/local/dx/help/dxall1224
%doc /usr/local/dx/help/dxall1225
%doc /usr/local/dx/help/dxall1226
%doc /usr/local/dx/help/dxall1227
%doc /usr/local/dx/help/dxall1228
%doc /usr/local/dx/help/dxall1229
%doc /usr/local/dx/help/dxall123
%doc /usr/local/dx/help/dxall1230
%doc /usr/local/dx/help/dxall1231
%doc /usr/local/dx/help/dxall1232
%doc /usr/local/dx/help/dxall1233
%doc /usr/local/dx/help/dxall1234
%doc /usr/local/dx/help/dxall1235
%doc /usr/local/dx/help/dxall1236
%doc /usr/local/dx/help/dxall1237
%doc /usr/local/dx/help/dxall1238
%doc /usr/local/dx/help/dxall1239
%doc /usr/local/dx/help/dxall124
%doc /usr/local/dx/help/dxall1240
%doc /usr/local/dx/help/dxall1241
%doc /usr/local/dx/help/dxall1242
%doc /usr/local/dx/help/dxall1243
%doc /usr/local/dx/help/dxall1244
%doc /usr/local/dx/help/dxall1245
%doc /usr/local/dx/help/dxall1246
%doc /usr/local/dx/help/dxall1247
%doc /usr/local/dx/help/dxall1248
%doc /usr/local/dx/help/dxall1249
%doc /usr/local/dx/help/dxall125
%doc /usr/local/dx/help/dxall1250
%doc /usr/local/dx/help/dxall1251
%doc /usr/local/dx/help/dxall1252
%doc /usr/local/dx/help/dxall1253
%doc /usr/local/dx/help/dxall1254
%doc /usr/local/dx/help/dxall1255
%doc /usr/local/dx/help/dxall1256
%doc /usr/local/dx/help/dxall1257
%doc /usr/local/dx/help/dxall1258
%doc /usr/local/dx/help/dxall1259
%doc /usr/local/dx/help/dxall126
%doc /usr/local/dx/help/dxall1260
%doc /usr/local/dx/help/dxall1261
%doc /usr/local/dx/help/dxall1262
%doc /usr/local/dx/help/dxall1263
%doc /usr/local/dx/help/dxall1264
%doc /usr/local/dx/help/dxall1265
%doc /usr/local/dx/help/dxall1266
%doc /usr/local/dx/help/dxall1267
%doc /usr/local/dx/help/dxall1268
%doc /usr/local/dx/help/dxall1269
%doc /usr/local/dx/help/dxall127
%doc /usr/local/dx/help/dxall1270
%doc /usr/local/dx/help/dxall1271
%doc /usr/local/dx/help/dxall1272
%doc /usr/local/dx/help/dxall1273
%doc /usr/local/dx/help/dxall1274
%doc /usr/local/dx/help/dxall1275
%doc /usr/local/dx/help/dxall1276
%doc /usr/local/dx/help/dxall1277
%doc /usr/local/dx/help/dxall1278
%doc /usr/local/dx/help/dxall1279
%doc /usr/local/dx/help/dxall128
%doc /usr/local/dx/help/dxall1280
%doc /usr/local/dx/help/dxall1281
%doc /usr/local/dx/help/dxall1282
%doc /usr/local/dx/help/dxall1283
%doc /usr/local/dx/help/dxall1284
%doc /usr/local/dx/help/dxall1285
%doc /usr/local/dx/help/dxall1286
%doc /usr/local/dx/help/dxall1287
%doc /usr/local/dx/help/dxall1288
%doc /usr/local/dx/help/dxall1289
%doc /usr/local/dx/help/dxall129
%doc /usr/local/dx/help/dxall1290
%doc /usr/local/dx/help/dxall1291
%doc /usr/local/dx/help/dxall1292
%doc /usr/local/dx/help/dxall1293
%doc /usr/local/dx/help/dxall1294
%doc /usr/local/dx/help/dxall1295
%doc /usr/local/dx/help/dxall1296
%doc /usr/local/dx/help/dxall1297
%doc /usr/local/dx/help/dxall1298
%doc /usr/local/dx/help/dxall1299
%doc /usr/local/dx/help/dxall13
%doc /usr/local/dx/help/dxall130
%doc /usr/local/dx/help/dxall1300
%doc /usr/local/dx/help/dxall1301
%doc /usr/local/dx/help/dxall1302
%doc /usr/local/dx/help/dxall1303
%doc /usr/local/dx/help/dxall1304
%doc /usr/local/dx/help/dxall1305
%doc /usr/local/dx/help/dxall1306
%doc /usr/local/dx/help/dxall1307
%doc /usr/local/dx/help/dxall1308
%doc /usr/local/dx/help/dxall1309
%doc /usr/local/dx/help/dxall131
%doc /usr/local/dx/help/dxall1310
%doc /usr/local/dx/help/dxall1311
%doc /usr/local/dx/help/dxall1312
%doc /usr/local/dx/help/dxall1313
%doc /usr/local/dx/help/dxall1314
%doc /usr/local/dx/help/dxall1315
%doc /usr/local/dx/help/dxall1316
%doc /usr/local/dx/help/dxall1317
%doc /usr/local/dx/help/dxall1318
%doc /usr/local/dx/help/dxall1319
%doc /usr/local/dx/help/dxall132
%doc /usr/local/dx/help/dxall1320
%doc /usr/local/dx/help/dxall1321
%doc /usr/local/dx/help/dxall1322
%doc /usr/local/dx/help/dxall1323
%doc /usr/local/dx/help/dxall1324
%doc /usr/local/dx/help/dxall1325
%doc /usr/local/dx/help/dxall1326
%doc /usr/local/dx/help/dxall1327
%doc /usr/local/dx/help/dxall1328
%doc /usr/local/dx/help/dxall1329
%doc /usr/local/dx/help/dxall133
%doc /usr/local/dx/help/dxall1330
%doc /usr/local/dx/help/dxall1331
%doc /usr/local/dx/help/dxall1332
%doc /usr/local/dx/help/dxall1333
%doc /usr/local/dx/help/dxall1334
%doc /usr/local/dx/help/dxall1335
%doc /usr/local/dx/help/dxall1336
%doc /usr/local/dx/help/dxall1337
%doc /usr/local/dx/help/dxall1338
%doc /usr/local/dx/help/dxall1339
%doc /usr/local/dx/help/dxall134
%doc /usr/local/dx/help/dxall1340
%doc /usr/local/dx/help/dxall1341
%doc /usr/local/dx/help/dxall1342
%doc /usr/local/dx/help/dxall1343
%doc /usr/local/dx/help/dxall1344
%doc /usr/local/dx/help/dxall1345
%doc /usr/local/dx/help/dxall1346
%doc /usr/local/dx/help/dxall1347
%doc /usr/local/dx/help/dxall1348
%doc /usr/local/dx/help/dxall1349
%doc /usr/local/dx/help/dxall135
%doc /usr/local/dx/help/dxall1350
%doc /usr/local/dx/help/dxall1351
%doc /usr/local/dx/help/dxall1352
%doc /usr/local/dx/help/dxall1353
%doc /usr/local/dx/help/dxall1354
%doc /usr/local/dx/help/dxall1355
%doc /usr/local/dx/help/dxall1356
%doc /usr/local/dx/help/dxall1357
%doc /usr/local/dx/help/dxall1358
%doc /usr/local/dx/help/dxall1359
%doc /usr/local/dx/help/dxall136
%doc /usr/local/dx/help/dxall1360
%doc /usr/local/dx/help/dxall1361
%doc /usr/local/dx/help/dxall1362
%doc /usr/local/dx/help/dxall1363
%doc /usr/local/dx/help/dxall1364
%doc /usr/local/dx/help/dxall1365
%doc /usr/local/dx/help/dxall1366
%doc /usr/local/dx/help/dxall1367
%doc /usr/local/dx/help/dxall1368
%doc /usr/local/dx/help/dxall1369
%doc /usr/local/dx/help/dxall137
%doc /usr/local/dx/help/dxall1370
%doc /usr/local/dx/help/dxall1371
%doc /usr/local/dx/help/dxall1372
%doc /usr/local/dx/help/dxall1373
%doc /usr/local/dx/help/dxall1374
%doc /usr/local/dx/help/dxall1375
%doc /usr/local/dx/help/dxall1376
%doc /usr/local/dx/help/dxall1377
%doc /usr/local/dx/help/dxall1378
%doc /usr/local/dx/help/dxall1379
%doc /usr/local/dx/help/dxall138
%doc /usr/local/dx/help/dxall1380
%doc /usr/local/dx/help/dxall1381
%doc /usr/local/dx/help/dxall1382
%doc /usr/local/dx/help/dxall1383
%doc /usr/local/dx/help/dxall1384
%doc /usr/local/dx/help/dxall1385
%doc /usr/local/dx/help/dxall1386
%doc /usr/local/dx/help/dxall1387
%doc /usr/local/dx/help/dxall1388
%doc /usr/local/dx/help/dxall1389
%doc /usr/local/dx/help/dxall139
%doc /usr/local/dx/help/dxall1390
%doc /usr/local/dx/help/dxall1391
%doc /usr/local/dx/help/dxall1392
%doc /usr/local/dx/help/dxall1393
%doc /usr/local/dx/help/dxall1394
%doc /usr/local/dx/help/dxall1395
%doc /usr/local/dx/help/dxall1396
%doc /usr/local/dx/help/dxall1397
%doc /usr/local/dx/help/dxall1398
%doc /usr/local/dx/help/dxall1399
%doc /usr/local/dx/help/dxall140
%doc /usr/local/dx/help/dxall1400
%doc /usr/local/dx/help/dxall1401
%doc /usr/local/dx/help/dxall1402
%doc /usr/local/dx/help/dxall1403
%doc /usr/local/dx/help/dxall1404
%doc /usr/local/dx/help/dxall1405
%doc /usr/local/dx/help/dxall1406
%doc /usr/local/dx/help/dxall1407
%doc /usr/local/dx/help/dxall141
%doc /usr/local/dx/help/dxall142
%doc /usr/local/dx/help/dxall143
%doc /usr/local/dx/help/dxall144
%doc /usr/local/dx/help/dxall145
%doc /usr/local/dx/help/dxall146
%doc /usr/local/dx/help/dxall147
%doc /usr/local/dx/help/dxall148
%doc /usr/local/dx/help/dxall149
%doc /usr/local/dx/help/dxall15
%doc /usr/local/dx/help/dxall150
%doc /usr/local/dx/help/dxall151
%doc /usr/local/dx/help/dxall152
%doc /usr/local/dx/help/dxall153
%doc /usr/local/dx/help/dxall154
%doc /usr/local/dx/help/dxall155
%doc /usr/local/dx/help/dxall156
%doc /usr/local/dx/help/dxall157
%doc /usr/local/dx/help/dxall158
%doc /usr/local/dx/help/dxall159
%doc /usr/local/dx/help/dxall160
%doc /usr/local/dx/help/dxall161
%doc /usr/local/dx/help/dxall162
%doc /usr/local/dx/help/dxall163
%doc /usr/local/dx/help/dxall164
%doc /usr/local/dx/help/dxall165
%doc /usr/local/dx/help/dxall166
%doc /usr/local/dx/help/dxall167
%doc /usr/local/dx/help/dxall168
%doc /usr/local/dx/help/dxall169
%doc /usr/local/dx/help/dxall17
%doc /usr/local/dx/help/dxall170
%doc /usr/local/dx/help/dxall171
%doc /usr/local/dx/help/dxall172
%doc /usr/local/dx/help/dxall173
%doc /usr/local/dx/help/dxall174
%doc /usr/local/dx/help/dxall175
%doc /usr/local/dx/help/dxall176
%doc /usr/local/dx/help/dxall177
%doc /usr/local/dx/help/dxall178
%doc /usr/local/dx/help/dxall179
%doc /usr/local/dx/help/dxall180
%doc /usr/local/dx/help/dxall181
%doc /usr/local/dx/help/dxall182
%doc /usr/local/dx/help/dxall183
%doc /usr/local/dx/help/dxall184
%doc /usr/local/dx/help/dxall185
%doc /usr/local/dx/help/dxall186
%doc /usr/local/dx/help/dxall187
%doc /usr/local/dx/help/dxall188
%doc /usr/local/dx/help/dxall189
%doc /usr/local/dx/help/dxall19
%doc /usr/local/dx/help/dxall190
%doc /usr/local/dx/help/dxall191
%doc /usr/local/dx/help/dxall192
%doc /usr/local/dx/help/dxall193
%doc /usr/local/dx/help/dxall194
%doc /usr/local/dx/help/dxall195
%doc /usr/local/dx/help/dxall196
%doc /usr/local/dx/help/dxall197
%doc /usr/local/dx/help/dxall198
%doc /usr/local/dx/help/dxall199
%doc /usr/local/dx/help/dxall2
%doc /usr/local/dx/help/dxall20
%doc /usr/local/dx/help/dxall200
%doc /usr/local/dx/help/dxall201
%doc /usr/local/dx/help/dxall203
%doc /usr/local/dx/help/dxall204
%doc /usr/local/dx/help/dxall206
%doc /usr/local/dx/help/dxall207
%doc /usr/local/dx/help/dxall208
%doc /usr/local/dx/help/dxall21
%doc /usr/local/dx/help/dxall210
%doc /usr/local/dx/help/dxall211
%doc /usr/local/dx/help/dxall213
%doc /usr/local/dx/help/dxall215
%doc /usr/local/dx/help/dxall217
%doc /usr/local/dx/help/dxall219
%doc /usr/local/dx/help/dxall22
%doc /usr/local/dx/help/dxall220
%doc /usr/local/dx/help/dxall221
%doc /usr/local/dx/help/dxall222
%doc /usr/local/dx/help/dxall223
%doc /usr/local/dx/help/dxall225
%doc /usr/local/dx/help/dxall227
%doc /usr/local/dx/help/dxall229
%doc /usr/local/dx/help/dxall23
%doc /usr/local/dx/help/dxall231
%doc /usr/local/dx/help/dxall233
%doc /usr/local/dx/help/dxall235
%doc /usr/local/dx/help/dxall237
%doc /usr/local/dx/help/dxall239
%doc /usr/local/dx/help/dxall24
%doc /usr/local/dx/help/dxall241
%doc /usr/local/dx/help/dxall243
%doc /usr/local/dx/help/dxall245
%doc /usr/local/dx/help/dxall247
%doc /usr/local/dx/help/dxall249
%doc /usr/local/dx/help/dxall25
%doc /usr/local/dx/help/dxall251
%doc /usr/local/dx/help/dxall252
%doc /usr/local/dx/help/dxall253
%doc /usr/local/dx/help/dxall254
%doc /usr/local/dx/help/dxall255
%doc /usr/local/dx/help/dxall256
%doc /usr/local/dx/help/dxall257
%doc /usr/local/dx/help/dxall258
%doc /usr/local/dx/help/dxall259
%doc /usr/local/dx/help/dxall26
%doc /usr/local/dx/help/dxall260
%doc /usr/local/dx/help/dxall261
%doc /usr/local/dx/help/dxall262
%doc /usr/local/dx/help/dxall263
%doc /usr/local/dx/help/dxall264
%doc /usr/local/dx/help/dxall265
%doc /usr/local/dx/help/dxall266
%doc /usr/local/dx/help/dxall267
%doc /usr/local/dx/help/dxall268
%doc /usr/local/dx/help/dxall269
%doc /usr/local/dx/help/dxall27
%doc /usr/local/dx/help/dxall270
%doc /usr/local/dx/help/dxall271
%doc /usr/local/dx/help/dxall272
%doc /usr/local/dx/help/dxall273
%doc /usr/local/dx/help/dxall274
%doc /usr/local/dx/help/dxall275
%doc /usr/local/dx/help/dxall276
%doc /usr/local/dx/help/dxall278
%doc /usr/local/dx/help/dxall28
%doc /usr/local/dx/help/dxall280
%doc /usr/local/dx/help/dxall282
%doc /usr/local/dx/help/dxall283
%doc /usr/local/dx/help/dxall284
%doc /usr/local/dx/help/dxall285
%doc /usr/local/dx/help/dxall286
%doc /usr/local/dx/help/dxall287
%doc /usr/local/dx/help/dxall288
%doc /usr/local/dx/help/dxall289
%doc /usr/local/dx/help/dxall29
%doc /usr/local/dx/help/dxall290
%doc /usr/local/dx/help/dxall291
%doc /usr/local/dx/help/dxall292
%doc /usr/local/dx/help/dxall293
%doc /usr/local/dx/help/dxall294
%doc /usr/local/dx/help/dxall295
%doc /usr/local/dx/help/dxall296
%doc /usr/local/dx/help/dxall297
%doc /usr/local/dx/help/dxall298
%doc /usr/local/dx/help/dxall299
%doc /usr/local/dx/help/dxall3
%doc /usr/local/dx/help/dxall30
%doc /usr/local/dx/help/dxall300
%doc /usr/local/dx/help/dxall301
%doc /usr/local/dx/help/dxall302
%doc /usr/local/dx/help/dxall304
%doc /usr/local/dx/help/dxall305
%doc /usr/local/dx/help/dxall306
%doc /usr/local/dx/help/dxall307
%doc /usr/local/dx/help/dxall308
%doc /usr/local/dx/help/dxall309
%doc /usr/local/dx/help/dxall31
%doc /usr/local/dx/help/dxall310
%doc /usr/local/dx/help/dxall312
%doc /usr/local/dx/help/dxall314
%doc /usr/local/dx/help/dxall316
%doc /usr/local/dx/help/dxall317
%doc /usr/local/dx/help/dxall318
%doc /usr/local/dx/help/dxall32
%doc /usr/local/dx/help/dxall320
%doc /usr/local/dx/help/dxall321
%doc /usr/local/dx/help/dxall322
%doc /usr/local/dx/help/dxall323
%doc /usr/local/dx/help/dxall324
%doc /usr/local/dx/help/dxall325
%doc /usr/local/dx/help/dxall326
%doc /usr/local/dx/help/dxall327
%doc /usr/local/dx/help/dxall328
%doc /usr/local/dx/help/dxall329
%doc /usr/local/dx/help/dxall33
%doc /usr/local/dx/help/dxall330
%doc /usr/local/dx/help/dxall331
%doc /usr/local/dx/help/dxall332
%doc /usr/local/dx/help/dxall333
%doc /usr/local/dx/help/dxall334
%doc /usr/local/dx/help/dxall335
%doc /usr/local/dx/help/dxall336
%doc /usr/local/dx/help/dxall337
%doc /usr/local/dx/help/dxall338
%doc /usr/local/dx/help/dxall339
%doc /usr/local/dx/help/dxall34
%doc /usr/local/dx/help/dxall340
%doc /usr/local/dx/help/dxall341
%doc /usr/local/dx/help/dxall342
%doc /usr/local/dx/help/dxall343
%doc /usr/local/dx/help/dxall344
%doc /usr/local/dx/help/dxall345
%doc /usr/local/dx/help/dxall346
%doc /usr/local/dx/help/dxall347
%doc /usr/local/dx/help/dxall348
%doc /usr/local/dx/help/dxall349
%doc /usr/local/dx/help/dxall35
%doc /usr/local/dx/help/dxall350
%doc /usr/local/dx/help/dxall351
%doc /usr/local/dx/help/dxall352
%doc /usr/local/dx/help/dxall353
%doc /usr/local/dx/help/dxall354
%doc /usr/local/dx/help/dxall355
%doc /usr/local/dx/help/dxall356
%doc /usr/local/dx/help/dxall357
%doc /usr/local/dx/help/dxall358
%doc /usr/local/dx/help/dxall359
%doc /usr/local/dx/help/dxall36
%doc /usr/local/dx/help/dxall361
%doc /usr/local/dx/help/dxall363
%doc /usr/local/dx/help/dxall364
%doc /usr/local/dx/help/dxall365
%doc /usr/local/dx/help/dxall366
%doc /usr/local/dx/help/dxall367
%doc /usr/local/dx/help/dxall368
%doc /usr/local/dx/help/dxall37
%doc /usr/local/dx/help/dxall370
%doc /usr/local/dx/help/dxall371
%doc /usr/local/dx/help/dxall372
%doc /usr/local/dx/help/dxall373
%doc /usr/local/dx/help/dxall374
%doc /usr/local/dx/help/dxall375
%doc /usr/local/dx/help/dxall376
%doc /usr/local/dx/help/dxall377
%doc /usr/local/dx/help/dxall378
%doc /usr/local/dx/help/dxall379
%doc /usr/local/dx/help/dxall38
%doc /usr/local/dx/help/dxall380
%doc /usr/local/dx/help/dxall381
%doc /usr/local/dx/help/dxall382
%doc /usr/local/dx/help/dxall383
%doc /usr/local/dx/help/dxall384
%doc /usr/local/dx/help/dxall385
%doc /usr/local/dx/help/dxall386
%doc /usr/local/dx/help/dxall387
%doc /usr/local/dx/help/dxall388
%doc /usr/local/dx/help/dxall389
%doc /usr/local/dx/help/dxall39
%doc /usr/local/dx/help/dxall390
%doc /usr/local/dx/help/dxall391
%doc /usr/local/dx/help/dxall392
%doc /usr/local/dx/help/dxall393
%doc /usr/local/dx/help/dxall394
%doc /usr/local/dx/help/dxall395
%doc /usr/local/dx/help/dxall396
%doc /usr/local/dx/help/dxall397
%doc /usr/local/dx/help/dxall399
%doc /usr/local/dx/help/dxall4
%doc /usr/local/dx/help/dxall40
%doc /usr/local/dx/help/dxall400
%doc /usr/local/dx/help/dxall401
%doc /usr/local/dx/help/dxall402
%doc /usr/local/dx/help/dxall403
%doc /usr/local/dx/help/dxall404
%doc /usr/local/dx/help/dxall405
%doc /usr/local/dx/help/dxall406
%doc /usr/local/dx/help/dxall407
%doc /usr/local/dx/help/dxall408
%doc /usr/local/dx/help/dxall409
%doc /usr/local/dx/help/dxall41
%doc /usr/local/dx/help/dxall410
%doc /usr/local/dx/help/dxall411
%doc /usr/local/dx/help/dxall413
%doc /usr/local/dx/help/dxall415
%doc /usr/local/dx/help/dxall417
%doc /usr/local/dx/help/dxall418
%doc /usr/local/dx/help/dxall419
%doc /usr/local/dx/help/dxall42
%doc /usr/local/dx/help/dxall420
%doc /usr/local/dx/help/dxall421
%doc /usr/local/dx/help/dxall423
%doc /usr/local/dx/help/dxall425
%doc /usr/local/dx/help/dxall427
%doc /usr/local/dx/help/dxall429
%doc /usr/local/dx/help/dxall43
%doc /usr/local/dx/help/dxall430
%doc /usr/local/dx/help/dxall431
%doc /usr/local/dx/help/dxall432
%doc /usr/local/dx/help/dxall433
%doc /usr/local/dx/help/dxall434
%doc /usr/local/dx/help/dxall435
%doc /usr/local/dx/help/dxall436
%doc /usr/local/dx/help/dxall437
%doc /usr/local/dx/help/dxall438
%doc /usr/local/dx/help/dxall439
%doc /usr/local/dx/help/dxall44
%doc /usr/local/dx/help/dxall440
%doc /usr/local/dx/help/dxall441
%doc /usr/local/dx/help/dxall442
%doc /usr/local/dx/help/dxall443
%doc /usr/local/dx/help/dxall444
%doc /usr/local/dx/help/dxall445
%doc /usr/local/dx/help/dxall446
%doc /usr/local/dx/help/dxall447
%doc /usr/local/dx/help/dxall448
%doc /usr/local/dx/help/dxall449
%doc /usr/local/dx/help/dxall45
%doc /usr/local/dx/help/dxall450
%doc /usr/local/dx/help/dxall451
%doc /usr/local/dx/help/dxall452
%doc /usr/local/dx/help/dxall453
%doc /usr/local/dx/help/dxall454
%doc /usr/local/dx/help/dxall455
%doc /usr/local/dx/help/dxall456
%doc /usr/local/dx/help/dxall457
%doc /usr/local/dx/help/dxall458
%doc /usr/local/dx/help/dxall459
%doc /usr/local/dx/help/dxall46
%doc /usr/local/dx/help/dxall460
%doc /usr/local/dx/help/dxall461
%doc /usr/local/dx/help/dxall462
%doc /usr/local/dx/help/dxall463
%doc /usr/local/dx/help/dxall464
%doc /usr/local/dx/help/dxall465
%doc /usr/local/dx/help/dxall466
%doc /usr/local/dx/help/dxall467
%doc /usr/local/dx/help/dxall468
%doc /usr/local/dx/help/dxall469
%doc /usr/local/dx/help/dxall47
%doc /usr/local/dx/help/dxall470
%doc /usr/local/dx/help/dxall471
%doc /usr/local/dx/help/dxall472
%doc /usr/local/dx/help/dxall473
%doc /usr/local/dx/help/dxall474
%doc /usr/local/dx/help/dxall475
%doc /usr/local/dx/help/dxall476
%doc /usr/local/dx/help/dxall477
%doc /usr/local/dx/help/dxall478
%doc /usr/local/dx/help/dxall479
%doc /usr/local/dx/help/dxall48
%doc /usr/local/dx/help/dxall480
%doc /usr/local/dx/help/dxall481
%doc /usr/local/dx/help/dxall482
%doc /usr/local/dx/help/dxall483
%doc /usr/local/dx/help/dxall484
%doc /usr/local/dx/help/dxall485
%doc /usr/local/dx/help/dxall486
%doc /usr/local/dx/help/dxall487
%doc /usr/local/dx/help/dxall488
%doc /usr/local/dx/help/dxall489
%doc /usr/local/dx/help/dxall49
%doc /usr/local/dx/help/dxall490
%doc /usr/local/dx/help/dxall491
%doc /usr/local/dx/help/dxall492
%doc /usr/local/dx/help/dxall493
%doc /usr/local/dx/help/dxall494
%doc /usr/local/dx/help/dxall495
%doc /usr/local/dx/help/dxall496
%doc /usr/local/dx/help/dxall497
%doc /usr/local/dx/help/dxall499
%doc /usr/local/dx/help/dxall5
%doc /usr/local/dx/help/dxall50
%doc /usr/local/dx/help/dxall501
%doc /usr/local/dx/help/dxall503
%doc /usr/local/dx/help/dxall505
%doc /usr/local/dx/help/dxall506
%doc /usr/local/dx/help/dxall507
%doc /usr/local/dx/help/dxall508
%doc /usr/local/dx/help/dxall509
%doc /usr/local/dx/help/dxall51
%doc /usr/local/dx/help/dxall510
%doc /usr/local/dx/help/dxall511
%doc /usr/local/dx/help/dxall512
%doc /usr/local/dx/help/dxall513
%doc /usr/local/dx/help/dxall514
%doc /usr/local/dx/help/dxall515
%doc /usr/local/dx/help/dxall516
%doc /usr/local/dx/help/dxall517
%doc /usr/local/dx/help/dxall518
%doc /usr/local/dx/help/dxall52
%doc /usr/local/dx/help/dxall520
%doc /usr/local/dx/help/dxall522
%doc /usr/local/dx/help/dxall523
%doc /usr/local/dx/help/dxall525
%doc /usr/local/dx/help/dxall527
%doc /usr/local/dx/help/dxall529
%doc /usr/local/dx/help/dxall53
%doc /usr/local/dx/help/dxall530
%doc /usr/local/dx/help/dxall531
%doc /usr/local/dx/help/dxall532
%doc /usr/local/dx/help/dxall533
%doc /usr/local/dx/help/dxall534
%doc /usr/local/dx/help/dxall535
%doc /usr/local/dx/help/dxall536
%doc /usr/local/dx/help/dxall537
%doc /usr/local/dx/help/dxall538
%doc /usr/local/dx/help/dxall539
%doc /usr/local/dx/help/dxall54
%doc /usr/local/dx/help/dxall540
%doc /usr/local/dx/help/dxall541
%doc /usr/local/dx/help/dxall542
%doc /usr/local/dx/help/dxall543
%doc /usr/local/dx/help/dxall544
%doc /usr/local/dx/help/dxall545
%doc /usr/local/dx/help/dxall546
%doc /usr/local/dx/help/dxall547
%doc /usr/local/dx/help/dxall548
%doc /usr/local/dx/help/dxall549
%doc /usr/local/dx/help/dxall55
%doc /usr/local/dx/help/dxall550
%doc /usr/local/dx/help/dxall551
%doc /usr/local/dx/help/dxall552
%doc /usr/local/dx/help/dxall553
%doc /usr/local/dx/help/dxall554
%doc /usr/local/dx/help/dxall555
%doc /usr/local/dx/help/dxall556
%doc /usr/local/dx/help/dxall557
%doc /usr/local/dx/help/dxall558
%doc /usr/local/dx/help/dxall559
%doc /usr/local/dx/help/dxall56
%doc /usr/local/dx/help/dxall560
%doc /usr/local/dx/help/dxall561
%doc /usr/local/dx/help/dxall562
%doc /usr/local/dx/help/dxall563
%doc /usr/local/dx/help/dxall564
%doc /usr/local/dx/help/dxall565
%doc /usr/local/dx/help/dxall566
%doc /usr/local/dx/help/dxall567
%doc /usr/local/dx/help/dxall568
%doc /usr/local/dx/help/dxall569
%doc /usr/local/dx/help/dxall57
%doc /usr/local/dx/help/dxall570
%doc /usr/local/dx/help/dxall571
%doc /usr/local/dx/help/dxall572
%doc /usr/local/dx/help/dxall573
%doc /usr/local/dx/help/dxall575
%doc /usr/local/dx/help/dxall576
%doc /usr/local/dx/help/dxall578
%doc /usr/local/dx/help/dxall58
%doc /usr/local/dx/help/dxall580
%doc /usr/local/dx/help/dxall582
%doc /usr/local/dx/help/dxall584
%doc /usr/local/dx/help/dxall586
%doc /usr/local/dx/help/dxall587
%doc /usr/local/dx/help/dxall589
%doc /usr/local/dx/help/dxall59
%doc /usr/local/dx/help/dxall590
%doc /usr/local/dx/help/dxall592
%doc /usr/local/dx/help/dxall594
%doc /usr/local/dx/help/dxall596
%doc /usr/local/dx/help/dxall597
%doc /usr/local/dx/help/dxall598
%doc /usr/local/dx/help/dxall599
%doc /usr/local/dx/help/dxall6
%doc /usr/local/dx/help/dxall60
%doc /usr/local/dx/help/dxall600
%doc /usr/local/dx/help/dxall601
%doc /usr/local/dx/help/dxall602
%doc /usr/local/dx/help/dxall603
%doc /usr/local/dx/help/dxall604
%doc /usr/local/dx/help/dxall605
%doc /usr/local/dx/help/dxall606
%doc /usr/local/dx/help/dxall607
%doc /usr/local/dx/help/dxall608
%doc /usr/local/dx/help/dxall609
%doc /usr/local/dx/help/dxall61
%doc /usr/local/dx/help/dxall610
%doc /usr/local/dx/help/dxall611
%doc /usr/local/dx/help/dxall612
%doc /usr/local/dx/help/dxall613
%doc /usr/local/dx/help/dxall614
%doc /usr/local/dx/help/dxall615
%doc /usr/local/dx/help/dxall616
%doc /usr/local/dx/help/dxall617
%doc /usr/local/dx/help/dxall618
%doc /usr/local/dx/help/dxall619
%doc /usr/local/dx/help/dxall62
%doc /usr/local/dx/help/dxall620
%doc /usr/local/dx/help/dxall621
%doc /usr/local/dx/help/dxall622
%doc /usr/local/dx/help/dxall623
%doc /usr/local/dx/help/dxall624
%doc /usr/local/dx/help/dxall625
%doc /usr/local/dx/help/dxall626
%doc /usr/local/dx/help/dxall627
%doc /usr/local/dx/help/dxall628
%doc /usr/local/dx/help/dxall629
%doc /usr/local/dx/help/dxall63
%doc /usr/local/dx/help/dxall630
%doc /usr/local/dx/help/dxall631
%doc /usr/local/dx/help/dxall632
%doc /usr/local/dx/help/dxall633
%doc /usr/local/dx/help/dxall634
%doc /usr/local/dx/help/dxall635
%doc /usr/local/dx/help/dxall636
%doc /usr/local/dx/help/dxall637
%doc /usr/local/dx/help/dxall638
%doc /usr/local/dx/help/dxall639
%doc /usr/local/dx/help/dxall64
%doc /usr/local/dx/help/dxall640
%doc /usr/local/dx/help/dxall641
%doc /usr/local/dx/help/dxall642
%doc /usr/local/dx/help/dxall643
%doc /usr/local/dx/help/dxall644
%doc /usr/local/dx/help/dxall645
%doc /usr/local/dx/help/dxall646
%doc /usr/local/dx/help/dxall647
%doc /usr/local/dx/help/dxall648
%doc /usr/local/dx/help/dxall649
%doc /usr/local/dx/help/dxall65
%doc /usr/local/dx/help/dxall650
%doc /usr/local/dx/help/dxall651
%doc /usr/local/dx/help/dxall652
%doc /usr/local/dx/help/dxall653
%doc /usr/local/dx/help/dxall654
%doc /usr/local/dx/help/dxall655
%doc /usr/local/dx/help/dxall656
%doc /usr/local/dx/help/dxall657
%doc /usr/local/dx/help/dxall658
%doc /usr/local/dx/help/dxall659
%doc /usr/local/dx/help/dxall66
%doc /usr/local/dx/help/dxall660
%doc /usr/local/dx/help/dxall661
%doc /usr/local/dx/help/dxall662
%doc /usr/local/dx/help/dxall663
%doc /usr/local/dx/help/dxall664
%doc /usr/local/dx/help/dxall665
%doc /usr/local/dx/help/dxall666
%doc /usr/local/dx/help/dxall667
%doc /usr/local/dx/help/dxall668
%doc /usr/local/dx/help/dxall669
%doc /usr/local/dx/help/dxall67
%doc /usr/local/dx/help/dxall670
%doc /usr/local/dx/help/dxall671
%doc /usr/local/dx/help/dxall672
%doc /usr/local/dx/help/dxall673
%doc /usr/local/dx/help/dxall674
%doc /usr/local/dx/help/dxall675
%doc /usr/local/dx/help/dxall676
%doc /usr/local/dx/help/dxall677
%doc /usr/local/dx/help/dxall678
%doc /usr/local/dx/help/dxall679
%doc /usr/local/dx/help/dxall68
%doc /usr/local/dx/help/dxall680
%doc /usr/local/dx/help/dxall681
%doc /usr/local/dx/help/dxall682
%doc /usr/local/dx/help/dxall683
%doc /usr/local/dx/help/dxall684
%doc /usr/local/dx/help/dxall685
%doc /usr/local/dx/help/dxall687
%doc /usr/local/dx/help/dxall689
%doc /usr/local/dx/help/dxall69
%doc /usr/local/dx/help/dxall691
%doc /usr/local/dx/help/dxall693
%doc /usr/local/dx/help/dxall694
%doc /usr/local/dx/help/dxall695
%doc /usr/local/dx/help/dxall697
%doc /usr/local/dx/help/dxall699
%doc /usr/local/dx/help/dxall7
%doc /usr/local/dx/help/dxall70
%doc /usr/local/dx/help/dxall701
%doc /usr/local/dx/help/dxall703
%doc /usr/local/dx/help/dxall705
%doc /usr/local/dx/help/dxall707
%doc /usr/local/dx/help/dxall709
%doc /usr/local/dx/help/dxall71
%doc /usr/local/dx/help/dxall711
%doc /usr/local/dx/help/dxall713
%doc /usr/local/dx/help/dxall715
%doc /usr/local/dx/help/dxall717
%doc /usr/local/dx/help/dxall719
%doc /usr/local/dx/help/dxall72
%doc /usr/local/dx/help/dxall721
%doc /usr/local/dx/help/dxall723
%doc /usr/local/dx/help/dxall725
%doc /usr/local/dx/help/dxall727
%doc /usr/local/dx/help/dxall729
%doc /usr/local/dx/help/dxall73
%doc /usr/local/dx/help/dxall731
%doc /usr/local/dx/help/dxall733
%doc /usr/local/dx/help/dxall735
%doc /usr/local/dx/help/dxall737
%doc /usr/local/dx/help/dxall739
%doc /usr/local/dx/help/dxall74
%doc /usr/local/dx/help/dxall741
%doc /usr/local/dx/help/dxall743
%doc /usr/local/dx/help/dxall744
%doc /usr/local/dx/help/dxall745
%doc /usr/local/dx/help/dxall746
%doc /usr/local/dx/help/dxall747
%doc /usr/local/dx/help/dxall748
%doc /usr/local/dx/help/dxall749
%doc /usr/local/dx/help/dxall75
%doc /usr/local/dx/help/dxall750
%doc /usr/local/dx/help/dxall751
%doc /usr/local/dx/help/dxall752
%doc /usr/local/dx/help/dxall753
%doc /usr/local/dx/help/dxall754
%doc /usr/local/dx/help/dxall755
%doc /usr/local/dx/help/dxall756
%doc /usr/local/dx/help/dxall757
%doc /usr/local/dx/help/dxall758
%doc /usr/local/dx/help/dxall759
%doc /usr/local/dx/help/dxall76
%doc /usr/local/dx/help/dxall760
%doc /usr/local/dx/help/dxall761
%doc /usr/local/dx/help/dxall762
%doc /usr/local/dx/help/dxall763
%doc /usr/local/dx/help/dxall764
%doc /usr/local/dx/help/dxall765
%doc /usr/local/dx/help/dxall766
%doc /usr/local/dx/help/dxall767
%doc /usr/local/dx/help/dxall768
%doc /usr/local/dx/help/dxall769
%doc /usr/local/dx/help/dxall77
%doc /usr/local/dx/help/dxall770
%doc /usr/local/dx/help/dxall771
%doc /usr/local/dx/help/dxall772
%doc /usr/local/dx/help/dxall773
%doc /usr/local/dx/help/dxall774
%doc /usr/local/dx/help/dxall775
%doc /usr/local/dx/help/dxall776
%doc /usr/local/dx/help/dxall777
%doc /usr/local/dx/help/dxall778
%doc /usr/local/dx/help/dxall779
%doc /usr/local/dx/help/dxall78
%doc /usr/local/dx/help/dxall780
%doc /usr/local/dx/help/dxall781
%doc /usr/local/dx/help/dxall782
%doc /usr/local/dx/help/dxall783
%doc /usr/local/dx/help/dxall784
%doc /usr/local/dx/help/dxall785
%doc /usr/local/dx/help/dxall786
%doc /usr/local/dx/help/dxall787
%doc /usr/local/dx/help/dxall788
%doc /usr/local/dx/help/dxall789
%doc /usr/local/dx/help/dxall79
%doc /usr/local/dx/help/dxall790
%doc /usr/local/dx/help/dxall791
%doc /usr/local/dx/help/dxall792
%doc /usr/local/dx/help/dxall793
%doc /usr/local/dx/help/dxall794
%doc /usr/local/dx/help/dxall795
%doc /usr/local/dx/help/dxall796
%doc /usr/local/dx/help/dxall797
%doc /usr/local/dx/help/dxall798
%doc /usr/local/dx/help/dxall799
%doc /usr/local/dx/help/dxall8
%doc /usr/local/dx/help/dxall80
%doc /usr/local/dx/help/dxall800
%doc /usr/local/dx/help/dxall801
%doc /usr/local/dx/help/dxall802
%doc /usr/local/dx/help/dxall803
%doc /usr/local/dx/help/dxall804
%doc /usr/local/dx/help/dxall805
%doc /usr/local/dx/help/dxall806
%doc /usr/local/dx/help/dxall807
%doc /usr/local/dx/help/dxall809
%doc /usr/local/dx/help/dxall81
%doc /usr/local/dx/help/dxall811
%doc /usr/local/dx/help/dxall812
%doc /usr/local/dx/help/dxall813
%doc /usr/local/dx/help/dxall814
%doc /usr/local/dx/help/dxall815
%doc /usr/local/dx/help/dxall817
%doc /usr/local/dx/help/dxall818
%doc /usr/local/dx/help/dxall819
%doc /usr/local/dx/help/dxall82
%doc /usr/local/dx/help/dxall820
%doc /usr/local/dx/help/dxall821
%doc /usr/local/dx/help/dxall822
%doc /usr/local/dx/help/dxall823
%doc /usr/local/dx/help/dxall824
%doc /usr/local/dx/help/dxall825
%doc /usr/local/dx/help/dxall826
%doc /usr/local/dx/help/dxall827
%doc /usr/local/dx/help/dxall828
%doc /usr/local/dx/help/dxall829
%doc /usr/local/dx/help/dxall83
%doc /usr/local/dx/help/dxall830
%doc /usr/local/dx/help/dxall831
%doc /usr/local/dx/help/dxall832
%doc /usr/local/dx/help/dxall833
%doc /usr/local/dx/help/dxall835
%doc /usr/local/dx/help/dxall837
%doc /usr/local/dx/help/dxall839
%doc /usr/local/dx/help/dxall84
%doc /usr/local/dx/help/dxall841
%doc /usr/local/dx/help/dxall843
%doc /usr/local/dx/help/dxall844
%doc /usr/local/dx/help/dxall845
%doc /usr/local/dx/help/dxall846
%doc /usr/local/dx/help/dxall847
%doc /usr/local/dx/help/dxall848
%doc /usr/local/dx/help/dxall849
%doc /usr/local/dx/help/dxall85
%doc /usr/local/dx/help/dxall850
%doc /usr/local/dx/help/dxall851
%doc /usr/local/dx/help/dxall852
%doc /usr/local/dx/help/dxall853
%doc /usr/local/dx/help/dxall854
%doc /usr/local/dx/help/dxall855
%doc /usr/local/dx/help/dxall856
%doc /usr/local/dx/help/dxall857
%doc /usr/local/dx/help/dxall858
%doc /usr/local/dx/help/dxall859
%doc /usr/local/dx/help/dxall86
%doc /usr/local/dx/help/dxall860
%doc /usr/local/dx/help/dxall862
%doc /usr/local/dx/help/dxall864
%doc /usr/local/dx/help/dxall866
%doc /usr/local/dx/help/dxall868
%doc /usr/local/dx/help/dxall87
%doc /usr/local/dx/help/dxall870
%doc /usr/local/dx/help/dxall871
%doc /usr/local/dx/help/dxall872
%doc /usr/local/dx/help/dxall873
%doc /usr/local/dx/help/dxall875
%doc /usr/local/dx/help/dxall876
%doc /usr/local/dx/help/dxall877
%doc /usr/local/dx/help/dxall878
%doc /usr/local/dx/help/dxall879
%doc /usr/local/dx/help/dxall88
%doc /usr/local/dx/help/dxall880
%doc /usr/local/dx/help/dxall881
%doc /usr/local/dx/help/dxall882
%doc /usr/local/dx/help/dxall883
%doc /usr/local/dx/help/dxall884
%doc /usr/local/dx/help/dxall885
%doc /usr/local/dx/help/dxall886
%doc /usr/local/dx/help/dxall887
%doc /usr/local/dx/help/dxall888
%doc /usr/local/dx/help/dxall889
%doc /usr/local/dx/help/dxall89
%doc /usr/local/dx/help/dxall890
%doc /usr/local/dx/help/dxall891
%doc /usr/local/dx/help/dxall892
%doc /usr/local/dx/help/dxall893
%doc /usr/local/dx/help/dxall894
%doc /usr/local/dx/help/dxall895
%doc /usr/local/dx/help/dxall896
%doc /usr/local/dx/help/dxall897
%doc /usr/local/dx/help/dxall898
%doc /usr/local/dx/help/dxall899
%doc /usr/local/dx/help/dxall9
%doc /usr/local/dx/help/dxall90
%doc /usr/local/dx/help/dxall900
%doc /usr/local/dx/help/dxall901
%doc /usr/local/dx/help/dxall902
%doc /usr/local/dx/help/dxall903
%doc /usr/local/dx/help/dxall904
%doc /usr/local/dx/help/dxall905
%doc /usr/local/dx/help/dxall906
%doc /usr/local/dx/help/dxall908
%doc /usr/local/dx/help/dxall909
%doc /usr/local/dx/help/dxall91
%doc /usr/local/dx/help/dxall910
%doc /usr/local/dx/help/dxall911
%doc /usr/local/dx/help/dxall912
%doc /usr/local/dx/help/dxall913
%doc /usr/local/dx/help/dxall914
%doc /usr/local/dx/help/dxall915
%doc /usr/local/dx/help/dxall916
%doc /usr/local/dx/help/dxall917
%doc /usr/local/dx/help/dxall918
%doc /usr/local/dx/help/dxall919
%doc /usr/local/dx/help/dxall92
%doc /usr/local/dx/help/dxall920
%doc /usr/local/dx/help/dxall921
%doc /usr/local/dx/help/dxall922
%doc /usr/local/dx/help/dxall923
%doc /usr/local/dx/help/dxall924
%doc /usr/local/dx/help/dxall925
%doc /usr/local/dx/help/dxall926
%doc /usr/local/dx/help/dxall927
%doc /usr/local/dx/help/dxall928
%doc /usr/local/dx/help/dxall929
%doc /usr/local/dx/help/dxall93
%doc /usr/local/dx/help/dxall930
%doc /usr/local/dx/help/dxall931
%doc /usr/local/dx/help/dxall932
%doc /usr/local/dx/help/dxall933
%doc /usr/local/dx/help/dxall934
%doc /usr/local/dx/help/dxall935
%doc /usr/local/dx/help/dxall936
%doc /usr/local/dx/help/dxall937
%doc /usr/local/dx/help/dxall938
%doc /usr/local/dx/help/dxall939
%doc /usr/local/dx/help/dxall94
%doc /usr/local/dx/help/dxall940
%doc /usr/local/dx/help/dxall941
%doc /usr/local/dx/help/dxall942
%doc /usr/local/dx/help/dxall943
%doc /usr/local/dx/help/dxall944
%doc /usr/local/dx/help/dxall945
%doc /usr/local/dx/help/dxall946
%doc /usr/local/dx/help/dxall947
%doc /usr/local/dx/help/dxall948
%doc /usr/local/dx/help/dxall949
%doc /usr/local/dx/help/dxall95
%doc /usr/local/dx/help/dxall950
%doc /usr/local/dx/help/dxall951
%doc /usr/local/dx/help/dxall952
%doc /usr/local/dx/help/dxall953
%doc /usr/local/dx/help/dxall954
%doc /usr/local/dx/help/dxall955
%doc /usr/local/dx/help/dxall956
%doc /usr/local/dx/help/dxall957
%doc /usr/local/dx/help/dxall958
%doc /usr/local/dx/help/dxall959
%doc /usr/local/dx/help/dxall96
%doc /usr/local/dx/help/dxall960
%doc /usr/local/dx/help/dxall961
%doc /usr/local/dx/help/dxall962
%doc /usr/local/dx/help/dxall963
%doc /usr/local/dx/help/dxall964
%doc /usr/local/dx/help/dxall965
%doc /usr/local/dx/help/dxall966
%doc /usr/local/dx/help/dxall967
%doc /usr/local/dx/help/dxall968
%doc /usr/local/dx/help/dxall969
%doc /usr/local/dx/help/dxall97
%doc /usr/local/dx/help/dxall970
%doc /usr/local/dx/help/dxall971
%doc /usr/local/dx/help/dxall972
%doc /usr/local/dx/help/dxall973
%doc /usr/local/dx/help/dxall974
%doc /usr/local/dx/help/dxall975
%doc /usr/local/dx/help/dxall976
%doc /usr/local/dx/help/dxall977
%doc /usr/local/dx/help/dxall978
%doc /usr/local/dx/help/dxall979
%doc /usr/local/dx/help/dxall98
%doc /usr/local/dx/help/dxall980
%doc /usr/local/dx/help/dxall981
%doc /usr/local/dx/help/dxall982
%doc /usr/local/dx/help/dxall983
%doc /usr/local/dx/help/dxall984
%doc /usr/local/dx/help/dxall985
%doc /usr/local/dx/help/dxall986
%doc /usr/local/dx/help/dxall987
%doc /usr/local/dx/help/dxall988
%doc /usr/local/dx/help/dxall989
%doc /usr/local/dx/help/dxall99
%doc /usr/local/dx/help/dxall990
%doc /usr/local/dx/help/dxall991
%doc /usr/local/dx/help/dxall992
%doc /usr/local/dx/help/dxall993
%doc /usr/local/dx/help/dxall994
%doc /usr/local/dx/help/dxall995
%doc /usr/local/dx/help/dxall997
%doc /usr/local/dx/help/dxall998
%doc /usr/local/dx/help/dxall999
%doc /usr/local/dx/help/hlpalhtl
%doc /usr/local/dx/help/hlpall
%doc /usr/local/dx/help/spots
%doc /usr/local/dx/help/mbidx
%doc /usr/local/dx/help/quikidx
%doc /usr/local/dx/help/svsmstrh
%doc /usr/local/dx/help/ugidx
%doc /usr/local/dx/help/usrefidx
%doc /usr/local/dx/help/GarHelpDir
%doc /usr/local/dx/help/MBHelpDir
%dir /usr/local/dx/html/
%doc /usr/local/dx/html/README.htm
%doc /usr/local/dx/html/README_SMP.htm
%doc /usr/local/dx/html/README_alphax.htm
%doc /usr/local/dx/html/README_hp700.htm
%doc /usr/local/dx/html/README_ibm6000.htm
%doc /usr/local/dx/html/README_intelnt.htm
%doc /usr/local/dx/html/README_sgi.htm
%doc /usr/local/dx/html/README_solaris.htm
%doc /usr/local/dx/html/allguide.htm
%doc /usr/local/dx/html/insguide.htm
%doc /usr/local/dx/html/proguide.htm
%doc /usr/local/dx/html/qikguide.htm
%doc /usr/local/dx/html/refguide.htm
%doc /usr/local/dx/html/usrguide.htm
%dir /usr/local/dx/html/pages/
%doc /usr/local/dx/html/pages/insgu002.htm
%doc /usr/local/dx/html/pages/insgu003.htm
%doc /usr/local/dx/html/pages/insgu004.htm
%doc /usr/local/dx/html/pages/insgu005.htm
%doc /usr/local/dx/html/pages/insgu006.htm
%doc /usr/local/dx/html/pages/insgu007.htm
%doc /usr/local/dx/html/pages/insgu008.htm
%doc /usr/local/dx/html/pages/insgu009.htm
%doc /usr/local/dx/html/pages/insgu010.htm
%doc /usr/local/dx/html/pages/insgu011.htm
%doc /usr/local/dx/html/pages/insgu012.htm
%doc /usr/local/dx/html/pages/insgu013.htm
%doc /usr/local/dx/html/pages/insgu014.htm
%doc /usr/local/dx/html/pages/insgu015.htm
%doc /usr/local/dx/html/pages/insgu016.htm
%doc /usr/local/dx/html/pages/insgu017.htm
%doc /usr/local/dx/html/pages/insgu018.htm
%doc /usr/local/dx/html/pages/insgu019.htm
%doc /usr/local/dx/html/pages/insgu020.htm
%doc /usr/local/dx/html/pages/insgu021.htm
%doc /usr/local/dx/html/pages/insgu022.htm
%doc /usr/local/dx/html/pages/insgu023.htm
%doc /usr/local/dx/html/pages/insgu024.htm
%doc /usr/local/dx/html/pages/insgu025.htm
%doc /usr/local/dx/html/pages/insgu026.htm
%doc /usr/local/dx/html/pages/insgu027.htm
%doc /usr/local/dx/html/pages/insgu028.htm
%doc /usr/local/dx/html/pages/insgu029.htm
%doc /usr/local/dx/html/pages/insgu030.htm
%doc /usr/local/dx/html/pages/insgu031.htm
%doc /usr/local/dx/html/pages/insgu032.htm
%doc /usr/local/dx/html/pages/insgu033.htm
%doc /usr/local/dx/html/pages/insgu034.htm
%doc /usr/local/dx/html/pages/insgu035.htm
%doc /usr/local/dx/html/pages/insgu036.htm
%doc /usr/local/dx/html/pages/insgu037.htm
%doc /usr/local/dx/html/pages/insgu038.htm
%doc /usr/local/dx/html/pages/insgu039.htm
%doc /usr/local/dx/html/pages/progu002.htm
%doc /usr/local/dx/html/pages/progu003.htm
%doc /usr/local/dx/html/pages/progu004.htm
%doc /usr/local/dx/html/pages/progu005.htm
%doc /usr/local/dx/html/pages/progu006.htm
%doc /usr/local/dx/html/pages/progu007.htm
%doc /usr/local/dx/html/pages/progu008.htm
%doc /usr/local/dx/html/pages/progu009.htm
%doc /usr/local/dx/html/pages/progu010.htm
%doc /usr/local/dx/html/pages/progu011.htm
%doc /usr/local/dx/html/pages/progu012.htm
%doc /usr/local/dx/html/pages/progu013.htm
%doc /usr/local/dx/html/pages/progu014.htm
%doc /usr/local/dx/html/pages/progu015.htm
%doc /usr/local/dx/html/pages/progu016.htm
%doc /usr/local/dx/html/pages/progu017.htm
%doc /usr/local/dx/html/pages/progu018.htm
%doc /usr/local/dx/html/pages/progu019.htm
%doc /usr/local/dx/html/pages/progu020.htm
%doc /usr/local/dx/html/pages/progu021.htm
%doc /usr/local/dx/html/pages/progu022.htm
%doc /usr/local/dx/html/pages/progu023.htm
%doc /usr/local/dx/html/pages/progu024.htm
%doc /usr/local/dx/html/pages/progu025.htm
%doc /usr/local/dx/html/pages/progu026.htm
%doc /usr/local/dx/html/pages/progu027.htm
%doc /usr/local/dx/html/pages/progu028.htm
%doc /usr/local/dx/html/pages/progu029.htm
%doc /usr/local/dx/html/pages/progu030.htm
%doc /usr/local/dx/html/pages/progu031.htm
%doc /usr/local/dx/html/pages/progu032.htm
%doc /usr/local/dx/html/pages/progu033.htm
%doc /usr/local/dx/html/pages/progu034.htm
%doc /usr/local/dx/html/pages/progu035.htm
%doc /usr/local/dx/html/pages/progu036.htm
%doc /usr/local/dx/html/pages/progu037.htm
%doc /usr/local/dx/html/pages/progu038.htm
%doc /usr/local/dx/html/pages/progu039.htm
%doc /usr/local/dx/html/pages/progu040.htm
%doc /usr/local/dx/html/pages/progu041.htm
%doc /usr/local/dx/html/pages/progu042.htm
%doc /usr/local/dx/html/pages/progu043.htm
%doc /usr/local/dx/html/pages/progu044.htm
%doc /usr/local/dx/html/pages/progu045.htm
%doc /usr/local/dx/html/pages/progu046.htm
%doc /usr/local/dx/html/pages/progu047.htm
%doc /usr/local/dx/html/pages/progu048.htm
%doc /usr/local/dx/html/pages/progu049.htm
%doc /usr/local/dx/html/pages/progu050.htm
%doc /usr/local/dx/html/pages/progu051.htm
%doc /usr/local/dx/html/pages/progu052.htm
%doc /usr/local/dx/html/pages/progu053.htm
%doc /usr/local/dx/html/pages/progu054.htm
%doc /usr/local/dx/html/pages/progu055.htm
%doc /usr/local/dx/html/pages/progu056.htm
%doc /usr/local/dx/html/pages/progu057.htm
%doc /usr/local/dx/html/pages/progu058.htm
%doc /usr/local/dx/html/pages/progu059.htm
%doc /usr/local/dx/html/pages/progu060.htm
%doc /usr/local/dx/html/pages/progu061.htm
%doc /usr/local/dx/html/pages/progu062.htm
%doc /usr/local/dx/html/pages/progu063.htm
%doc /usr/local/dx/html/pages/progu064.htm
%doc /usr/local/dx/html/pages/progu065.htm
%doc /usr/local/dx/html/pages/progu066.htm
%doc /usr/local/dx/html/pages/progu067.htm
%doc /usr/local/dx/html/pages/progu068.htm
%doc /usr/local/dx/html/pages/progu069.htm
%doc /usr/local/dx/html/pages/progu070.htm
%doc /usr/local/dx/html/pages/progu071.htm
%doc /usr/local/dx/html/pages/progu072.htm
%doc /usr/local/dx/html/pages/progu073.htm
%doc /usr/local/dx/html/pages/progu074.htm
%doc /usr/local/dx/html/pages/progu075.htm
%doc /usr/local/dx/html/pages/progu076.htm
%doc /usr/local/dx/html/pages/progu077.htm
%doc /usr/local/dx/html/pages/progu078.htm
%doc /usr/local/dx/html/pages/progu079.htm
%doc /usr/local/dx/html/pages/progu080.htm
%doc /usr/local/dx/html/pages/progu081.htm
%doc /usr/local/dx/html/pages/progu082.htm
%doc /usr/local/dx/html/pages/progu083.htm
%doc /usr/local/dx/html/pages/progu084.htm
%doc /usr/local/dx/html/pages/progu085.htm
%doc /usr/local/dx/html/pages/progu086.htm
%doc /usr/local/dx/html/pages/progu087.htm
%doc /usr/local/dx/html/pages/progu088.htm
%doc /usr/local/dx/html/pages/progu089.htm
%doc /usr/local/dx/html/pages/progu090.htm
%doc /usr/local/dx/html/pages/progu091.htm
%doc /usr/local/dx/html/pages/progu092.htm
%doc /usr/local/dx/html/pages/progu093.htm
%doc /usr/local/dx/html/pages/progu094.htm
%doc /usr/local/dx/html/pages/progu095.htm
%doc /usr/local/dx/html/pages/progu096.htm
%doc /usr/local/dx/html/pages/progu097.htm
%doc /usr/local/dx/html/pages/progu098.htm
%doc /usr/local/dx/html/pages/progu099.htm
%doc /usr/local/dx/html/pages/progu100.htm
%doc /usr/local/dx/html/pages/progu101.htm
%doc /usr/local/dx/html/pages/progu102.htm
%doc /usr/local/dx/html/pages/progu103.htm
%doc /usr/local/dx/html/pages/progu104.htm
%doc /usr/local/dx/html/pages/progu105.htm
%doc /usr/local/dx/html/pages/progu106.htm
%doc /usr/local/dx/html/pages/progu107.htm
%doc /usr/local/dx/html/pages/progu108.htm
%doc /usr/local/dx/html/pages/progu109.htm
%doc /usr/local/dx/html/pages/progu110.htm
%doc /usr/local/dx/html/pages/progu111.htm
%doc /usr/local/dx/html/pages/progu112.htm
%doc /usr/local/dx/html/pages/progu113.htm
%doc /usr/local/dx/html/pages/progu114.htm
%doc /usr/local/dx/html/pages/progu115.htm
%doc /usr/local/dx/html/pages/progu116.htm
%doc /usr/local/dx/html/pages/progu117.htm
%doc /usr/local/dx/html/pages/progu118.htm
%doc /usr/local/dx/html/pages/progu119.htm
%doc /usr/local/dx/html/pages/progu120.htm
%doc /usr/local/dx/html/pages/progu121.htm
%doc /usr/local/dx/html/pages/progu122.htm
%doc /usr/local/dx/html/pages/progu123.htm
%doc /usr/local/dx/html/pages/progu124.htm
%doc /usr/local/dx/html/pages/progu125.htm
%doc /usr/local/dx/html/pages/progu126.htm
%doc /usr/local/dx/html/pages/progu127.htm
%doc /usr/local/dx/html/pages/progu128.htm
%doc /usr/local/dx/html/pages/progu129.htm
%doc /usr/local/dx/html/pages/progu130.htm
%doc /usr/local/dx/html/pages/progu131.htm
%doc /usr/local/dx/html/pages/progu132.htm
%doc /usr/local/dx/html/pages/progu133.htm
%doc /usr/local/dx/html/pages/progu134.htm
%doc /usr/local/dx/html/pages/progu135.htm
%doc /usr/local/dx/html/pages/progu136.htm
%doc /usr/local/dx/html/pages/progu137.htm
%doc /usr/local/dx/html/pages/progu138.htm
%doc /usr/local/dx/html/pages/progu139.htm
%doc /usr/local/dx/html/pages/progu140.htm
%doc /usr/local/dx/html/pages/progu141.htm
%doc /usr/local/dx/html/pages/progu142.htm
%doc /usr/local/dx/html/pages/progu143.htm
%doc /usr/local/dx/html/pages/progu144.htm
%doc /usr/local/dx/html/pages/progu145.htm
%doc /usr/local/dx/html/pages/progu146.htm
%doc /usr/local/dx/html/pages/progu147.htm
%doc /usr/local/dx/html/pages/progu148.htm
%doc /usr/local/dx/html/pages/progu149.htm
%doc /usr/local/dx/html/pages/progu150.htm
%doc /usr/local/dx/html/pages/progu151.htm
%doc /usr/local/dx/html/pages/progu152.htm
%doc /usr/local/dx/html/pages/progu153.htm
%doc /usr/local/dx/html/pages/progu154.htm
%doc /usr/local/dx/html/pages/progu155.htm
%doc /usr/local/dx/html/pages/progu156.htm
%doc /usr/local/dx/html/pages/progu157.htm
%doc /usr/local/dx/html/pages/progu158.htm
%doc /usr/local/dx/html/pages/progu159.htm
%doc /usr/local/dx/html/pages/progu160.htm
%doc /usr/local/dx/html/pages/progu161.htm
%doc /usr/local/dx/html/pages/progu162.htm
%doc /usr/local/dx/html/pages/progu163.htm
%doc /usr/local/dx/html/pages/progu164.htm
%doc /usr/local/dx/html/pages/progu165.htm
%doc /usr/local/dx/html/pages/progu166.htm
%doc /usr/local/dx/html/pages/progu167.htm
%doc /usr/local/dx/html/pages/progu168.htm
%doc /usr/local/dx/html/pages/progu169.htm
%doc /usr/local/dx/html/pages/progu170.htm
%doc /usr/local/dx/html/pages/progu171.htm
%doc /usr/local/dx/html/pages/progu172.htm
%doc /usr/local/dx/html/pages/progu173.htm
%doc /usr/local/dx/html/pages/progu174.htm
%doc /usr/local/dx/html/pages/progu175.htm
%doc /usr/local/dx/html/pages/progu176.htm
%doc /usr/local/dx/html/pages/progu177.htm
%doc /usr/local/dx/html/pages/progu178.htm
%doc /usr/local/dx/html/pages/progu179.htm
%doc /usr/local/dx/html/pages/progu180.htm
%doc /usr/local/dx/html/pages/progu181.htm
%doc /usr/local/dx/html/pages/progu182.htm
%doc /usr/local/dx/html/pages/progu183.htm
%doc /usr/local/dx/html/pages/progu184.htm
%doc /usr/local/dx/html/pages/progu185.htm
%doc /usr/local/dx/html/pages/progu186.htm
%doc /usr/local/dx/html/pages/progu187.htm
%doc /usr/local/dx/html/pages/progu188.htm
%doc /usr/local/dx/html/pages/progu189.htm
%doc /usr/local/dx/html/pages/progu190.htm
%doc /usr/local/dx/html/pages/progu191.htm
%doc /usr/local/dx/html/pages/progu192.htm
%doc /usr/local/dx/html/pages/progu193.htm
%doc /usr/local/dx/html/pages/progu194.htm
%doc /usr/local/dx/html/pages/progu195.htm
%doc /usr/local/dx/html/pages/progu196.htm
%doc /usr/local/dx/html/pages/progu197.htm
%doc /usr/local/dx/html/pages/progu198.htm
%doc /usr/local/dx/html/pages/progu199.htm
%doc /usr/local/dx/html/pages/progu200.htm
%doc /usr/local/dx/html/pages/progu201.htm
%doc /usr/local/dx/html/pages/progu202.htm
%doc /usr/local/dx/html/pages/progu203.htm
%doc /usr/local/dx/html/pages/progu204.htm
%doc /usr/local/dx/html/pages/progu205.htm
%doc /usr/local/dx/html/pages/progu206.htm
%doc /usr/local/dx/html/pages/progu207.htm
%doc /usr/local/dx/html/pages/progu208.htm
%doc /usr/local/dx/html/pages/progu209.htm
%doc /usr/local/dx/html/pages/progu210.htm
%doc /usr/local/dx/html/pages/progu211.htm
%doc /usr/local/dx/html/pages/progu212.htm
%doc /usr/local/dx/html/pages/progu213.htm
%doc /usr/local/dx/html/pages/progu214.htm
%doc /usr/local/dx/html/pages/progu215.htm
%doc /usr/local/dx/html/pages/progu216.htm
%doc /usr/local/dx/html/pages/progu217.htm
%doc /usr/local/dx/html/pages/progu218.htm
%doc /usr/local/dx/html/pages/progu219.htm
%doc /usr/local/dx/html/pages/progu220.htm
%doc /usr/local/dx/html/pages/progu221.htm
%doc /usr/local/dx/html/pages/progu222.htm
%doc /usr/local/dx/html/pages/progu223.htm
%doc /usr/local/dx/html/pages/progu224.htm
%doc /usr/local/dx/html/pages/progu225.htm
%doc /usr/local/dx/html/pages/progu226.htm
%doc /usr/local/dx/html/pages/progu227.htm
%doc /usr/local/dx/html/pages/progu228.htm
%doc /usr/local/dx/html/pages/progu229.htm
%doc /usr/local/dx/html/pages/progu230.htm
%doc /usr/local/dx/html/pages/progu231.htm
%doc /usr/local/dx/html/pages/progu232.htm
%doc /usr/local/dx/html/pages/progu233.htm
%doc /usr/local/dx/html/pages/progu234.htm
%doc /usr/local/dx/html/pages/progu235.htm
%doc /usr/local/dx/html/pages/progu236.htm
%doc /usr/local/dx/html/pages/progu237.htm
%doc /usr/local/dx/html/pages/progu238.htm
%doc /usr/local/dx/html/pages/progu239.htm
%doc /usr/local/dx/html/pages/progu240.htm
%doc /usr/local/dx/html/pages/progu241.htm
%doc /usr/local/dx/html/pages/progu242.htm
%doc /usr/local/dx/html/pages/progu243.htm
%doc /usr/local/dx/html/pages/progu244.htm
%doc /usr/local/dx/html/pages/progu245.htm
%doc /usr/local/dx/html/pages/progu246.htm
%doc /usr/local/dx/html/pages/progu247.htm
%doc /usr/local/dx/html/pages/progu248.htm
%doc /usr/local/dx/html/pages/progu249.htm
%doc /usr/local/dx/html/pages/progu250.htm
%doc /usr/local/dx/html/pages/progu251.htm
%doc /usr/local/dx/html/pages/progu252.htm
%doc /usr/local/dx/html/pages/progu253.htm
%doc /usr/local/dx/html/pages/progu254.htm
%doc /usr/local/dx/html/pages/progu255.htm
%doc /usr/local/dx/html/pages/progu256.htm
%doc /usr/local/dx/html/pages/progu257.htm
%doc /usr/local/dx/html/pages/progu258.htm
%doc /usr/local/dx/html/pages/progu259.htm
%doc /usr/local/dx/html/pages/progu260.htm
%doc /usr/local/dx/html/pages/progu261.htm
%doc /usr/local/dx/html/pages/progu262.htm
%doc /usr/local/dx/html/pages/progu263.htm
%doc /usr/local/dx/html/pages/progu264.htm
%doc /usr/local/dx/html/pages/progu265.htm
%doc /usr/local/dx/html/pages/progu266.htm
%doc /usr/local/dx/html/pages/progu267.htm
%doc /usr/local/dx/html/pages/progu268.htm
%doc /usr/local/dx/html/pages/progu269.htm
%doc /usr/local/dx/html/pages/progu270.htm
%doc /usr/local/dx/html/pages/progu271.htm
%doc /usr/local/dx/html/pages/progu272.htm
%doc /usr/local/dx/html/pages/progu273.htm
%doc /usr/local/dx/html/pages/progu274.htm
%doc /usr/local/dx/html/pages/progu275.htm
%doc /usr/local/dx/html/pages/progu276.htm
%doc /usr/local/dx/html/pages/progu277.htm
%doc /usr/local/dx/html/pages/progu278.htm
%doc /usr/local/dx/html/pages/progu279.htm
%doc /usr/local/dx/html/pages/progu280.htm
%doc /usr/local/dx/html/pages/progu281.htm
%doc /usr/local/dx/html/pages/progu282.htm
%doc /usr/local/dx/html/pages/progu283.htm
%doc /usr/local/dx/html/pages/progu284.htm
%doc /usr/local/dx/html/pages/progu285.htm
%doc /usr/local/dx/html/pages/progu286.htm
%doc /usr/local/dx/html/pages/progu287.htm
%doc /usr/local/dx/html/pages/progu288.htm
%doc /usr/local/dx/html/pages/progu289.htm
%doc /usr/local/dx/html/pages/progu290.htm
%doc /usr/local/dx/html/pages/progu291.htm
%doc /usr/local/dx/html/pages/progu292.htm
%doc /usr/local/dx/html/pages/progu293.htm
%doc /usr/local/dx/html/pages/progu294.htm
%doc /usr/local/dx/html/pages/progu295.htm
%doc /usr/local/dx/html/pages/progu296.htm
%doc /usr/local/dx/html/pages/progu297.htm
%doc /usr/local/dx/html/pages/progu298.htm
%doc /usr/local/dx/html/pages/progu299.htm
%doc /usr/local/dx/html/pages/progu300.htm
%doc /usr/local/dx/html/pages/progu301.htm
%doc /usr/local/dx/html/pages/progu302.htm
%doc /usr/local/dx/html/pages/progu303.htm
%doc /usr/local/dx/html/pages/progu304.htm
%doc /usr/local/dx/html/pages/progu305.htm
%doc /usr/local/dx/html/pages/progu306.htm
%doc /usr/local/dx/html/pages/progu307.htm
%doc /usr/local/dx/html/pages/progu308.htm
%doc /usr/local/dx/html/pages/progu309.htm
%doc /usr/local/dx/html/pages/progu310.htm
%doc /usr/local/dx/html/pages/progu311.htm
%doc /usr/local/dx/html/pages/progu312.htm
%doc /usr/local/dx/html/pages/progu313.htm
%doc /usr/local/dx/html/pages/progu314.htm
%doc /usr/local/dx/html/pages/progu315.htm
%doc /usr/local/dx/html/pages/progu316.htm
%doc /usr/local/dx/html/pages/progu317.htm
%doc /usr/local/dx/html/pages/progu318.htm
%doc /usr/local/dx/html/pages/progu319.htm
%doc /usr/local/dx/html/pages/progu320.htm
%doc /usr/local/dx/html/pages/progu321.htm
%doc /usr/local/dx/html/pages/progu322.htm
%doc /usr/local/dx/html/pages/progu323.htm
%doc /usr/local/dx/html/pages/progu324.htm
%doc /usr/local/dx/html/pages/progu325.htm
%doc /usr/local/dx/html/pages/progu326.htm
%doc /usr/local/dx/html/pages/progu327.htm
%doc /usr/local/dx/html/pages/progu328.htm
%doc /usr/local/dx/html/pages/progu329.htm
%doc /usr/local/dx/html/pages/progu330.htm
%doc /usr/local/dx/html/pages/progu331.htm
%doc /usr/local/dx/html/pages/progu332.htm
%doc /usr/local/dx/html/pages/progu333.htm
%doc /usr/local/dx/html/pages/progu334.htm
%doc /usr/local/dx/html/pages/progu335.htm
%doc /usr/local/dx/html/pages/progu336.htm
%doc /usr/local/dx/html/pages/progu337.htm
%doc /usr/local/dx/html/pages/progu338.htm
%doc /usr/local/dx/html/pages/progu339.htm
%doc /usr/local/dx/html/pages/progu340.htm
%doc /usr/local/dx/html/pages/progu341.htm
%doc /usr/local/dx/html/pages/progu342.htm
%doc /usr/local/dx/html/pages/progu343.htm
%doc /usr/local/dx/html/pages/progu344.htm
%doc /usr/local/dx/html/pages/progu345.htm
%doc /usr/local/dx/html/pages/progu346.htm
%doc /usr/local/dx/html/pages/progu347.htm
%doc /usr/local/dx/html/pages/progu348.htm
%doc /usr/local/dx/html/pages/progu349.htm
%doc /usr/local/dx/html/pages/progu350.htm
%doc /usr/local/dx/html/pages/progu351.htm
%doc /usr/local/dx/html/pages/qikgu002.htm
%doc /usr/local/dx/html/pages/qikgu003.htm
%doc /usr/local/dx/html/pages/qikgu004.htm
%doc /usr/local/dx/html/pages/qikgu005.htm
%doc /usr/local/dx/html/pages/qikgu006.htm
%doc /usr/local/dx/html/pages/qikgu007.htm
%doc /usr/local/dx/html/pages/qikgu008.htm
%doc /usr/local/dx/html/pages/qikgu009.htm
%doc /usr/local/dx/html/pages/qikgu010.htm
%doc /usr/local/dx/html/pages/qikgu011.htm
%doc /usr/local/dx/html/pages/qikgu012.htm
%doc /usr/local/dx/html/pages/qikgu013.htm
%doc /usr/local/dx/html/pages/qikgu014.htm
%doc /usr/local/dx/html/pages/qikgu015.htm
%doc /usr/local/dx/html/pages/qikgu016.htm
%doc /usr/local/dx/html/pages/qikgu017.htm
%doc /usr/local/dx/html/pages/qikgu018.htm
%doc /usr/local/dx/html/pages/qikgu019.htm
%doc /usr/local/dx/html/pages/qikgu020.htm
%doc /usr/local/dx/html/pages/qikgu021.htm
%doc /usr/local/dx/html/pages/qikgu022.htm
%doc /usr/local/dx/html/pages/qikgu023.htm
%doc /usr/local/dx/html/pages/qikgu024.htm
%doc /usr/local/dx/html/pages/qikgu025.htm
%doc /usr/local/dx/html/pages/qikgu026.htm
%doc /usr/local/dx/html/pages/qikgu027.htm
%doc /usr/local/dx/html/pages/qikgu028.htm
%doc /usr/local/dx/html/pages/qikgu029.htm
%doc /usr/local/dx/html/pages/qikgu030.htm
%doc /usr/local/dx/html/pages/qikgu031.htm
%doc /usr/local/dx/html/pages/qikgu032.htm
%doc /usr/local/dx/html/pages/qikgu033.htm
%doc /usr/local/dx/html/pages/qikgu034.htm
%doc /usr/local/dx/html/pages/refgu002.htm
%doc /usr/local/dx/html/pages/refgu003.htm
%doc /usr/local/dx/html/pages/refgu004.htm
%doc /usr/local/dx/html/pages/refgu005.htm
%doc /usr/local/dx/html/pages/refgu006.htm
%doc /usr/local/dx/html/pages/refgu007.htm
%doc /usr/local/dx/html/pages/refgu008.htm
%doc /usr/local/dx/html/pages/refgu009.htm
%doc /usr/local/dx/html/pages/refgu010.htm
%doc /usr/local/dx/html/pages/refgu011.htm
%doc /usr/local/dx/html/pages/refgu012.htm
%doc /usr/local/dx/html/pages/refgu013.htm
%doc /usr/local/dx/html/pages/refgu014.htm
%doc /usr/local/dx/html/pages/refgu015.htm
%doc /usr/local/dx/html/pages/refgu016.htm
%doc /usr/local/dx/html/pages/refgu017.htm
%doc /usr/local/dx/html/pages/refgu018.htm
%doc /usr/local/dx/html/pages/refgu019.htm
%doc /usr/local/dx/html/pages/refgu020.htm
%doc /usr/local/dx/html/pages/refgu021.htm
%doc /usr/local/dx/html/pages/refgu022.htm
%doc /usr/local/dx/html/pages/refgu023.htm
%doc /usr/local/dx/html/pages/refgu024.htm
%doc /usr/local/dx/html/pages/refgu025.htm
%doc /usr/local/dx/html/pages/refgu026.htm
%doc /usr/local/dx/html/pages/refgu027.htm
%doc /usr/local/dx/html/pages/refgu028.htm
%doc /usr/local/dx/html/pages/refgu029.htm
%doc /usr/local/dx/html/pages/refgu030.htm
%doc /usr/local/dx/html/pages/refgu031.htm
%doc /usr/local/dx/html/pages/refgu032.htm
%doc /usr/local/dx/html/pages/refgu033.htm
%doc /usr/local/dx/html/pages/refgu034.htm
%doc /usr/local/dx/html/pages/refgu035.htm
%doc /usr/local/dx/html/pages/refgu036.htm
%doc /usr/local/dx/html/pages/refgu037.htm
%doc /usr/local/dx/html/pages/refgu038.htm
%doc /usr/local/dx/html/pages/refgu039.htm
%doc /usr/local/dx/html/pages/refgu040.htm
%doc /usr/local/dx/html/pages/refgu041.htm
%doc /usr/local/dx/html/pages/refgu042.htm
%doc /usr/local/dx/html/pages/refgu043.htm
%doc /usr/local/dx/html/pages/refgu044.htm
%doc /usr/local/dx/html/pages/refgu045.htm
%doc /usr/local/dx/html/pages/refgu046.htm
%doc /usr/local/dx/html/pages/refgu047.htm
%doc /usr/local/dx/html/pages/refgu048.htm
%doc /usr/local/dx/html/pages/refgu049.htm
%doc /usr/local/dx/html/pages/refgu050.htm
%doc /usr/local/dx/html/pages/refgu051.htm
%doc /usr/local/dx/html/pages/refgu052.htm
%doc /usr/local/dx/html/pages/refgu053.htm
%doc /usr/local/dx/html/pages/refgu054.htm
%doc /usr/local/dx/html/pages/refgu055.htm
%doc /usr/local/dx/html/pages/refgu056.htm
%doc /usr/local/dx/html/pages/refgu057.htm
%doc /usr/local/dx/html/pages/refgu058.htm
%doc /usr/local/dx/html/pages/refgu059.htm
%doc /usr/local/dx/html/pages/refgu060.htm
%doc /usr/local/dx/html/pages/refgu061.htm
%doc /usr/local/dx/html/pages/refgu062.htm
%doc /usr/local/dx/html/pages/refgu063.htm
%doc /usr/local/dx/html/pages/refgu064.htm
%doc /usr/local/dx/html/pages/refgu065.htm
%doc /usr/local/dx/html/pages/refgu066.htm
%doc /usr/local/dx/html/pages/refgu067.htm
%doc /usr/local/dx/html/pages/refgu068.htm
%doc /usr/local/dx/html/pages/refgu069.htm
%doc /usr/local/dx/html/pages/refgu070.htm
%doc /usr/local/dx/html/pages/refgu071.htm
%doc /usr/local/dx/html/pages/refgu072.htm
%doc /usr/local/dx/html/pages/refgu073.htm
%doc /usr/local/dx/html/pages/refgu074.htm
%doc /usr/local/dx/html/pages/refgu075.htm
%doc /usr/local/dx/html/pages/refgu076.htm
%doc /usr/local/dx/html/pages/refgu077.htm
%doc /usr/local/dx/html/pages/refgu078.htm
%doc /usr/local/dx/html/pages/refgu079.htm
%doc /usr/local/dx/html/pages/refgu080.htm
%doc /usr/local/dx/html/pages/refgu081.htm
%doc /usr/local/dx/html/pages/refgu082.htm
%doc /usr/local/dx/html/pages/refgu083.htm
%doc /usr/local/dx/html/pages/refgu084.htm
%doc /usr/local/dx/html/pages/refgu085.htm
%doc /usr/local/dx/html/pages/refgu086.htm
%doc /usr/local/dx/html/pages/refgu087.htm
%doc /usr/local/dx/html/pages/refgu088.htm
%doc /usr/local/dx/html/pages/refgu089.htm
%doc /usr/local/dx/html/pages/refgu090.htm
%doc /usr/local/dx/html/pages/refgu091.htm
%doc /usr/local/dx/html/pages/refgu092.htm
%doc /usr/local/dx/html/pages/refgu093.htm
%doc /usr/local/dx/html/pages/refgu094.htm
%doc /usr/local/dx/html/pages/refgu095.htm
%doc /usr/local/dx/html/pages/refgu096.htm
%doc /usr/local/dx/html/pages/refgu097.htm
%doc /usr/local/dx/html/pages/refgu098.htm
%doc /usr/local/dx/html/pages/refgu099.htm
%doc /usr/local/dx/html/pages/refgu100.htm
%doc /usr/local/dx/html/pages/refgu101.htm
%doc /usr/local/dx/html/pages/refgu102.htm
%doc /usr/local/dx/html/pages/refgu103.htm
%doc /usr/local/dx/html/pages/refgu104.htm
%doc /usr/local/dx/html/pages/refgu105.htm
%doc /usr/local/dx/html/pages/refgu106.htm
%doc /usr/local/dx/html/pages/refgu107.htm
%doc /usr/local/dx/html/pages/refgu108.htm
%doc /usr/local/dx/html/pages/refgu109.htm
%doc /usr/local/dx/html/pages/refgu110.htm
%doc /usr/local/dx/html/pages/refgu111.htm
%doc /usr/local/dx/html/pages/refgu112.htm
%doc /usr/local/dx/html/pages/refgu113.htm
%doc /usr/local/dx/html/pages/refgu114.htm
%doc /usr/local/dx/html/pages/refgu115.htm
%doc /usr/local/dx/html/pages/refgu116.htm
%doc /usr/local/dx/html/pages/refgu117.htm
%doc /usr/local/dx/html/pages/refgu118.htm
%doc /usr/local/dx/html/pages/refgu119.htm
%doc /usr/local/dx/html/pages/refgu120.htm
%doc /usr/local/dx/html/pages/refgu121.htm
%doc /usr/local/dx/html/pages/refgu122.htm
%doc /usr/local/dx/html/pages/refgu123.htm
%doc /usr/local/dx/html/pages/refgu124.htm
%doc /usr/local/dx/html/pages/refgu125.htm
%doc /usr/local/dx/html/pages/refgu126.htm
%doc /usr/local/dx/html/pages/refgu127.htm
%doc /usr/local/dx/html/pages/refgu128.htm
%doc /usr/local/dx/html/pages/refgu129.htm
%doc /usr/local/dx/html/pages/refgu130.htm
%doc /usr/local/dx/html/pages/refgu131.htm
%doc /usr/local/dx/html/pages/refgu132.htm
%doc /usr/local/dx/html/pages/refgu133.htm
%doc /usr/local/dx/html/pages/refgu134.htm
%doc /usr/local/dx/html/pages/refgu135.htm
%doc /usr/local/dx/html/pages/refgu136.htm
%doc /usr/local/dx/html/pages/refgu137.htm
%doc /usr/local/dx/html/pages/refgu138.htm
%doc /usr/local/dx/html/pages/refgu139.htm
%doc /usr/local/dx/html/pages/refgu140.htm
%doc /usr/local/dx/html/pages/refgu141.htm
%doc /usr/local/dx/html/pages/refgu142.htm
%doc /usr/local/dx/html/pages/refgu143.htm
%doc /usr/local/dx/html/pages/refgu144.htm
%doc /usr/local/dx/html/pages/refgu145.htm
%doc /usr/local/dx/html/pages/refgu146.htm
%doc /usr/local/dx/html/pages/refgu147.htm
%doc /usr/local/dx/html/pages/refgu148.htm
%doc /usr/local/dx/html/pages/refgu149.htm
%doc /usr/local/dx/html/pages/refgu150.htm
%doc /usr/local/dx/html/pages/refgu151.htm
%doc /usr/local/dx/html/pages/refgu152.htm
%doc /usr/local/dx/html/pages/refgu153.htm
%doc /usr/local/dx/html/pages/refgu154.htm
%doc /usr/local/dx/html/pages/refgu155.htm
%doc /usr/local/dx/html/pages/refgu156.htm
%doc /usr/local/dx/html/pages/refgu157.htm
%doc /usr/local/dx/html/pages/refgu158.htm
%doc /usr/local/dx/html/pages/refgu159.htm
%doc /usr/local/dx/html/pages/refgu160.htm
%doc /usr/local/dx/html/pages/refgu161.htm
%doc /usr/local/dx/html/pages/refgu162.htm
%doc /usr/local/dx/html/pages/refgu163.htm
%doc /usr/local/dx/html/pages/refgu164.htm
%doc /usr/local/dx/html/pages/refgu165.htm
%doc /usr/local/dx/html/pages/refgu166.htm
%doc /usr/local/dx/html/pages/refgu167.htm
%doc /usr/local/dx/html/pages/refgu168.htm
%doc /usr/local/dx/html/pages/refgu169.htm
%doc /usr/local/dx/html/pages/refgu170.htm
%doc /usr/local/dx/html/pages/refgu171.htm
%doc /usr/local/dx/html/pages/refgu172.htm
%doc /usr/local/dx/html/pages/refgu173.htm
%doc /usr/local/dx/html/pages/refgu174.htm
%doc /usr/local/dx/html/pages/refgu175.htm
%doc /usr/local/dx/html/pages/usrgu002.htm
%doc /usr/local/dx/html/pages/usrgu003.htm
%doc /usr/local/dx/html/pages/usrgu004.htm
%doc /usr/local/dx/html/pages/usrgu005.htm
%doc /usr/local/dx/html/pages/usrgu006.htm
%doc /usr/local/dx/html/pages/usrgu007.htm
%doc /usr/local/dx/html/pages/usrgu008.htm
%doc /usr/local/dx/html/pages/usrgu009.htm
%doc /usr/local/dx/html/pages/usrgu010.htm
%doc /usr/local/dx/html/pages/usrgu011.htm
%doc /usr/local/dx/html/pages/usrgu012.htm
%doc /usr/local/dx/html/pages/usrgu013.htm
%doc /usr/local/dx/html/pages/usrgu014.htm
%doc /usr/local/dx/html/pages/usrgu015.htm
%doc /usr/local/dx/html/pages/usrgu016.htm
%doc /usr/local/dx/html/pages/usrgu017.htm
%doc /usr/local/dx/html/pages/usrgu018.htm
%doc /usr/local/dx/html/pages/usrgu019.htm
%doc /usr/local/dx/html/pages/usrgu020.htm
%doc /usr/local/dx/html/pages/usrgu021.htm
%doc /usr/local/dx/html/pages/usrgu022.htm
%doc /usr/local/dx/html/pages/usrgu023.htm
%doc /usr/local/dx/html/pages/usrgu024.htm
%doc /usr/local/dx/html/pages/usrgu025.htm
%doc /usr/local/dx/html/pages/usrgu026.htm
%doc /usr/local/dx/html/pages/usrgu027.htm
%doc /usr/local/dx/html/pages/usrgu028.htm
%doc /usr/local/dx/html/pages/usrgu029.htm
%doc /usr/local/dx/html/pages/usrgu030.htm
%doc /usr/local/dx/html/pages/usrgu031.htm
%doc /usr/local/dx/html/pages/usrgu032.htm
%doc /usr/local/dx/html/pages/usrgu033.htm
%doc /usr/local/dx/html/pages/usrgu034.htm
%doc /usr/local/dx/html/pages/usrgu035.htm
%doc /usr/local/dx/html/pages/usrgu036.htm
%doc /usr/local/dx/html/pages/usrgu037.htm
%doc /usr/local/dx/html/pages/usrgu038.htm
%doc /usr/local/dx/html/pages/usrgu039.htm
%doc /usr/local/dx/html/pages/usrgu040.htm
%doc /usr/local/dx/html/pages/usrgu041.htm
%doc /usr/local/dx/html/pages/usrgu042.htm
%doc /usr/local/dx/html/pages/usrgu043.htm
%doc /usr/local/dx/html/pages/usrgu044.htm
%doc /usr/local/dx/html/pages/usrgu045.htm
%doc /usr/local/dx/html/pages/usrgu046.htm
%doc /usr/local/dx/html/pages/usrgu047.htm
%doc /usr/local/dx/html/pages/usrgu048.htm
%doc /usr/local/dx/html/pages/usrgu049.htm
%doc /usr/local/dx/html/pages/usrgu050.htm
%doc /usr/local/dx/html/pages/usrgu051.htm
%doc /usr/local/dx/html/pages/usrgu052.htm
%doc /usr/local/dx/html/pages/usrgu053.htm
%doc /usr/local/dx/html/pages/usrgu054.htm
%doc /usr/local/dx/html/pages/usrgu055.htm
%doc /usr/local/dx/html/pages/usrgu056.htm
%doc /usr/local/dx/html/pages/usrgu057.htm
%doc /usr/local/dx/html/pages/usrgu058.htm
%doc /usr/local/dx/html/pages/usrgu059.htm
%doc /usr/local/dx/html/pages/usrgu060.htm
%doc /usr/local/dx/html/pages/usrgu061.htm
%doc /usr/local/dx/html/pages/usrgu062.htm
%doc /usr/local/dx/html/pages/usrgu063.htm
%doc /usr/local/dx/html/pages/usrgu064.htm
%doc /usr/local/dx/html/pages/usrgu065.htm
%doc /usr/local/dx/html/pages/usrgu066.htm
%doc /usr/local/dx/html/pages/usrgu067.htm
%doc /usr/local/dx/html/pages/usrgu068.htm
%doc /usr/local/dx/html/pages/usrgu069.htm
%doc /usr/local/dx/html/pages/usrgu070.htm
%doc /usr/local/dx/html/pages/usrgu071.htm
%doc /usr/local/dx/html/pages/usrgu072.htm
%doc /usr/local/dx/html/pages/usrgu073.htm
%doc /usr/local/dx/html/pages/usrgu074.htm
%doc /usr/local/dx/html/pages/usrgu075.htm
%doc /usr/local/dx/html/pages/usrgu076.htm
%doc /usr/local/dx/html/pages/usrgu077.htm
%dir /usr/local/dx/html/images/
/usr/local/dx/html/images/3dcurs.gif
/usr/local/dx/html/images/adctlpt.gif
/usr/local/dx/html/images/arch.gif
/usr/local/dx/html/images/autoax.gif
/usr/local/dx/html/images/autoexp.gif
/usr/local/dx/html/images/brwswin.gif
/usr/local/dx/html/images/camera.gif
/usr/local/dx/html/images/cmaped.gif
/usr/local/dx/html/images/cmputcfg.gif
/usr/local/dx/html/images/colomap1.gif
/usr/local/dx/html/images/colormap.gif
/usr/local/dx/html/images/confgdb.gif
/usr/local/dx/html/images/ctpanacc.gif
/usr/local/dx/html/images/ctpangrp.gif
/usr/local/dx/html/images/ctrlpan.gif
/usr/local/dx/html/images/dataorg.gif
/usr/local/dx/html/images/datapr1.gif
/usr/local/dx/html/images/datdpnd.gif
/usr/local/dx/html/images/dialint.gif
/usr/local/dx/html/images/dinhd.gif
/usr/local/dx/html/images/dxicon8.gif
/usr/local/dx/html/images/dxlogo.gif
/usr/local/dx/html/images/example1.gif
/usr/local/dx/html/images/excutgrp.gif
/usr/local/dx/html/images/exticon.gif
/usr/local/dx/html/images/filesel.gif
/usr/local/dx/html/images/findtool.gif
/usr/local/dx/html/images/fldobj.gif
/usr/local/dx/html/images/flehole.gif
/usr/local/dx/html/images/flesurf.gif
/usr/local/dx/html/images/flexmp.gif
/usr/local/dx/html/images/flseldb.gif
/usr/local/dx/html/images/flselint.gif
/usr/local/dx/html/images/fragment.gif
/usr/local/dx/html/images/framctrl.gif
/usr/local/dx/html/images/fulldp.gif
/usr/local/dx/html/images/genwave.gif
/usr/local/dx/html/images/griddb.gif
/usr/local/dx/html/images/gridtype.gif
/usr/local/dx/html/images/grparts.gif
/usr/local/dx/html/images/hand.gif
/usr/local/dx/html/images/hdrdat.gif
/usr/local/dx/html/images/hello1.gif
/usr/local/dx/html/images/hello2.gif
/usr/local/dx/html/images/helpwin.gif
/usr/local/dx/html/images/htswork.gif
/usr/local/dx/html/images/imagwin.gif
/usr/local/dx/html/images/impconf.gif
/usr/local/dx/html/images/inputcfg.gif
/usr/local/dx/html/images/intlabl.gif
/usr/local/dx/html/images/irggrid.gif
/usr/local/dx/html/images/macrname.gif
/usr/local/dx/html/images/majcomp.gif
/usr/local/dx/html/images/map.gif
/usr/local/dx/html/images/map2plan.gif
/usr/local/dx/html/images/mapdform.gif
/usr/local/dx/html/images/matpa1.gif
/usr/local/dx/html/images/matpa2.gif
/usr/local/dx/html/images/matpa3.gif
/usr/local/dx/html/images/matpa4.gif
/usr/local/dx/html/images/modbuild.gif
/usr/local/dx/html/images/navigate.gif
/usr/local/dx/html/images/opendb.gif
/usr/local/dx/html/images/optbox.gif
/usr/local/dx/html/images/patrx1.gif
/usr/local/dx/html/images/patrx2.gif
/usr/local/dx/html/images/patry1.gif
/usr/local/dx/html/images/patry2.gif
/usr/local/dx/html/images/prodarxy.gif
/usr/local/dx/html/images/prodarz.gif
/usr/local/dx/html/images/prtimg.gif
/usr/local/dx/html/images/quikovx.gif
/usr/local/dx/html/images/reggrid.gif
/usr/local/dx/html/images/rendopts.gif
/usr/local/dx/html/images/reorient.gif
/usr/local/dx/html/images/saveas.gif
/usr/local/dx/html/images/savimg.gif
/usr/local/dx/html/images/sealevel.gif
/usr/local/dx/html/images/selattr.gif
/usr/local/dx/html/images/selctint.gif
/usr/local/dx/html/images/seqctrl.gif
/usr/local/dx/html/images/setattr.gif
/usr/local/dx/html/images/sgroup.gif
/usr/local/dx/html/images/shcomps.gif
/usr/local/dx/html/images/simfdp.gif
/usr/local/dx/html/images/skwdgrid.gif
/usr/local/dx/html/images/slidint.gif
/usr/local/dx/html/images/startup.gif
/usr/local/dx/html/images/stepint.gif
/usr/local/dx/html/images/strgint.gif
/usr/local/dx/html/images/strngint.gif
/usr/local/dx/html/images/strtsrv.gif
/usr/local/dx/html/images/strtsrvo.gif
/usr/local/dx/html/images/textint.gif
/usr/local/dx/html/images/throtdb.gif
/usr/local/dx/html/images/transfrm.gif
/usr/local/dx/html/images/txtmesh.gif
/usr/local/dx/html/images/usefle.gif
/usr/local/dx/html/images/veclist.gif
/usr/local/dx/html/images/vertord.gif
/usr/local/dx/html/images/vrtordu1.gif
/usr/local/dx/html/images/vrtordu2.gif
/usr/local/dx/html/images/vuctrl.gif
/usr/local/dx/html/images/wrpdgrid.gif
/usr/local/dx/html/images/xgroup.gif
/usr/local/dx/html/images/xgrpasgn.gif
/usr/local/dx/html/images/xirega.gif
/usr/local/dx/html/images/xmesha.gif
/usr/local/dx/html/images/xmodf1.gif
/usr/local/dx/html/images/xmodf10.gif
/usr/local/dx/html/images/xmodf11.gif
/usr/local/dx/html/images/xmodf12.gif
/usr/local/dx/html/images/xmodf13.gif
/usr/local/dx/html/images/xmodf2.gif
/usr/local/dx/html/images/xmodf3.gif
/usr/local/dx/html/images/xmodf4.gif
/usr/local/dx/html/images/xmodf6.gif
/usr/local/dx/html/images/xmodf7.gif
/usr/local/dx/html/images/xmodf8.gif
/usr/local/dx/html/images/xmodf9.gif
/usr/local/dx/html/images/xmpmacro.gif
/usr/local/dx/html/images/xproda.gif
%doc /usr/local/dx/html/index.htm
%doc /usr/local/dx/html/index.html
%dir %doc /usr/local/dx/man/
%dir %doc /usr/local/dx/man/manl/
%doc /usr/local/dx/man/manl/dx.l
%dir %doc /usr/local/dx/man/catl/
%doc /usr/local/dx/man/catl/dx.l
%dir /usr/local/dx/fonts/
%doc /usr/local/dx/fonts/Readme
/usr/local/dx/fonts/area.dx
/usr/local/dx/fonts/cyril_d.dx
/usr/local/dx/fonts/fixed.dx
/usr/local/dx/fonts/gothiceng_t.dx
/usr/local/dx/fonts/gothicger_t.dx
/usr/local/dx/fonts/gothicit_t.dx
/usr/local/dx/fonts/greek_d.dx
/usr/local/dx/fonts/greek_s.dx
/usr/local/dx/fonts/italic_d.dx
/usr/local/dx/fonts/italic_t.dx
/usr/local/dx/fonts/pitman.dx
/usr/local/dx/fonts/roman_d.dx
/usr/local/dx/fonts/roman_dser.dx
/usr/local/dx/fonts/roman_ext.dx
/usr/local/dx/fonts/roman_s.dx
/usr/local/dx/fonts/roman_sfix.dx
/usr/local/dx/fonts/roman_tser.dx
/usr/local/dx/fonts/script_d.dx
/usr/local/dx/fonts/script_s.dx
/usr/local/dx/fonts/variable.dx
%dir %doc /usr/local/dx/doc/
%doc /usr/local/dx/doc/README
%doc /usr/local/dx/doc/README_SMP
%doc /usr/local/dx/doc/README_alphax
%doc /usr/local/dx/doc/README_aviion
%doc /usr/local/dx/doc/README_hp700
%doc /usr/local/dx/doc/README_ibm6000
%doc /usr/local/dx/doc/README_ibmpvs
%doc /usr/local/dx/doc/README_indigo
%doc /usr/local/dx/doc/README_intelnt
%doc /usr/local/dx/doc/README_sgi
%doc /usr/local/dx/doc/README_sgi4
%doc /usr/local/dx/doc/README_solaris
%doc /usr/local/dx/doc/README_sun4
/usr/local/bin/dx
