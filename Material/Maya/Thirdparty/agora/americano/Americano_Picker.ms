try (DestroyDialog MyCharacter)catch()

rollout MyCharacter "Ch picker" width:516 height:710
(
	
	local Char = ""
 	local Ccolor = dotnetclass "system.drawing.color"	
	Local Mysel = #()
	
	
	edittext 'edt1' "Char Name" pos:[11,10] width:184 height:24 align:#left toolTip:"Tip the prefix of the character" 
	text: "Americano"
	
	
	
	dotNetControl 'head' "system.windows.forms.button" pos:[218,7] width:45 height:55 align:#left
	dotNetControl 'Neck' "system.windows.forms.button" pos:[232,63] width:17 height:25 align:#left
	dotNetControl 'RClavicle' "system.windows.forms.button" pos:[150,72] width:74 height:16 align:#left
	dotNetControl 'LClavicle' "system.windows.forms.button" pos:[256,72] width:78 height:16 align:#left
	dotNetControl 'RFk_Upp' "system.windows.forms.button" pos:[150,90] width:23 height:89 align:#left
	dotNetControl 'LFk_Upp' "system.windows.forms.button" pos:[311,90] width:23 height:89 align:#left
	dotNetControl 'RIkAPole' "system.windows.forms.button" pos:[150,181] width:23 height:23 align:#left
	dotNetControl 'LIkAPole' "system.windows.forms.button" pos:[311,181] width:23 height:23 align:#left
	dotNetControl 'RFk_Fore' "system.windows.forms.button" pos:[150,205] width:23 height:89 align:#left
	dotNetControl 'LFk_Fore' "system.windows.forms.button" pos:[311,205] width:23 height:89 align:#left
	dotNetControl 'IkSpn02' "system.windows.forms.button" pos:[186,92] width:113 height:22 align:#left
	dotNetControl 'FkSpn03' "system.windows.forms.button" pos:[189,118] width:108 height:49 align:#left
	dotNetControl 'IkSpn01' "system.windows.forms.button" pos:[190,172] width:102 height:19 align:#left
	dotNetControl 'FkSpn02' "system.windows.forms.button" pos:[193,195] width:97 height:37 align:#left
	dotNetControl 'FkSpn01' "system.windows.forms.button" pos:[193,234] width:97 height:33 align:#left
	dotNetControl 'Cog' "system.windows.forms.button" pos:[180,270] width:123 height:15 align:#left
	dotNetControl 'pelvis' "system.windows.forms.button" pos:[187,288] width:108 height:25 align:#left
	dotNetControl 'RFkHnd' "system.windows.forms.button" pos:[143,295] width:30 height:29 align:#left
	dotNetControl 'LFkHnd' "system.windows.forms.button" pos:[311,295] width:31 height:29 align:#left
	dotNetControl 'RIkHnd' "system.windows.forms.button" pos:[110,295] width:31 height:29 align:#left
	dotNetControl 'LIkHnd' "system.windows.forms.button" pos:[344,295] width:29 height:29 align:#left
	dotNetControl 'RFk_Thg' "system.windows.forms.button" pos:[187,315] width:23 height:119 align:#left
	dotNetControl 'LFk_Thg' "system.windows.forms.button" pos:[272,315] width:23 height:119 align:#left
	dotNetControl 'RIkLPole' "system.windows.forms.button" pos:[187,436] width:23 height:23 align:#left
	dotNetControl 'LIkLPole' "system.windows.forms.button" pos:[272,436] width:23 height:23 align:#left
	dotNetControl 'RFk_Clf' "system.windows.forms.button" pos:[187,461] width:23 height:119 align:#left
	dotNetControl 'LFk_Clf' "system.windows.forms.button" pos:[272,461] width:23 height:119 align:#left
	dotNetControl 'RFkFt' "system.windows.forms.button" pos:[148,582] width:63 height:27 align:#left
	dotNetControl 'LFkFt' "system.windows.forms.button" pos:[272,582] width:60 height:27 align:#left
	dotNetControl 'RFkFtoe' "system.windows.forms.button" pos:[121,590] width:25 height:18 align:#left
	dotNetControl 'LFkFtoe' "system.windows.forms.button" pos:[335,591] width:25 height:18 align:#left
	dotNetControl 'MstR' "system.windows.forms.button" pos:[79,674] width:336 height:12 align:#left
	dotNetControl 'RAllF' "system.windows.forms.button" pos:[80,327] width:93 height:24 align:#left
	dotNetControl 'LAllF' "system.windows.forms.button" pos:[311,327] width:93 height:21 align:#left
	dotNetControl 'RF000' "system.windows.forms.button" pos:[157,354] width:15 height:15 align:#left
	dotNetControl 'LF000' "system.windows.forms.button" pos:[311,351] width:15 height:15 align:#left
	dotNetControl 'RF0001' "system.windows.forms.button" pos:[157,371] width:15 height:15 align:#left
	dotNetControl 'LF0001' "system.windows.forms.button" pos:[311,368] width:15 height:15 align:#left
	dotNetControl 'RF0002' "system.windows.forms.button" pos:[157,387] width:15 height:15 align:#left
	dotNetControl 'LF0002' "system.windows.forms.button" pos:[311,384] width:15 height:15 align:#left
	dotNetControl 'RF001' "system.windows.forms.button" pos:[137,354] width:15 height:15 align:#left
	dotNetControl 'RF011' "system.windows.forms.button" pos:[137,371] width:15 height:15 align:#left
	dotNetControl 'RF012' "system.windows.forms.button" pos:[137,387] width:15 height:15 align:#left
	dotNetControl 'LF001' "system.windows.forms.button" pos:[331,351] width:15 height:15 align:#left
	dotNetControl 'LF011' "system.windows.forms.button" pos:[331,367] width:15 height:15 align:#left
	dotNetControl 'LF012' "system.windows.forms.button" pos:[331,384] width:15 height:15 align:#left
	dotNetControl 'RF013' "system.windows.forms.button" pos:[137,403] width:15 height:15 align:#left
	dotNetControl 'LF013' "system.windows.forms.button" pos:[331,400] width:15 height:15 align:#left
	dotNetControl 'RF002' "system.windows.forms.button" pos:[117,355] width:15 height:15 align:#left
	dotNetControl 'RF021' "system.windows.forms.button" pos:[117,372] width:15 height:15 align:#left
	dotNetControl 'RF022' "system.windows.forms.button" pos:[117,388] width:15 height:15 align:#left
	dotNetControl 'RF023' "system.windows.forms.button" pos:[117,404] width:15 height:15 align:#left
	dotNetControl 'LF002' "system.windows.forms.button" pos:[350,351] width:15 height:15 align:#left
	dotNetControl 'LF021' "system.windows.forms.button" pos:[350,367] width:15 height:15 align:#left
	dotNetControl 'LF022' "system.windows.forms.button" pos:[350,384] width:15 height:15 align:#left
	dotNetControl 'LF023' "system.windows.forms.button" pos:[350,400] width:15 height:15 align:#left
	dotNetControl 'LF003' "system.windows.forms.button" pos:[369,351] width:15 height:15 align:#left
	dotNetControl 'LF031' "system.windows.forms.button" pos:[369,367] width:15 height:15 align:#left
	dotNetControl 'LF032' "system.windows.forms.button" pos:[369,384] width:15 height:15 align:#left
	dotNetControl 'LF033' "system.windows.forms.button" pos:[369,400] width:15 height:15 align:#left
	dotNetControl 'RF003' "system.windows.forms.button" pos:[99,355] width:15 height:15 align:#left
	dotNetControl 'RF031' "system.windows.forms.button" pos:[99,372] width:15 height:15 align:#left
	dotNetControl 'RF032' "system.windows.forms.button" pos:[99,388] width:15 height:15 align:#left
	dotNetControl 'RF033' "system.windows.forms.button" pos:[99,404] width:15 height:15 align:#left
	dotNetControl 'RF004' "system.windows.forms.button" pos:[81,355] width:15 height:15 align:#left
	dotNetControl 'RF041' "system.windows.forms.button" pos:[81,372] width:15 height:15 align:#left
	dotNetControl 'RF042' "system.windows.forms.button" pos:[81,388] width:15 height:15 align:#left
	dotNetControl 'RF043' "system.windows.forms.button" pos:[81,404] width:15 height:15 align:#left
	dotNetControl 'LF004' "system.windows.forms.button" pos:[388,351] width:15 height:15 align:#left
	dotNetControl 'LF041' "system.windows.forms.button" pos:[388,367] width:15 height:15 align:#left
	dotNetControl 'LF042' "system.windows.forms.button" pos:[388,384] width:15 height:15 align:#left
	dotNetControl 'LF043' "system.windows.forms.button" pos:[388,400] width:15 height:15 align:#left
	dotNetControl 'RIkFt' "system.windows.forms.button" pos:[172,612] width:39 height:27 align:#left
	dotNetControl 'LIkFt' "system.windows.forms.button" pos:[272,612] width:39 height:27 align:#left
	dotNetControl 'LIkHll' "system.windows.forms.button" pos:[256,624] width:15 height:15 align:#left
	dotNetControl 'RIkHll' "system.windows.forms.button" pos:[213,624] width:15 height:15 align:#left
	dotNetControl 'RFkIkToe' "system.windows.forms.button" pos:[159,615] width:9 height:24 align:#left
	dotNetControl 'LFkIkToe' "system.windows.forms.button" pos:[315,615] width:9 height:24 align:#left
	dotNetControl 'RIkToe' "system.windows.forms.button" pos:[139,620] width:16 height:19 align:#left
	dotNetControl 'LIkToe' "system.windows.forms.button" pos:[327,620] width:16 height:19 align:#left
	dotNetControl 'RIkTip' "system.windows.forms.button" pos:[121,624] width:15 height:15 align:#left
	dotNetControl 'LIkTip' "system.windows.forms.button" pos:[346,624] width:15 height:15 align:#left
	dotNetControl 'RAMBndy' "system.windows.forms.button" pos:[123,182] width:18 height:19 align:#left
	dotNetControl 'RAUBndy' "system.windows.forms.button" pos:[126,157] width:11 height:12 align:#left
	dotNetControl 'RADBndy' "system.windows.forms.button" pos:[126,214] width:11 height:12 align:#left
	dotNetControl 'LAMBndy' "system.windows.forms.button" pos:[342,182] width:18 height:19 align:#left
	dotNetControl 'LAUBndy' "system.windows.forms.button" pos:[345,157] width:11 height:12 align:#left
	dotNetControl 'LADBndy' "system.windows.forms.button" pos:[345,214] width:11 height:12 align:#left
	dotNetControl 'RKnee' "system.windows.forms.button" pos:[160,462] width:18 height:19 align:#left
	dotNetControl 'RKneeUP' "system.windows.forms.button" pos:[163,437] width:11 height:12 align:#left
	dotNetControl 'RKneeD' "system.windows.forms.button" pos:[163,494] width:11 height:12 align:#left
	dotNetControl 'LKnee' "system.windows.forms.button" pos:[303,459] width:18 height:19 align:#left
	dotNetControl 'LKneeUP' "system.windows.forms.button" pos:[306,434] width:11 height:12 align:#left
	dotNetControl 'LKneeD' "system.windows.forms.button" pos:[306,491] width:11 height:12 align:#left
	dotNetControl 'SelAll' "system.windows.forms.button" pos:[386,48] width:96 height:34 align:#left
	dotNetControl 'KeyAll' "system.windows.forms.button" pos:[386,86] width:96 height:34 align:#left
	dotNetControl 'KeySel' "system.windows.forms.button" pos:[386,124] width:96 height:34 align:#left
	dotNetControl 'LFootAtt' "system.windows.forms.button" pos:[377,601] width:29 height:29 align:#left
	dotNetControl 'RHandAtt' "system.windows.forms.button" pos:[79,295] width:29 height:29 align:#left
	dotNetControl 'RFootAtt' "system.windows.forms.button" pos:[76,603] width:29 height:29 align:#left
	dotNetControl 'LHandAtt' "system.windows.forms.button" pos:[376,295] width:29 height:29 align:#left
	dotNetControl 'SpineAtt' "system.windows.forms.button" pos:[226,322] width:29 height:29 align:#left
	dotNetControl 'HeadAtt' "system.windows.forms.button" pos:[267,8] width:29 height:29 align:#left
	dotNetControl 'LHIkAttch' "system.windows.forms.button" pos:[352,279] width:11 height:11 align:#left
	dotNetControl 'RHIkAttch' "system.windows.forms.button" pos:[119,280] width:11 height:11 align:#left
	dotNetControl 'LFIkAttch' "system.windows.forms.button" pos:[287,642] width:11 height:11 align:#left
	dotNetControl 'RFIkAttch' "system.windows.forms.button" pos:[187,642] width:11 height:11 align:#left
	dotNetControl 'AllRIF' "system.windows.forms.button" pos:[137,421] width:15 height:15 align:#left
	dotNetControl 'AllRMF' "system.windows.forms.button" pos:[117,422] width:15 height:15 align:#left
	dotNetControl 'AllRCF' "system.windows.forms.button" pos:[99,422] width:15 height:15 align:#left
	dotNetControl 'AllRMeF' "system.windows.forms.button" pos:[81,422] width:15 height:15 align:#left
	dotNetControl 'AllRPF' "system.windows.forms.button" pos:[157,404] width:15 height:15 align:#left
	dotNetControl 'AllLPF' "system.windows.forms.button" pos:[311,402] width:15 height:15 align:#left
	dotNetControl 'AllLIF' "system.windows.forms.button" pos:[331,418] width:15 height:15 align:#left
	dotNetControl 'AllLMF' "system.windows.forms.button" pos:[350,418] width:15 height:15 align:#left
	dotNetControl 'AllLCF' "system.windows.forms.button" pos:[369,418] width:15 height:15 align:#left
	dotNetControl 'AllLMeF' "system.windows.forms.button" pos:[388,418] width:15 height:15 align:#left	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	HyperLink 'hl_web' "www.ivanlobon.com" pos:[78,691] width:97 height:15 color:(color 255 255 255) hovercolor:(color 255 255 255) visitedcolor:(color 200 200 200) address:"http://www.ivanlobon.com" align:#left 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
	HyperLink 'cust240' "Contact" pos:[375,691] width:75 height:15 address:"mailto:animaciones@ivanlobon.com" color:(color 255 255 255) hovercolor:(color 111 111 111) visitedcolor:(color 255 255 255) align:#left
	
	


	
	
	
	-------------------------------------------------------------------------------------------------------

	
	on MyCharacter open do
	(
	
	Head.flatStyle=Head.flatStyle.flat
	Head.backColor=Head.backColor.darkgreen
	
	Neck.flatStyle=Neck.flatStyle.flat
	Neck.backColor=Neck.backColor.darkgreen
		
	RClavicle.flatStyle=RClavicle.flatStyle.flat
	RClavicle.backColor=RClavicle.backColor.green
		
	LClavicle.flatStyle=LClavicle.flatStyle.flat
	LClavicle.backColor=LClavicle.backColor.green
	
	RFk_Upp.flatStyle=RFk_Upp.flatStyle.flat
	RFk_Upp.backColor=RFk_Upp.backColor.green
	
	LFk_Upp.flatStyle=LFk_Upp.flatStyle.flat
	LFk_Upp.backColor=LFk_Upp.backColor.green
	
	RIkAPole.flatStyle=RIkAPole.flatStyle.flat
	RIkAPole.backColor=RIkAPole.backColor.DarkRed
	
	LIkAPole.flatStyle=LIkAPole.flatStyle.flat
	LIkAPole.backColor=LIkAPole.backColor.DarkRed
	
	RFk_Fore.flatStyle=RFk_Fore.flatStyle.flat
	RFk_Fore.backColor=RFk_Fore.backColor.green
	
	LFk_Fore.flatStyle=LFk_Fore.flatStyle.flat
	LFk_Fore.backColor=LFk_Fore.backColor.green
	
	
	FkSpn03.flatStyle=FkSpn03.flatStyle.flat
	FkSpn03.backColor=FkSpn03.backColor.Yellow
	
	IkSpn02.flatStyle=IkSpn02.flatStyle.flat
	IkSpn02.backColor=IkSpn02.backColor.DarkBlue
	
	FkSpn02.flatStyle=FkSpn02.flatStyle.flat
	FkSpn02.backColor=FkSpn02.backColor.Yellow
	
	IkSpn01.flatStyle=IkSpn01.flatStyle.flat
	IkSpn01.backColor=IkSpn01.backColor.DarkBlue
	
	FkSpn01.flatStyle=FkSpn01.flatStyle.flat
	FkSpn01.backColor=FkSpn01.backColor.Yellow
	
	-- 	FkSpn00.flatStyle=FkSpn00.flatStyle.flat
	-- 	FkSpn00.backColor=FkSpn00.backColor.Yellow
	
	Cog.flatStyle=Cog.flatStyle.flat
	Cog.backColor=Cog.backColor.Red
	
	Pelvis.flatStyle=Pelvis.flatStyle.flat
	Pelvis.backColor=Pelvis.backColor.DarkBlue           
	
	RFkHnd.flatStyle=RFkHnd.flatStyle.flat
	RFkHnd.backColor=RFkHnd.backColor.GreenYellow
	
	LFkHnd.flatStyle=LFkHnd.flatStyle.flat
	LFkHnd.backColor=LFkHnd.backColor.GreenYellow
	
	RIkHnd.flatStyle=RIkHnd.flatStyle.flat
	RIkHnd.backColor=RIkHnd.backColor.DarkRed
	RIkHnd.text="Ik"
	
	LIkHnd.flatStyle=LIkHnd.flatStyle.flat
	LIkHnd.backColor=LIkHnd.backColor.DarkRed
	LIkHnd.text="Ik"
	
	RFk_Thg.flatStyle=RFk_Thg.flatStyle.flat
	RFk_Thg.backColor=RFk_Thg.backColor.green
	
	LFk_Thg.flatStyle=LFk_Thg.flatStyle.flat
	LFk_Thg.backColor=LFk_Thg.backColor.green
	
	RIkLPole.flatStyle=RIkLPole.flatStyle.flat
	RIkLPole.backColor=RIkLPole.backColor.DarkRed
	
	LIkLPole.flatStyle=LIkLPole.flatStyle.flat
	LIkLPole.backColor=LIkLPole.backColor.DarkRed
	
	RFk_Clf.flatStyle=RFk_Clf.flatStyle.flat
	RFk_Clf.backColor=RFk_Clf.backColor.green
	
	LFk_Clf.flatStyle=LFk_Clf.flatStyle.flat
	LFk_Clf.backColor=LFk_Clf.backColor.green
	
	RFkFt.flatStyle=RFkFt.flatStyle.flat
	RFkFt.backColor=RFkFt.backColor.GreenYellow
	
	LFkFt.flatStyle=LFkFt.flatStyle.flat
	LFkFt.backColor=LFkFt.backColor.GreenYellow
	
	RFkFtoe.flatStyle=RFkFtoe.flatStyle.flat
	RFkFtoe.backColor=RFkFtoe.backColor.Green
	
	LFkFtoe.flatStyle=LFkFtoe.flatStyle.flat
	LFkFtoe.backColor=LFkFtoe.backColor.Green
	
	MstR.flatStyle=MstR.flatStyle.flat
	MstR.backColor=MstR.backColor.Red
	
	RAllF.flatStyle=RAllF.flatStyle.flat
	RAllF.backColor=RAllF.backColor.Purple
	RAllF.text="All_Fingers"
	
	LAllF.flatStyle=LAllF.flatStyle.flat
	LAllF.backColor=LAllF.backColor.Purple
	LAllF.text="All_Fingers"
	
	RF000.flatStyle=RF000.flatStyle.flat
	RF000.backColor=RF000.backColor.Purple 
	
	LF000.flatStyle=LF000.flatStyle.flat
	LF000.backColor=LF000.backColor.Purple  
	
	RF0001.flatStyle=RF0001.flatStyle.flat
	RF0001.backColor=RF0001.backColor.Purple 
	
	LF0001.flatStyle=LF0001.flatStyle.flat
	LF0001.backColor=LF0001.backColor.Purple 
	
	RF0002.flatStyle=RF0002.flatStyle.flat
	RF0002.backColor=RF0002.backColor.Purple  
	
	LF0002.flatStyle=LF0002.flatStyle.flat
	LF0002.backColor=LF0002.backColor.Purple   
	
	RF001.flatStyle=RF001.flatStyle.flat
	RF001.backColor=RF001.backColor.Purple 
	
	LF001.flatStyle=LF001.flatStyle.flat
	LF001.backColor=LF001.backColor.Purple  
	
	RF011.flatStyle=RF011.flatStyle.flat
	RF011.backColor=RF011.backColor.Purple 
	
	LF011.flatStyle=LF011.flatStyle.flat
	LF011.backColor=LF011.backColor.Purple  
	
	RF012.flatStyle=RF012.flatStyle.flat
	RF012.backColor=RF012.backColor.Purple          
	
	LF012.flatStyle=LF012.flatStyle.flat
	LF012.backColor=LF012.backColor.Purple   
	
	RF013.flatStyle=RF013.flatStyle.flat
	RF013.backColor=RF013.backColor.Purple 
	
	LF013.flatStyle=LF013.flatStyle.flat
	LF013.backColor=LF013.backColor.Purple  
	
	RF002.flatStyle=RF002.flatStyle.flat
	RF002.backColor=RF002.backColor.Purple 
	
	LF002.flatStyle=LF002.flatStyle.flat
	LF002.backColor=LF002.backColor.Purple 
	
	RF021.flatStyle=RF021.flatStyle.flat
	RF021.backColor=RF021.backColor.Purple 
	
	LF021.flatStyle=LF021.flatStyle.flat
	LF021.backColor=LF021.backColor.Purple 
	
	RF022.flatStyle=RF022.flatStyle.flat
	RF022.backColor=RF022.backColor.Purple 
	
	LF022.flatStyle=LF022.flatStyle.flat
	LF022.backColor=LF022.backColor.Purple 
	
	RF023.flatStyle=RF023.flatStyle.flat
	RF023.backColor=RF023.backColor.Purple 
	
	LF023.flatStyle=LF023.flatStyle.flat
	LF023.backColor=LF023.backColor.Purple 
	
	RF003.flatStyle=RF003.flatStyle.flat
	RF003.backColor=RF003.backColor.Purple 
	
	LF003.flatStyle=LF003.flatStyle.flat
	LF003.backColor=LF003.backColor.Purple 
	
	RF031.flatStyle=RF031.flatStyle.flat
	RF031.backColor=RF031.backColor.Purple 
	
	LF031.flatStyle=LF031.flatStyle.flat
	LF031.backColor=LF031.backColor.Purple 
	
	RF032.flatStyle=RF032.flatStyle.flat
	RF032.backColor=RF032.backColor.Purple 
	
	LF032.flatStyle=LF032.flatStyle.flat
	LF032.backColor=LF032.backColor.Purple 
	
	RF033.flatStyle=RF033.flatStyle.flat
	RF033.backColor=RF033.backColor.Purple 
	
	LF033.flatStyle=LF033.flatStyle.flat
	LF033.backColor=LF033.backColor.Purple 
	
	RF004.flatStyle=RF004.flatStyle.flat
	RF004.backColor=RF004.backColor.Purple 
	
	LF004.flatStyle=LF004.flatStyle.flat
	LF004.backColor=LF004.backColor.Purple 
	
	RF041.flatStyle=RF041.flatStyle.flat
	RF041.backColor=RF041.backColor.Purple 
	
	LF041.flatStyle=LF041.flatStyle.flat
	LF041.backColor=LF041.backColor.Purple 
	
	RF042.flatStyle=RF042.flatStyle.flat
	RF042.backColor=RF042.backColor.Purple 
	
	LF042.flatStyle=LF042.flatStyle.flat
	LF042.backColor=LF042.backColor.Purple 
	
	RF043.flatStyle=RF043.flatStyle.flat
	RF043.backColor=RF043.backColor.Purple 
	
	LF043.flatStyle=LF043.flatStyle.flat
	LF043.backColor=LF043.backColor.Purple 
	
	RIkFt.flatStyle=RIkFt.flatStyle.flat
	RIkFt.backColor=RIkFt.backColor.DarkRed
	RIkFt.text="Ik" 
	
	LIkFt.flatStyle=LIkFt.flatStyle.flat
	LIkFt.backColor=LIkFt.backColor.DarkRed
	LIkFt.text="Ik" 
	
	RIkHll.flatStyle=LIkFt.flatStyle.flat
	RIkHll.backColor=LIkFt.backColor.Red
	
	LIkHll.flatStyle=LIkFt.flatStyle.flat
	LIkHll.backColor=LIkFt.backColor.Red       
	
	RIkTip.flatStyle=RIkTip.flatStyle.flat
	RIkTip.backColor=RIkTip.backColor.Red
	
	LIkTip.flatStyle=LIkTip.flatStyle.flat
	LIkTip.backColor=LIkTip.backColor.Red    
	
	RFkIkToe.flatStyle=RFkIkToe.flatStyle.flat
	RFkIkToe.backColor=RFkIkToe.backColor.Green
	
	LFkIkToe.flatStyle=LFkIkToe.flatStyle.flat
	LFkIkToe.backColor=LFkIkToe.backColor.Green 
	
	RIkToe.flatStyle=RIkToe.flatStyle.flat
	RIkToe.backColor=RIkToe.backColor.DarkRed
	
	LIkToe.flatStyle=LIkToe.flatStyle.flat
	LIkToe.backColor=LIkToe.backColor.DarkRed   
	
	RAMBndy.flatStyle=RAMBndy.flatStyle.flat
	RAMBndy.backColor=RAMBndy.backColor.Orange  
	
	RAUBndy.flatStyle=RAUBndy.flatStyle.flat
	RAUBndy.backColor=RAUBndy.backColor.Orange  
	
	RADBndy.flatStyle=RADBndy.flatStyle.flat
	RADBndy.backColor=RADBndy.backColor.Orange  
	
	LAMBndy.flatStyle=LAMBndy.flatStyle.flat
	LAMBndy.backColor=LAMBndy.backColor.Orange  
	
	LAUBndy.flatStyle=LAUBndy.flatStyle.flat
	LAUBndy.backColor=LAUBndy.backColor.Orange  
	
	LADBndy.flatStyle=LADBndy.flatStyle.flat
	LADBndy.backColor=LADBndy.backColor.Orange  
	
	RADBndy.flatStyle=RADBndy.flatStyle.flat
	RADBndy.backColor=RADBndy.backColor.Orange  
	
	RKnee.flatStyle=RKnee.flatStyle.flat
	RKnee.backColor=RKnee.backColor.Orange  
	
	RKneeUp.flatStyle=RKneeUp.flatStyle.flat
	RKneeUp.backColor=RKneeUp.backColor.Orange  
	
	RKneeD.flatStyle=RKneeD.flatStyle.flat
	RKneeD.backColor=RKneeD.backColor.Orange  
	
	LKnee.flatStyle=LKnee.flatStyle.flat
	LKnee.backColor=LKnee.backColor.Orange  
	
	LKneeUP.flatStyle=LKneeUP.flatStyle.flat
	LKneeUP.backColor=LKneeUP.backColor.Orange  
	
	LKneeD.flatStyle=LKneeD.flatStyle.flat
	LKneeD.backColor=LKneeD.backColor.Orange  
	
	SelAll.flatStyle=SelAll.flatStyle.flat
	SelAll.backColor=SelAll.backColor.darkgreen
	SelAll.text="Select All" 
	
	KeyAll.flatStyle=KeyAll.flatStyle.flat
	KeyAll.backColor=KeyAll.backColor.red
	KeyAll.text="Key All" 
	KeySel
	
	KeySel.flatStyle=KeySel.flatStyle.flat
	KeySel.backColor=KeySel.backColor.Orange
	KeySel.text="Key Selection" 
	
	LHandAtt.flatStyle=LHandAtt.flatStyle.flat
	LHandAtt.backColor=LHandAtt.backColor.Yellow
	LHandAtt.text="Att"
	
	RHandAtt.flatStyle=RHandAtt.flatStyle.flat
	RHandAtt.backColor=RHandAtt.backColor.Yellow
	RHandAtt.text="Att"
	
	LFootAtt.flatStyle=LFootAtt.flatStyle.flat
	LFootAtt.backColor=LFootAtt.backColor.Yellow
	LFootAtt.text="Att"
	
	RFootAtt.flatStyle=RFootAtt.flatStyle.flat
	RFootAtt.backColor=RFootAtt.backColor.Yellow
	RFootAtt.text="Att"
	
	SpineAtt.flatStyle=SpineAtt.flatStyle.flat
	SpineAtt.backColor=SpineAtt.backColor.Yellow
	SpineAtt.text="Att"
	
	HeadAtt.flatStyle=HeadAtt.flatStyle.flat
	HeadAtt.backColor=HeadAtt.backColor.Yellow
	HeadAtt.text="Att"
	
	LHIkAttch.flatStyle=LHIkAttch.flatStyle.flat
	LHIkAttch.backColor=LHIkAttch.backColor.DarkBlue
	
	RHIkAttch.flatStyle=RHIkAttch.flatStyle.flat
	RHIkAttch.backColor=RHIkAttch.backColor.DarkBlue
	
	LFIkAttch.flatStyle=LFIkAttch.flatStyle.flat
	LFIkAttch.backColor=LFIkAttch.backColor.DarkBlue
	
	RFIkAttch.flatStyle=RFIkAttch.flatStyle.flat
	RFIkAttch.backColor=RFIkAttch.backColor.DarkBlue
	
	AllRIF.flatStyle=AllRIF.flatStyle.flat
	AllRIF.backColor=AllRIF.backColor.violet
	
	AllRMF.flatStyle=AllRMF.flatStyle.flat
	AllRMF.backColor=AllRMF.backColor.violet
	
	AllRCF.flatStyle=AllRCF.flatStyle.flat
	AllRCF.backColor=AllRCF.backColor.violet
	
	AllRMeF.flatStyle=AllRMeF.flatStyle.flat
	AllRMeF.backColor=AllRMeF.backColor.violet
	
	AllRPF.flatStyle=AllRPF.flatStyle.flat
	AllRPF.backColor=AllRPF.backColor.violet
	
	AllLPF.flatStyle=AllLPF.flatStyle.flat
	AllLPF.backColor=AllLPF.backColor.violet
	
	AllLIF.flatStyle=AllLIF.flatStyle.flat
	AllLIF.backColor=AllLIF.backColor.violet
	
	AllLMF.flatStyle=AllLMF.flatStyle.flat
	AllLMF.backColor=AllLMF.backColor.violet
	
	AllLCF.flatStyle=AllLCF.flatStyle.flat
	AllLCF.backColor=AllLCF.backColor.violet
	
	AllLMeF.flatStyle=AllLMeF.flatStyle.flat
	AllLMeF.backColor=AllLMeF.backColor.violet
	
	
	
	)
	on head mouseDown senderArg arg do
	( 
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "Head_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "Head_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "Head_Control" as string))
						)
	)
	on Neck mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "Neck_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "Neck_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "Neck_Control" as string))
						)
	)
	on RClavicle mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_clavicle_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_clavicle_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_clavicle_Control" as string))
						)
	)
	on LClavicle mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_clavicle_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_clavicle_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_clavicle_Control" as string))
						)
	)
	on RFk_Upp mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_UpperArm_Fk_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_UpperArm_Fk_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_UpperArm_Fk_Control" as string))
						)
	)
	on LFk_Upp mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_UpperArm_Fk_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_UpperArm_Fk_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_UpperArm_Fk_Control" as string))
						)
	)
	on RIkAPole mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Arm_Ik_Pole_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Arm_Ik_Pole_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Arm_Ik_Pole_Control" as string))
						)
	)
	on LIkAPole mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Arm_Ik_Pole_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Arm_Ik_Pole_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Arm_Ik_Pole_Control" as string))
						)
	)
	on RFk_Fore mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_ForeArm_Fk_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_ForeArm_Fk_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_ForeArm_Fk_Control" as string))
						)
	)
	on LFk_Fore mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_ForeArm_Fk_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_ForeArm_Fk_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_ForeArm_Fk_Control" as string))
						)
	)
	on IkSpn02 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "Spine_Ik_002_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "Spine_Ik_002_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "Spine_Ik_002_Control" as string))
						)
	)
	on FkSpn03 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "Spine003_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "Spine003_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "Spine003_Control" as string))
						)
	)
	on IkSpn01 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "Spine_Ik_001_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "Spine_Ik_001_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "Spine_Ik_001_Control" as string))
						)
	)
	on FkSpn02 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "Spine002_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "Spine002_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "Spine002_Control" as string))
						)
	)
		on FkSpn01 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "Spine001_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "Spine001_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "Spine001_Control" as string))
						)
	)
	on Cog mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "Cog_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "Cog_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "Cog_Control" as string))
						)
	)
	on pelvis mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "Pelvis_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "Pelvis_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "Pelvis_Control" as string))
						)
	)
	on RFkHnd mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Hand_Fk_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Hand_Fk_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Hand_Fk_Control" as string))
						)
	)
	on LFkHnd mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Hand_Fk_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Hand_Fk_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Hand_Fk_Control" as string))
						)
	)
	on RIkHnd mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Hand_Ik_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Hand_Ik_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Hand_Ik_Control" as string))
						)
	)
	on LIkHnd mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Hand_Ik_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Hand_Ik_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Hand_Ik_Control" as string))
						)
	)
	on RFk_Thg mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Thigh_Fk_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Thigh_Fk_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Thigh_Fk_Control" as string))
						)
	)
	on LFk_Thg mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Thigh_Fk_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Thigh_Fk_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Thigh_Fk_Control" as string))
						)
	)
	on RIkLPole mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Leg_Ik_Pole_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Leg_Ik_Pole_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Leg_Ik_Pole_Control" as string))
						)
	)
	on LIkLPole mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Leg_Ik_Pole_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Leg_Ik_Pole_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Leg_Ik_Pole_Control" as string))
						)
	)
	on RFk_Clf mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Calf_Fk_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Calf_Fk_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Calf_Fk_Control" as string))
						)
	)
	on LFk_Clf mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Calf_Fk_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Calf_Fk_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Calf_Fk_Control" as string))
						)
	)
	on RFkFt mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Foot_Fk_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Foot_Fk_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Foot_Fk_Control" as string))
						)
	)
	on LFkFt mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Foot_Fk_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Foot_Fk_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Foot_Fk_Control" as string))
						)
	)
	on RFkFtoe mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Toe_Fk_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Toe_Fk_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Toe_Fk_Control" as string))
						)
	)
	on LFkFtoe mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Toe_Fk_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Toe_Fk_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Toe_Fk_Control" as string))
						)
	)
	on MstR mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "Master" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "Master" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "Master" as string))
						)
	)
	on RAllF mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
		(
			selectmore (execute("$" + edt1.text + "_" + "R_Finger"+"*"+"_control*" as string))
	selectmore (execute("$" + edt1.text + "_" + "R_Knuckles"+"*"+"_control*" as string))
		)else if keyboard.altPressed then
				(
				deselect (execute("$" + edt1.text + "_" + "R_Finger"+"*"+"_control*" as string))
	deselect (execute("$" + edt1.text + "_" + "R_Knuckles"+"*"+"_control*" as string))
				)else
					(
					select (execute("$" + edt1.text + "_" + "R_Finger"+"*"+"_control*" as string))
	selectmore (execute("$" + edt1.text + "_" + "R_Knuckles"+"*"+"_control*" as string))
					)
	
	)
	on LAllF mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
		(
			selectmore (execute("$" + edt1.text + "_" + "L_Finger"+"*"+"_control*" as string))
	selectmore (execute("$" + edt1.text + "_" + "L_Knuckles"+"*"+"_control*" as string))
		)else if keyboard.altPressed then
				(
				deselect (execute("$" + edt1.text + "_" + "L_Finger"+"*"+"_control*" as string))
	deselect (execute("$" + edt1.text + "_" + "L_Knuckles"+"*"+"_control*" as string))
				)else
					(
					select (execute("$" + edt1.text + "_" + "L_Finger"+"*"+"_control*" as string))
	selectmore (execute("$" + edt1.text + "_" + "L_Knuckles"+"*"+"_control*" as string))
					)
	
	)
	on RF000 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	 				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Knuckles_0000_Control" as string)))catch()
	 					)
						else if keyboard.altPressed then
	 					(
	 					try (deselect (execute("$" + edt1.text + "_" + "R_Knuckles_0000_Control" as string)))catch()
	 					)else
	 						(
	 						try (select (execute("$" + edt1.text + "_" + "R_Knuckles_0000_Control" as string)))catch()
	 						)
	)
	on LF000 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	 				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Knuckles_0000_Control" as string)))catch()
	 					)
						else if keyboard.altPressed then
	 					(
	 					try (deselect (execute("$" + edt1.text + "_" + "L_Knuckles_0000_Control" as string)))catch()
	 					)else
	 						(
	 						try (select (execute("$" + edt1.text + "_" + "L_Knuckles_0000_Control" as string)))catch()
	 						)
	)
	on RF0001 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_0000_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Finger_0000_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Finger_0000_Control" as string)))catch()
						)
	)
	on LF0001 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_0000_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Finger_0000_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Finger_0000_Control" as string)))catch()
						)
	)
	on RF0002 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_0001_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Finger_0001_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Finger_0001_Control" as string)))catch()
						)
	)
	on LF0002 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_0001_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Finger_0001_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Finger_0001_Control" as string)))catch()
						)
	)
	on RF001 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	 				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Knuckles_001_Control" as string)))catch()
	 					)
						else if keyboard.altPressed then
	 					(
	 					try (deselect (execute("$" + edt1.text + "_" + "R_Knuckles_001_Control" as string)))catch()
	 					)else
	 						(
	 						try (select (execute("$" + edt1.text + "_" + "R_Knuckles_001_Control" as string)))catch()
	 						)
	)
	on RF011 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_001_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Finger_001_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Finger_001_Control" as string)))catch()
						)
	)
	on RF012 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_011_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Finger_011_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Finger_011_Control" as string)))catch()
						)
	)
	on LF001 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	 				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Knuckles_001_Control" as string)))catch()
	 					)
						else if keyboard.altPressed then
	 					(
	 					try (deselect (execute("$" + edt1.text + "_" + "L_Knuckles_001_Control" as string)))catch()
	 					)else
	 						(
	 						try (select (execute("$" + edt1.text + "_" + "L_Knuckles_001_Control" as string)))catch()
	 						)
	)
	on LF011 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_001_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Finger_001_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Finger_001_Control" as string)))catch()
						)
	)
	on LF012 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_011_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Finger_011_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Finger_011_Control" as string)))catch()
						)
	)
	on RF013 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_021_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Finger_021_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Finger_021_Control" as string)))catch()
						)
	)
	on LF013 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_021_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Finger_021_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Finger_021_Control" as string)))catch()
						)
	)
	on RF002 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	 				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Knuckles_002_Control" as string)))catch()
	 					)
						else if keyboard.altPressed then
	 					(
	 					try (deselect (execute("$" + edt1.text + "_" + "R_Knuckles_002_Control" as string)))catch()
	 					)else
	 						(
	 						try (select (execute("$" + edt1.text + "_" + "R_Knuckles_002_Control" as string)))catch()
	 						)
	)
	on RF021 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_002_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Finger_002_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Finger_002_Control" as string)))catch()
						)
	)
	on RF022 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_012_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Finger_012_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Finger_012_Control" as string)))catch()
						)
	)
	on RF023 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_022_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Finger_022_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Finger_022_Control" as string)))catch()
						)
	)
	on LF002 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	 				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Knuckles_002_Control" as string)))catch()
	 					)
						else if keyboard.altPressed then
	 					(
	 					try (deselect (execute("$" + edt1.text + "_" + "L_Knuckles_002_Control" as string)))catch()
	 					)else
	 						(
	 						try (select (execute("$" + edt1.text + "_" + "L_Knuckles_002_Control" as string)))catch()
	 						)
	)
	on LF021 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_002_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Finger_002_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Finger_002_Control" as string)))catch()
						)
	)
	on LF022 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_012_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Finger_012_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Finger_012_Control" as string)))catch()
						)
	)
	on LF023 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_022_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Finger_022_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Finger_022_Control" as string)))catch()
						)
	)
	on LF003 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	 				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Knuckles_003_Control" as string)))catch()
	 					)
						else if keyboard.altPressed then
	 					(
	 					try (deselect (execute("$" + edt1.text + "_" + "L_Knuckles_003_Control" as string)))catch()
	 					)else
	 						(
	 						try (select (execute("$" + edt1.text + "_" + "L_Knuckles_003_Control" as string)))catch()
	 						)
	)
	on LF031 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_003_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Finger_003_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Finger_003_Control" as string)))catch()
						)
	)
	on LF032 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_013_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Finger_013_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Finger_013_Control" as string)))catch()
						)
	)
	on LF033 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_023_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Finger_023_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Finger_023_Control" as string)))catch()
						)
	)
	on RF003 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	 				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Knuckles_003_Control" as string)))catch()
	 					)
						else if keyboard.altPressed then
	 					(
	 					try (deselect (execute("$" + edt1.text + "_" + "R_Knuckles_003_Control" as string)))catch()
	 					)else
	 						(
	 						try (select (execute("$" + edt1.text + "_" + "R_Knuckles_003_Control" as string)))catch()
	 						)
	)
	on RF031 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_003_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Finger_003_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Finger_003_Control" as string)))catch()
						)
	)
	on RF032 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_013_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Finger_013_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Finger_013_Control" as string)))catch()
						)
	)
	on RF033 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_023_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Finger_023_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Finger_023_Control" as string)))catch()
						)
	)
	on RF004 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Knuckles_004_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Knuckles_004_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Knuckles_004_Control" as string)))catch()
						)
	)
	on RF041 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_004_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Finger_004_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Finger_004_Control" as string)))catch()
						)
	)
	on RF042 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_014_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Finger_014_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Finger_014_Control" as string)))catch()
						)
	)
	on RF043 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_024_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "R_Finger_024_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "R_Finger_024_Control" as string)))catch()
						)
	)
	on LF004 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Knuckles_004_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Knuckles_004_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Knuckles_004_Control" as string)))catch()
						)
	)
	on LF041 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_004_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Finger_004_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Finger_004_Control" as string)))catch()
						)
	)
	on LF042 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_014_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Finger_014_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Finger_014_Control" as string)))catch()
						)
	)
	on LF043 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				 Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_024_Control" as string)))catch()
					)
				else if keyboard.altPressed then
					(
					try (deselect (execute("$" + edt1.text + "_" + "L_Finger_024_Control" as string)))catch()
					)else
						(
						try (select (execute("$" + edt1.text + "_" + "L_Finger_024_Control" as string)))catch()
						)
	)
	on RIkFt mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Foot_Ik_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Foot_Ik_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Foot_Ik_Control" as string))
						)
	)
	on LIkFt mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Foot_Ik_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Foot_Ik_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Foot_Ik_Control" as string))
						)
	)
	on LIkHll mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Ik_Heel_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Ik_Heel_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Ik_Heel_Control" as string))
						)
	)
	on RIkHll mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Ik_Heel_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Ik_Heel_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Ik_Heel_Control" as string))
						)
	)
	on RFkIkToe mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "FkIk_R_Toe_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "FkIk_R_Toe_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "FkIk_R_Toe_Control" as string))
						)
	)
	on LFkIkToe mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "FkIk_L_Toe_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "FkIk_L_Toe_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "FkIk_L_Toe_Control" as string))
						)
	)
	on RIkToe mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "Ik_R_Toe_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "Ik_R_Toe_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "Ik_R_Toe_Control" as string))
						)
	)
	on LIkToe mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "Ik_L_Toe_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "Ik_L_Toe_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "Ik_L_Toe_Control" as string))
						)
	)
	on RIkTip mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Ik_Tip_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Ik_Tip_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Ik_Tip_Control" as string))
						)
	)
	on LIkTip mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Ik_Tip_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Ik_Tip_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Ik_Tip_Control" as string))
						)
	)
	on RAMBndy mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Elbow_Bendy_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Elbow_Bendy_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Elbow_Bendy_Control" as string))
						)
	)
	on RAUBndy mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_UpperArm_Bendy_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_UpperArm_Bendy_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_UpperArm_Bendy_Control" as string))
						)
	)
	on RADBndy mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_ForeArm_Bendy_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_ForeArm_Bendy_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_ForeArm_Bendy_Control" as string))
						)
	)
	on LAMBndy mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Elbow_Bendy_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Elbow_Bendy_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Elbow_Bendy_Control" as string))
						)
	)
	on LAUBndy mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_UpperArm_Bendy_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_UpperArm_Bendy_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_UpperArm_Bendy_Control" as string))
						)
	)
	on LADBndy mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_ForeArm_Bendy_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_ForeArm_Bendy_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_ForeArm_Bendy_Control" as string))
						)
	)
	on RKnee mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_knee_Bendy_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_knee_Bendy_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_knee_Bendy_Control" as string))
						)
	)
	on RKneeUP mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Thigh_Bendy_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Thigh_Bendy_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Thigh_Bendy_Control" as string))
						)
	)
	on RKneeD mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Calf_Bendy_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Calf_Bendy_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Calf_Bendy_Control" as string))
						)
	)
	on LKnee mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_knee_Bendy_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_knee_Bendy_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_knee_Bendy_Control" as string))
						)
	)
	on LKneeUP mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Thigh_Bendy_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Thigh_Bendy_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Thigh_Bendy_Control" as string))
						)
	)
	on LKneeD mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Calf_Bendy_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Calf_Bendy_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Calf_Bendy_Control" as string))
						)
	)
	on SelAll mouseDown senderArg arg do
	(
		select (execute("$" + edt1.text + "_" + "*_Control*" as string))
	)
	on KeyAll mouseDown senderArg arg do
	(
	Mysel = #()
	For item in selection do
	(
		append Mysel item
	)
		select (execute("$" + edt1.text + "_" + "*_Control*" as string))
	max set key keys
	Try
	(			
	select Mysel
	)catch()
	
	)
	on KeySel mouseDown senderArg arg do
	(
	max set key keys
	)
	on LFootAtt mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Foot_Att_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Foot_Att_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Foot_Att_Control" as string))
						)
	)
	on RHandAtt mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Hand_Att_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Hand_Att_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Hand_Att_Control" as string))
						)
	)
	on RFootAtt mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Foot_Att_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Foot_Att_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Foot_Att_Control" as string))
						)
	)
	on LHandAtt mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Hand_Att_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Hand_Att_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Hand_Att_Control" as string))
						)
	)
	on HeadAtt mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "Head_Att" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "Head_Att" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "Head_Att" as string))
						)
	)
	on LHIkAttch mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Ik_Parent_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Ik_Parent_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Ik_Parent_Control" as string))
						)
	)
	on RHIkAttch mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Ik_Parent_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Ik_Parent_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Ik_Parent_Control" as string))
						)
	)
	on LFIkAttch mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "L_Ik_Foot_Parent_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "L_Ik_Foot_Parent_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "L_Ik_Foot_Parent_Control" as string))
						)
	)
	on RFIkAttch mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "R_Ik_Foot_Parent_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "R_Ik_Foot_Parent_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "R_Ik_Foot_Parent_Control" as string))
						)
	)
	on AllRIF mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	
				Try (selectmore (execute("$" + edt1.text + "_" + "R_Knuckles_001_Control" as string)))catch()
				Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_001_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_011_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_021_Control" as string)))catch()
					)else if keyboard.altPressed then
					(
					Try (deselect (execute("$" + edt1.text + "_" + "R_Knuckles_001_Control" as string)))catch()
					Try (deselect (execute("$" + edt1.text + "_" + "R_Finger_001_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "R_Finger_011_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "R_Finger_021_Control" as string)))catch()
					)else
						(
	clearselection()
						Try (select (execute("$" + edt1.text + "_" + "R_Knuckles_001_Control" as string)))catch()
						Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_001_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_011_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_021_Control" as string)))catch()
				)	
	)
	on AllRMF mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	
				Try (selectmore (execute("$" + edt1.text + "_" + "R_Knuckles_002_Control" as string)))catch()
				Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_002_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_012_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_022_Control" as string)))catch()
					)else if keyboard.altPressed then
					(
					Try (deselect (execute("$" + edt1.text + "_" + "R_Knuckles_002_Control" as string)))catch()
					Try (deselect (execute("$" + edt1.text + "_" + "R_Finger_002_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "R_Finger_012_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "R_Finger_022_Control" as string)))catch()
					)else
						(
	clearselection()
						Try (select (execute("$" + edt1.text + "_" + "R_Knuckles_002_Control" as string)))catch()
						Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_002_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_012_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_022_Control" as string)))catch()
				)	
	)
	on AllRCF mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	
				Try (selectmore (execute("$" + edt1.text + "_" + "R_Knuckles_003_Control" as string)))catch()
				Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_003_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_013_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_023_Control" as string)))catch()
					)else if keyboard.altPressed then
					(
					Try (deselect (execute("$" + edt1.text + "_" + "R_Knuckles_003_Control" as string)))catch()
					Try (deselect (execute("$" + edt1.text + "_" + "R_Finger_003_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "R_Finger_013_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "R_Finger_023_Control" as string)))catch()
					)else
						(
	clearselection()
						Try (select (execute("$" + edt1.text + "_" + "R_Knuckles_003_Control" as string)))catch()
						Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_003_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_013_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_023_Control" as string)))catch()
				)
	)
	on AllRMeF mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	
	       Try (selectmore (execute("$" + edt1.text + "_" + "R_Knuckles_004_Control" as string)))catch()
				Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_004_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_014_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_024_Control" as string)))catch()
					)else if keyboard.altPressed then
					(
					Try (deselect (execute("$" + edt1.text + "_" + "R_Knuckles_004_Control" as string)))catch()
					Try (deselect (execute("$" + edt1.text + "_" + "R_Finger_004_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "R_Finger_014_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "R_Finger_024_Control" as string)))catch()
					)else
						(
	clearselection()
						Try (select (execute("$" + edt1.text + "_" + "R_Knuckles_004_Control" as string)))catch()
						Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_004_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_014_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_024_Control" as string)))catch()
				)				
	)
	on AllRPF mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	
			Try (selectmore (execute("$" + edt1.text + "_" + "R_Knuckles_0000_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_0000_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_0001_Control" as string)))catch()
					)else if keyboard.altPressed then
					(
					Try (deselect (execute("$" + edt1.text + "_" + "R_Knuckles_0000_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "R_Finger_0000_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "R_Finger_0001_Control" as string)))catch()
					)else
						(
	clearselection()
						Try (select (execute("$" + edt1.text + "_" + "R_Knuckles_0000_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_0000_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "R_Finger_0001_Control" as string)))catch()
				)		
	)
	on AllLPF mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	
				Try (selectmore (execute("$" + edt1.text + "_" + "L_Knuckles_0000_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_0000_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_0001_Control" as string)))catch()
					)else if keyboard.altPressed then
					(
					Try (deselect (execute("$" + edt1.text + "_" + "L_Knuckles_0000_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "L_Finger_0000_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "L_Finger_0001_Control" as string)))catch()
					)else
						(
	clearselection()
						Try (select (execute("$" + edt1.text + "_" + "L_Knuckles_0000_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_0000_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_0001_Control" as string)))catch()
				)		
	)
	on AllLIF mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	
				Try (selectmore (execute("$" + edt1.text + "_" + "L_Knuckles_001_Control" as string)))catch()
				Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_001_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_011_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_021_Control" as string)))catch()
					)else if keyboard.altPressed then
					(
					Try (deselect (execute("$" + edt1.text + "_" + "L_Knuckles_001_Control" as string)))catch()
					Try (deselect (execute("$" + edt1.text + "_" + "L_Finger_001_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "L_Finger_011_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "L_Finger_021_Control" as string)))catch()
					)else
						(
	clearselection()
						Try (select (execute("$" + edt1.text + "_" + "L_Knuckles_001_Control" as string)))catch()
						Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_001_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_011_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_021_Control" as string)))catch()
				)	
	)
	on AllLMF mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	
				Try (selectmore (execute("$" + edt1.text + "_" + "L_Knuckles_002_Control" as string)))catch()
				Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_002_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_012_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_022_Control" as string)))catch()
					)else if keyboard.altPressed then
					(
					Try (deselect (execute("$" + edt1.text + "_" + "L_Knuckles_002_Control" as string)))catch()
					Try (deselect (execute("$" + edt1.text + "_" + "L_Finger_002_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "L_Finger_012_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "L_Finger_022_Control" as string)))catch()
					)else
						(
	clearselection()
						Try (select (execute("$" + edt1.text + "_" + "L_Knuckles_002_Control" as string)))catch()
						Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_002_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_012_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_022_Control" as string)))catch()
				)	
	)
	on AllLCF mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
	
				Try (selectmore (execute("$" + edt1.text + "_" + "L_Knuckles_003_Control" as string)))catch()
				Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_003_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_013_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_023_Control" as string)))catch()
					)else if keyboard.altPressed then
					(
					Try (deselect (execute("$" + edt1.text + "_" + "L_Knuckles_003_Control" as string)))catch()
					Try (deselect (execute("$" + edt1.text + "_" + "L_Finger_003_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "L_Finger_013_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "L_Finger_023_Control" as string)))catch()
					)else
						(
	clearselection()
						Try (select (execute("$" + edt1.text + "_" + "L_Knuckles_003_Control" as string)))catch()
						Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_003_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_013_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_023_Control" as string)))catch()
				)
	)
	on AllLMeF mouseDown senderArg arg do
	(
	
		if keyboard.controlPressed then
			(
	       Try (selectmore (execute("$" + edt1.text + "_" + "L_Knuckles_004_Control" as string)))catch()
				Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_004_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_014_Control" as string)))catch()
			Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_024_Control" as string)))catch()
					)else if keyboard.altPressed then
					(
					Try (deselect (execute("$" + edt1.text + "_" + "L_Knuckles_004_Control" as string)))catch()
					Try (deselect (execute("$" + edt1.text + "_" + "L_Finger_004_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "L_Finger_014_Control" as string)))catch()
				Try (deselect (execute("$" + edt1.text + "_" + "L_Finger_024_Control" as string)))catch()
					)else
						(
	clearselection()
						Try (select (execute("$" + edt1.text + "_" + "L_Knuckles_004_Control" as string)))catch()
						Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_004_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_014_Control" as string)))catch()
					Try (selectmore (execute("$" + edt1.text + "_" + "L_Finger_024_Control" as string)))catch()
				)				
	)
	on cust1193 mouseDown senderArg arg do
	(
		if keyboard.controlPressed then
			(
				selectmore (execute("$" + edt1.text + "_" + "Spine001_Control" as string))
					)else if keyboard.altPressed then
					(
					deselect (execute("$" + edt1.text + "_" + "Spine001_Control" as string))
					)else
						(
						select (execute("$" + edt1.text + "_" + "Spine001_Control" as string))
						)
	)
)

--  try (cui.UnRegisterDialogBar instantRigFloater; closeRolloutFloater instantRigFloater)catch()
-- try closeRolloutFloater instantRigFloater catch()
instantRigFloater = newRolloutFloater "Ch picker" 516 693
 
instantRigFloater.pos = [10,50] 
cui.RegisterDialogBar instantRigFloater
-- cui.DockDialogBar instantRigFloater 
-- cui.floatdialogbar instantRigFloater 
cui.DockDialogBar instantRigFloater #cui_dock_left

addRollout MyCharacter instantRigFloater
 

-- createDialog MyCharacter 516 693 60 130 style:#(#style_titlebar, #style_border, #style_sysmenu, #style_minimizebox) 
--  ////////////////////////////////////////////////////////////////////////////////////////////////////