#include <stdio.h>
#include <string.h>

typedef struct{
	char name[16];
	char intd[64];
	int popul;
}Attract;
#define VertexType Attract
#include </home/lxll/c/sy7/pGraph.h>
#define NUM 13
#define ResetCin() do{}while(fgetc(stdin)!='\n')

void menu();
char choose(char c);
void SetVex(VertexType *vex, const char *name, const char *intd, int popul);
void PrintVex(VertexType *vex);

int main()
{
	MGraph MG_G, *G=&MG_G;
	InitGraph(G, NUM);

	char cs[2], c;
	const int n=G->vexnum;
	int i, j, path[n], cost[n];
	SetGW(G, DWS_MAX);
	InsertArc(G, "$ (1,3)#750, (1,9)#180, (1,11)#470, (2,6)#660, (2,8)#200, (2,11)#330, (2,12)#640, (3,6)#780, (4,7)#420, (4,8)#70, (5,7)#390, (5,10)#790, (5,11)#360, (5,13)#560, (6,7)#510, (6,10)#790, (7,10)#90, (7,12)#160, (9,10)#460, (9,11)#600, (9,12)#480, (10,12)#360, (11,12)#290, (12,13)#10");
	SetVex(GetVex(G,1), "大门", "景区入口, 同时也是售票处, 气势非凡", 666);
	SetVex(GetVex(G,2), "天宫道", "由托塔天王手下镇守", 220);
	SetVex(GetVex(G,3), "南天王殿", "冰天雪地, 由四大天王之一增长天王镇守", 360);
	SetVex(GetVex(G,4), "西天王殿", "烈火焚天, 由四大天王之一广目天王镇守", 480);
	SetVex(GetVex(G,5), "北天王殿", "荆棘遍布, 由四大天王之一多闻天王镇守", 600);
	SetVex(GetVex(G,6), "东天王殿", "远古遗迹, 由四大天王之一持国天王镇守", 1111);
	SetVex(GetVex(G,7), "彩虹楼", "彩虹, 由二郎神结义兄弟朱子真镇守", 1000);
	SetVex(GetVex(G,8), "朝会殿", "议天下事, 由二神结义兄弟袁洪镇守", 1200);
	SetVex(GetVex(G,9), "凌霄宝殿", "恢宏大气, 由二郎神亲自镇守", 1500);
	SetVex(GetVex(G,10), "神兽森林", "凶兽穷奇出没之地, 神兽白虎居住之地", 800);
	SetVex(GetVex(G,11), "兜率宫", "太上老君炼丹之地", 2500);
	SetVex(GetVex(G,12), "玲珑宝塔", "托塔李天王的法宝所化", 2400);
	SetVex(GetVex(G,13), "混沌之门", "传说中可以穿越时空的神秘地域", 5000);

	ungetc('\n', stdin);
	menu();
	for(;;){
		if( scanf("%1[0-9a-zA-Z]", cs)<1 ){
			fgetc(stdin);
			continue;
		}
		c=cs[0];
		c=choose(c);
		switch(c)
		{
			case 'A':
				puts("所有景点如下:");
				for(i=0;i<n;i++)
					if(GetVex0(G,i)->name[0])
						printf("%s  ", GetVex0(G,i)->name);
				ln();
			break;
			case 'Q':
				puts("exit");
				return 0;
			break;
			default:
				printf(">>>case '%c': do nothing!\n", c);

		}

		ResetCin();
		menu();
	}

	DestroyGraph(G);
}

void menu()
{
	puts("\nA.列出景点  B.游览开始");
}

void SetVex(VertexType *vex, const char *name, const char *intd, int popul)
{
	strcpy(vex->name, name);
	strcpy(vex->intd, intd);
	vex->popul=popul;
}

void PrintVex(VertexType *vex)
{
	printf("%s:", vex->name);
	printf("简介: %s\n", vex->intd);
	printf("人气: %d\n", vex->popul);
}

char choose(char c)
{
	if(0x30<=c&&c<=0x39)
		c-=0x30;
	else if(0x41<=c&&c<=0x5a)
		c-=0x40;
	else if(0x61<=c&&c<=0x7a)
		c-=0x60;
	else
		c=-1;
	c+=0x40;
	printf(">>>检测到选项\'%c\'\n", c);
	return c;
}
