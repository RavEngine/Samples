//Maya ASCII 2024 scene
//Name: rat.ma
//Last modified: Tue, Nov 14, 2023 08:15:34 PM
//Codeset: 1252
requires maya "2024";
requires -nodeType "aiOptions" -nodeType "aiAOVDriver" -nodeType "aiAOVFilter" "mtoa" "5.3.1.1";
currentUnit -l centimeter -a degree -t film;
fileInfo "application" "maya";
fileInfo "product" "Maya 2024";
fileInfo "version" "2024";
fileInfo "cutIdentifier" "202304191415-7fa20164c6";
fileInfo "osv" "Windows 10 Pro v2009 (Build: 19045)";
fileInfo "UUID" "22E5BE94-4EB9-7111-76A6-9D9BB7327678";
createNode transform -s -n "persp";
	rename -uid "77013D81-4BA5-5112-8E84-12B0021AAD35";
	setAttr ".t" -type "double3" 5.4157298224522119 1.2999973397453906 3.6582853212097151 ;
	setAttr ".r" -type "double3" -18.338352730154565 47.399999999989163 4.6988736842792619e-15 ;
createNode camera -s -n "perspShape" -p "persp";
	rename -uid "2D885BE8-4822-D9A5-817B-1FB95D27D653";
	setAttr -k off ".v";
	setAttr ".fl" 34.999999999999993;
	setAttr ".coi" 6.1230546337302947;
	setAttr ".imn" -type "string" "persp";
	setAttr ".den" -type "string" "persp_depth";
	setAttr ".man" -type "string" "persp_mask";
	setAttr ".tp" -type "double3" 1.9810011573719595 -0.95208950819831695 0.5477001371487551 ;
	setAttr ".hc" -type "string" "viewSet -p %camera";
createNode transform -s -n "top";
	rename -uid "151B2869-4944-41AB-A7F2-65B434E86E82";
	setAttr ".v" no;
	setAttr ".t" -type "double3" -0.94109156512592484 1000.1 3.3928827479539896 ;
	setAttr ".r" -type "double3" -90 0 0 ;
createNode camera -s -n "topShape" -p "top";
	rename -uid "1461444A-4F75-409D-5C34-8584CDDF1480";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 11.602668375302512;
	setAttr ".imn" -type "string" "top";
	setAttr ".den" -type "string" "top_depth";
	setAttr ".man" -type "string" "top_mask";
	setAttr ".hc" -type "string" "viewSet -t %camera";
	setAttr ".o" yes;
	setAttr ".ai_translator" -type "string" "orthographic";
createNode transform -s -n "front";
	rename -uid "92C347A2-46B4-8C6C-6987-73B9DF4EBFC5";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 1.2112225888916843 -0.71854264052079286 1000.295350713791 ;
createNode camera -s -n "frontShape" -p "front";
	rename -uid "D4E47FD8-4FF1-56F7-D4B6-FFB21395C3F9";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 995.83789652763221;
	setAttr ".ow" 0.87957231015642889;
	setAttr ".imn" -type "string" "front";
	setAttr ".den" -type "string" "front_depth";
	setAttr ".man" -type "string" "front_mask";
	setAttr ".tp" -type "double3" 0 0 4.4574541861587242 ;
	setAttr ".hc" -type "string" "viewSet -f %camera";
	setAttr ".o" yes;
	setAttr ".ai_translator" -type "string" "orthographic";
createNode transform -s -n "side";
	rename -uid "1F5FF2A2-4103-0C54-602E-87BB52747FEA";
	setAttr ".v" no;
	setAttr ".t" -type "double3" 1000.1 0 0 ;
	setAttr ".r" -type "double3" 0 90 0 ;
createNode camera -s -n "sideShape" -p "side";
	rename -uid "0AC4845C-4628-B0DD-50FF-50944B7726D6";
	setAttr -k off ".v" no;
	setAttr ".rnd" no;
	setAttr ".coi" 1000.1;
	setAttr ".ow" 33.6;
	setAttr ".imn" -type "string" "side";
	setAttr ".den" -type "string" "side_depth";
	setAttr ".man" -type "string" "side_mask";
	setAttr ".hc" -type "string" "viewSet -s %camera";
	setAttr ".o" yes;
	setAttr ".ai_translator" -type "string" "orthographic";
createNode transform -n "imagePlane1";
	rename -uid "F72CF6F9-40DD-E8A1-0CDF-41BC461DABC1";
	setAttr ".t" -type "double3" 0 0 -2.2723335777815423 ;
createNode imagePlane -n "imagePlaneShape1" -p "imagePlane1";
	rename -uid "41A863AF-48BC-22D0-A440-E3B790F6C580";
	setAttr -k off ".v";
	setAttr ".fc" 101;
	setAttr ".imn" -type "string" "C:/Users/Admin/Downloads/rat.png";
	setAttr ".cov" -type "short2" 992 339 ;
	setAttr ".dlc" no;
	setAttr ".w" 9.92;
	setAttr ".h" 3.39;
	setAttr ".cs" -type "string" "sRGB";
createNode transform -n "Rat";
	rename -uid "C66C9DE0-420D-D05E-8A76-79A665232CB5";
createNode transform -n "body" -p "Rat";
	rename -uid "4DF46141-427C-2F94-977F-939FDB005F2C";
	setAttr ".t" -type "double3" 1.3173848527240948 -0.47718117311413738 -0.00095037538237224828 ;
createNode mesh -n "bodyShape" -p "body";
	rename -uid "4DC5F00D-4067-55B4-9272-829C681F3AE4";
	setAttr -k off ".v";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.24337729581408424 0.25922322115494267 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 23 ".pt";
	setAttr ".pt[0]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[1]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[6]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[7]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[8]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[11]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[12]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[15]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[24]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[27]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[28]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[31]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[32]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[35]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[36]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[39]" -type "float3" 0 7.4505806e-09 0 ;
	setAttr ".pt[40]" -type "float3" -0.0055909548 7.4505806e-09 0 ;
	setAttr ".pt[41]" -type "float3" -0.033848461 0 0 ;
	setAttr ".pt[42]" -type "float3" -0.033848468 0 0 ;
	setAttr ".pt[43]" -type "float3" -0.0055909548 7.4505806e-09 0 ;
	setAttr ".pt[105]" -type "float3" 0 0.027766388 0 ;
	setAttr ".pt[106]" -type "float3" 0 0.012557682 0 ;
	setAttr ".pt[115]" -type "float3" 0.029729506 -0.00081072003 0 ;
createNode transform -n "earR" -p "Rat";
	rename -uid "88BB98DC-4EE8-9486-DE82-68B94B60BAF9";
	setAttr ".t" -type "double3" 2.5205428779795751 -0.16689296283628863 0.3430881578358409 ;
	setAttr ".r" -type "double3" 71.281020393246351 -10.431079242076345 18.187370888351289 ;
	setAttr ".s" -type "double3" 0.2139214439320711 0.2139214439320711 0.2139214439320711 ;
createNode mesh -n "earRShape" -p "earR";
	rename -uid "8FDD1757-4432-4A8F-C8E7-2E908729D707";
	setAttr -k off ".v";
	setAttr -s 2 ".iog";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.79325056076049805 0.8170095682144165 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 6 ".pt";
	setAttr ".pt[2]" -type "float3" -2.9802322e-08 -1.1920929e-07 0 ;
	setAttr ".pt[4]" -type "float3" 0.11680071 -0.032887109 0.030053809 ;
	setAttr ".pt[5]" -type "float3" 0.11680071 -0.032887109 0.030053809 ;
	setAttr ".pt[6]" -type "float3" 0.11680071 -0.032887109 0.030053809 ;
	setAttr ".pt[7]" -type "float3" 0.11680071 -0.032887109 0.030053809 ;
	setAttr ".dr" 1;
createNode transform -n "earL" -p "Rat";
	rename -uid "6E639F0B-4E5C-7544-F23F-CD8DFD39DBD0";
	setAttr ".t" -type "double3" 2.5205428779795751 -0.16689296283628863 -0.30774341083516366 ;
	setAttr ".r" -type "double3" 19.782142616266714 15.561743773798703 5.5114701340099135 ;
	setAttr ".s" -type "double3" 0.2139214439320711 0.2139214439320711 0.2139214439320711 ;
createNode transform -n "eyeR" -p "Rat";
	rename -uid "6B233659-4268-78CE-D0BD-DEB76B93CAD4";
	setAttr ".t" -type "double3" 2.8412874025183372 -0.37129308968325769 0.28437582087105012 ;
	setAttr ".s" -type "double3" 0.076834234741584614 0.076834234741584614 0.076834234741584614 ;
createNode mesh -n "eyeRShape" -p "eyeR";
	rename -uid "D25F1E14-4570-9919-CCA5-A383403C5D6E";
	setAttr -k off ".v";
	setAttr -s 2 ".iog";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.2404964714899408 0.75118617092450135 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
createNode transform -n "eyeL" -p "Rat";
	rename -uid "8EAF579A-40FD-7AAE-D04C-41A3A28458BD";
	setAttr ".t" -type "double3" 2.8412874025183372 -0.37129308968325769 -0.27629721058917805 ;
	setAttr ".s" -type "double3" 0.076834234741584614 0.076834234741584614 0.076834234741584614 ;
createNode transform -n "leg" -p "Rat";
	rename -uid "B0F5A5EE-4A01-0ACF-8BB9-5E8C1CFCC2B6";
	setAttr ".t" -type "double3" 2.0209162410232562 -0.69666779102357179 0.49321987157123526 ;
	setAttr ".r" -type "double3" 0 0 -43.318004461454841 ;
	setAttr ".s" -type "double3" 0.1807170349782429 0.1807170349782429 0.1807170349782429 ;
createNode mesh -n "legShape" -p "leg";
	rename -uid "EE02B2A8-4C84-F078-B2A7-B09FCD467101";
	setAttr -k off ".v";
	setAttr -s 4 ".iog";
	setAttr ".vir" yes;
	setAttr ".vif" yes;
	setAttr ".pv" -type "double2" 0.82054987951450609 0.19971977195794821 ;
	setAttr ".uvst[0].uvsn" -type "string" "map1";
	setAttr ".cuvs" -type "string" "map1";
	setAttr ".dcc" -type "string" "Ambient+Diffuse";
	setAttr ".covm[0]"  0 1 1;
	setAttr ".cdvm[0]"  0 1 1;
	setAttr -s 11 ".pt";
	setAttr ".pt[2]" -type "float3" -4.4408921e-16 4.4408921e-16 -0.4993425 ;
	setAttr ".pt[3]" -type "float3" -4.4408921e-16 4.4408921e-16 -0.4993425 ;
	setAttr ".pt[4]" -type "float3" -4.4408921e-16 4.4408921e-16 -0.4993425 ;
	setAttr ".pt[5]" -type "float3" -4.4408921e-16 4.4408921e-16 -0.4993425 ;
	setAttr ".pt[16]" -type "float3" 0.028673392 -0.30730426 0 ;
	setAttr ".pt[19]" -type "float3" 0.028673392 -0.30730426 0 ;
	setAttr ".pt[28]" -type "float3" 0.29573187 0.25016627 0.069786467 ;
	setAttr ".pt[29]" -type "float3" 0.36207649 0.12736954 0.069786467 ;
	setAttr ".pt[30]" -type "float3" 0.36207649 0.12736954 -0.069786467 ;
	setAttr ".pt[31]" -type "float3" 0.29573187 0.25016627 -0.069786467 ;
createNode transform -n "leg1" -p "Rat";
	rename -uid "BEA93D4C-4987-B712-476C-66808DCFB93B";
	setAttr ".t" -type "double3" -0.17090387577637789 -0.69666779102357179 0.49321987157123526 ;
	setAttr ".r" -type "double3" 0 0 -43.318004461454841 ;
	setAttr ".s" -type "double3" 0.1807170349782429 0.1807170349782429 0.1807170349782429 ;
createNode transform -n "leg2" -p "Rat";
	rename -uid "DE2E8189-4D90-F185-E570-8296578367AE";
	setAttr ".t" -type "double3" -0.17090387577637789 -0.69666779102357179 -0.49748977569853448 ;
	setAttr ".r" -type "double3" 0 0 -43.318004461454841 ;
	setAttr ".s" -type "double3" 0.1807170349782429 0.1807170349782429 -0.1807170349782429 ;
createNode transform -n "leg3" -p "Rat";
	rename -uid "3C4A9F14-4DA4-99BC-AD4B-75B7691B9EE7";
	setAttr ".t" -type "double3" 2.0209162410232562 -0.69666779102357179 -0.49748977569853448 ;
	setAttr ".r" -type "double3" 0 0 -43.318004461454841 ;
	setAttr ".s" -type "double3" 0.1807170349782429 0.1807170349782429 -0.1807170349782429 ;
parent -s -nc -r -add "|Rat|earR|earRShape" "earL" ;
parent -s -nc -r -add "|Rat|eyeR|eyeRShape" "eyeL" ;
parent -s -nc -r -add "|Rat|leg|legShape" "leg1" ;
parent -s -nc -r -add "|Rat|leg|legShape" "leg2" ;
parent -s -nc -r -add "|Rat|leg|legShape" "leg3" ;
createNode lightLinker -s -n "lightLinker1";
	rename -uid "01A8458B-4396-2358-C4C2-2FA717517B73";
	setAttr -s 2 ".lnk";
	setAttr -s 2 ".slnk";
