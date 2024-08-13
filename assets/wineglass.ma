//Maya ASCII 2023 scene
//Name: wineglass.ma
//Last modified: Mon, Aug 12, 2024 06:09:46 PM
//Codeset: 1252
requires maya "2023";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2023";
fileInfo "version" "2023";
fileInfo "cutIdentifier" "202202161415-df43006fd3";
fileInfo "osv" "Windows 10 Home v2009 (Build: 19045)";
fileInfo "UUID" "1116B5D0-4149-A7CC-FAF1-F4BBD1EF4CD7";
createNode transform -s -n "persp";
	rename -uid "365523A0-4A8D-F97D-6A39-45B9788C5277";
	setAttr ".v" no;
	setAttr ".t" -type "double3" -3.3547799369200826 7.3264862200715317 6.1924173557796198 ;
	setAttr ".r" -type "double3" -35.138352729549403 -29.000000000000405 1.8182500665724289e-15 ;
createNode camera -s -n "perspShape" -p "persp";
	rename -uid "F4070440-4469-7521-DEC9-A0882C36FA6F";
	setAttr -k off ".v" no;
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 8.667474993484408;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".tp" -type "double3" -0.40610834956169128 3.7538044452667236 -0.79703235626220703 ;
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	rename -uid "3C125192-4DED-5BAD-0046-D2A05F11C424";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 1000.1 0 ;
	setAttr ".r" -type "double3" -90 0 0 ;
createNode camera -s -n "topShape" -p "top";
	rename -uid "D674E4C3-4943-CBBC-1E8F-8381CE3C3955";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
createNode transform -s -n "front";
	rename -uid "61C5665C-4849-649E-3068-22BEFE5BE44F";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 0 0 1000.1 ;
createNode camera -s -n "frontShape" -p "front";
	rename -uid "81599CBC-4DD4-A0B2-A8C3-86A14C62575D";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
createNode transform -s -n "side";
	rename -uid "727FA921-414E-3F7B-27D8-6D9A60A19C5E";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 1000.1 0 0 ;
	setAttr ".r" -type "double3" 0 90 0 ;
createNode camera -s -n "sideShape" -p "side";
	rename -uid "F7F96B29-4F0D-6175-860B-EABE30AD6A3D";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 30;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
createNode transform -n "pCylinder1";
	rename -uid "9EB43B8F-4B25-6E16-BE1B-BE8A5C2ED5CB";
	setAttr ".t" -type "double3" 0 1 0 ;
createNode mesh -n "pCylinderShape1" -p "pCylinder1";
	rename -uid "BC9DC0CA-484D-9DA0-88B8-7B83E5993D6E";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.5 0.49999996274709702 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 52 ".pt";
	setAttr ".pt[0]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[1]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[2]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[3]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[4]" -type "float3" 0 -2.2351742e-08 0 ;
	setAttr ".pt[5]" -type "float3" 0 -2.2351742e-08 0 ;
	setAttr ".pt[6]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[7]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[8]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[9]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[10]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[11]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[12]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[13]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[14]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[15]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[16]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[17]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[18]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[19]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[21]" -type "float3" 0 -7.4505806e-09 0 ;
	setAttr ".pt[242]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[243]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[246]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[248]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[250]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[252]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[254]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[256]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[258]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[260]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[262]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[264]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[266]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[268]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[270]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[272]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[274]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[276]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[278]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".pt[280]" -type "float3" 0 3.7252903e-09 0 ;
	setAttr ".dr" 1;
createNode lightLinker -s -n "lightLinker1";
	rename -uid "182AF432-4B3E-F65E-B722-8BB7DBEE9786";
	setAttr -s 2 ".lnk";
	setAttr -s 2 ".slnk";
createNode shapeEditorManager -n "shapeEditorManager";
	rename -uid "C5454D5B-4B65-C1B4-DE67-B48C231C14E5";
createNode poseInterpolatorManager -n "poseInterpolatorManager";
	rename -uid "DCFC86AB-4A8F-F411-A3DA-37B90D83032D";
createNode displayLayerManager -n "layerManager";
	rename -uid "93F9B121-4B58-4478-152B-6BB189546D22";
createNode displayLayer -n "defaultLayer";
	rename -uid "65061469-419C-C0BF-09F4-7EB67B06DC81";
createNode renderLayerManager -n "renderLayerManager";
	rename -uid "BEB6E66A-4F95-CF8E-5523-DD993B3DB2CE";
createNode renderLayer -n "defaultRenderLayer";
	rename -uid "006BFDD1-43F9-2E4A-2455-ADBC77F74870";
	setAttr ".g" yes;
createNode polyCylinder -n "polyCylinder1";
	rename -uid "DA507A57-42AD-2877-5D91-E1AFD153ABEE";
	setAttr ".r" 0.14;
	setAttr ".sc" 1;
	setAttr ".cuv" 3;
createNode polyExtrudeEdge -n "polyExtrudeEdge1";
	rename -uid "80C5AB03-4E26-5AD2-3859-11B2201386F7";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 1 "e[20:39]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 1 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" -1.4901161e-08 2 -2.2351742e-08 ;
	setAttr ".rs" 62734;
	setAttr ".lt" -type "double3" 2.0816681711721685e-17 -3.1225022567582528e-17 0.135489391142427 ;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -0.14000003039836884 2 -0.14000006020069122 ;
	setAttr ".cbx" -type "double3" 0.14000000059604645 2 0.14000001549720764 ;
createNode polyExtrudeEdge -n "polyExtrudeEdge2";
	rename -uid "5DC3E922-4140-AB5A-6FF1-EFA9B0770E69";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 19 "e[102]" "e[104]" "e[106]" "e[108]" "e[110]" "e[112]" "e[114]" "e[116]" "e[118]" "e[120]" "e[122]" "e[124]" "e[126]" "e[128]" "e[130]" "e[132]" "e[134]" "e[136]" "e[138:139]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 1 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" -1.4901161e-08 2.0456452 -1.4901161e-08 ;
	setAttr ".rs" 47629;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -0.23462598025798798 2.0456452369689941 -0.23462599515914917 ;
	setAttr ".cbx" -type "double3" 0.23462595045566559 2.0456452369689941 0.23462596535682678 ;
