								 // AMXXCharConverter.cpp: определяет экспортированные функции для приложения DLL.
//

#include "studio_api.h"
#include <stdio.h>
#include "UniConversion.h"
#define SourceLink "https://github.com/Chuvi-w/AMXX_Studio-ANSI-2-UTF8-converter"
#define ForumLink  "http://amx-x.ru/viewtopic.php?f=6&t=16353"

extern const char *BuildNumber();

EXPORT void PluginLoad(load_info *LoadInfo) 
{
	LoadInfo->sPluginName = "AMXX_Studio char converter.";
	LoadInfo->sPluginDescription = "ANSI->UTF8->ANSI converter";
	SendStudioMsg(SCM_MENU_ADDSUBITEM, "Tools->Converter", -1);
	SendStudioMsg(SCM_MENU_ADDITEM, "Converter->ANSI->UTF8", -1);
	SendStudioMsg(SCM_MENU_ADDITEM, "Converter->UTF8->ANSI", -1);
	SendStudioMsg(SCM_MENU_ADDITEM, "Converter->About", -1);
	/* [...] */
}

EXPORT void PluginUnload() 
{
	SendStudioMsg(SCM_REMOVE_MENUITEM, "UTF8->ANSI", 0);
	SendStudioMsg(SCM_REMOVE_MENUITEM, "ANSI->UTF8", 0);
	SendStudioMsg(SCM_REMOVE_MENUITEM, "ANSI->UTF8", 0);
	SendStudioMsg(SCM_REMOVE_MENUITEM, "About", 0);
	SendStudioMsg(SCM_REMOVE_MENUITEM, "Converter", 0);

}

void ANSI2UTF8()
{
	char *text=(char*)SendStudioMsg(SCM_EDITOR_GETTEXT,"",-1);
	if(!text)
		return;
	/*
	char *start=0,*end=0,endc,*c=text,*max=strlen(text)+text;
	char *UTF8Buf=new char[strlen(text)*3+1];
	size_t UTF8BufSz=0;
	do 
	{
	  if(*c++=='/')
	  {
		  if(*c=='/'){while(*c++!='\n'&&c<max){}}						 
		  else 
			  if(*c++=='*')
			  {
				  while((c[0]!='*')&&(c[1]!='/')&&(c<max-1))
				  {
					  c++;
				  }
			  }
	  }
	  if(*c=='\"')
	  {
		  if(!start)
		  {
			  start=c++;
		  }
		  else
		  {
			  end=c++;
			  endc=*end;

		  }
	  }

	} while (*c!='\0');
*/
	char *utf8=new char[strlen(text)*3+1];
	ascii_to_utf8(text,strlen(text)+1,utf8);
	SendStudioMsg(SCM_EDITOR_SETTEXT,utf8,-1);
	delete [] utf8;
}

void UTF82ANSI()
{
	char *text=(char*)SendStudioMsg(SCM_EDITOR_GETTEXT,"",-1);
	if(!text)
		return;
	char *ansi=new char[strlen(text)+1];
	utf8_to_ascii(text,strlen(text)+1,ansi);
	SendStudioMsg(SCM_EDITOR_SETTEXT,ansi,-1);
	delete []ansi;
}

void About()
{
	char AboutStr[1000];
	sprintf_s(AboutStr,"AMXX_Studio char converter\n\nAuthor:Chuvi\nBuildNumber:%s\nSource:%s\nDiscussion at %s",BuildNumber(),SourceLink,ForumLink);
	int len=strlen(AboutStr);
	strcat(AboutStr,"\n\nCopy this info to code?");

	if(MessageBoxA(0,AboutStr,"AMXX_Studio char converter",MB_YESNO)==IDYES)
	{
		AboutStr[len+1]=0;
		char *text=(char*)SendStudioMsg(SCM_EDITOR_GETTEXT,"",-1);
		int tlen=strlen(text)+strlen(AboutStr)+10;
		char *outtext=new char[tlen];
		sprintf_s(outtext,tlen-1,"/*\n%s*/\n%s",AboutStr,text);
		SendStudioMsg(SCM_EDITOR_SETTEXT,outtext,-1);
		delete [] outtext;

	}
}
EXPORT int CustomItemClick(CHAR *Caption) 
{
	if (strcmp(Caption, "ANSI->UTF8") == 0) 
	{ 
		ANSI2UTF8();
		return PLUGIN_HANDLED;
	}
	else if (strcmp(Caption, "UTF8->ANSI") == 0) 
	{ 
		UTF82ANSI();
		return PLUGIN_HANDLED;
	}
	else if(strcmp(Caption,"About")==0)
	{
		About();
		return PLUGIN_HANDLED;
	}
		return PLUGIN_CONTINUE;
}