createNode shapeEditorManager -n "shapeEditorManager";
	rename -uid "9DA3DC10-405C-D647-9E1D-96A3FD99B8FF";
createNode poseInterpolatorManager -n "poseInterpolatorManager";
	rename -uid "0403FEEF-4C24-DC0B-D2DC-07B4FA5CFD6D";
createNode displayLayerManager -n "layerManager";
	rename -uid "DDC0D890-4459-DFC7-02AD-43AAC9DAC232";
createNode displayLayer -n "defaultLayer";
	rename -uid "7CACFBB5-49F0-1C2E-C9AE-2C85E34F859D";
	setAttr ".ufem" -type "stringArray" 0  ;
createNode renderLayerManager -n "renderLayerManager";
	rename -uid "EC05B850-497A-9F08-F8B1-FFA315138A69";
createNode renderLayer -n "defaultRenderLayer";
	rename -uid "58DC5A0F-4595-1C11-2B5D-4182D415A0D8";
	setAttr ".g" yes;
createNode aiOptions -s -n "defaultArnoldRenderOptions";
	rename -uid "199C9C9D-41BE-6651-DDA9-9CA7464CF4C3";
	setAttr ".version" -type "string" "5.3.1.1";
createNode aiAOVFilter -s -n "defaultArnoldFilter";
	rename -uid "83BA8669-4E1C-F990-DD0B-94B1F5167942";
	setAttr ".ai_translator" -type "string" "gaussian";
createNode aiAOVDriver -s -n "defaultArnoldDriver";
	rename -uid "5907747D-4B31-7E3B-FB97-1996391058B7";
	setAttr ".ai_translator" -type "string" "exr";
createNode aiAOVDriver -s -n "defaultArnoldDisplayDriver";
	rename -uid "21423F2F-4A9D-EE99-5124-6D870847BB9B";
	setAttr ".output_mode" 0;
	setAttr ".ai_translator" -type "string" "maya";