createNode polyTweak -n "polyTweak1";
	rename -uid "56773884-4F61-639C-7CA4-E7B662DC0D83";
	setAttr ".uopa" yes;
	setAttr -s 23 ".tk";
	setAttr ".tk[42]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[43]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[44]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[45]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[46]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[47]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[48]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[49]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[50]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[51]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[52]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[53]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[54]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[55]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[56]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[57]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[58]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[59]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[60]" -type "float3" 0 -0.050160348 0 ;
	setAttr ".tk[61]" -type "float3" 0 -0.050160348 0 ;
createNode polyExtrudeEdge -n "polyExtrudeEdge3";
	rename -uid "36CAB6F0-4457-5A9E-E62C-1C8ED708A8F0";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 19 "e[142]" "e[144]" "e[146]" "e[148]" "e[150]" "e[152]" "e[154]" "e[156]" "e[158]" "e[160]" "e[162]" "e[164]" "e[166]" "e[168]" "e[170]" "e[172]" "e[174]" "e[176]" "e[178:179]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 1 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 0 2.3161139 0 ;
	setAttr ".rs" 46572;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -0.66571831703186035 2.316114068031311 -0.6657184362411499 ;
	setAttr ".cbx" -type "double3" 0.66571831703186035 2.316114068031311 0.6657184362411499 ;
createNode polyTweak -n "polyTweak2";
	rename -uid "4C3A0C9D-477B-7CE6-A4F9-1DAC9280431B";
	setAttr ".uopa" yes;
	setAttr -s 20 ".tk[62:81]" -type "float3"  0.40999332 0.27046883 -0.13321464
		 0.34876117 0.27046883 -0.25338969 0.25338969 0.27046883 -0.34876111 0.13321492 0.27046883
		 -0.40999329 -1.7111749e-09 0.27046883 -0.43109244 -0.13321492 0.27046883 -0.40999317
		 -0.25338969 0.27046883 -0.34876099 -0.34876108 0.27046883 -0.25338969 -0.40999317
		 0.27046883 -0.13321477 -0.43109235 0.27046883 2.7378794e-08 -0.40999317 0.27046883
		 0.13321494 -0.34876096 0.27046883 0.25338969 -0.25338969 0.27046883 0.34876108 -0.13321489
		 0.27046883 0.4099932 5.1335238e-08 0.27046883 0.43109244 0.13321494 0.27046883 0.40999317
		 0.25338969 0.27046883 0.34876108 0.34876108 0.27046883 0.25338969 0.40999317 0.27046883
		 0.13321494 0.43109235 0.27046883 2.0876332e-07;
createNode polyExtrudeEdge -n "polyExtrudeEdge4";
	rename -uid "DBAFF885-4390-4CB1-B72A-2991D59E25C7";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 19 "e[182]" "e[184]" "e[186]" "e[188]" "e[190]" "e[192]" "e[194]" "e[196]" "e[198]" "e[200]" "e[202]" "e[204]" "e[206]" "e[208]" "e[210]" "e[212]" "e[214]" "e[216]" "e[218:219]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 1 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 0 2.8171256 0 ;
	setAttr ".rs" 46012;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -0.91459560394287109 2.817125678062439 -0.91459578275680542 ;
	setAttr ".cbx" -type "double3" 0.91459560394287109 2.817125678062439 0.91459578275680542 ;
createNode polyTweak -n "polyTweak3";
	rename -uid "9AF89F52-4FAA-DCF2-AE7D-6289B69B5F76";
	setAttr ".uopa" yes;
	setAttr -s 20 ".tk[82:101]" -type "float3"  0.23669635 0.50101173 -0.076907158
		 0.20134594 0.50101173 -0.14628638 0.14628637 0.50101173 -0.20134591 0.076907329 0.50101173
		 -0.23669635 -6.5586536e-09 0.50101173 -0.24887733 -0.076907329 0.50101173 -0.23669633
		 -0.14628638 0.50101173 -0.20134585 -0.20134588 0.50101173 -0.14628637 -0.23669633
		 0.50101173 -0.076907232 -0.2488773 0.50101173 1.02355e-08 -0.23669633 0.50101173
		 0.076907329 -0.20134585 0.50101173 0.14628637 -0.14628637 0.50101173 0.20134586 -0.076907322
		 0.50101173 0.23669633 2.4065976e-08 0.50101173 0.24887733 0.076907329 0.50101173
		 0.23669633 0.14628637 0.50101173 0.20134586 0.20134586 0.50101173 0.14628637 0.23669632
		 0.50101173 0.076907329 0.2488773 0.50101173 1.1495198e-07;
createNode polyExtrudeEdge -n "polyExtrudeEdge5";
	rename -uid "10ECE987-418B-CBF5-2036-0BB4D0970D94";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 19 "e[222]" "e[224]" "e[226]" "e[228]" "e[230]" "e[232]" "e[234]" "e[236]" "e[238]" "e[240]" "e[242]" "e[244]" "e[246]" "e[248]" "e[250]" "e[252]" "e[254]" "e[256]" "e[258:259]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 1 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 0 3.3060632 0 ;
	setAttr ".rs" 48751;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -0.99167811870574951 3.306063175201416 -0.99167829751968384 ;
	setAttr ".cbx" -type "double3" 0.99167811870574951 3.306063175201416 0.99167829751968384 ;