createNode script -n "uiConfigurationScriptNode";
	rename -uid "9E345488-4549-4197-A3E4-57B02B0812FC";
	setAttr ".b" -type "string" (
		"// Maya Mel UI Configuration File.\n//\n//  This script is machine generated.  Edit at your own risk.\n//\n//\n\nglobal string $gMainPane;\nif (`paneLayout -exists $gMainPane`) {\n\n\tglobal int $gUseScenePanelConfig;\n\tint    $useSceneConfig = $gUseScenePanelConfig;\n\tint    $nodeEditorPanelVisible = stringArrayContains(\"nodeEditorPanel1\", `getPanel -vis`);\n\tint    $nodeEditorWorkspaceControlOpen = (`workspaceControl -exists nodeEditorPanel1Window` && `workspaceControl -q -visible nodeEditorPanel1Window`);\n\tint    $menusOkayInPanels = `optionVar -q allowMenusInPanels`;\n\tint    $nVisPanes = `paneLayout -q -nvp $gMainPane`;\n\tint    $nPanes = 0;\n\tstring $editorName;\n\tstring $panelName;\n\tstring $itemFilterName;\n\tstring $panelConfig;\n\n\t//\n\t//  get current state of the UI\n\t//\n\tsceneUIReplacement -update $gMainPane;\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Top View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Top View\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"|top\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n"
		+ "            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n"
		+ "            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -bluePencil 1\n            -greasePencils 0\n            -excludeObjectPreset \"All\" \n            -shadows 0\n            -captureSequenceNumber -1\n            -width 937\n            -height 557\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Side View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Side View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"|side\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n"
		+ "            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n"
		+ "            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -bluePencil 1\n            -greasePencils 0\n            -excludeObjectPreset \"All\" \n"
		+ "            -shadows 0\n            -captureSequenceNumber -1\n            -width 937\n            -height 556\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Front View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Front View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        modelEditor -e \n            -camera \"|front\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"wireframe\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n"
		+ "            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 0\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n"
		+ "            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n"
		+ "            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -bluePencil 1\n            -greasePencils 0\n            -excludeObjectPreset \"All\" \n            -shadows 0\n            -captureSequenceNumber -1\n            -width 937\n            -height 556\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"modelPanel\" (localizedPanelLabel(\"Persp View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tmodelPanel -edit -l (localizedPanelLabel(\"Persp View\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n"
		+ "        modelEditor -e \n            -camera \"|persp\" \n            -useInteractiveMode 0\n            -displayLights \"default\" \n            -displayAppearance \"smoothShaded\" \n            -activeOnly 0\n            -ignorePanZoom 0\n            -wireframeOnShaded 0\n            -headsUpDisplay 1\n            -holdOuts 1\n            -selectionHiliteDisplay 1\n            -useDefaultMaterial 0\n            -bufferMode \"double\" \n            -twoSidedLighting 0\n            -backfaceCulling 0\n            -xray 0\n            -jointXray 0\n            -activeComponentsXray 0\n            -displayTextures 1\n            -smoothWireframe 0\n            -lineWidth 1\n            -textureAnisotropic 0\n            -textureHilight 1\n            -textureSampling 2\n            -textureDisplay \"modulate\" \n            -textureMaxSize 16384\n            -fogging 0\n            -fogSource \"fragment\" \n            -fogMode \"linear\" \n            -fogStart 0\n            -fogEnd 100\n            -fogDensity 0.1\n            -fogColor 0.5 0.5 0.5 1 \n            -depthOfFieldPreview 1\n"
		+ "            -maxConstantTransparency 1\n            -rendererName \"vp2Renderer\" \n            -objectFilterShowInHUD 1\n            -isFiltered 0\n            -colorResolution 256 256 \n            -bumpResolution 512 512 \n            -textureCompression 0\n            -transparencyAlgorithm \"frontAndBackCull\" \n            -transpInShadows 0\n            -cullingOverride \"none\" \n            -lowQualityLighting 0\n            -maximumNumHardwareLights 1\n            -occlusionCulling 0\n            -shadingModel 0\n            -useBaseRenderer 0\n            -useReducedRenderer 0\n            -smallObjectCulling 0\n            -smallObjectThreshold -1 \n            -interactiveDisableShadows 0\n            -interactiveBackFaceCull 0\n            -sortTransparent 1\n            -controllers 1\n            -nurbsCurves 1\n            -nurbsSurfaces 1\n            -polymeshes 1\n            -subdivSurfaces 1\n            -planes 1\n            -lights 1\n            -cameras 1\n            -controlVertices 1\n            -hulls 1\n            -grid 1\n"
		+ "            -imagePlane 1\n            -joints 1\n            -ikHandles 1\n            -deformers 1\n            -dynamics 1\n            -particleInstancers 1\n            -fluids 1\n            -hairSystems 1\n            -follicles 1\n            -nCloths 1\n            -nParticles 1\n            -nRigids 1\n            -dynamicConstraints 1\n            -locators 1\n            -manipulators 1\n            -pluginShapes 1\n            -dimensions 1\n            -handles 1\n            -pivots 1\n            -textures 1\n            -strokes 1\n            -motionTrails 1\n            -clipGhosts 1\n            -bluePencil 1\n            -greasePencils 0\n            -excludeObjectPreset \"All\" \n            -shadows 0\n            -captureSequenceNumber -1\n            -width 1884\n            -height 1203\n            -sceneRenderFilter 0\n            $editorName;\n        modelEditor -e -viewSelected 0 $editorName;\n        modelEditor -e \n            -pluginObjects \"gpuCacheDisplayFilter\" 1 \n            $editorName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"ToggledOutliner\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"ToggledOutliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -showShapes 0\n            -showAssignedMaterials 0\n            -showTimeEditor 1\n            -showReferenceNodes 1\n            -showReferenceMembers 1\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n            -organizeByLayer 1\n            -organizeByClip 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showParentContainers 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n"
		+ "            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -isSet 0\n            -isSetMember 0\n            -showUfeItems 1\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n"
		+ "            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            -ignoreOutlinerColor 0\n            -renderFilterVisible 0\n            -renderFilterIndex 0\n            -selectionOrder \"chronological\" \n            -expandAttribute 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"outlinerPanel\" (localizedPanelLabel(\"Outliner\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\toutlinerPanel -edit -l (localizedPanelLabel(\"Outliner\")) -mbv $menusOkayInPanels  $panelName;\n\t\t$editorName = $panelName;\n        outlinerEditor -e \n            -showShapes 0\n            -showAssignedMaterials 0\n            -showTimeEditor 1\n            -showReferenceNodes 0\n            -showReferenceMembers 0\n            -showAttributes 0\n            -showConnected 0\n            -showAnimCurvesOnly 0\n            -showMuteInfo 0\n"
		+ "            -organizeByLayer 1\n            -organizeByClip 1\n            -showAnimLayerWeight 1\n            -autoExpandLayers 1\n            -autoExpand 0\n            -showDagOnly 1\n            -showAssets 1\n            -showContainedOnly 1\n            -showPublishedAsConnected 0\n            -showParentContainers 0\n            -showContainerContents 1\n            -ignoreDagHierarchy 0\n            -expandConnections 0\n            -showUpstreamCurves 1\n            -showUnitlessCurves 1\n            -showCompounds 1\n            -showLeafs 1\n            -showNumericAttrsOnly 0\n            -highlightActive 1\n            -autoSelectNewObjects 0\n            -doNotSelectNewObjects 0\n            -dropIsParent 1\n            -transmitFilters 0\n            -setFilter \"defaultSetFilter\" \n            -showSetMembers 1\n            -allowMultiSelection 1\n            -alwaysToggleSelect 0\n            -directSelect 0\n            -showUfeItems 1\n            -displayMode \"DAG\" \n            -expandObjects 0\n            -setsIgnoreFilters 1\n"
		+ "            -containersIgnoreFilters 0\n            -editAttrName 0\n            -showAttrValues 0\n            -highlightSecondary 0\n            -showUVAttrsOnly 0\n            -showTextureNodesOnly 0\n            -attrAlphaOrder \"default\" \n            -animLayerFilterOptions \"allAffecting\" \n            -sortOrder \"none\" \n            -longNames 0\n            -niceNames 1\n            -showNamespace 1\n            -showPinIcons 0\n            -mapMotionTrails 0\n            -ignoreHiddenAttribute 0\n            -ignoreOutlinerColor 0\n            -renderFilterVisible 0\n            $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"graphEditor\" (localizedPanelLabel(\"Graph Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Graph Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n"
		+ "                -showAssignedMaterials 0\n                -showTimeEditor 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -organizeByClip 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 1\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showParentContainers 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 1\n                -showCompounds 0\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 1\n                -doNotSelectNewObjects 0\n"
		+ "                -dropIsParent 1\n                -transmitFilters 1\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -showUfeItems 1\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n                -showPinIcons 1\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                -renderFilterVisible 0\n                $editorName;\n"
		+ "\n\t\t\t$editorName = ($panelName+\"GraphEd\");\n            animCurveEditor -e \n                -displayValues 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -showPlayRangeShades \"on\" \n                -lockPlayRangeShades \"off\" \n                -smoothness \"fine\" \n                -resultSamples 1\n                -resultScreenSamples 0\n                -resultUpdate \"delayed\" \n                -showUpstreamCurves 1\n                -keyMinScale 1\n                -stackedCurvesMin -1\n                -stackedCurvesMax 1\n                -stackedCurvesSpace 0.2\n                -preSelectionHighlight 0\n                -constrainDrag 0\n                -valueLinesToggle 0\n                -highlightAffectedCurves 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dopeSheetPanel\" (localizedPanelLabel(\"Dope Sheet\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dope Sheet\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"OutlineEd\");\n            outlinerEditor -e \n                -showShapes 1\n                -showAssignedMaterials 0\n                -showTimeEditor 1\n                -showReferenceNodes 0\n                -showReferenceMembers 0\n                -showAttributes 1\n                -showConnected 1\n                -showAnimCurvesOnly 1\n                -showMuteInfo 0\n                -organizeByLayer 1\n                -organizeByClip 1\n                -showAnimLayerWeight 1\n                -autoExpandLayers 1\n                -autoExpand 0\n                -showDagOnly 0\n                -showAssets 1\n                -showContainedOnly 0\n                -showPublishedAsConnected 0\n                -showParentContainers 0\n                -showContainerContents 0\n                -ignoreDagHierarchy 0\n                -expandConnections 1\n                -showUpstreamCurves 1\n                -showUnitlessCurves 0\n"
		+ "                -showCompounds 1\n                -showLeafs 1\n                -showNumericAttrsOnly 1\n                -highlightActive 0\n                -autoSelectNewObjects 0\n                -doNotSelectNewObjects 1\n                -dropIsParent 1\n                -transmitFilters 0\n                -setFilter \"0\" \n                -showSetMembers 0\n                -allowMultiSelection 1\n                -alwaysToggleSelect 0\n                -directSelect 0\n                -showUfeItems 1\n                -displayMode \"DAG\" \n                -expandObjects 0\n                -setsIgnoreFilters 1\n                -containersIgnoreFilters 0\n                -editAttrName 0\n                -showAttrValues 0\n                -highlightSecondary 0\n                -showUVAttrsOnly 0\n                -showTextureNodesOnly 0\n                -attrAlphaOrder \"default\" \n                -animLayerFilterOptions \"allAffecting\" \n                -sortOrder \"none\" \n                -longNames 0\n                -niceNames 1\n                -showNamespace 1\n"
		+ "                -showPinIcons 0\n                -mapMotionTrails 1\n                -ignoreHiddenAttribute 0\n                -ignoreOutlinerColor 0\n                -renderFilterVisible 0\n                $editorName;\n\n\t\t\t$editorName = ($panelName+\"DopeSheetEd\");\n            dopeSheetEditor -e \n                -displayValues 0\n                -snapTime \"integer\" \n                -snapValue \"none\" \n                -outliner \"dopeSheetPanel1OutlineEd\" \n                -showSummary 1\n                -showScene 0\n                -hierarchyBelow 0\n                -showTicks 1\n                -selectionWindow 0 0 0 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"timeEditorPanel\" (localizedPanelLabel(\"Time Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Time Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n"
		+ "\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"clipEditorPanel\" (localizedPanelLabel(\"Trax Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Trax Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = clipEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayValues 0\n                -snapTime \"none\" \n                -snapValue \"none\" \n                -initialized 0\n                -manageSequencer 0 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"sequenceEditorPanel\" (localizedPanelLabel(\"Camera Sequencer\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Camera Sequencer\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = sequenceEditorNameFromPanel($panelName);\n            clipEditor -e \n                -displayValues 0\n"
		+ "                -snapTime \"none\" \n                -snapValue \"none\" \n                -initialized 0\n                -manageSequencer 1 \n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperGraphPanel\" (localizedPanelLabel(\"Hypergraph Hierarchy\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypergraph Hierarchy\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"HyperGraphEd\");\n            hyperGraph -e \n                -graphLayoutStyle \"hierarchicalLayout\" \n                -orientation \"horiz\" \n                -mergeConnections 0\n                -zoom 1\n                -animateTransition 0\n                -showRelationships 1\n                -showShapes 0\n                -showDeformers 0\n                -showExpressions 0\n                -showConstraints 0\n                -showConnectionFromSelected 0\n                -showConnectionToSelected 0\n"
		+ "                -showConstraintLabels 0\n                -showUnderworld 0\n                -showInvisible 0\n                -transitionFrames 1\n                -opaqueContainers 0\n                -freeform 0\n                -imagePosition 0 0 \n                -imageScale 1\n                -imageEnabled 0\n                -graphType \"DAG\" \n                -heatMapDisplay 0\n                -updateSelection 1\n                -updateNodeAdded 1\n                -useDrawOverrideColor 0\n                -limitGraphTraversal -1\n                -range 0 0 \n                -iconSize \"smallIcons\" \n                -showCachedConnections 0\n                $editorName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"hyperShadePanel\" (localizedPanelLabel(\"Hypershade\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Hypershade\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"visorPanel\" (localizedPanelLabel(\"Visor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Visor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"nodeEditorPanel\" (localizedPanelLabel(\"Node Editor\")) `;\n\tif ($nodeEditorPanelVisible || $nodeEditorWorkspaceControlOpen) {\n\t\tif (\"\" == $panelName) {\n\t\t\tif ($useSceneConfig) {\n\t\t\t\t$panelName = `scriptedPanel -unParent  -type \"nodeEditorPanel\" -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels `;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -consistentNameSize 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -connectNodeOnCreation 0\n"
		+ "                -connectOnDrop 0\n                -copyConnectionsOnPaste 0\n                -connectionStyle \"bezier\" \n                -defaultPinnedState 0\n                -additiveGraphingMode 0\n                -connectedGraphingMode 1\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -crosshairOnEdgeDragging 0\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                -showUnitConversions 0\n                -editorMode \"default\" \n                -hasWatchpoint 0\n                $editorName;\n\t\t\t}\n\t\t} else {\n\t\t\t$label = `panel -q -label $panelName`;\n"
		+ "\t\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Node Editor\")) -mbv $menusOkayInPanels  $panelName;\n\n\t\t\t$editorName = ($panelName+\"NodeEditorEd\");\n            nodeEditor -e \n                -allAttributes 0\n                -allNodes 0\n                -autoSizeNodes 1\n                -consistentNameSize 1\n                -createNodeCommand \"nodeEdCreateNodeCommand\" \n                -connectNodeOnCreation 0\n                -connectOnDrop 0\n                -copyConnectionsOnPaste 0\n                -connectionStyle \"bezier\" \n                -defaultPinnedState 0\n                -additiveGraphingMode 0\n                -connectedGraphingMode 1\n                -settingsChangedCallback \"nodeEdSyncControls\" \n                -traversalDepthLimit -1\n                -keyPressCommand \"nodeEdKeyPressCommand\" \n                -nodeTitleMode \"name\" \n                -gridSnap 0\n                -gridVisibility 1\n                -crosshairOnEdgeDragging 0\n                -popupMenuScript \"nodeEdBuildPanelMenus\" \n                -showNamespace 1\n"
		+ "                -showShapes 1\n                -showSGShapes 0\n                -showTransforms 1\n                -useAssets 1\n                -syncedSelection 1\n                -extendToShapes 1\n                -showUnitConversions 0\n                -editorMode \"default\" \n                -hasWatchpoint 0\n                $editorName;\n\t\t\tif (!$useSceneConfig) {\n\t\t\t\tpanel -e -l $label $panelName;\n\t\t\t}\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"createNodePanel\" (localizedPanelLabel(\"Create Node\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Create Node\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"polyTexturePlacementPanel\" (localizedPanelLabel(\"UV Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"UV Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"renderWindowPanel\" (localizedPanelLabel(\"Render View\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Render View\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"shapePanel\" (localizedPanelLabel(\"Shape Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tshapePanel -edit -l (localizedPanelLabel(\"Shape Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextPanel \"posePanel\" (localizedPanelLabel(\"Pose Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tposePanel -edit -l (localizedPanelLabel(\"Pose Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n"
		+ "\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynRelEdPanel\" (localizedPanelLabel(\"Dynamic Relationships\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Dynamic Relationships\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"relationshipPanel\" (localizedPanelLabel(\"Relationship Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Relationship Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"referenceEditorPanel\" (localizedPanelLabel(\"Reference Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Reference Editor\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"dynPaintScriptedPanelType\" (localizedPanelLabel(\"Paint Effects\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Paint Effects\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"scriptEditorPanel\" (localizedPanelLabel(\"Script Editor\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Script Editor\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"profilerPanel\" (localizedPanelLabel(\"Profiler Tool\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Profiler Tool\")) -mbv $menusOkayInPanels  $panelName;\n"
		+ "\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\t$panelName = `sceneUIReplacement -getNextScriptedPanel \"contentBrowserPanel\" (localizedPanelLabel(\"Content Browser\")) `;\n\tif (\"\" != $panelName) {\n\t\t$label = `panel -q -label $panelName`;\n\t\tscriptedPanel -edit -l (localizedPanelLabel(\"Content Browser\")) -mbv $menusOkayInPanels  $panelName;\n\t\tif (!$useSceneConfig) {\n\t\t\tpanel -e -l $label $panelName;\n\t\t}\n\t}\n\n\n\tif ($useSceneConfig) {\n        string $configName = `getPanel -cwl (localizedPanelLabel(\"Current Layout\"))`;\n        if (\"\" != $configName) {\n\t\t\tpanelConfiguration -edit -label (localizedPanelLabel(\"Current Layout\")) \n\t\t\t\t-userCreated false\n\t\t\t\t-defaultImage \"vacantCell.xP:/\"\n\t\t\t\t-image \"\"\n\t\t\t\t-sc false\n\t\t\t\t-configString \"global string $gMainPane; paneLayout -e -cn \\\"single\\\" -ps 1 100 100 $gMainPane;\"\n\t\t\t\t-removeAllPanels\n\t\t\t\t-ap false\n\t\t\t\t\t(localizedPanelLabel(\"Persp View\")) \n\t\t\t\t\t\"modelPanel\"\n"
		+ "\t\t\t\t\t\"$panelName = `modelPanel -unParent -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels `;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -controllers 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -bluePencil 1\\n    -greasePencils 0\\n    -excludeObjectPreset \\\"All\\\" \\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 1884\\n    -height 1203\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t\t\"modelPanel -edit -l (localizedPanelLabel(\\\"Persp View\\\")) -mbv $menusOkayInPanels  $panelName;\\n$editorName = $panelName;\\nmodelEditor -e \\n    -cam `findStartUpCamera persp` \\n    -useInteractiveMode 0\\n    -displayLights \\\"default\\\" \\n    -displayAppearance \\\"smoothShaded\\\" \\n    -activeOnly 0\\n    -ignorePanZoom 0\\n    -wireframeOnShaded 0\\n    -headsUpDisplay 1\\n    -holdOuts 1\\n    -selectionHiliteDisplay 1\\n    -useDefaultMaterial 0\\n    -bufferMode \\\"double\\\" \\n    -twoSidedLighting 0\\n    -backfaceCulling 0\\n    -xray 0\\n    -jointXray 0\\n    -activeComponentsXray 0\\n    -displayTextures 1\\n    -smoothWireframe 0\\n    -lineWidth 1\\n    -textureAnisotropic 0\\n    -textureHilight 1\\n    -textureSampling 2\\n    -textureDisplay \\\"modulate\\\" \\n    -textureMaxSize 16384\\n    -fogging 0\\n    -fogSource \\\"fragment\\\" \\n    -fogMode \\\"linear\\\" \\n    -fogStart 0\\n    -fogEnd 100\\n    -fogDensity 0.1\\n    -fogColor 0.5 0.5 0.5 1 \\n    -depthOfFieldPreview 1\\n    -maxConstantTransparency 1\\n    -rendererName \\\"vp2Renderer\\\" \\n    -objectFilterShowInHUD 1\\n    -isFiltered 0\\n    -colorResolution 256 256 \\n    -bumpResolution 512 512 \\n    -textureCompression 0\\n    -transparencyAlgorithm \\\"frontAndBackCull\\\" \\n    -transpInShadows 0\\n    -cullingOverride \\\"none\\\" \\n    -lowQualityLighting 0\\n    -maximumNumHardwareLights 1\\n    -occlusionCulling 0\\n    -shadingModel 0\\n    -useBaseRenderer 0\\n    -useReducedRenderer 0\\n    -smallObjectCulling 0\\n    -smallObjectThreshold -1 \\n    -interactiveDisableShadows 0\\n    -interactiveBackFaceCull 0\\n    -sortTransparent 1\\n    -controllers 1\\n    -nurbsCurves 1\\n    -nurbsSurfaces 1\\n    -polymeshes 1\\n    -subdivSurfaces 1\\n    -planes 1\\n    -lights 1\\n    -cameras 1\\n    -controlVertices 1\\n    -hulls 1\\n    -grid 1\\n    -imagePlane 1\\n    -joints 1\\n    -ikHandles 1\\n    -deformers 1\\n    -dynamics 1\\n    -particleInstancers 1\\n    -fluids 1\\n    -hairSystems 1\\n    -follicles 1\\n    -nCloths 1\\n    -nParticles 1\\n    -nRigids 1\\n    -dynamicConstraints 1\\n    -locators 1\\n    -manipulators 1\\n    -pluginShapes 1\\n    -dimensions 1\\n    -handles 1\\n    -pivots 1\\n    -textures 1\\n    -strokes 1\\n    -motionTrails 1\\n    -clipGhosts 1\\n    -bluePencil 1\\n    -greasePencils 0\\n    -excludeObjectPreset \\\"All\\\" \\n    -shadows 0\\n    -captureSequenceNumber -1\\n    -width 1884\\n    -height 1203\\n    -sceneRenderFilter 0\\n    $editorName;\\nmodelEditor -e -viewSelected 0 $editorName;\\nmodelEditor -e \\n    -pluginObjects \\\"gpuCacheDisplayFilter\\\" 1 \\n    $editorName\"\n"
		+ "\t\t\t\t$configName;\n\n            setNamedPanelLayout (localizedPanelLabel(\"Current Layout\"));\n        }\n\n        panelHistory -e -clear mainPanelHistory;\n        sceneUIReplacement -clear;\n\t}\n\n\ngrid -spacing 5 -size 12 -divisions 5 -displayAxes yes -displayGridLines yes -displayDivisionLines yes -displayPerspectiveLabels no -displayOrthographicLabels no -displayAxesBold yes -perspectiveLabelPosition axis -orthographicLabelPosition edge;\nviewManip -drawCompass 0 -compassAngle 0 -frontParameters \"\" -homeParameters \"\" -selectionLockParameters \"\";\n}\n");
	setAttr ".st" 3;
createNode script -n "sceneConfigurationScriptNode";
	rename -uid "E9944582-40E1-4063-924C-AEBD4506B8E5";
	setAttr ".b" -type "string" "playbackOptions -min 1 -max 120 -ast 1 -aet 200 ";
	setAttr ".st" 6;
createNode polyCube -n "polyCube1";
	rename -uid "F6FCD0E0-4365-D844-E6FF-4CA04ED65A44";
	setAttr ".cuv" 4;
createNode polyExtrudeEdge -n "polyExtrudeEdge1";
	rename -uid "7C6E15C3-44AE-24DE-B0E0-52A886AE0A65";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 4 "e[5]" "e[7]" "e[9]" "e[11]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 1.8170201 -0.47718117 0 ;
	setAttr ".rs" 39388;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 1.8170200377950187 -0.97718117311413721 -0.5 ;
	setAttr ".cbx" -type "double3" 1.8170200377950187 0.022818826885862786 0.5 ;
createNode deleteComponent -n "deleteComponent1";
	rename -uid "444169EC-4B17-E379-5CA4-63A688CB5D3A";
	setAttr ".dc" -type "componentList" 1 "f[4]";
createNode deleteComponent -n "deleteComponent2";
	rename -uid "4C09D758-472D-037E-7EFF-8A879066319A";
	setAttr ".dc" -type "componentList" 1 "f[4]";
createNode polyExtrudeEdge -n "polyExtrudeEdge2";
	rename -uid "A100555B-406D-7C70-3FBC-8F8EC57007E7";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 4 "e[4]" "e[6]" "e[8]" "e[10]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 0.81702006 -0.39931163 0 ;
	setAttr ".rs" 55858;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 0.81702003779501875 -0.98775253370221094 -0.58844089508056641 ;
	setAttr ".cbx" -type "double3" 0.81702003779501875 0.18912925645892187 0.58844089508056641 ;
createNode polyTweak -n "polyTweak1";
	rename -uid "F5CAAA66-45E6-4A4D-FE75-08874DC4E450";
	setAttr ".uopa" yes;
	setAttr -s 8 ".tk";
	setAttr ".tk[0]" -type "float3" 0 -0.010571349 0.088440903 ;
	setAttr ".tk[2]" -type "float3" 0 0.16631046 0.088440903 ;
	setAttr ".tk[4]" -type "float3" 0 0.16631046 -0.088440903 ;
	setAttr ".tk[6]" -type "float3" 0 -0.010571349 -0.088440903 ;
	setAttr ".tk[8]" -type "float3" -1.1920929e-07 2.2351742e-08 0 ;
	setAttr ".tk[9]" -type "float3" -1.1920929e-07 2.2351742e-08 0 ;
	setAttr ".tk[10]" -type "float3" -1.1920929e-07 2.2351742e-08 0 ;
	setAttr ".tk[11]" -type "float3" -1.1920929e-07 2.2351742e-08 0 ;
createNode polyExtrudeEdge -n "polyExtrudeEdge3";
	rename -uid "5434DE43-471D-4687-8B4B-87BEB082AB03";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[22]" "e[24]" "e[26:27]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 0.14066134 -0.37906137 0 ;
	setAttr ".rs" 41285;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 0.14066133799643477 -0.96750227287228541 -0.58844089508056641 ;
	setAttr ".cbx" -type "double3" 0.14066133799643477 0.20937951728884741 0.58844089508056641 ;
createNode polyTweak -n "polyTweak2";
	rename -uid "4A11DE65-4116-B120-8572-5889EC162911";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[12:15]" -type "float3"  -0.67635876 0.020250252 1.8626451e-09
		 -0.67635876 0.02025024 1.8626451e-09 -0.67635876 0.02025024 -1.8626451e-09 -0.67635876
		 0.020250252 -1.8626451e-09;
createNode polyExtrudeEdge -n "polyExtrudeEdge4";
	rename -uid "F4E541F4-4CBC-061C-70DD-E0BA24AAD285";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[30]" "e[32]" "e[34:35]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" -0.48709682 -0.41956192 0 ;
	setAttr ".rs" 44541;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -0.48709680733590166 -0.88535312488491968 -0.46579122543334961 ;
	setAttr ".cbx" -type "double3" -0.48709680733590166 0.046229266377134759 0.46579122543334961 ;
createNode polyTweak -n "polyTweak3";
	rename -uid "33F6BE6A-4AD9-C929-35D6-D98465BDEA49";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[16:19]" -type "float3"  -0.62775815 0.082149118 -0.12264965
		 -0.62775815 -0.16315028 -0.12264965 -0.62775815 -0.16315028 0.12264965 -0.62775815
		 0.082149118 0.12264965;
createNode polyTweak -n "polyTweak4";
	rename -uid "D6B17B2D-4BC7-4A09-DB5B-CC8AF73C9001";
	setAttr ".uopa" yes;
	setAttr -s 12 ".tk";
	setAttr ".tk[1]" -type "float3" -0.27526149 0 0 ;
	setAttr ".tk[3]" -type "float3" -0.27526149 0 0 ;
	setAttr ".tk[5]" -type "float3" -0.27526149 0 0 ;
	setAttr ".tk[7]" -type "float3" -0.27526149 0 0 ;
	setAttr ".tk[8]" -type "float3" 0 8.9406967e-08 -1.4901161e-07 ;
	setAttr ".tk[9]" -type "float3" 0 -8.9406967e-08 -1.4901161e-07 ;
	setAttr ".tk[10]" -type "float3" 0 -1.1920929e-07 1.4901161e-07 ;
	setAttr ".tk[11]" -type "float3" 0 1.1920929e-07 1.4901161e-07 ;
	setAttr ".tk[20]" -type "float3" -5.9604645e-08 -8.9406967e-08 5.9604645e-08 ;
	setAttr ".tk[21]" -type "float3" -5.9604645e-08 8.9406967e-08 5.9604645e-08 ;
	setAttr ".tk[22]" -type "float3" -5.9604645e-08 8.9406967e-08 -5.9604645e-08 ;
	setAttr ".tk[23]" -type "float3" -5.9604645e-08 -8.9406967e-08 -5.9604645e-08 ;
createNode deleteComponent -n "deleteComponent3";
	rename -uid "7977BC5C-495F-64CD-1856-83B7F86CB087";
	setAttr ".dc" -type "componentList" 3 "e[14]" "e[16]" "e[18:19]";
createNode deleteComponent -n "deleteComponent4";
	rename -uid "70A879C7-4409-4E12-6CC7-23A3EE8357EF";
	setAttr ".dc" -type "componentList" 1 "f[4:7]";
createNode polyExtrudeEdge -n "polyExtrudeEdge5";
	rename -uid "87028F37-4792-CE2C-6C8A-5DBE2683E669";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[22]" "e[24]" "e[26:27]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" -0.48709682 -0.41956192 0 ;
	setAttr ".rs" 61110;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -0.48709680733590166 -0.8853530950825973 -0.46579122543334961 ;
	setAttr ".cbx" -type "double3" -0.48709680733590166 0.046229266377134759 0.46579122543334961 ;
createNode polyExtrudeEdge -n "polyExtrudeEdge6";
	rename -uid "3205D3B1-47D4-61D6-C979-85A1ED5B4337";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 4 "e[5]" "e[7]" "e[9]" "e[11]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 1.5417585 -0.47718117 0 ;
	setAttr ".rs" 50820;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 1.541758576060247 -0.97718117311413721 -0.5 ;
	setAttr ".cbx" -type "double3" 1.541758576060247 0.022818826885862786 0.5 ;
createNode polyTweak -n "polyTweak5";
	rename -uid "87EA40AC-42DE-8D29-5FA4-0D8D9C8C39B4";
	setAttr ".uopa" yes;
	setAttr -s 8 ".tk";
	setAttr ".tk[1]" -type "float3" 5.9604645e-08 0 0 ;
	setAttr ".tk[3]" -type "float3" 5.9604645e-08 0 0 ;
	setAttr ".tk[5]" -type "float3" 5.9604645e-08 0 0 ;
	setAttr ".tk[7]" -type "float3" 5.9604645e-08 0 0 ;
	setAttr ".tk[20]" -type "float3" -0.31338096 0.35383704 -0.3538371 ;
	setAttr ".tk[21]" -type "float3" -0.31338096 -0.35383704 -0.3538371 ;
	setAttr ".tk[22]" -type "float3" -0.31338096 -0.35383704 0.3538371 ;
	setAttr ".tk[23]" -type "float3" -0.31338096 0.35383704 0.3538371 ;
createNode polyExtrudeEdge -n "polyExtrudeEdge7";
	rename -uid "33FDC495-4572-2597-6922-A2AF6C7BEB7D";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[46]" "e[48]" "e[50:51]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 1.9153748 -0.52433145 0 ;
	setAttr ".rs" 37768;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 1.9153747350224968 -0.97625217512066798 -0.45192071795463562 ;
	setAttr ".cbx" -type "double3" 1.9153747350224968 -0.072410709409074347 0.45192071795463562 ;
createNode polyTweak -n "polyTweak6";
	rename -uid "2A1370CA-4584-CEC3-E409-4E9FF9C1EF28";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[24:27]" -type "float3"  0.37361622 0.00092900544 -0.048079286
		 0.37361622 -0.095229529 -0.048079286 0.37361622 -0.095229529 0.048079286 0.37361622
		 0.00092900544 0.048079286;
createNode polyExtrudeEdge -n "polyExtrudeEdge8";
	rename -uid "F39E89E3-45D4-855F-7E34-D18DFC86BEF7";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[54]" "e[56]" "e[58:59]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 2.3763342 -0.48269859 0 ;
	setAttr ".rs" 40938;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 2.3763341695317743 -0.93430975749905543 -0.45161113142967224 ;
	setAttr ".cbx" -type "double3" 2.3763341695317743 -0.031087435035066169 0.45161113142967224 ;
createNode polyTweak -n "polyTweak7";
	rename -uid "22B9833D-4B43-959E-3D4C-84A2B6A3EC06";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[28:31]" -type "float3"  0.46095946 0.041942462 -0.00030959444
		 0.46095946 0.041323289 -0.00030959444 0.46095946 0.041323289 0.00030959444 0.46095946
		 0.041942462 0.00030959444;
createNode polyExtrudeEdge -n "polyExtrudeEdge9";
	rename -uid "7001FC3F-4196-B0FE-24EE-F5A77C717007";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[62]" "e[64]" "e[66:67]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 2.7580476 -0.6083101 0 ;
	setAttr ".rs" 65149;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 2.699170687819433 -0.9196749396603866 -0.31688258051872253 ;
	setAttr ".cbx" -type "double3" 2.8169246703633783 -0.29694528057988123 0.31688258051872253 ;
createNode polyTweak -n "polyTweak8";
	rename -uid "68D54650-4990-CD27-C044-5E91073CC353";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[32:35]" -type "float3"  0.32283646 0.014634787 -0.13472855
		 0.44059056 -0.26585785 -0.13472855 0.44059056 -0.26585785 0.13472855 0.32283646 0.014634787
		 0.13472855;
createNode polyExtrudeEdge -n "polyExtrudeEdge10";
	rename -uid "62C0CB15-4512-327E-DB60-1DBA29FBD134";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[70]" "e[72]" "e[74:75]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 3.1133921 -0.75981456 0 ;
	setAttr ".rs" 33508;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 3.0545151025304316 -0.93685821369107203 -0.18018114566802979 ;
	setAttr ".cbx" -type "double3" 3.1722690850743769 -0.58277089074070887 0.18018114566802979 ;
createNode polyTweak -n "polyTweak9";
	rename -uid "CFE50A24-40D5-E942-1B5E-039218A4259D";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[36:39]" -type "float3"  0.35534453 -0.017183267 -0.13670143
		 0.35534453 -0.28582561 -0.13670143 0.35534453 -0.28582561 0.13670143 0.35534453 -0.017183267
		 0.13670143;
createNode polyExtrudeEdge -n "polyExtrudeEdge11";
	rename -uid "CAC547A1-4178-AA8D-180C-67B0A7553781";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[38]" "e[40]" "e[42:43]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" -0.80047786 -0.41956192 0 ;
	setAttr ".rs" 57414;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -0.80047788319497148 -0.53151608183796839 -0.11195412278175354 ;
	setAttr ".cbx" -type "double3" -0.80047788319497148 -0.30760777666981653 0.11195412278175354 ;
createNode polyTweak -n "polyTweak10";
	rename -uid "E262D72B-47FB-1C05-E016-0595F9CF362F";
	setAttr ".uopa" yes;
	setAttr -s 8 ".tk";
	setAttr ".tk[20]" -type "float3" 1.0430813e-07 0 0 ;
	setAttr ".tk[21]" -type "float3" 1.0430813e-07 0 0 ;
	setAttr ".tk[22]" -type "float3" 1.0430813e-07 0 0 ;
	setAttr ".tk[23]" -type "float3" 1.0430813e-07 0 0 ;
	setAttr ".tk[40]" -type "float3" 0.22557849 0.029003009 -0.1469229 ;
	setAttr ".tk[41]" -type "float3" 0.22557849 -0.23257999 -0.1469229 ;
	setAttr ".tk[42]" -type "float3" 0.22557849 -0.23257999 0.11929581 ;
	setAttr ".tk[43]" -type "float3" 0.22557849 0.029003009 0.11929581 ;
createNode polyExtrudeEdge -n "polyExtrudeEdge12";
	rename -uid "58BFB3A2-4F80-F201-26CA-F3B3645217F2";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[86]" "e[88]" "e[90:91]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" -1.3317932 -0.48874363 0 ;
	setAttr ".rs" 58039;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -1.3317932098856453 -0.58810814395363764 -0.099364496767520905 ;
	setAttr ".cbx" -type "double3" -1.3317932098856453 -0.38937914296801523 0.099364496767520905 ;
createNode polyTweak -n "polyTweak11";
	rename -uid "54696F06-4947-8C7E-E0E5-FE89627E9505";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[44:47]" -type "float3"  -0.53131539 -0.056592066 -0.012589627
		 -0.53131539 -0.081771366 -0.012589627 -0.53131539 -0.081771366 0.012589627 -0.53131539
		 -0.056592066 0.012589627;
createNode polyExtrudeEdge -n "polyExtrudeEdge13";
	rename -uid "5FC09192-4271-03EB-FD36-D799C9752EB4";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[94]" "e[96]" "e[98:99]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" -1.9931701 -0.50257999 0 ;
	setAttr ".rs" 39579;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -2.0145749062052252 -0.58412129357274012 -0.083501756191253662 ;
	setAttr ".cbx" -type "double3" -1.9717654198160652 -0.42103867158110575 0.083501756191253662 ;