createNode polyTweak -n "polyTweak4";
	rename -uid "EC6A0F60-4563-9E82-C436-94B044047565";
	setAttr ".uopa" yes;
	setAttr -s 20 ".tk[102:121]" -type "float3"  0.073309839 0.48893732 -0.023819765
		 0.062361084 0.48893732 -0.045307964 0.04530796 0.48893732 -0.062361076 0.023819806
		 0.48893732 -0.073309824 -2.0313531e-09 0.48893732 -0.077082515 -0.023819815 0.48893732
		 -0.073309816 -0.045307964 0.48893732 -0.062361039 -0.062361043 0.48893732 -0.04530796
		 -0.073309816 0.48893732 -0.023819786 -0.0770825 0.48893732 3.1701486e-09 -0.073309816
		 0.48893732 0.023819815 -0.062361039 0.48893732 0.04530796 -0.04530796 0.48893732
		 0.062361047 -0.023819804 0.48893732 0.073309824 7.4537372e-09 0.48893732 0.077082515
		 0.023819815 0.48893732 0.073309816 0.04530796 0.48893732 0.062361047 0.062361047
		 0.48893732 0.04530796 0.073309816 0.48893732 0.023819815 0.0770825 0.48893732 3.5603041e-08;
createNode polySplitRing -n "polySplitRing1";
	rename -uid "B73B00E1-4914-6087-A17E-56AFD36B7414";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 1 "e[40:59]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 1 0 1;
	setAttr ".wt" 0.53895068168640137;
	setAttr ".dr" no;
	setAttr ".re" 56;
	setAttr ".sma" 29.999999999999996;
	setAttr ".stp" 2;
	setAttr ".div" 5;
	setAttr ".p[0]"  0 0 1;
	setAttr ".fq" yes;
createNode polyTweak -n "polyTweak5";
	rename -uid "A684F2B2-4E9A-8D0F-0335-B288F2E3EB58";
	setAttr ".uopa" yes;
	setAttr -s 22 ".tk";
	setAttr ".tk[122]" -type "float3" -0.081788287 0.44774118 0.026574578 ;
	setAttr ".tk[123]" -type "float3" -0.069573261 0.44774118 0.050547924 ;
	setAttr ".tk[124]" -type "float3" -0.050547916 0.44774118 0.069573253 ;
	setAttr ".tk[125]" -type "float3" -0.026574627 0.44774118 0.081788272 ;
	setAttr ".tk[126]" -type "float3" 2.2662832e-09 0.44774118 0.085997298 ;
	setAttr ".tk[127]" -type "float3" 0.026574627 0.44774118 0.081788264 ;
	setAttr ".tk[128]" -type "float3" 0.050547924 0.44774118 0.069573231 ;
	setAttr ".tk[129]" -type "float3" 0.069573246 0.44774118 0.050547916 ;
	setAttr ".tk[130]" -type "float3" 0.081788264 0.44774118 0.026574593 ;
	setAttr ".tk[131]" -type "float3" 0.085997269 0.44774118 -3.5367833e-09 ;
	setAttr ".tk[132]" -type "float3" 0.081788264 0.44774118 -0.026574627 ;
	setAttr ".tk[133]" -type "float3" 0.069573231 0.44774118 -0.050547916 ;
	setAttr ".tk[134]" -type "float3" 0.050547916 0.44774118 -0.069573238 ;
	setAttr ".tk[135]" -type "float3" 0.026574619 0.44774118 -0.081788257 ;
	setAttr ".tk[136]" -type "float3" -8.3157818e-09 0.44774118 -0.085997298 ;
	setAttr ".tk[137]" -type "float3" -0.026574627 0.44774118 -0.081788264 ;
	setAttr ".tk[138]" -type "float3" -0.050547916 0.44774118 -0.069573238 ;
	setAttr ".tk[139]" -type "float3" -0.069573238 0.44774118 -0.050547916 ;
	setAttr ".tk[140]" -type "float3" -0.081788257 0.44774118 -0.026574627 ;
	setAttr ".tk[141]" -type "float3" -0.085997269 0.44774118 -3.9720607e-08 ;