createNode polyTweak -n "polyTweak12";
	rename -uid "C34C9828-4E04-509F-0475-66A7BEF93519";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[48:51]" -type "float3"  -0.68278176 0.0039868373 -0.015862744
		 -0.63997215 -0.031659521 -0.015862744 -0.63997215 -0.031659521 0.015862744 -0.68278176
		 0.0039868373 0.015862744;
createNode polyExtrudeEdge -n "polyExtrudeEdge14";
	rename -uid "6FB55C52-4EA7-BFDC-0025-2DB4953DE990";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[102]" "e[104]" "e[106:107]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" -2.5798311 -0.39188921 0 ;
	setAttr ".rs" 47357;
	setAttr ".lt" -type "double3" -2.2204269286129076e-16 0.51819536142769718 2.4286128663675299e-17 ;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -2.613827130173731 -0.46438041254694895 -0.07846406102180481 ;
	setAttr ".cbx" -type "double3" -2.5458349197855474 -0.31939802244122462 0.07846406102180481 ;
createNode polyTweak -n "polyTweak13";
	rename -uid "D323D963-41FA-FE54-75BC-028EF7C59BCA";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[52:55]" -type "float3"  -0.59925228 0.11974088 -0.0050376975
		 -0.57406944 0.10164063 -0.0050376975 -0.57406944 0.10164063 0.0050376975 -0.59925228
		 0.11974088 0.0050376975;
createNode polyExtrudeEdge -n "polyExtrudeEdge15";
	rename -uid "66CA1B56-4EC0-E595-1F14-24A5A1602353";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[110]" "e[112]" "e[114:115]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" -3.1326544 -0.17856596 0 ;
	setAttr ".rs" 41792;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -3.1661232918253424 -0.24012238457615809 -0.067356720566749573 ;
	setAttr ".cbx" -type "double3" -3.0991853683939459 -0.11700955703671412 0.067356720566749573 ;
createNode polyTweak -n "polyTweak14";
	rename -uid "490352DC-4D61-284B-CC23-F7B554344FA4";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[56:59]" -type "float3"  -0.063646995 0.063481562 -0.0089028813
		 -0.063646995 0.047209121 -0.0089028813 -0.063646995 0.047209121 0.0089028813 -0.063646995
		 0.063481562 0.0089028813;
createNode polyExtrudeEdge -n "polyExtrudeEdge16";
	rename -uid "1FE9EC30-40CA-2041-EA45-0EB093B3C47D";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[118]" "e[120]" "e[122:123]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" -3.3857911 -0.12447698 0 ;
	setAttr ".rs" 52741;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -3.4022249191751959 -0.19258937910016016 -0.067356720566749573 ;
	setAttr ".cbx" -type "double3" -3.3693570106974127 -0.056364572791413825 0.067356720566749573 ;
createNode polyTweak -n "polyTweak15";
	rename -uid "D51D62CE-45B5-5087-1EAC-CD80FEC88A24";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[60:63]" -type "float3"  -0.23610139 0.047533013 0
		 -0.27017185 0.060644977 -3.7252903e-09 -0.27017179 0.060644969 0 -0.23610142 0.047533013
		 0;
createNode polyExtrudeEdge -n "polyExtrudeEdge17";
	rename -uid "7F80D262-43F8-CE58-8BB9-2F9B78A9DAA4";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[126]" "e[128]" "e[130:131]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" -3.6692173 -0.020626061 0 ;
	setAttr ".rs" 54868;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -3.7001384705057623 -0.071708626298265021 -0.054723702371120453 ;
	setAttr ".cbx" -type "double3" -3.6382960289469244 0.030456506462736566 0.054723702371120453 ;
createNode polyTweak -n "polyTweak16";
	rename -uid "BF1DE0EE-4B65-F5B2-3EEF-DDA6D7869548";
	setAttr ".uopa" yes;
	setAttr -s 8 ".tk[60:67]" -type "float3"  0 0.0072601354 -0.0071795862
		 0 -0.0072601354 -0.0071795862 0 -0.0072601354 0.0071795862 0 0.0072601354 0.0071795862
		 -0.29791352 0.12088076 -0.012633018 -0.26893923 0.086821064 -0.012633018 -0.26893923
		 0.086821064 0.012633018 -0.29791352 0.12088076 0.012633018;
createNode polyExtrudeEdge -n "polyExtrudeEdge18";
	rename -uid "ED5721EE-4932-C2C6-39B6-5F89EA738298";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[134]" "e[136]" "e[138:139]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" -4.0413499 0.012430542 -1.8626451e-09 ;
	setAttr ".rs" 41520;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -4.0420307129374029 -0.034355974940614264 -0.042880617082118988 ;
	setAttr ".cbx" -type "double3" -4.0406688660135748 0.059217058869047601 0.04288061335682869 ;
createNode polyTweak -n "polyTweak17";
	rename -uid "56EB9101-49A6-3283-6BB4-518BCD2487BC";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[68:71]" -type "float3"  -0.34189236 0.037352666 -0.011843089
		 -0.4023729 0.028760552 -0.011843088 -0.40237296 0.028760523 0.011843087 -0.34189242
		 0.037352651 0.011843088;
createNode polyExtrudeEdge -n "polyExtrudeEdge19";
	rename -uid "F3DCA635-407A-30C2-F499-0BB26B0B6B65";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 3 "e[142]" "e[144]" "e[146:147]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" -4.446733 0.048017554 -1.8626451e-09 ;
	setAttr ".rs" 61077;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" -4.4474138229837896 0.014177166672392327 -0.031015254557132721 ;
	setAttr ".cbx" -type "double3" -4.4460519760599615 0.081857942791624505 0.031015250831842422 ;
createNode polyTweak -n "polyTweak18";
	rename -uid "C2A4A52D-4902-C94D-D296-789D43FF7E72";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[72:75]" -type "float3"  -0.40538296 0.048533153 -0.011865362
		 -0.40538296 0.022640888 -0.011865362 -0.40538296 0.022640903 0.011865362 -0.40538296
		 0.048533153 0.01186536;
createNode polyMergeVert -n "polyMergeVert1";
	rename -uid "580DB505-4E63-0052-3631-F1A642D314D0";
	setAttr ".ics" -type "componentList" 1 "vtx[76:79]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".d" 1e-06;
createNode polyTweak -n "polyTweak19";
	rename -uid "9ADDBF35-48DB-9814-604B-A6AFF3959C52";
	setAttr ".uopa" yes;
	setAttr -s 8 ".tk[72:79]" -type "float3"  0 0.01143931 -0.010484311
		 0 -0.011439311 -0.010484311 0 -0.011439294 0.010484311 0 0.01143931 0.010484311 -0.10553612
		 0.055083796 -0.031015253 -0.10689797 -0.012596958 -0.031015253 -0.10689797 -0.012596918
		 0.031015253 -0.10553612 0.055083796 0.031015253;
createNode polySplit -n "polySplit1";
	rename -uid "441E8D50-4BA1-3703-C844-6EBDAFF7E02B";
	setAttr -s 10 ".e[0:9]"  0.58077103 0.59723502 0.603809 0.59220499
		 0.57363701 0.61321598 0.61520803 0.625337 0.49566999 0;
	setAttr -s 10 ".d[0:9]"  -2147483566 -2147483574 -2147483582 -2147483590 -2147483598 -2147483639 
		-2147483640 -2147483630 -2147483622 -2147483606;
	setAttr ".sma" 180;
	setAttr ".m2015" yes;
createNode polySplit -n "polySplit2";
	rename -uid "0113DBC1-4191-220C-8573-818BB053624D";
	setAttr -s 10 ".e[0:9]"  1 0.48721501 0.39893001 0.42394999 0.44570199
		 0.46332499 0.421442 0.43751201 0.48549199 0.49232501;
	setAttr -s 10 ".d[0:9]"  -2147483611 -2147483626 -2147483634 -2147483644 -2147483643 -2147483602 
		-2147483594 -2147483586 -2147483578 -2147483570;
	setAttr ".sma" 180;
	setAttr ".m2015" yes;
createNode polySplitRing -n "polySplitRing1";
	rename -uid "53EB7BEC-4DAF-708B-5A63-5B96FA73BDB3";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 9 "e[6:7]" "e[16]" "e[24]" "e[32]" "e[48]" "e[56]" "e[64]" "e[72]" "e[80]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".wt" 0.47727903723716736;
	setAttr ".dr" no;
	setAttr ".re" 80;
	setAttr ".sma" 29.999999999999996;
	setAttr ".p[0]"  0 0 1;
	setAttr ".fq" yes;
createNode polyTweak -n "polyTweak20";
	rename -uid "D5DED11D-4D75-4F48-B03E-D3BBD8728FCC";
	setAttr ".uopa" yes;
	setAttr -s 18 ".tk[77:94]" -type "float3"  0 0 -0.0096765487 0 0 -0.02863632
		 0 0 -0.050362367 0 0 -0.071774855 0 0 -0.071824074 0 0 -0.079465345 0 0 -0.093521342
		 0 0 -0.093521342 0 0 -0.074028522 0 0 0.074028522 0 0 0.093521342 0 0 0.093521342
		 0 0 0.079465345 0 0 0.071824074 0 0 0.071774855 0 0 0.050362367 0 0 0.02863632 0
		 0 0.0052857571;
createNode polySplitRing -n "polySplitRing2";
	rename -uid "379F1D37-4649-8F47-FF67-3D8395E9BDC1";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 9 "e[10:11]" "e[19]" "e[27]" "e[35]" "e[51]" "e[59]" "e[67]" "e[75]" "e[83]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".wt" 0.52717846632003784;
	setAttr ".dr" no;
	setAttr ".re" 19;
	setAttr ".sma" 29.999999999999996;
	setAttr ".p[0]"  0 0 1;
	setAttr ".fq" yes;
createNode polyTweak -n "polyTweak21";
	rename -uid "965D24F4-4FAD-7D1D-3DD0-E5A0EDF8AF07";
	setAttr ".uopa" yes;
	setAttr -s 9 ".tk[95:103]" -type "float3"  0 0.061624922 0 0 0.061624922
		 0 0 0.061624922 0 0 0.061624922 0 0 0.061624922 0 0 0.061624922 0 0 0.061624922 0
		 0 0.061624922 0 0 0.061624922 0;
createNode polyExtrudeEdge -n "polyExtrudeEdge20";
	rename -uid "E04FB06C-4A50-7C81-6D7C-D9B15CC54ED6";
	setAttr ".uopa" yes;
	setAttr ".ics" -type "componentList" 7 "e[78]" "e[80]" "e[82:83]" "e[152]" "e[178]" "e[188]" "e[207]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 3.3389707 -0.85941678 -0.016008938 ;
	setAttr ".rs" 43152;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 3.2800936490544794 -0.9651076264661117 -0.070561878383159637 ;
	setAttr ".cbx" -type "double3" 3.3978477508077143 -0.75372595265324549 0.038544002920389175 ;
createNode polyTweak -n "polyTweak22";
	rename -uid "796BA8F3-4434-223F-4950-D892DD7957CA";
	setAttr ".uopa" yes;
	setAttr -s 10 ".tk[105:114]" -type "float3"  0 -0.057252456 0 0 -0.057252456
		 0 0 -0.057252456 0 0 -0.057252456 0 0 -0.057252456 0 0 -0.057252456 0 0 -0.057252456
		 0 0 -0.057252456 0 0 -0.057252456 0 0 -0.057252456 0;
createNode polyMergeVert -n "polyMergeVert2";
	rename -uid "0117E804-4053-9B09-9902-B7A386A8C66D";
	setAttr ".ics" -type "componentList" 1 "vtx[115:122]";
	setAttr ".ix" -type "matrix" 1 0 0 0 0 1 0 0 0 0 1 0 1.3170200377950187 -0.47718117311413721 0 1;
	setAttr ".d" 1e-06;
createNode polyTweak -n "polyTweak23";
	rename -uid "C23F1FA5-4DBE-7DB1-F0CD-FB9AC1FA383F";
	setAttr ".uopa" yes;
	setAttr -s 8 ".tk[115:122]" -type "float3"  0.13458079 0.01258205 -0.04858733
		 0.076607175 -0.032960042 -0.053873092 0.016826577 -0.079922207 -0.04858733 0.016826577
		 -0.14154713 -0.0036545752 0.016826577 -0.079922207 0.045556247 0.085214563 -0.026198393
		 0.055232793 0.13458079 0.01258205 0.045556247 0.13458079 0.06983453 -0.0040742215;
createNode polyCube -n "polyCube2";
	rename -uid "1C90FEF6-4793-6D40-C3BE-04B10798442C";
	setAttr ".cuv" 4;
createNode deleteComponent -n "deleteComponent5";
	rename -uid "F61A8C71-4A2D-88AF-A02C-909E2C6AE5B4";
	setAttr ".dc" -type "componentList" 2 "f[0:3]" "f[5]";
createNode polyExtrudeFace -n "polyExtrudeFace1";
	rename -uid "CC517B11-4065-9BF3-3400-43841BC30BD8";
	setAttr ".ics" -type "componentList" 1 "f[0]";
	setAttr ".ix" -type "matrix" 0.199875347712755 0.065666855288768311 0.038731042681181216 0
		 -0.056278097494045082 0.053773772551766366 0.19925747489613507 0 0.051429614942543334 -0.19636351411608291 0.067518510090395695 0
		 2.5205428779795751 -0.16689296283628863 0.3430881578358409 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 2.5767813 -0.068409674 0.36818531 ;
	setAttr ".rs" 44176;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 2.4966413476195979 -0.29040043024496265 0.23658139352260588 ;
	setAttr ".cbx" -type "double3" 2.6539474586767979 0.1649342137296288 0.49460671214977409 ;
createNode polyTweak -n "polyTweak24";
	rename -uid "9DE753E8-4B03-54F1-8F4E-9BA28BC61FC7";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[0:3]" -type "float3"  -0.18361895 -0.26736996 0.024633279
		 -3.1086245e-15 -0.065656863 0.082450233 -3.1086245e-15 0.57905072 -0.72715831 -3.1086245e-15
		 0.065656863 -0.082450233;
createNode polySphere -n "polySphere1";
	rename -uid "BCA4CA10-4729-2BEE-DD1A-C1B9C53A531F";
createNode polyCube -n "polyCube3";
	rename -uid "50446002-4077-8E1A-284F-658E04AC14DB";
	setAttr ".cuv" 4;
createNode polyExtrudeFace -n "polyExtrudeFace2";
	rename -uid "CE8DA795-4A27-FF4E-6BE1-6A96DF4D3C50";
	setAttr ".ics" -type "componentList" 1 "f[3]";
	setAttr ".ix" -type "matrix" 0.13148198215429246 -0.12398038191627654 0 0 0.12398038191627654 0.13148198215429246 0 0
		 0 0 0.1807170349782429 0 1.2348018938731007 -0.69666779102357179 4.1992190093998714 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 1.1728117 -0.76240879 4.1992192 ;
	setAttr ".rs" 54530;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 1.1070707118378162 -0.82439897305885634 4.1088604919107503 ;
	setAttr ".cbx" -type "double3" 1.2385526939921085 -0.70041859114257976 4.2895775268889924 ;
createNode polyExtrudeFace -n "polyExtrudeFace3";
	rename -uid "600165FD-4210-7A96-B4DC-6EA16736FBE4";
	setAttr ".ics" -type "componentList" 1 "f[3]";
	setAttr ".ix" -type "matrix" 0.13148198215429246 -0.12398038191627654 0 0 0.12398038191627654 0.13148198215429246 0 0
		 0 0 0.1807170349782429 0 1.2348018938731007 -0.69666779102357179 4.1992190093998714 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 1.0871321 -0.90582901 4.1992192 ;
	setAttr ".rs" 43217;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 1.0213909675422486 -0.96781925398212565 4.1088604919107503 ;
	setAttr ".cbx" -type "double3" 1.1528731342059835 -0.84383881652443782 4.2895778715793824 ;
createNode polyTweak -n "polyTweak25";
	rename -uid "7BD65A8F-47A3-A898-FAD5-67B5D3ADF3C1";
	setAttr ".uopa" yes;
	setAttr -s 5 ".tk";
	setAttr ".tk[8]" -type "float3" 0.19951737 -0.90266353 0 ;
	setAttr ".tk[9]" -type "float3" 0.19951737 -0.90266353 0 ;
	setAttr ".tk[10]" -type "float3" 0.19951737 -0.90266353 0 ;
	setAttr ".tk[11]" -type "float3" 0.19951737 -0.90266353 0 ;
createNode polyExtrudeFace -n "polyExtrudeFace4";
	rename -uid "487E85B5-404A-BFE3-838D-1DB957FCF73D";
	setAttr ".ics" -type "componentList" 1 "f[3]";
	setAttr ".ix" -type "matrix" 0.13148198215429246 -0.12398038191627654 0 0 0.12398038191627654 0.13148198215429246 0 0
		 0 0 0.1807170349782429 0 1.2348018938731007 -0.69666779102357179 4.1992190093998714 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 1.0579469 -0.9815703 4.1992192 ;
	setAttr ".rs" 63327;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 0.96789572062554186 -0.98901799965037751 4.1088604919107503 ;
	setAttr ".cbx" -type "double3" 1.1479981210567303 -0.97412261589649396 4.2895778715793824 ;
createNode polyTweak -n "polyTweak26";
	rename -uid "ECCAC772-445D-4DFA-E8AC-67AC08D3337D";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[12:15]" -type "float3"  0.27922094 -0.72759694 0 0.060849339
		 -0.10385194 0 0.060849339 -0.10385194 0 0.27922094 -0.72759694 0;
createNode polyExtrudeFace -n "polyExtrudeFace5";
	rename -uid "E0D59170-4087-BC89-37FB-CD95E51A1002";
	setAttr ".ics" -type "componentList" 1 "f[3]";
	setAttr ".ix" -type "matrix" 0.13148198215429246 -0.12398038191627654 0 0 0.12398038191627654 0.13148198215429246 0 0
		 0 0 0.1807170349782429 0 1.2348018938731007 -0.69666779102357179 4.1992190093998714 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 1.0842309 -1.1129899 4.1992192 ;
	setAttr ".rs" 60361;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 1.0294353304020105 -1.1370005457745602 4.1393938775447099 ;
	setAttr ".cbx" -type "double3" 1.1390263805107623 -1.0889791957009729 4.2590444859454228 ;
createNode polyTweak -n "polyTweak27";
	rename -uid "83B0099E-413A-751E-E86D-FD8A1326DD78";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[16:19]" -type "float3"  0.86607993 -0.42211819 0.16895686
		 0.3433581 -0.43649739 0.16895686 0.3433581 -0.43649739 -0.16895686 0.86607993 -0.42211819
		 -0.16895686;
createNode polyExtrudeFace -n "polyExtrudeFace6";
	rename -uid "6FD010C7-406D-B8B3-FA25-2EA082039219";
	setAttr ".ics" -type "componentList" 1 "f[3]";
	setAttr ".ix" -type "matrix" 0.13148198215429246 -0.12398038191627654 0 0 0.12398038191627654 0.13148198215429246 0 0
		 0 0 0.1807170349782429 0 1.2348018938731007 -0.69666779102357179 4.1992190093998714 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 1.1330439 -1.1449062 4.1992192 ;
	setAttr ".rs" 46024;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 1.1176239790900153 -1.2027101186162881 4.1393942006919495 ;
	setAttr ".cbx" -type "double3" 1.148463815630882 -1.0871022463977913 4.2590445074885723 ;
createNode polyTweak -n "polyTweak28";
	rename -uid "FE0F112A-4822-5260-A3CC-D69F1B5B70DD";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[20:23]" -type "float3"  0.60449243 0.070243381 0 0.03086831
		 0.043383449 0 0.03086831 0.043383449 0 0.60449243 0.070243381 0;
createNode polyExtrudeFace -n "polyExtrudeFace7";
	rename -uid "DEB6DA8A-4B59-FEC0-9625-F09DC2FBB316";
	setAttr ".ics" -type "componentList" 1 "f[3]";
	setAttr ".ix" -type "matrix" 0.13148198215429246 -0.12398038191627654 0 0 0.12398038191627654 0.13148198215429246 0 0
		 0 0 0.1807170349782429 0 1.2348018938731007 -0.69666779102357179 4.1992190093998714 1;
	setAttr ".ws" yes;
	setAttr ".pvt" -type "float3" 1.2391183 -1.1439675 4.1992192 ;
	setAttr ".rs" 52627;
	setAttr ".c[0]"  0 1 1;
	setAttr ".cbn" -type "double3" 1.2286598531693678 -1.1831724584398506 4.1586434785849962 ;
	setAttr ".cbx" -type "double3" 1.2495767392788106 -1.1047624643724794 4.2397952295955257 ;
createNode polyTweak -n "polyTweak29";
	rename -uid "5178AD52-44B0-1C4D-37A5-79A1085CF12E";
	setAttr ".uopa" yes;
	setAttr -s 4 ".tk[24:27]" -type "float3"  0.37285489 0.5001775 0.10651612
		 0.47411764 0.31275067 0.10651612 0.47411764 0.31275067 -0.10651612 0.37285489 0.5001775
		 -0.10651612;
createNode polyTweakUV -n "polyTweakUV1";
	rename -uid "0A7C7031-4F70-8A35-188E-7A8930E6D519";
	setAttr ".uopa" yes;
	setAttr -s 392 ".uvtk";
	setAttr ".uvtk[0:249]" -type "float2" -0.18007264 0.06542322 -0.33317265
		 0.06542322 -0.18007264 -0.087676734 -0.33317265 -0.087676734 -0.18007264 -0.24077675
		 -0.33317265 -0.24077675 -0.18007264 -0.39387676 -0.33317265 -0.39387676 -0.18007264
		 -0.5469768 -0.33317265 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768;
	setAttr ".uvtk[250:391]" 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.5628227
		 -0.5469768 0.049577318 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.25662264
		 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.25662264 -0.5469768 0.049577318
		 0.06542322 -0.5628227 0.06542322 -0.25662264 -0.5469768 0.049577318 0.06542322 -0.5628227
		 0.06542322 -0.25662264 -0.5469768 -0.20715848 -0.5469768 -0.19707593 -0.5469768 -0.19707593
		 0.06542322 -0.19305006 -0.5469768 -0.19305006 0.06542322 -0.2001563 -0.5469768 -0.2001563
		 0.06542322 -0.21152738 -0.5469768 -0.21152738 0.06542322 -0.33317265 -0.33466008
		 -0.18728921 0.06542322 -0.32717606 0.06542322 -0.18007264 -0.33496514 -0.33337906
		 0.06542322 -0.33337906 -0.5469768 -0.25397098 0.06542322 -0.25397098 0.06542322 -0.25397098
		 -0.5469768 -0.24879318 0.06542322 -0.24879318 0.06542322 -0.24879318 -0.5469768 -0.19472745
		 0.06542322 -0.19472745 -0.5469768 -0.21004969 0.06542322 -0.18007264 0.0005164668
		 -0.33317265 -0.0028137043 -0.28987476 0.06542322 -0.27908245 -0.5469768 -0.27908245
		 0.06542322 -0.30473158 -0.5469768 -0.30473158 0.06542322 -0.29489031 -0.5469768 -0.29489031
		 0.06542322 -0.26550731 -0.5469768 -0.26550731 0.06542322 -0.26132283 -0.5469768 -0.27053699
		 -0.5469768 -0.27053699 -0.5469768 -0.27053699 0.06542322 -0.27053699 -0.5469768 -0.27053699
		 0.06542322 -0.27053699 -0.5469768 -0.27053699 0.06542322 -0.27053699 -0.5469768 -0.27053699
		 0.06542322 -0.33317265 -0.16074818 -0.27053699 0.06542322 -0.24270838 0.06542322
		 -0.18007264 -0.16074818 -0.24270838 0.06542322 -0.24270838 -0.5469768 -0.24270838
		 0.06542322 -0.24270838 0.06542322 -0.24270838 -0.5469768 -0.24270838 -0.5469768 -0.23997858
		 -0.5469768 -0.23997858 -0.5469768 -0.23997858 0.06542322 -0.23997858 -0.5469768 -0.23997858
		 0.06542322 -0.23997858 -0.5469768 -0.23997858 0.06542322 -0.23997858 -0.5469768 -0.23997858
		 0.06542322 -0.33317265 -0.47458795 -0.23997858 0.06542322 -0.2732667 0.06542322 -0.18007264
		 -0.47458795 -0.2732667 0.06542322 -0.2732667 -0.5469768 -0.2732667 0.06542322 -0.2732667
		 0.06542322 -0.2732667 -0.5469768 -0.2732667 -0.5469768 0.049577318 0.06542322 -0.5628227
		 0.06542322 -0.25662264 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.25662264
		 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.25662264 -0.5469768 0.049577318
		 0.06542322 -0.5628227 0.06542322 -0.25662264 -0.5469768 0.049577318 0.06542322 -0.5628227
		 0.06542322 -0.25662264 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.25662264
		 -0.5469768 0.049577318 0.06542322 -0.5628227 0.06542322 -0.25662264 -0.5469768 0.049577318
		 0.06542322 -0.5628227 0.06542322 -0.25662264 -0.5469768;
createNode polyTweakUV -n "polyTweakUV2";
	rename -uid "84ECA9A3-4F19-EE80-F664-F2A220F6415D";
	setAttr ".uopa" yes;
	setAttr -s 38 ".uvtk[0:37]" -type "float2" 0.41743791 0.087271929 0.22366188
		 0.087271929 0.41743791 -0.10650411 0.22366188 -0.10650411 0.41743791 -0.30028018
		 0.22366188 -0.30028018 0.41743791 -0.49405622 0.22366188 -0.49405622 0.41743791 -0.68783236
		 0.22366188 -0.68783236 0.029885758 0.087271929 0.029885758 -0.10650411 0.61121398
		 0.087271929 0.61121398 -0.10650411 0.41743791 -0.49405622 0.22366188 -0.49405622
		 0.22366188 -0.68783236 0.41743791 -0.68783236 0.41743791 -0.49405622 0.22366188 -0.49405622
		 0.22366188 -0.68783236 0.41743791 -0.68783236 0.41743791 -0.49405622 0.22366188 -0.49405622
		 0.22366188 -0.68783236 0.41743791 -0.68783236 0.41743791 -0.49405622 0.22366188 -0.49405622
		 0.22366188 -0.68783236 0.41743791 -0.68783236 0.41743791 -0.49405622 0.22366188 -0.49405622
		 0.22366188 -0.68783236 0.41743791 -0.68783236 0.41743791 -0.49405622 0.22366188 -0.49405622
		 0.22366188 -0.68783236 0.41743791 -0.68783236;