createNode script -n "uiConfigurationScriptNode";
	rename -uid "D535A61C-4E3B-0124-8C21-3AAE387AB7F2";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $nodeEditorPanelVisible = stringArrayContains(\"nodeEditorPanel1\", `getPanel -vis`);\n\tint    $nodeEditorWorkspaceControlOpen = (`workspaceControl -exists nodeEditorPanel1Window` && `workspaceControl -q -visible nodeEditorPanel1Window`);\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\n\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"|top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n"
		+ "            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n"
		+ "            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 0\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 1\n            -height 1\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"|side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n"
		+ "            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n"
		+ "            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 0\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 1\n            -height 1\n"
		+ "            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"|front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n"
		+ "            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n"
		+ "            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n"
		+ "            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 0\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 1\n            -height 1\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"|persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n"
		+ "            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 32768\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n"
		+ "            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n"
		+ "            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -greasePencils 0\n            -shadows 0\n            -captureSequenceNumber -1\n            -width 2641\n            -height 1639\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"ToggledOutliner\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"ToggledOutliner\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -showShapes 0\n            -showAssignedMaterials 0\n            -showTimeEditor 1\n            -showReferenceNodes 1\n            -showReferenceMembers 1\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -organizeByClip 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showParentContainers 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n"
		+ "            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -isSet 0\n            -isSetMember 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            -ignoreOutlinerColor 0\n            -renderFilterVisible 0\n            -renderFilterIndex 0\n            -selectionOrder \"chronological\" \n            -expandAttribute 0\n            $editorName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -showShapes 0\n            -showAssignedMaterials 0\n            -showTimeEditor 1\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -organizeByClip 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showParentContainers 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n"
		+ "            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"0\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n"
		+ "            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            -ignoreOutlinerColor 0\n            -renderFilterVisible 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAssignedMaterials 0\n                -showTimeEditor 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -organizeByClip 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n"
		+ "                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showParentContainers 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n"
		+ "                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                -renderFilterVisible 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayValues 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showPlayRangeShades \"on\" \n                -lockPlayRangeShades \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n"
		+ "                -keyMinScale 1\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -preSelectionHighlight 0\n                -constrainDrag 0\n                -valueLinesToggle 1\n                -highlightAffectedCurves 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAssignedMaterials 0\n                -showTimeEditor 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n"
		+ "                -showMuteInfo 0\n                -organizeByLayer 1\n                -organizeByClip 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showParentContainers 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n"
		+ "                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                -renderFilterVisible 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayValues 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n"
		+ "                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"timeEditorPanel\" (localizedPanelLabel(\"Time Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Time Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayValues 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n"
		+ "                -initialized 0\n                -manageSequencer 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"sequenceEditorPanel\" (localizedPanelLabel(\"Camera Sequencer\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayValues 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -initialized 0\n                -manageSequencer 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n"
		+ "                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"nodeEditorPanel\" (localizedPanelLabel(\"Node Editor\")) `;\n\tif ($nodeEditorPanelVisible || $nodeEditorWorkspaceControlOpen) {\n"
		+ "\t\tif (\"\" == $panelName) {\n\t\t\tif ($useSceneConfig) {\n\t\t\t\t$panelName = `scriptedPanel -unParent  -type \"nodeEditorPanel\" -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -consistentNameSize 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -connectNodeOnCreation 0\n                -connectOnDrop 0\n                -copyConnectionsOnPaste 0\n                -connectionStyle \"bezier\" \n                -defaultPinnedState 0\n                -additiveGraphingMode 0\n                -connectedGraphingMode 1\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -crosshairOnEdgeDragging 0\n"
		+ "                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                -showUnitConversions 0\n                -editorMode \"default\" \n                -hasWatchpoint 0\n                $editorName;\n\t\t\t}\n\t\t} else {\n\t\t\t$label = `panel -q -label $panelName`;\n\t\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -consistentNameSize 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -connectNodeOnCreation 0\n                -connectOnDrop 0\n                -copyConnectionsOnPaste 0\n                -connectionStyle \"bezier\" \n                -defaultPinnedState 0\n"
		+ "                -additiveGraphingMode 0\n                -connectedGraphingMode 1\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -crosshairOnEdgeDragging 0\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                -showUnitConversions 0\n                -editorMode \"default\" \n                -hasWatchpoint 0\n                $editorName;\n\t\t\tif (!$useSceneConfig) {\n\t\t\t\tpanel -e -l $label $panelName;\n\t\t\t}\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"createNodePanel\" (localizedPanelLabel(\"Create Node\")) `;\n\tif (\"\" != $panelName) {\n"
		+ "\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"shapePanel\" (localizedPanelLabel(\"Shape Editor\")) `;\n\tif (\"\" != $panelName) {\n"
		+ "\t\t$label = `panel -q -label $panelName`;\n\t\tshapePanel -edit -l (localizedPanelLabel(\"Shape Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"posePanel\" (localizedPanelLabel(\"Pose Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tposePanel -edit -l (localizedPanelLabel(\"Pose Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n"
		+ "\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n"
		+ "\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"profilerPanel\" (localizedPanelLabel(\"Profiler Tool\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Profiler Tool\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"contentBrowserPanel\" (localizedPanelLabel(\"Content Browser\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Content Browser\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n"
		+ "        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-userCreated false\n\t\t\t\t-defaultImage \"vacantCell.xP:/\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"single\\\" -ps 1 100 100 $gMainPane;\"\n\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -controllers 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 0\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 2641\\n    -height 1639\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 32768\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -controllers 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -greasePencils 0\\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 2641\\n    -height 1639\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 5 -size 12 -divisions 5 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	rename -uid "C7718136-4F5C-45C3-E67C-45901813F1A1";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 120 -ast 1 -aet 200 ";
	setAttr ".st" 6;
createNode polyBevel3 -n "polyBevel1";
	rename -uid "3175A19A-484E-21D7-AF1F-05A804EF75C7";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 19 "e[462]" "e[464]" "e[466]" "e[468]" "e[470]" "e[472]" "e[474]" "e[476]" "e[478]" "e[480]" "e[482]" "e[484]" "e[486]" "e[488]" "e[490]" "e[492]" "e[494]" "e[496]" "e[498:499]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 1 0 1;
	setAttr ".ws" yes;
	setAttr ".oaf" yes;
	setAttr ".f" 0.10999999999999993;
	setAttr ".sg" 2;
	setAttr ".at" 180;
	setAttr ".sn" yes;
	setAttr ".mv" yes;
	setAttr ".mvt" 0.0001;
	setAttr ".sa" 30;
createNode polyTweak -n "polyTweak6";
	rename -uid "36FD6C0C-4EFB-EE02-83D1-E89E192BF6EF";
	setAttr ".uopa" yes;
	setAttr -s 182 ".tk";
	setAttr ".tk[0]" -type "float3" 0.24609876 0 -0.079962246 ;
	setAttr ".tk[1]" -type "float3" 0.2093439 0 -0.15209725 ;
	setAttr ".tk[2]" -type "float3" 0.15209731 0 -0.20934385 ;
	setAttr ".tk[3]" -type "float3" 0.079962365 0 -0.24609867 ;
	setAttr ".tk[4]" -type "float3" 2.754194e-08 0 -0.25876334 ;
	setAttr ".tk[5]" -type "float3" -0.079962246 0 -0.24609834 ;
	setAttr ".tk[6]" -type "float3" -0.15209725 0 -0.20934375 ;
	setAttr ".tk[7]" -type "float3" -0.20934378 0 -0.1520972 ;
	setAttr ".tk[8]" -type "float3" -0.24609865 0 -0.079962231 ;
	setAttr ".tk[9]" -type "float3" -0.25876331 0 4.131293e-08 ;
	setAttr ".tk[10]" -type "float3" -0.24609865 0 0.079962268 ;
	setAttr ".tk[11]" -type "float3" -0.20934375 0 0.15209727 ;
	setAttr ".tk[12]" -type "float3" -0.1520972 0 0.20934382 ;
	setAttr ".tk[13]" -type "float3" -0.079962239 0 0.24609867 ;
	setAttr ".tk[14]" -type "float3" 1.9830216e-08 0 0.25876334 ;
	setAttr ".tk[15]" -type "float3" 0.079962254 0 0.24609865 ;
	setAttr ".tk[16]" -type "float3" 0.15209725 0 0.20934381 ;
	setAttr ".tk[17]" -type "float3" 0.20934375 0 0.15209725 ;
	setAttr ".tk[18]" -type "float3" 0.24609828 0 0.079962261 ;
	setAttr ".tk[19]" -type "float3" 0.25876331 0 4.131293e-08 ;
	setAttr ".tk[20]" -type "float3" -0.011238744 0 0.0036516872 ;
	setAttr ".tk[21]" -type "float3" -0.0095602479 0 0.006945923 ;
	setAttr ".tk[22]" -type "float3" -0.0069459258 0 0.0095602442 ;
	setAttr ".tk[23]" -type "float3" -0.0036516893 0 0.011238741 ;
	setAttr ".tk[24]" -type "float3" -1.2577758e-09 0 0.011817109 ;
	setAttr ".tk[25]" -type "float3" 0.0036516872 0 0.011238739 ;
	setAttr ".tk[26]" -type "float3" 0.0069459225 0 0.0095602423 ;
	setAttr ".tk[27]" -type "float3" 0.0095602423 0 0.0069459206 ;
	setAttr ".tk[28]" -type "float3" 0.011238739 0 0.0036516855 ;
	setAttr ".tk[29]" -type "float3" 0.011817107 0 -1.8866635e-09 ;
	setAttr ".tk[30]" -type "float3" 0.011238739 0 -0.003651689 ;
	setAttr ".tk[31]" -type "float3" 0.0095602404 0 -0.0069459234 ;
	setAttr ".tk[32]" -type "float3" 0.0069459206 0 -0.0095602442 ;
	setAttr ".tk[33]" -type "float3" 0.0036516862 0 -0.011238741 ;
	setAttr ".tk[34]" -type "float3" -9.0559854e-10 0 -0.011817108 ;
	setAttr ".tk[35]" -type "float3" -0.0036516879 0 -0.011238739 ;
	setAttr ".tk[36]" -type "float3" -0.006945922 0 -0.0095602432 ;
	setAttr ".tk[37]" -type "float3" -0.0095602404 0 -0.006945923 ;
	setAttr ".tk[38]" -type "float3" -0.011238737 0 -0.0036516886 ;
	setAttr ".tk[39]" -type "float3" -0.011817107 0 -1.8866635e-09 ;
	setAttr ".tk[40]" -type "float3" -1.213544e-09 0 -1.8203165e-09 ;
	setAttr ".tk[41]" -type "float3" -1.213544e-09 0 -1.8203165e-09 ;
	setAttr ".tk[42]" -type "float3" -0.015533368 0 0.0050470866 ;
	setAttr ".tk[43]" -type "float3" -0.01321347 0 0.0096001457 ;
	setAttr ".tk[44]" -type "float3" -0.0096001467 0 0.013213466 ;
	setAttr ".tk[45]" -type "float3" -0.0050470931 0 0.015533362 ;
	setAttr ".tk[46]" -type "float3" 6.4831078e-11 0 0.016332736 ;
	setAttr ".tk[47]" -type "float3" 0.0050470931 0 0.015533358 ;
	setAttr ".tk[48]" -type "float3" 0.0096001467 0 0.013213463 ;
	setAttr ".tk[49]" -type "float3" 0.013213466 0 0.009600142 ;
	setAttr ".tk[50]" -type "float3" 0.01553336 0 0.0050470922 ;
	setAttr ".tk[51]" -type "float3" 0.016332736 0 -1.555945e-09 ;
	setAttr ".tk[52]" -type "float3" 0.01553336 0 -0.005047095 ;
	setAttr ".tk[53]" -type "float3" 0.013213463 0 -0.0096001476 ;
	setAttr ".tk[54]" -type "float3" 0.0096001429 0 -0.013213466 ;
	setAttr ".tk[55]" -type "float3" 0.0050470927 0 -0.015533362 ;
	setAttr ".tk[56]" -type "float3" -1.9449318e-09 0 -0.01633274 ;
	setAttr ".tk[57]" -type "float3" -0.0050470941 0 -0.01553336 ;
	setAttr ".tk[58]" -type "float3" -0.0096001429 0 -0.013213466 ;
	setAttr ".tk[59]" -type "float3" -0.013213465 0 -0.0096001439 ;
	setAttr ".tk[60]" -type "float3" -0.01553336 0 -0.005047095 ;
	setAttr ".tk[61]" -type "float3" -0.016332736 0 -8.4280369e-09 ;
	setAttr ".tk[62]" -type "float3" -0.0016020396 0 0.00052053318 ;
	setAttr ".tk[63]" -type "float3" -0.0013627762 0 0.00099011429 ;
	setAttr ".tk[64]" -type "float3" -0.00099011429 0 0.001362776 ;
	setAttr ".tk[65]" -type "float3" -0.00052053411 0 0.0016020394 ;
	setAttr ".tk[66]" -type "float3" 6.686378e-12 0 0.0016844833 ;
	setAttr ".tk[67]" -type "float3" 0.00052053411 0 0.001602039 ;
	setAttr ".tk[68]" -type "float3" 0.00099011441 0 0.0013627758 ;
	setAttr ".tk[69]" -type "float3" 0.0013627759 0 0.00099011429 ;
	setAttr ".tk[70]" -type "float3" 0.0016020391 0 0.00052053371 ;
	setAttr ".tk[71]" -type "float3" 0.0016844829 0 -1.258344e-10 ;
	setAttr ".tk[72]" -type "float3" 0.0016020391 0 -0.00052053423 ;
	setAttr ".tk[73]" -type "float3" 0.0013627757 0 -0.00099011429 ;
	setAttr ".tk[74]" -type "float3" 0.00099011429 0 -0.0013627759 ;
	setAttr ".tk[75]" -type "float3" 0.00052053406 0 -0.0016020393 ;
	setAttr ".tk[76]" -type "float3" -2.0059127e-10 0 -0.0016844837 ;
	setAttr ".tk[77]" -type "float3" -0.00052053417 0 -0.0016020393 ;
	setAttr ".tk[78]" -type "float3" -0.00099011429 0 -0.0013627759 ;
	setAttr ".tk[79]" -type "float3" -0.0013627759 0 -0.00099011429 ;
	setAttr ".tk[80]" -type "float3" -0.001602039 0 -0.00052053423 ;
	setAttr ".tk[81]" -type "float3" -0.0016844831 0 -8.3459029e-10 ;
	setAttr ".tk[142]" -type "float3" -0.016304148 -2.9802322e-08 -0.022440739 ;
	setAttr ".tk[143]" -type "float3" -0.0085715996 -2.9802322e-08 -0.026380667 ;
	setAttr ".tk[144]" -type "float3" -2.1257096e-09 -2.9802322e-08 -0.027738275 ;
	setAttr ".tk[145]" -type "float3" 0.008571594 -2.9802322e-08 -0.026380669 ;
	setAttr ".tk[146]" -type "float3" 0.016304143 -2.9802322e-08 -0.022440741 ;
	setAttr ".tk[147]" -type "float3" 0.022440735 -2.9802322e-08 -0.016304154 ;
	setAttr ".tk[148]" -type "float3" 0.026380667 -2.9802322e-08 -0.0085716024 ;
	setAttr ".tk[149]" -type "float3" 0.027738273 -2.9802322e-08 -4.4285615e-09 ;
	setAttr ".tk[150]" -type "float3" 0.026380667 -2.9802322e-08 0.0085715931 ;
	setAttr ".tk[151]" -type "float3" 0.022440735 -2.9802322e-08 0.016304145 ;
	setAttr ".tk[152]" -type "float3" 0.016304148 -2.9802322e-08 0.022440733 ;
	setAttr ".tk[153]" -type "float3" 0.0085715977 -2.9802322e-08 0.026380667 ;
	setAttr ".tk[154]" -type "float3" -2.9523741e-09 -2.9802322e-08 0.027738275 ;
	setAttr ".tk[155]" -type "float3" -0.0085716033 -2.9802322e-08 0.026380669 ;
	setAttr ".tk[156]" -type "float3" -0.016304158 -2.9802322e-08 0.022440741 ;
	setAttr ".tk[157]" -type "float3" -0.022440748 -2.9802322e-08 0.016304154 ;
	setAttr ".tk[158]" -type "float3" -0.026380682 -2.9802322e-08 0.0085715977 ;
	setAttr ".tk[159]" -type "float3" -0.027738273 -2.9802322e-08 -4.4285615e-09 ;
	setAttr ".tk[160]" -type "float3" -0.026380662 -2.9802322e-08 -0.0085716015 ;
	setAttr ".tk[161]" -type "float3" -0.022440733 -2.9802322e-08 -0.016304154 ;
	setAttr ".tk[162]" -type "float3" -0.024533637 -1.4901161e-08 -0.033767652 ;
	setAttr ".tk[163]" -type "float3" -0.012898096 -1.4901161e-08 -0.039696254 ;
	setAttr ".tk[164]" -type "float3" -3.1986569e-09 -1.4901161e-08 -0.041739114 ;
	setAttr ".tk[165]" -type "float3" 0.012898091 -1.4901161e-08 -0.039696258 ;
	setAttr ".tk[166]" -type "float3" 0.024533629 -1.4901161e-08 -0.033767652 ;
	setAttr ".tk[167]" -type "float3" 0.033767648 -1.4901161e-08 -0.024533637 ;
	setAttr ".tk[168]" -type "float3" 0.039696258 -1.4901161e-08 -0.0128981 ;
	setAttr ".tk[169]" -type "float3" 0.041739106 -1.4901161e-08 -6.6638681e-09 ;
	setAttr ".tk[170]" -type "float3" 0.039696258 -1.4901161e-08 0.012898088 ;
	setAttr ".tk[171]" -type "float3" 0.033767648 -1.4901161e-08 0.024533628 ;
	setAttr ".tk[172]" -type "float3" 0.024533637 -1.4901161e-08 0.033767648 ;
	setAttr ".tk[173]" -type "float3" 0.012898092 -1.4901161e-08 0.039696254 ;
	setAttr ".tk[174]" -type "float3" -4.4425792e-09 -1.4901161e-08 0.041739106 ;
	setAttr ".tk[175]" -type "float3" -0.012898101 -1.4901161e-08 0.039696258 ;
	setAttr ".tk[176]" -type "float3" -0.024533648 -1.4901161e-08 0.033767652 ;
	setAttr ".tk[177]" -type "float3" -0.03376767 -1.4901161e-08 0.024533637 ;
	setAttr ".tk[178]" -type "float3" -0.039696272 -1.4901161e-08 0.012898092 ;
	setAttr ".tk[179]" -type "float3" -0.041739106 -1.4901161e-08 -6.6638681e-09 ;
	setAttr ".tk[180]" -type "float3" -0.039696246 -1.4901161e-08 -0.012898099 ;
	setAttr ".tk[181]" -type "float3" -0.033767644 -1.4901161e-08 -0.024533637 ;
	setAttr ".tk[182]" -type "float3" -0.027783705 -1.3322676e-15 -0.038240999 ;
	setAttr ".tk[183]" -type "float3" -0.014606761 -1.3322676e-15 -0.044954989 ;
	setAttr ".tk[184]" -type "float3" -3.6223968e-09 -1.3322676e-15 -0.047268469 ;
	setAttr ".tk[185]" -type "float3" 0.014606753 -1.3322676e-15 -0.044954993 ;
	setAttr ".tk[186]" -type "float3" 0.027783705 -1.3322676e-15 -0.038241003 ;
	setAttr ".tk[187]" -type "float3" 0.038240992 -1.3322676e-15 -0.027783716 ;
	setAttr ".tk[188]" -type "float3" 0.044954982 -1.3322676e-15 -0.014606768 ;
	setAttr ".tk[189]" -type "float3" 0.047268461 -1.3322676e-15 -7.5466593e-09 ;
	setAttr ".tk[190]" -type "float3" 0.044954982 -1.3322676e-15 0.014606753 ;
	setAttr ".tk[191]" -type "float3" 0.038240992 -1.3322676e-15 0.027783705 ;
	setAttr ".tk[192]" -type "float3" 0.027783712 -1.3322676e-15 0.038240992 ;
	setAttr ".tk[193]" -type "float3" 0.014606758 -1.3322676e-15 0.044954989 ;
	setAttr ".tk[194]" -type "float3" -5.0311062e-09 -1.3322676e-15 0.047268469 ;
	setAttr ".tk[195]" -type "float3" -0.014606767 -1.3322676e-15 0.044954993 ;
	setAttr ".tk[196]" -type "float3" -0.027783724 -1.3322676e-15 0.038241003 ;
	setAttr ".tk[197]" -type "float3" -0.038241021 -1.3322676e-15 0.027783709 ;
	setAttr ".tk[198]" -type "float3" -0.044955011 -1.3322676e-15 0.014606758 ;
	setAttr ".tk[199]" -type "float3" -0.047268461 -1.3322676e-15 -7.5466593e-09 ;
	setAttr ".tk[200]" -type "float3" -0.044954982 -1.3322676e-15 -0.014606765 ;
	setAttr ".tk[201]" -type "float3" -0.038240988 -1.3322676e-15 -0.027783709 ;
	setAttr ".tk[202]" -type "float3" -0.024533637 1.4901161e-08 -0.033767652 ;
	setAttr ".tk[203]" -type "float3" -0.012898096 1.4901161e-08 -0.039696254 ;
	setAttr ".tk[204]" -type "float3" -3.1986569e-09 1.4901161e-08 -0.041739114 ;
	setAttr ".tk[205]" -type "float3" 0.012898091 1.4901161e-08 -0.039696258 ;
	setAttr ".tk[206]" -type "float3" 0.024533629 1.4901161e-08 -0.033767652 ;
	setAttr ".tk[207]" -type "float3" 0.033767648 1.4901161e-08 -0.024533637 ;
	setAttr ".tk[208]" -type "float3" 0.039696258 1.4901161e-08 -0.0128981 ;
	setAttr ".tk[209]" -type "float3" 0.041739106 1.4901161e-08 -6.6638681e-09 ;
	setAttr ".tk[210]" -type "float3" 0.039696258 1.4901161e-08 0.012898088 ;
	setAttr ".tk[211]" -type "float3" 0.033767648 1.4901161e-08 0.024533628 ;
	setAttr ".tk[212]" -type "float3" 0.024533637 1.4901161e-08 0.033767644 ;
	setAttr ".tk[213]" -type "float3" 0.012898092 1.4901161e-08 0.039696254 ;
	setAttr ".tk[214]" -type "float3" -4.4425792e-09 1.4901161e-08 0.041739106 ;
	setAttr ".tk[215]" -type "float3" -0.012898101 1.4901161e-08 0.039696258 ;
	setAttr ".tk[216]" -type "float3" -0.024533648 1.4901161e-08 0.033767652 ;
	setAttr ".tk[217]" -type "float3" -0.03376767 1.4901161e-08 0.024533637 ;
	setAttr ".tk[218]" -type "float3" -0.039696272 1.4901161e-08 0.012898092 ;
	setAttr ".tk[219]" -type "float3" -0.041739106 1.4901161e-08 -6.6638681e-09 ;
	setAttr ".tk[220]" -type "float3" -0.039696246 1.4901161e-08 -0.012898099 ;
	setAttr ".tk[221]" -type "float3" -0.033767644 1.4901161e-08 -0.024533637 ;
	setAttr ".tk[222]" -type "float3" -0.016304148 2.9802322e-08 -0.022440741 ;
	setAttr ".tk[223]" -type "float3" -0.0085715996 2.9802322e-08 -0.026380667 ;
	setAttr ".tk[224]" -type "float3" -2.1257096e-09 2.9802322e-08 -0.027738275 ;
	setAttr ".tk[225]" -type "float3" 0.008571594 2.9802322e-08 -0.026380669 ;
	setAttr ".tk[226]" -type "float3" 0.016304143 2.9802322e-08 -0.022440741 ;
	setAttr ".tk[227]" -type "float3" 0.022440735 2.9802322e-08 -0.016304154 ;
	setAttr ".tk[228]" -type "float3" 0.026380667 2.9802322e-08 -0.0085716024 ;
	setAttr ".tk[229]" -type "float3" 0.027738273 2.9802322e-08 -4.4285615e-09 ;
	setAttr ".tk[230]" -type "float3" 0.026380667 2.9802322e-08 0.0085715931 ;
	setAttr ".tk[231]" -type "float3" 0.022440735 2.9802322e-08 0.016304145 ;
	setAttr ".tk[232]" -type "float3" 0.016304154 2.9802322e-08 0.022440735 ;
	setAttr ".tk[233]" -type "float3" 0.0085715977 2.9802322e-08 0.026380667 ;
	setAttr ".tk[234]" -type "float3" -2.9523741e-09 2.9802322e-08 0.027738275 ;
	setAttr ".tk[235]" -type "float3" -0.0085716033 2.9802322e-08 0.026380669 ;
	setAttr ".tk[236]" -type "float3" -0.016304158 2.9802322e-08 0.022440741 ;
	setAttr ".tk[237]" -type "float3" -0.022440748 2.9802322e-08 0.016304154 ;
	setAttr ".tk[238]" -type "float3" -0.026380682 2.9802322e-08 0.0085715977 ;
	setAttr ".tk[239]" -type "float3" -0.027738273 2.9802322e-08 -4.4285615e-09 ;
	setAttr ".tk[240]" -type "float3" -0.026380662 2.9802322e-08 -0.0085716015 ;
	setAttr ".tk[241]" -type "float3" -0.022440732 2.9802322e-08 -0.016304154 ;
createNode polyBevel3 -n "polyBevel2";
	rename -uid "1FF28B5A-4467-A2D7-7604-8AB0DF841814";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 1 "e[0:19]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 1 0 1;
	setAttr ".ws" yes;
	setAttr ".oaf" yes;
	setAttr ".f" 0.059999999999999942;
	setAttr ".sg" 2;
	setAttr ".at" 180;
	setAttr ".sn" yes;
	setAttr ".mv" yes;
	setAttr ".mvt" 0.0001;
	setAttr ".sa" 30;
createNode polyExtrudeFace -n "polyExtrudeFace1";
	rename -uid "2B8FCA2B-43A3-494A-F24B-128C4C237A7B";
	setAttr ".ics" -type "componentList" 1 "f[20:119]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 0 1 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 0 2.8769023 0 ;
	setAttr ".rs" 57607;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -0.99167811870574951 2 -0.99167829751968384 ;
	setAttr ".cbx" -type "double3" 0.99167811870574951 3.7538044452667236 0.99167829751968384 ;
createNode polySmoothFace -n "polySmoothFace1";
	rename -uid "2D83D764-4260-4EAB-F9F5-068853631755";
	setAttr ".ics" -type "componentList" 1 "f[*]";
	setAttr ".sdt" 2;
	setAttr ".dv" 2;
	setAttr ".suv" yes;
	setAttr ".ps" 0.10000000149011612;
	setAttr ".ro" 1;
	setAttr ".ma" yes;
	setAttr ".m08" yes;
select -ne :time1;
	setAttr ".o" 1;
	setAttr ".unw" 1;
select -ne :hardwareRenderingGlobals;
	setAttr ".otfna" -type "stringArray" 22 "NURBS Curves" "NURBS Surfaces" "Polygons" "Subdiv Surface" "Particles" "Particle Instance" "Fluids" "Strokes" "Image Planes" "UI" "Lights" "Cameras" "Locators" "Joints" "IK Handles" "Deformers" "Motion Trails" "Components" "Hair Systems" "Follicles" "Misc. UI" "Ornaments"  ;
	setAttr ".otfva" -type "Int32Array" 22 0 1 1 1 1 1
		 1 1 1 0 0 0 0 0 0 0 0 0
		 0 0 0 0 ;
	setAttr ".fprt" yes;
select -ne :renderPartition;
	setAttr -s 2 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 5 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderingList1;
select -ne :initialShadingGroup;
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	addAttr -ci true -h true -sn "dss" -ln "defaultSurfaceShader" -dt "string";
	setAttr ".ren" -type "string" "arnold";
	setAttr ".dss" -type "string" "lambert1";
select -ne :defaultResolution;
	setAttr ".pa" 1;
select -ne :defaultColorMgtGlobals;
	setAttr ".cfe" yes;
	setAttr ".cfp" -type "string" "<MAYA_RESOURCES>/OCIO-configs/Maya2022-default/config.ocio";
	setAttr ".vtn" -type "string" "ACES 1.0 SDR-video (sRGB)";
	setAttr ".vn" -type "string" "ACES 1.0 SDR-video";
	setAttr ".dn" -type "string" "sRGB";
	setAttr ".wsn" -type "string" "ACEScg";
	setAttr ".otn" -type "string" "ACES 1.0 SDR-video (sRGB)";
	setAttr ".potn" -type "string" "ACES 1.0 SDR-video (sRGB)";
select -ne :hardwareRenderGlobals;
	setAttr ".ctrs" 256;
	setAttr ".btrs" 512;
select -ne :ikSystem;
	setAttr -s 4 ".sol";
connectAttr "polySmoothFace1.out" "pCylinderShape1.i";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr "polyCylinder1.out" "polyExtrudeEdge1.ip";
connectAttr "pCylinderShape1.wm" "polyExtrudeEdge1.mp";
connectAttr "polyTweak1.out" "polyExtrudeEdge2.ip";
connectAttr "pCylinderShape1.wm" "polyExtrudeEdge2.mp";
connectAttr "polyExtrudeEdge1.out" "polyTweak1.ip";
connectAttr "polyTweak2.out" "polyExtrudeEdge3.ip";
connectAttr "pCylinderShape1.wm" "polyExtrudeEdge3.mp";
connectAttr "polyExtrudeEdge2.out" "polyTweak2.ip";
connectAttr "polyTweak3.out" "polyExtrudeEdge4.ip";
connectAttr "pCylinderShape1.wm" "polyExtrudeEdge4.mp";
connectAttr "polyExtrudeEdge3.out" "polyTweak3.ip";
connectAttr "polyTweak4.out" "polyExtrudeEdge5.ip";
connectAttr "pCylinderShape1.wm" "polyExtrudeEdge5.mp";
connectAttr "polyExtrudeEdge4.out" "polyTweak4.ip";
connectAttr "polyTweak5.out" "polySplitRing1.ip";
connectAttr "pCylinderShape1.wm" "polySplitRing1.mp";
connectAttr "polyExtrudeEdge5.out" "polyTweak5.ip";
connectAttr "polyTweak6.out" "polyBevel1.ip";
connectAttr "pCylinderShape1.wm" "polyBevel1.mp";
connectAttr "polySplitRing1.out" "polyTweak6.ip";
connectAttr "polyBevel1.out" "polyBevel2.ip";
connectAttr "pCylinderShape1.wm" "polyBevel2.mp";
connectAttr "polyBevel2.out" "polyExtrudeFace1.ip";
connectAttr "pCylinderShape1.wm" "polyExtrudeFace1.mp";
connectAttr "polyExtrudeFace1.out" "polySmoothFace1.ip";
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "pCylinderShape1.iog" ":initialShadingGroup.dsm" -na;
// End of wineglass.ma