createNode polyTweakUV -n "polyTweakUV3";
	rename -uid "0075758B-401C-455E-2E6F-7AA680E7C1F2";
	setAttr ".uopa" yes;
	setAttr -s 439 ".uvtk";
	setAttr ".uvtk[0:249]" -type "float2" 0.11906558 0.59189832 0.081208661 0.59189832
		 0.043351732 0.59189832 0.005494833 0.59189832 -0.032362089 0.59189832 -0.07021898
		 0.59189832 -0.10807592 0.59189832 -0.14593285 0.59189832 -0.18378976 0.59189832 -0.22164667
		 0.59189832 -0.2595036 0.59189832 -0.29736054 0.59189832 -0.33521742 0.59189832 -0.37307435
		 0.59189832 -0.41093129 0.59189832 -0.44878823 0.59189832 -0.48664516 0.59189832 -0.52450204
		 0.59189832 -0.56235898 0.59189832 -0.60021591 0.59189832 -0.63807279 0.59189832 0.11906558
		 0.55404145 0.081208661 0.55404145 0.043351732 0.55404145 0.005494833 0.55404145 -0.032362089
		 0.55404145 -0.07021898 0.55404145 -0.10807592 0.55404145 -0.14593285 0.55404145 -0.18378976
		 0.55404145 -0.22164667 0.55404145 -0.2595036 0.55404145 -0.29736054 0.55404145 -0.33521742
		 0.55404145 -0.37307435 0.55404145 -0.41093129 0.55404145 -0.44878823 0.55404145 -0.48664516
		 0.55404145 -0.52450204 0.55404145 -0.56235898 0.55404145 -0.60021591 0.55404145 -0.63807279
		 0.55404145 0.11906558 0.51618451 0.081208661 0.51618451 0.043351732 0.51618451 0.005494833
		 0.51618451 -0.032362089 0.51618451 -0.07021898 0.51618451 -0.10807592 0.51618451
		 -0.14593285 0.51618451 -0.18378976 0.51618451 -0.22164667 0.51618451 -0.2595036 0.51618451
		 -0.29736054 0.51618451 -0.33521742 0.51618451 -0.37307435 0.51618451 -0.41093129
		 0.51618451 -0.44878823 0.51618451 -0.48664516 0.51618451 -0.52450204 0.51618451 -0.56235898
		 0.51618451 -0.60021591 0.51618451 -0.63807279 0.51618451 0.11906558 0.47832766 0.081208661
		 0.47832766 0.043351732 0.47832766 0.005494833 0.47832766 -0.032362089 0.47832766
		 -0.07021898 0.47832766 -0.10807592 0.47832766 -0.14593285 0.47832766 -0.18378976
		 0.47832766 -0.22164667 0.47832766 -0.2595036 0.47832766 -0.29736054 0.47832766 -0.33521742
		 0.47832766 -0.37307435 0.47832766 -0.41093129 0.47832766 -0.44878823 0.47832766 -0.48664516
		 0.47832766 -0.52450204 0.47832766 -0.56235898 0.47832766 -0.60021591 0.47832766 -0.63807279
		 0.47832766 0.11906558 0.44047073 0.081208661 0.44047073 0.043351732 0.44047073 0.005494833
		 0.44047073 -0.032362089 0.44047073 -0.07021898 0.44047073 -0.10807592 0.44047073
		 -0.14593285 0.44047073 -0.18378976 0.44047073 -0.22164667 0.44047073 -0.2595036 0.44047073
		 -0.29736054 0.44047073 -0.33521742 0.44047073 -0.37307435 0.44047073 -0.41093129
		 0.44047073 -0.44878823 0.44047073 -0.48664516 0.44047073 -0.52450204 0.44047073 -0.56235898
		 0.44047073 -0.60021591 0.44047073 -0.63807279 0.44047073 0.11906558 0.40261382 0.081208661
		 0.40261382 0.043351732 0.40261382 0.005494833 0.40261382 -0.032362089 0.40261382
		 -0.07021898 0.40261382 -0.10807592 0.40261382 -0.14593285 0.40261382 -0.18378976
		 0.40261382 -0.22164667 0.40261382 -0.2595036 0.40261382 -0.29736054 0.40261382 -0.33521742
		 0.40261382 -0.37307435 0.40261382 -0.41093129 0.40261382 -0.44878823 0.40261382 -0.48664516
		 0.40261382 -0.52450204 0.40261382 -0.56235898 0.40261382 -0.60021591 0.40261382 -0.63807279
		 0.40261382 0.11906558 0.36475688 0.081208661 0.36475688 0.043351732 0.36475688 0.005494833
		 0.36475688 -0.032362089 0.36475688 -0.07021898 0.36475688 -0.10807592 0.36475688
		 -0.14593285 0.36475688 -0.18378976 0.36475688 -0.22164667 0.36475688 -0.2595036 0.36475688
		 -0.29736054 0.36475688 -0.33521742 0.36475688 -0.37307435 0.36475688 -0.41093129
		 0.36475688 -0.44878823 0.36475688 -0.48664516 0.36475688 -0.52450204 0.36475688 -0.56235898
		 0.36475688 -0.60021591 0.36475688 -0.63807279 0.36475688 0.11906558 0.32689995 0.081208661
		 0.32689995 0.043351732 0.32689995 0.005494833 0.32689995 -0.032362089 0.32689995
		 -0.07021898 0.32689995 -0.10807592 0.32689995 -0.14593285 0.32689995 -0.18378976
		 0.32689995 -0.22164667 0.32689995 -0.2595036 0.32689995 -0.29736054 0.32689995 -0.33521742
		 0.32689995 -0.37307435 0.32689995 -0.41093129 0.32689995 -0.44878823 0.32689995 -0.48664516
		 0.32689995 -0.52450204 0.32689995 -0.56235898 0.32689995 -0.60021591 0.32689995 -0.63807279
		 0.32689995 0.11906558 0.28904307 0.081208661 0.28904307 0.043351732 0.28904307 0.005494833
		 0.28904307 -0.032362089 0.28904307 -0.07021898 0.28904307 -0.10807592 0.28904307
		 -0.14593285 0.28904307 -0.18378976 0.28904307 -0.22164667 0.28904307 -0.2595036 0.28904307
		 -0.29736054 0.28904307 -0.33521742 0.28904307 -0.37307435 0.28904307 -0.41093129
		 0.28904307 -0.44878823 0.28904307 -0.48664516 0.28904307 -0.52450204 0.28904307 -0.56235898
		 0.28904307 -0.60021591 0.28904307 -0.63807279 0.28904307 0.11906558 0.25118607 0.081208661
		 0.25118607 0.043351732 0.25118607 0.005494833 0.25118607 -0.032362089 0.25118607
		 -0.07021898 0.25118607 -0.10807592 0.25118607 -0.14593285 0.25118607 -0.18378976
		 0.25118607 -0.22164667 0.25118607 -0.2595036 0.25118607 -0.29736054 0.25118607 -0.33521742
		 0.25118607 -0.37307435 0.25118607 -0.41093129 0.25118607 -0.44878823 0.25118607 -0.48664516
		 0.25118607 -0.52450204 0.25118607 -0.56235898 0.25118607 -0.60021591 0.25118607 -0.63807279
		 0.25118607 0.11906558 0.21332917 0.081208661 0.21332917 0.043351732 0.21332917 0.005494833
		 0.21332917 -0.032362089 0.21332917 -0.07021898 0.21332917 -0.10807592 0.21332917
		 -0.14593285 0.21332917 -0.18378976 0.21332917 -0.22164667 0.21332917 -0.2595036 0.21332917
		 -0.29736054 0.21332917 -0.33521742 0.21332917 -0.37307435 0.21332917 -0.41093129
		 0.21332917 -0.44878823 0.21332917 -0.48664516 0.21332917 -0.52450204 0.21332917 -0.56235898
		 0.21332917 -0.60021591 0.21332917 -0.63807279 0.21332917 0.11906558 0.17547232 0.081208661
		 0.17547232 0.043351732 0.17547232 0.005494833 0.17547232 -0.032362089 0.17547232
		 -0.07021898 0.17547232 -0.10807592 0.17547232 -0.14593285 0.17547232 -0.18378976
		 0.17547232 -0.22164667 0.17547232 -0.2595036 0.17547232 -0.29736054 0.17547232 -0.33521742
		 0.17547232 -0.37307435 0.17547232 -0.41093129 0.17547232 -0.44878823 0.17547232 -0.48664516
		 0.17547232 -0.52450204 0.17547232 -0.56235898 0.17547232;
	setAttr ".uvtk[250:438]" -0.60021591 0.17547232 -0.63807279 0.17547232 0.11906558
		 0.13761535 0.081208661 0.13761535 0.043351732 0.13761535 0.005494833 0.13761535 -0.032362089
		 0.13761535 -0.07021898 0.13761535 -0.10807592 0.13761535 -0.14593285 0.13761535 -0.18378976
		 0.13761535 -0.22164667 0.13761535 -0.2595036 0.13761535 -0.29736054 0.13761535 -0.33521742
		 0.13761535 -0.37307435 0.13761535 -0.41093129 0.13761535 -0.44878823 0.13761535 -0.48664516
		 0.13761535 -0.52450204 0.13761535 -0.56235898 0.13761535 -0.60021591 0.13761535 -0.63807279
		 0.13761535 0.11906558 0.099758402 0.081208661 0.099758402 0.043351732 0.099758402
		 0.005494833 0.099758402 -0.032362089 0.099758402 -0.07021898 0.099758402 -0.10807592
		 0.099758402 -0.14593285 0.099758402 -0.18378976 0.099758402 -0.22164667 0.099758402
		 -0.2595036 0.099758402 -0.29736054 0.099758402 -0.33521742 0.099758402 -0.37307435
		 0.099758402 -0.41093129 0.099758402 -0.44878823 0.099758402 -0.48664516 0.099758402
		 -0.52450204 0.099758402 -0.56235898 0.099758402 -0.60021591 0.099758402 -0.63807279
		 0.099758402 0.11906558 0.061901465 0.081208661 0.061901465 0.043351732 0.061901465
		 0.005494833 0.061901465 -0.032362089 0.061901465 -0.07021898 0.061901465 -0.10807592
		 0.061901465 -0.14593285 0.061901465 -0.18378976 0.061901465 -0.22164667 0.061901465
		 -0.2595036 0.061901465 -0.29736054 0.061901465 -0.33521742 0.061901465 -0.37307435
		 0.061901465 -0.41093129 0.061901465 -0.44878823 0.061901465 -0.48664516 0.061901465
		 -0.52450204 0.061901465 -0.56235898 0.061901465 -0.60021591 0.061901465 -0.63807279
		 0.061901465 0.11906558 0.024044588 0.081208661 0.024044588 0.043351732 0.024044588
		 0.005494833 0.024044588 -0.032362089 0.024044588 -0.07021898 0.024044588 -0.10807592
		 0.024044588 -0.14593285 0.024044588 -0.18378976 0.024044588 -0.22164667 0.024044588
		 -0.2595036 0.024044588 -0.29736054 0.024044588 -0.33521742 0.024044588 -0.37307435
		 0.024044588 -0.41093129 0.024044588 -0.44878823 0.024044588 -0.48664516 0.024044588
		 -0.52450204 0.024044588 -0.56235898 0.024044588 -0.60021591 0.024044588 -0.63807279
		 0.024044588 0.11906558 -0.013812348 0.081208661 -0.013812348 0.043351732 -0.013812348
		 0.005494833 -0.013812348 -0.032362089 -0.013812348 -0.07021898 -0.013812348 -0.10807592
		 -0.013812348 -0.14593285 -0.013812348 -0.18378976 -0.013812348 -0.22164667 -0.013812348
		 -0.2595036 -0.013812348 -0.29736054 -0.013812348 -0.33521742 -0.013812348 -0.37307435
		 -0.013812348 -0.41093129 -0.013812348 -0.44878823 -0.013812348 -0.48664516 -0.013812348
		 -0.52450204 -0.013812348 -0.56235898 -0.013812348 -0.60021591 -0.013812348 -0.63807279
		 -0.013812348 0.11906558 -0.051669285 0.081208661 -0.051669285 0.043351732 -0.051669285
		 0.005494833 -0.051669285 -0.032362089 -0.051669285 -0.07021898 -0.051669285 -0.10807592
		 -0.051669285 -0.14593285 -0.051669285 -0.18378976 -0.051669285 -0.22164667 -0.051669285
		 -0.2595036 -0.051669285 -0.29736054 -0.051669285 -0.33521742 -0.051669285 -0.37307435
		 -0.051669285 -0.41093129 -0.051669285 -0.44878823 -0.051669285 -0.48664516 -0.051669285
		 -0.52450204 -0.051669285 -0.56235898 -0.051669285 -0.60021591 -0.051669285 -0.63807279
		 -0.051669285 0.11906558 -0.089526162 0.081208661 -0.089526162 0.043351732 -0.089526162
		 0.005494833 -0.089526162 -0.032362089 -0.089526162 -0.07021898 -0.089526162 -0.10807592
		 -0.089526162 -0.14593285 -0.089526162 -0.18378976 -0.089526162 -0.22164667 -0.089526162
		 -0.2595036 -0.089526162 -0.29736054 -0.089526162 -0.33521742 -0.089526162 -0.37307435
		 -0.089526162 -0.41093129 -0.089526162 -0.44878823 -0.089526162 -0.48664516 -0.089526162
		 -0.52450204 -0.089526162 -0.56235898 -0.089526162 -0.60021591 -0.089526162 -0.63807279
		 -0.089526162 0.10013712 0.62975526 0.062280163 0.62975526 0.024423301 0.62975526
		 -0.013433635 0.62975526 -0.051290557 0.62975526 -0.089147449 0.62975526 -0.12700438
		 0.62975526 -0.16486126 0.62975526 -0.2027182 0.62975526 -0.2405751 0.62975526 -0.27843201
		 0.62975526 -0.31628889 0.62975526 -0.35414582 0.62975526 -0.39200276 0.62975526 -0.42985964
		 0.62975526 -0.46771657 0.62975526 -0.50557345 0.62975526 -0.54343039 0.62975526 -0.58128732
		 0.62975526 -0.6191442 0.62975526 0.10013712 -0.12738298 0.062280163 -0.12738298 0.024423301
		 -0.12738298 -0.013433635 -0.12738298 -0.051290557 -0.12738298 -0.089147449 -0.12738298
		 -0.12700438 -0.12738298 -0.16486126 -0.12738298 -0.2027182 -0.12738298 -0.2405751
		 -0.12738298 -0.27843201 -0.12738298 -0.31628889 -0.12738298 -0.35414582 -0.12738298
		 -0.39200276 -0.12738298 -0.42985964 -0.12738298 -0.46771657 -0.12738298 -0.50557345
		 -0.12738298 -0.54343039 -0.12738298 -0.58128732 -0.12738298 -0.6191442 -0.12738298;
createNode polyTweakUV -n "polyTweakUV4";
	rename -uid "CBE6D3CE-42AD-2E4E-2508-0A9C44B484C5";
	setAttr ".uopa" yes;
	setAttr -s 12 ".uvtk[0:11]" -type "float2" 0.043250591 0.69200957 0.043250591
		 0.69200957 0.043250591 0.69200957 0.043250591 0.69200957 0.043250591 0.69200957 0.043250591
		 0.69200957 0.043250591 0.69200957 0.043250591 0.69200957 0.043250591 0.69200957 0.043250591
		 0.69200957 0.043250591 0.69200957 0.043250591 0.69200957;
select -ne :time1;
	setAttr ".o" 1;
	setAttr ".unw" 1;
select -ne :hardwareRenderingGlobals;
	setAttr ".otfna" -type "stringArray" 22 "NURBS Curves" "NURBS Surfaces" "Polygons" "Subdiv Surface" "Particles" "Particle Instance" "Fluids" "Strokes" "Image Planes" "UI" "Lights" "Cameras" "Locators" "Joints" "IK Handles" "Deformers" "Motion Trails" "Components" "Hair Systems" "Follicles" "Misc. UI" "Ornaments"  ;
	setAttr ".otfva" -type "Int32Array" 22 0 1 1 1 1 1
		 1 1 1 0 0 0 0 0 0 0 0 0
		 0 0 0 0 ;
	setAttr ".fprt" yes;
	setAttr ".rtfm" 1;
select -ne :renderPartition;
	setAttr -s 2 ".st";
select -ne :renderGlobalsList1;
select -ne :defaultShaderList1;
	setAttr -s 5 ".s";
select -ne :postProcessList1;
	setAttr -s 2 ".p";
select -ne :defaultRenderingList1;
select -ne :standardSurface1;
	setAttr ".bc" -type "float3" 0.40000001 0.40000001 0.40000001 ;
	setAttr ".sr" 0.5;
select -ne :initialShadingGroup;
	setAttr -s 9 ".dsm";
	setAttr ".ro" yes;
select -ne :initialParticleSE;
	setAttr ".ro" yes;
select -ne :defaultRenderGlobals;
	addAttr -ci true -h true -sn "dss" -ln "defaultSurfaceShader" -dt "string";
	setAttr ".ren" -type "string" "arnold";
	setAttr ".dss" -type "string" "standardSurface1";
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
connectAttr ":defaultColorMgtGlobals.cme" "imagePlaneShape1.cme";
connectAttr ":defaultColorMgtGlobals.cfe" "imagePlaneShape1.cmcf";
connectAttr ":defaultColorMgtGlobals.cfp" "imagePlaneShape1.cmcp";
connectAttr ":defaultColorMgtGlobals.wsn" "imagePlaneShape1.ws";
connectAttr ":perspShape.msg" "imagePlaneShape1.ltc";
connectAttr "polyTweakUV1.out" "bodyShape.i";
connectAttr "polyTweakUV1.uvtk[0]" "bodyShape.uvst[0].uvtw";
connectAttr "polyTweakUV4.out" "|Rat|earR|earRShape.i";
connectAttr "polyTweakUV4.uvtk[0]" "|Rat|earR|earRShape.uvst[0].uvtw";
connectAttr "polyTweakUV3.out" "|Rat|eyeR|eyeRShape.i";
connectAttr "polyTweakUV3.uvtk[0]" "|Rat|eyeR|eyeRShape.uvst[0].uvtw";
connectAttr "polyTweakUV2.out" "|Rat|leg|legShape.i";
connectAttr "polyTweakUV2.uvtk[0]" "|Rat|leg|legShape.uvst[0].uvtw";
relationship "link" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "link" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialShadingGroup.message" ":defaultLightSet.message";
relationship "shadowLink" ":lightLinker1" ":initialParticleSE.message" ":defaultLightSet.message";
connectAttr "layerManager.dli[0]" "defaultLayer.id";
connectAttr "renderLayerManager.rlmi[0]" "defaultRenderLayer.rlid";
connectAttr ":defaultArnoldDisplayDriver.msg" ":defaultArnoldRenderOptions.drivers"
		 -na;
connectAttr ":defaultArnoldFilter.msg" ":defaultArnoldRenderOptions.filt";
connectAttr ":defaultArnoldDriver.msg" ":defaultArnoldRenderOptions.drvr";
connectAttr "polyCube1.out" "polyExtrudeEdge1.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge1.mp";
connectAttr "polyExtrudeEdge1.out" "deleteComponent1.ig";
connectAttr "deleteComponent1.og" "deleteComponent2.ig";
connectAttr "polyTweak1.out" "polyExtrudeEdge2.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge2.mp";
connectAttr "deleteComponent2.og" "polyTweak1.ip";
connectAttr "polyTweak2.out" "polyExtrudeEdge3.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge3.mp";
connectAttr "polyExtrudeEdge2.out" "polyTweak2.ip";
connectAttr "polyTweak3.out" "polyExtrudeEdge4.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge4.mp";
connectAttr "polyExtrudeEdge3.out" "polyTweak3.ip";
connectAttr "polyExtrudeEdge4.out" "polyTweak4.ip";
connectAttr "polyTweak4.out" "deleteComponent3.ig";
connectAttr "deleteComponent3.og" "deleteComponent4.ig";
connectAttr "deleteComponent4.og" "polyExtrudeEdge5.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge5.mp";
connectAttr "polyTweak5.out" "polyExtrudeEdge6.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge6.mp";
connectAttr "polyExtrudeEdge5.out" "polyTweak5.ip";
connectAttr "polyTweak6.out" "polyExtrudeEdge7.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge7.mp";
connectAttr "polyExtrudeEdge6.out" "polyTweak6.ip";
connectAttr "polyTweak7.out" "polyExtrudeEdge8.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge8.mp";
connectAttr "polyExtrudeEdge7.out" "polyTweak7.ip";
connectAttr "polyTweak8.out" "polyExtrudeEdge9.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge9.mp";
connectAttr "polyExtrudeEdge8.out" "polyTweak8.ip";
connectAttr "polyTweak9.out" "polyExtrudeEdge10.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge10.mp";
connectAttr "polyExtrudeEdge9.out" "polyTweak9.ip";
connectAttr "polyTweak10.out" "polyExtrudeEdge11.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge11.mp";
connectAttr "polyExtrudeEdge10.out" "polyTweak10.ip";
connectAttr "polyTweak11.out" "polyExtrudeEdge12.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge12.mp";
connectAttr "polyExtrudeEdge11.out" "polyTweak11.ip";
connectAttr "polyTweak12.out" "polyExtrudeEdge13.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge13.mp";
connectAttr "polyExtrudeEdge12.out" "polyTweak12.ip";
connectAttr "polyTweak13.out" "polyExtrudeEdge14.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge14.mp";
connectAttr "polyExtrudeEdge13.out" "polyTweak13.ip";
connectAttr "polyTweak14.out" "polyExtrudeEdge15.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge15.mp";
connectAttr "polyExtrudeEdge14.out" "polyTweak14.ip";
connectAttr "polyTweak15.out" "polyExtrudeEdge16.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge16.mp";
connectAttr "polyExtrudeEdge15.out" "polyTweak15.ip";
connectAttr "polyTweak16.out" "polyExtrudeEdge17.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge17.mp";
connectAttr "polyExtrudeEdge16.out" "polyTweak16.ip";
connectAttr "polyTweak17.out" "polyExtrudeEdge18.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge18.mp";
connectAttr "polyExtrudeEdge17.out" "polyTweak17.ip";
connectAttr "polyTweak18.out" "polyExtrudeEdge19.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge19.mp";
connectAttr "polyExtrudeEdge18.out" "polyTweak18.ip";
connectAttr "polyTweak19.out" "polyMergeVert1.ip";
connectAttr "bodyShape.wm" "polyMergeVert1.mp";
connectAttr "polyExtrudeEdge19.out" "polyTweak19.ip";
connectAttr "polyMergeVert1.out" "polySplit1.ip";
connectAttr "polySplit1.out" "polySplit2.ip";
connectAttr "polyTweak20.out" "polySplitRing1.ip";
connectAttr "bodyShape.wm" "polySplitRing1.mp";
connectAttr "polySplit2.out" "polyTweak20.ip";
connectAttr "polyTweak21.out" "polySplitRing2.ip";
connectAttr "bodyShape.wm" "polySplitRing2.mp";
connectAttr "polySplitRing1.out" "polyTweak21.ip";
connectAttr "polyTweak22.out" "polyExtrudeEdge20.ip";
connectAttr "bodyShape.wm" "polyExtrudeEdge20.mp";
connectAttr "polySplitRing2.out" "polyTweak22.ip";
connectAttr "polyTweak23.out" "polyMergeVert2.ip";
connectAttr "bodyShape.wm" "polyMergeVert2.mp";
connectAttr "polyExtrudeEdge20.out" "polyTweak23.ip";
connectAttr "polyCube2.out" "deleteComponent5.ig";
connectAttr "polyTweak24.out" "polyExtrudeFace1.ip";
connectAttr "|Rat|earR|earRShape.wm" "polyExtrudeFace1.mp";
connectAttr "deleteComponent5.og" "polyTweak24.ip";
connectAttr "polyCube3.out" "polyExtrudeFace2.ip";
connectAttr "|Rat|leg|legShape.wm" "polyExtrudeFace2.mp";
connectAttr "polyTweak25.out" "polyExtrudeFace3.ip";
connectAttr "|Rat|leg|legShape.wm" "polyExtrudeFace3.mp";
connectAttr "polyExtrudeFace2.out" "polyTweak25.ip";
connectAttr "polyTweak26.out" "polyExtrudeFace4.ip";
connectAttr "|Rat|leg|legShape.wm" "polyExtrudeFace4.mp";
connectAttr "polyExtrudeFace3.out" "polyTweak26.ip";
connectAttr "polyTweak27.out" "polyExtrudeFace5.ip";
connectAttr "|Rat|leg|legShape.wm" "polyExtrudeFace5.mp";
connectAttr "polyExtrudeFace4.out" "polyTweak27.ip";
connectAttr "polyTweak28.out" "polyExtrudeFace6.ip";
connectAttr "|Rat|leg|legShape.wm" "polyExtrudeFace6.mp";
connectAttr "polyExtrudeFace5.out" "polyTweak28.ip";
connectAttr "polyTweak29.out" "polyExtrudeFace7.ip";
connectAttr "|Rat|leg|legShape.wm" "polyExtrudeFace7.mp";
connectAttr "polyExtrudeFace6.out" "polyTweak29.ip";
connectAttr "polyMergeVert2.out" "polyTweakUV1.ip";
connectAttr "polyExtrudeFace7.out" "polyTweakUV2.ip";
connectAttr "polySphere1.out" "polyTweakUV3.ip";
connectAttr "polyExtrudeFace1.out" "polyTweakUV4.ip";
connectAttr "defaultRenderLayer.msg" ":defaultRenderingList1.r" -na;
connectAttr "bodyShape.iog" ":initialShadingGroup.dsm" -na;
connectAttr "|Rat|earR|earRShape.iog" ":initialShadingGroup.dsm" -na;
connectAttr "|Rat|earL|earRShape.iog" ":initialShadingGroup.dsm" -na;
connectAttr "|Rat|eyeR|eyeRShape.iog" ":initialShadingGroup.dsm" -na;
connectAttr "|Rat|eyeL|eyeRShape.iog" ":initialShadingGroup.dsm" -na;
connectAttr "|Rat|leg|legShape.iog" ":initialShadingGroup.dsm" -na;
connectAttr "|Rat|leg1|legShape.iog" ":initialShadingGroup.dsm" -na;
connectAttr "|Rat|leg2|legShape.iog" ":initialShadingGroup.dsm" -na;
connectAttr "|Rat|leg3|legShape.iog" ":initialShadingGroup.dsm" -na;
// End of rat.ma
