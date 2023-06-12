#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;
int sc[10],j=1,hp=100,jq=200,m4,m4d,ak,akd,us,usd,de,ded,ka,fi,pk,pkd,mi,mid,ly,lyd,l1,l1d;
bool b=true;
string s;
void SHOP(int & j,int & jq,int & m4,int & m4d,int & ak,int & akd,int & us,int & usd,int & de,int & ded,int & ka,int & fi,int & pk,int & pkd,int & mi,int & mid,int & ly,int & lyd,int & l1,int & l1d)
{
    string s;
    system("color e4");
fhs:cout<<"请按以下提示输入指令:"<<endl;
    cout<<"购买:BUY,出售:SELL,返回:BACK"<<endl;
    cout<<"指令:";
    cin>>s;
    if (s=="BACK") return;
    if (s!="BUY" && s!="SELL")
	{
		cout<<"输入无效,请重新输入"<<endl;
		goto fhs;
	}
    if (s=="BUY")
    {
		cout<<"M4 200$"<<endl;
		cout<<"伤害:50,子弹:30"<<endl;
		cout<<"AK47 240$"<<endl;
		cout<<"伤害:60,子弹:30"<<endl;
		if (j>=2)
		{
			cout<<"USP 80$"<<endl;
			cout<<"伤害:75,子弹:9"<<endl;
			cout<<"DESERT EAGLE 100$"<<endl;
			cout<<"伤害:100,子弹:7"<<endl;
    	}
		if (j>=3)
    	{
			cout<<"KATANA 150$"<<endl;
			cout<<"伤害:75,子弹:-"<<endl;
			cout<<"FIRST BLOOD 100$"<<endl;
			cout<<"伤害:50,子弹:-"<<endl;
		}
		if (j>=4)
    	{
			cout<<"PKP 250$"<<endl;
			cout<<"伤害:45/90,135,子弹:60/20*3"<<endl;
			cout<<"MINIGUN 400$"<<endl;
			cout<<"伤害:35/140,175,210,子弹:120/20*6"<<endl;
		}
		if (j>=5)
    	{
			cout<<"LYNX 320$"<<endl;
			cout<<"伤害:125/185/250,子弹:8"<<endl;
			cout<<"L115 370$"<<endl;
			cout<<"伤害:175/260/350,子弹:6"<<endl;
		}
fhh:	cout<<"如果购买武器,请输入武器名称,否则请输入NULL"<<endl;
		cout<<"购买:";
		cin>>s;
		if (s=="NULL") goto fhs;
		if (s!="M4" && s!="AK47" && s!="USP" && s!="DESERTEAGLE" && s!="USP" && s!="KATANA" && s!="FIRSTBLOOD" && s!="PKP" && s!="MINIGUN" && s!="LYNX" && s!="L115")
		{
			cout<<"输入无效,请重新输入"<<endl;
			goto fhh;
		}
		if (s=="M4")
		if (jq>=200)
		{
			m4=1;
			m4d=30;
			cout<<"M4购买成功!"<<endl;
			jq-=200;
		} else cout<<"金钱不足,M4购买失败!"<<endl;
		if (s=="AK47")
		if (jq>=240)
		{
			ak=1;
			akd=30;
			cout<<"AK47购买成功!"<<endl;
			jq-=240;
		} else cout<<"金钱不足,AK47购买失败!"<<endl;
		if (s=="USP")
		if (jq>=80)
		{
			if (j<2) cout<<"等级不足,USP购买失败!"<<endl;
			us=1;
			usd=9;
			cout<<"USP购买成功!"<<endl;
			jq-=80;
		} else cout<<"金钱不足,USP购买失败!"<<endl;
		if (s=="DESERTEAGLE")
		if (jq>=100)
		{
			if (j<2) cout<<"等级不足,DESERT EAGLE购买失败!"<<endl;
			de=1;
			ded=7;
			cout<<"DESERT EAGLE购买成功!"<<endl;
			jq-=100;
		} else cout<<"金钱不足,DESERT EAGLE购买失败!"<<endl;
		if (s=="KATANA")
		if (jq>=150)
		{
			if (j<3) cout<<"等级不足,KATANA购买失败!"<<endl;
			ka=1;
			cout<<"KATANA购买成功!"<<endl;
			jq-=150;
		} else cout<<"金钱不足,KATANA购买失败!"<<endl;
		if (s=="FIRSTBLOOD")
		if (jq>=100)
		{
			if (j<3) cout<<"等级不足,FIRST BLOOD购买失败!"<<endl;
			fi=1;
			cout<<"FIRST BLOOD购买成功!"<<endl;
			jq-=100;
		} else cout<<"金钱不足,FIRST BLOOD购买失败!"<<endl;
		if (s=="PKP")
		if (jq>=250)
		{
			if (j<4) cout<<"等级不足,PKP购买失败!"<<endl;
			pk=1;
			pkd=60;
			cout<<"PKP购买成功!"<<endl;
			jq-=250;
		} else cout<<"金钱不足,PKP购买失败!"<<endl;
		if (s=="MINIGUN")
		if (jq>=400)
		{
			if (j<4) cout<<"等级不足,MINIGUN购买失败!"<<endl;
			mi=1;
			mid=120;
			cout<<"MINIGUN购买成功!"<<endl;
			jq-=400;
		} else cout<<"金钱不足,MINIGUN购买失败!"<<endl;
		if (s=="LYNX")
		if (jq>=320)
		{
			if (j<5) cout<<"等级不足,LYNX购买失败!"<<endl;
			ly=1;
			lyd=8;
			cout<<"LYNX购买成功!"<<endl;
			jq-=320;
		} else cout<<"金钱不足,LYNX购买失败!"<<endl;
		if (s=="L115")
		if (jq>=370)
		{
			if (j<5) cout<<"等级不足,L115购买失败!"<<endl;
			l1=1;
			l1d=6;
			cout<<"L115购买成功!"<<endl;
			jq-=370;
		} else cout<<"金钱不足,L115购买失败!"<<endl;
	}
	if (s=="SELL")
	{
		if (m4==1) cout<<"M4 100$"<<endl;
		if (ak==1) cout<<"AK47 120$"<<endl;
		if (us==1) cout<<"USP 40$"<<endl;
		if (de==1) cout<<"DESERT EAGLE 50$"<<endl;
		if (ka==1) cout<<"KATANA 80$"<<endl;
		if (fi==1) cout<<"FIRST BLOOD 50$"<<endl;
		if (pk==1) cout<<"PKP 130$"<<endl;
		if (mi==1) cout<<"MINIGUN 200$"<<endl;
		if (ly==1) cout<<"LYNX 160$"<<endl;
		if (l1==1) cout<<"L115 190$"<<endl;
fho:	cout<<"如果出售武器,请输入武器名称,否则请输入NULL"<<endl;
		cout<<"出售:";
		cin>>s;
		if (s=="NULL") goto fhp;
		if (s!="M4" && s!="AK47" && s!="USP" && s!="DESERTEAGLE" && s!="USP" && s!="KATANA" && s!="FIRSTBLOOD" && s!="PKP" && s!="MINIGUN" && s!="LYNX" && s!="L115")
		{
			cout<<"输入无效,请重新输入"<<endl;
			goto fho;
		}
		if (s=="M4")
		if (m4==1)
		{
			m4=0;
			m4d=0;
			cout<<"M4出售成功!"<<endl;
			jq+=100;
		} else cout<<"你并没有M4,出售失败!"<<endl;
		if (s=="AK47")
		if (ak==1)
		{
			ak=0;
			akd=0;
			cout<<"AK47出售成功!"<<endl;
			jq+=120;
		} else cout<<"你并没有AK47,出售失败!"<<endl;
		if (s=="USP")
		if (us==1)
		{
			us=0;
			usd=0;
			cout<<"USP出售成功!"<<endl;
			jq+=40;
		} else cout<<"你并没有USP,出售失败!"<<endl;
		if (s=="DESERTEAGLE")
		if (de==1)
		{
			de=0;
			ded=0;
			cout<<"DESERT EAGLE出售成功!"<<endl;
			jq+=50;
		} else cout<<"你并没有DESERT EAGLE,出售失败!"<<endl;
		if (s=="KATANA")
		if (ka==1)
		{
			ka=0;
			cout<<"KATANA出售成功!"<<endl;
			jq+=80;
		} else cout<<"你并没有KATANA,出售失败!"<<endl;
		if (s=="FIRSTBLOOD")
		if (fi==1)
		{
			fi=0;
			cout<<"FIRST BLOOD出售成功!"<<endl;
			jq+=50;
		} else cout<<"你并没有FIRST BLOOD,出售失败!"<<endl;
		if (s=="PKP")
		if (pk==1)
		{
			pk=0;
			pkd=0;
			cout<<"PKP出售成功!"<<endl;
			jq+=130;
		} else cout<<"你并没有PKP,出售失败!"<<endl;
		if (s=="MINIGUN")
		if (mi==1)
		{
			mi=0;
			mid=0;
			cout<<"MINIGUN出售成功!"<<endl;
			jq+=200;
		} else cout<<"你并没有MINIGUN,出售失败!"<<endl;
		if (s=="LYNX")
		if (ly==1)
		{
			ly=0;
			lyd=0;
			cout<<"LYNX出售成功!"<<endl;
			jq+=160;
		} else cout<<"你并没有LYNX,出售失败!"<<endl;
		if (s=="L115")
		if (l1==1)
		{
			l1=0;
			l1d=0;
			cout<<"L115出售成功!"<<endl;
			jq+=190;
		} else cout<<"你并没有L115,出售失败!"<<endl;
	}
fhp:cout<<"请按以下提示输入指令:"<<endl;
	cout<<"如果返回,请输入YES,否则请输入NO"<<endl;
	cout<<"指令:";
	cin>>s;
	if (s=="NO") goto fhs;
	if (s!="YES")
	{
		cout<<"输入无效,请重新输入"<<endl;
		goto fhp;
	}
}
void MISSON(int sc[],int & j,int & hp,int & jq,int & m4,int & m4d,int & ak,int & akd,int & us,int & usd,int & de,int & ded,int & ka,int & fi,int & pk,int & pkd,int & mi,int & mid)
{
    int h,b=0,c=0;
    string s;
	system("color ce");
fh0:cout<<"选择关卡,一共5关,如果挑战关卡,请输入第几关,否则请输入0"<<endl;
	cout<<"关卡:";
	cin>>s;
	if (s=="0") return;
	if (s!="1" && s!="2" && s!="3" && s!="4" && s!="5")
	{
		cout<<"输入无效,请重新输入"<<endl;
		goto fh0;
	}
	if (s=="1")
	{
		int a=hp,x=3;
		system("color a9");
		h=100;
fh1:	cout<<"如果挑战关卡,请输入使用武器,否则请输入NULL"<<endl;
		cout<<"使用武器:";
		cin>>s;
		if (s=="NULL") goto fh0;
		if (s!="M4" && s!="AK47" && s!="USP" && s!="DESERTEAGLE" && s!="USP" && s!="KATANA" && s!="FIRSTBLOOD" && s!="PKP" && s!="MINIGUN" && s!="LYNX" && s!="L115")
		{
			cout<<"输入无效,请重新输入"<<endl;
			goto fh1;
		}
		if (s=="M4")
		{
			if (m4==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh1;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:M4,当前弹药:"<<m4d<<endl;
fh2:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (m4d==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (m4d==0 && s=="A") goto fh2;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh2;
				}
				if (s=="A")
				{
					h-=50;
					m4d--;
					cout<<"嗒~嗒~嗒~"<<endl;
					cout<<"敌减50HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-50..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") m4d=30;
				if (s=="Q") goto fh1;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=10;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减10HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-10###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="AK47")
		{
			if (ak==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh1;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:AK47,当前弹药:"<<akd<<endl;
fh3:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (akd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (akd==0 && s=="A") goto fh3;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh3;
				}
				if (s=="A")
				{
					h-=60;
					akd--;
					cout<<"~~当~当~~"<<endl;
					cout<<"敌减60HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-60..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") akd=30;
				if (s=="Q") goto fh1;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=10;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减10HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-10###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="USP")
		{
			if (us==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh1;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:USP,当前弹药:"<<usd<<endl;
fh4:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (usd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (usd==0 && s=="A") goto fh4;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh4;
				}
				if (s=="A")
				{
					h-=75;
					usd--;
					cout<<"~~~乒~~~~"<<endl;
					cout<<"敌减75HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-75..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") usd=9;
				if (s=="Q") goto fh1;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=10;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减10HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-10###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="DESERTEAGLE")
		{
			if (de==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh1;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:DESERT EAGLE,当前弹药:"<<ded<<endl;
fh5:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (ded==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (ded==0 && s=="A") goto fh5;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh5;
				}
				if (s=="A")
				{
					h-=100;
					ded--;
					cout<<"~~~轰~~~~"<<endl;
					cout<<"敌减100HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-100..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") ded=7;
				if (s=="Q") goto fh1;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=10;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减10HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-10###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="KATANA")
		{
			if (ka==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh1;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:KATANA"<<endl;
fh6:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"砍击:A,前进:W,后退:S,切换武器:Q"<<endl;
				cout<<"指令:";
				cin>>s;
				if (s!="A" && s!="W" && s!="S" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh6;
				}
				if (s=="A")
				{
					if (x>1)
					{
						cout<<"请先缩短距离!"<<endl;
						goto fh6;
					}
					h-=75;
					cout<<"~~~噗~~~~"<<endl;
					cout<<"敌减75HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-75..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="Q") goto fh1;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=10;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减10HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-10###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="FIRSTBLOOD")
		{
			if (fi==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh1;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:FIRST BLOOD"<<endl;
fh7:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"砍击:A,前进:W,后退:S,切换武器:Q"<<endl;
				cout<<"指令:";
				cin>>s;
				if (s!="A" && s!="W" && s!="S" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh7;
				}
				if (s=="A")
				{
					if (x>1)
					{
						cout<<"请先缩短距离!"<<endl;
						goto fh7;
					}
					h-=50;
					cout<<"~~咔~噗~~"<<endl;
					cout<<"敌减50HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-50..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="Q") goto fh1;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=10;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减10HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-10###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="PKP")
		{
			if (pk==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh1;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:PKP,当前弹药:"<<pkd<<endl;
fh8:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,扫射:X,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (pkd==0) cout<<"警告!弹匣为空!请换弹"<<endl; else
				if (pkd<3) cout<<"警告!弹药不足扫射所需"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((pkd==0 && s=="A" || (pkd==0 && s=="X")) || (pkd<3 && s=="X")) goto fh8;
				if (s!="A" && s!="X" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh8;
				}
				if (s=="A")
				{
					h-=45;
					pkd--;
					cout<<"~~~嗡~~~~"<<endl;
					cout<<"敌减45HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-45..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="X")
				{
					srand(time(NULL));
					int v=2+rand()%(2-1+1);
					if (v==2) h-=90; else h-=135;
					pkd-=3;
					cout<<"~~~嗡~~~~"<<endl;
					if (v==2) cout<<"敌减90HP~"<<endl; else cout<<"敌减135HP"<<endl;
					cout<<"........."<<endl;
					if (v==2) cout<<"...-90..."<<endl; else cout<<"..-135..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") pkd=60;
				if (s=="Q") goto fh1;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=10;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减10HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-10###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="MINIGUN")
		{
			if (mi==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh1;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:MINIGUN,当前弹药:"<<mid<<endl;
fh9:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,扫射:X,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (mid==0) cout<<"警告!弹匣为空!请换弹"<<endl; else
				if (mid<6) cout<<"警告!弹药不足扫射所需"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((mid==0 && s=="A" || (mid==0 && s=="X")) || (mid<6 && s=="X")) goto fh9;
				if (s!="A" && s!="X" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh9;
				}
				if (s=="A")
				{
					h-=35;
					mid--;
					cout<<"~~~隆~~~~"<<endl;
					cout<<"敌减35HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-35..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="X")
				{
					srand(time(NULL));
					int v=4+rand()%(3-1+1);
					if (v==4) h-=140; else if (v==5) h-=175; else h-=210;
					mid-=6;
					cout<<"~~~隆~~~~"<<endl;
					if (v==4) cout<<"敌减140HP"<<endl; else
					if (v==5) cout<<"敌减175HP"<<endl; else cout<<"敌减210HP"<<endl;
					cout<<"........."<<endl;
					if (v==4) cout<<"..-140..."<<endl; else
					if (v==5) cout<<"..-175..."<<endl; else cout<<"..-210..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") mid=120;
				if (s=="Q") goto fh1;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=10;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减10HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-10###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="LYNX")
		{
			if (ly==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh1;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:LYNX,当前弹药:"<<lyd<<endl;
fh10:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,狙击:E,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (lyd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((lyd==0 && s=="A") || (lyd==0 && s=="E")) goto fh10;
				if (s!="A" && s!="E" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh10;
				}
				if (s=="A")
				{
					h-=125;
					lyd--;
					cout<<"~~~咻~~~~"<<endl;
					cout<<"敌减125HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-125..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="E")
				{
					if (x<5)
					{
						cout<<"请先增长距离!"<<endl;
						goto fh10;
					}
					srand(time(NULL));
					int v=1+rand()%(3-1+1);
					if (v==1) h-=250; else h-=185;
					lyd--;
					cout<<"~~~咻~~~~"<<endl;
					if (v==1) cout<<"~~爆头~~~"<<endl;
					if (v==1) cout<<"敌减250HP"<<endl; else cout<<"敌减185HP"<<endl;
					cout<<"........."<<endl;
					if (v==1) cout<<"..-250..."<<endl; else cout<<"..-185..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") lyd=8;
				if (s=="Q") goto fh1;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=10;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减10HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-10###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="L115")
		{
			if (l1==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh1;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:L115,当前弹药:"<<l1d<<endl;
fh11:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,狙击:E,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (l1d==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((l1d==0 && s=="A") || (l1d==0 && s=="E")) goto fh11;
				if (s!="A" && s!="E" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh11;
				}
				if (s=="A")
				{
					h-=175;
					l1d--;
					cout<<"~~咔~咻~~"<<endl;
					cout<<"敌减175HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-175..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="E")
				{
					if (x<5)
					{
						cout<<"请先增长距离!"<<endl;
						goto fh11;
					}
					srand(time(NULL));
					int v=1+rand()%(2-1+1);
					if (v==1) h-=350; else h-=260;
					l1d--;
					cout<<"~~咔~咻~~"<<endl;
					if (v==1) cout<<"~~爆头~~~"<<endl;
					if (v==1) cout<<"敌减350HP"<<endl; else cout<<"敌减260HP"<<endl;
					cout<<"........."<<endl;
					if (v==1) cout<<"..-350..."<<endl; else cout<<"..-260..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") l1d=6;
				if (s=="Q") goto fh1;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=10;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减10HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-10###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		sc[1]++;
		if (sc[1]>3) sc[1]=3;
		if (j==1) cout<<"升级!"<<endl;
		cout<<"恭喜过关!"<<endl;
		if (j==1)
		{
			jq+=50;
			cout<<"获得50$"<<endl;
		} else
		{
			jq+=30;
			cout<<"获得30$"<<endl;
		}
		if (j==1) j=2;
		cout<<"损失血量:"<<a-hp<<endl;
	}
	if (s=="2")
	{
		if (j<2)
		{
			cout<<"请先通过第1关!"<<endl;
			goto fh0;
		}
		int a=hp,x=3;
		system("color b9");
		h=150;
fh16:	cout<<"如果挑战关卡,请输入使用武器,否则请输入NULL"<<endl;
		cout<<"使用武器:";
		cin>>s;
		if (s=="NULL") goto fh0;
		if (s!="M4" && s!="AK47" && s!="USP" && s!="DESERTEAGLE" && s!="USP" && s!="KATANA" && s!="FIRSTBLOOD" && s!="PKP" && s!="MINIGUN" && s!="LYNX" && s!="L115")
		{
			cout<<"输入无效,请重新输入"<<endl;
			goto fh16;
		}
		if (s=="M4")
		{
			if (m4==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh16;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:M4,当前弹药:"<<m4d<<endl;
fh17:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (m4d==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (m4d==0 && s=="A") goto fh17;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh17;
				}
				if (s=="A")
				{
					h-=50;
					m4d--;
					cout<<"嗒~嗒~嗒~"<<endl;
					cout<<"敌减50HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-50..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") m4d=30;
				if (s=="Q") goto fh16;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="AK47")
		{
			if (ak==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh16;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:AK47,当前弹药:"<<akd<<endl;
fh18:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (akd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (akd==0 && s=="A") goto fh18;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh18;
				}
				if (s=="A")
				{
					h-=60;
					akd--;
					cout<<"~~当~当~~"<<endl;
					cout<<"敌减60HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-60..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") akd=30;
				if (s=="Q") goto fh16;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="USP")
		{
			if (us==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh16;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:USP,当前弹药:"<<usd<<endl;
fh19:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (usd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (usd==0 && s=="A") goto fh19;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh19;
				}
				if (s=="A")
				{
					h-=75;
					usd--;
					cout<<"~~~乒~~~~"<<endl;
					cout<<"敌减75HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-75..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") usd=9;
				if (s=="Q") goto fh16;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="DESERTEAGLE")
		{
			if (de==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh16;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:DESERT EAGLE,当前弹药:"<<ded<<endl;
fh20:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (ded==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (ded==0 && s=="A") goto fh20;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh20;
				}
				if (s=="A")
				{
					h-=100;
					ded--;
					cout<<"~~~轰~~~~"<<endl;
					cout<<"敌减100HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-100..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") ded=7;
				if (s=="Q") goto fh16;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="KATANA")
		{
			if (ka==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh16;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:KATANA"<<endl;
fh21:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"砍击:A,前进:W,后退:S,切换武器:Q"<<endl;
				cout<<"指令:";
				cin>>s;
				if (s!="A" && s!="W" && s!="S" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh21;
				}
				if (s=="A")
				{
					if (x>1)
					{
						cout<<"请先缩短距离!"<<endl;
						goto fh21;
					}
					h-=75;
					cout<<"~~~噗~~~~"<<endl;
					cout<<"敌减75HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-75..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="Q") goto fh16;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="FIRSTBLOOD")
		{
			if (fi==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh16;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:FIRST BLOOD"<<endl;
fh22:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,切换武器:Q"<<endl;
				cout<<"指令:";
				cin>>s;
				if (s!="A" && s!="W" && s!="S" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh22;
				}
				if (s=="A")
				{
					if (x>1)
					{
						cout<<"请先缩短距离!"<<endl;
						goto fh22;
					}
					h-=50;
					cout<<"~~咔~噗~~"<<endl;
					cout<<"敌减50HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-50..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="Q") goto fh16;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="PKP")
		{
			if (pk==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh16;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:PKP,当前弹药:"<<pkd<<endl;
fh23:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,扫射:X,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (pkd==0) cout<<"警告!弹匣为空!请换弹"<<endl; else
				if (pkd<3) cout<<"警告!弹药不足扫射所需"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((pkd==0 && s=="A" || (pkd==0 && s=="X")) || (pkd<3 && s=="X")) goto fh23;
				if (s!="A" && s!="X" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh23;
				}
				if (s=="A")
				{
					h-=45;
					pkd--;
					cout<<"~~~嗡~~~~"<<endl;
					cout<<"敌减45HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-45..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="X")
				{
					int v=2+rand()%(2-1+1);
					if (v==2) h-=90; else h-=135;
					pkd-=3;
					cout<<"~~~嗡~~~~"<<endl;
					if (v==2) cout<<"敌减90HP~"<<endl; else cout<<"敌减135HP"<<endl;
					cout<<"........."<<endl;
					if (v==2) cout<<"...-90..."<<endl; else cout<<"..-135..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") pkd=60;
				if (s=="Q") goto fh16;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="MINIGUN")
		{
			if (mi==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh16;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:MINIGUN,当前弹药:"<<mid<<endl;
fh24:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,扫射:X,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (mid==0) cout<<"警告!弹匣为空!请换弹"<<endl; else
				if (mid<6) cout<<"警告!弹药不足扫射所需"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((mid==0 && s=="A" || (mid==0 && s=="X")) || (mid<6 && s=="X")) goto fh24;
				if (s!="A" && s!="X" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh24;
				}
				if (s=="A")
				{
					h-=35;
					mid--;
					cout<<"~~~隆~~~~"<<endl;
					cout<<"敌减35HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-35..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="X")
				{
					srand(time(NULL));
					int v=4+rand()%(3-1+1);
					if (v==4) h-=140; else if (v==5) h-=175; else h-=210;
					mid-=6;
					cout<<"~~~隆~~~~"<<endl;
					if (v==4) cout<<"敌减140HP"<<endl; else
					if (v==5) cout<<"敌减175HP"<<endl; else cout<<"敌减210HP"<<endl;
					cout<<"........."<<endl;
					if (v==4) cout<<"..-140..."<<endl; else
					if (v==5) cout<<"..-175..."<<endl; else cout<<"..-210..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") mid=120;
				if (s=="Q") goto fh16;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="LYNX")
		{
			if (ly==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh16;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:LYNX,当前弹药:"<<lyd<<endl;
fh25:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,狙击:E,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (lyd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((lyd==0 && s=="A") || (lyd==0 && s=="E")) goto fh25;
				if (s!="A" && s!="E" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh25;
				}
				if (s=="A")
				{
					h-=125;
					lyd--;
					cout<<"~~~咻~~~~"<<endl;
					cout<<"敌减125HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-125..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="E")
				{
					if (x<5)
					{
						cout<<"请先增长距离!"<<endl;
						goto fh25;
					}
					srand(time(NULL));
					int v=1+rand()%(3-1+1);
					if (v==1) h-=250; else h-=185;
					lyd--;
					cout<<"~~~咻~~~~"<<endl;
					if (v==1) cout<<"~~爆头~~~"<<endl;
					if (v==1) cout<<"敌减250HP"<<endl; else cout<<"敌减185HP"<<endl;
					cout<<"........."<<endl;
					if (v==1) cout<<"..-250..."<<endl; else cout<<"..-185..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") lyd=8;
				if (s=="Q") goto fh16;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="L115")
		{
			if (l1==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh16;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:L115,当前弹药:"<<l1d<<endl;
fh26:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,狙击:E,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (l1d==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((l1d==0 && s=="A") || (l1d==0 && s=="E")) goto fh26;
				if (s!="A" && s!="E" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh26;
				}
				if (s=="A")
				{
					h-=175;
					l1d--;
					cout<<"~~咔~咻~~"<<endl;
					cout<<"敌减175HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-175..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="E")
				{
					if (x<5)
					{
						cout<<"请先增长距离!"<<endl;
						goto fh26;
					}
					srand(time(NULL));
					int v=1+rand()%(2-1+1);
					if (v==1) h-=350; else h-=260;
					l1d--;
					cout<<"~~咔~咻~~"<<endl;
					if (v==1) cout<<"~~爆头~~~"<<endl;
					if (v==1) cout<<"敌减350HP"<<endl; else cout<<"敌减260HP"<<endl;
					cout<<"........."<<endl;
					if (v==1) cout<<"..-350..."<<endl; else cout<<"..-260..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") l1d=6;
				if (s=="Q") goto fh16;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		sc[2]++;
		if (sc[2]>3) sc[2]=3;
		if (j==2) cout<<"升级!"<<endl;
		cout<<"恭喜过关!"<<endl;
		if (j==2)
		{
			jq+=150;
			cout<<"获得150$"<<endl;
		} else
		{
			jq+=80;
			cout<<"获得80$"<<endl;
		}
		if (j==2) j=3;
		cout<<"损失血量:"<<a-hp<<endl;
	}
	if (s=="3")
	{
		if (j<3)
		{
			cout<<"请先通过第2关!"<<endl;
			goto fh0;
		}
		int a=hp,x=3;
		system("color c9");
		h=500;
fh31:	cout<<"如果挑战关卡,请输入使用武器,否则请输入NULL"<<endl;
		cout<<"使用武器:";
		cin>>s;
		if (s=="NULL") goto fh0;
		if (s!="M4" && s!="AK47" && s!="USP" && s!="DESERTEAGLE" && s!="USP" && s!="KATANA" && s!="FIRSTBLOOD" && s!="PKP" && s!="MINIGUN" && s!="LYNX" && s!="L115")
		{
			cout<<"输入无效,请重新输入"<<endl;
			goto fh31;
		}
		if (s=="M4")
		{
			if (m4==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh31;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:M4,当前弹药:"<<m4d<<endl;
fh32:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (m4d==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (m4d==0 && s=="A") goto fh32;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh32;
				}
				if (s=="A")
				{
					h-=50;
					m4d--;
					cout<<"嗒~嗒~嗒~"<<endl;
					cout<<"敌减50HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-50..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") m4d=30;
				if (s=="Q") goto fh31;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="AK47")
		{
			if (ak==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh31;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:AK47,当前弹药:"<<akd<<endl;
fh33:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (akd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (akd==0 && s=="A") goto fh33;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh33;
				}
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh33;
				}
				if (s=="A")
				{
					h-=60;
					akd--;
					cout<<"~~当~当~~"<<endl;
					cout<<"敌减60HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-60..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") akd=30;
				if (s=="Q") goto fh31;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="USP")
		{
			if (us==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh31;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:USP,当前弹药:"<<usd<<endl;
fh34:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (usd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (usd==0 && s=="A") goto fh34;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh34;
				}
				if (s=="A")
				{
					h-=75;
					usd--;
					cout<<"~~~乒~~~~"<<endl;
					cout<<"敌减75HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-75..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") usd=9;
				if (s=="Q") goto fh31;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="DESERTEAGLE")
		{
			if (de==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh31;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:DESERT EAGLE,当前弹药:"<<ded<<endl;
fh35:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (ded==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (ded==0 && s=="A") goto fh35;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh35;
				}
				if (s=="A")
				{
					h-=100;
					ded--;
					cout<<"~~~轰~~~~"<<endl;
					cout<<"敌减100HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-100..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") ded=7;
				if (s=="Q") goto fh31;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="KATANA")
		{
			if (ka==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh31;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:KATANA"<<endl;
fh36:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"砍击:A,前进:W,后退:S,切换武器:Q"<<endl;
				cout<<"指令:";
				cin>>s;
				if (s!="A" && s!="W" && s!="S" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh36;
				}
				if (s=="A")
				{
					if (x>1)
					{
						cout<<"请先缩短距离!"<<endl;
						goto fh36;
					}
					h-=75;
					cout<<"~~~噗~~~~"<<endl;
					cout<<"敌减75HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-75..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="Q") goto fh31;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="FIRSTBLOOD")
		{
			if (fi==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh31;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:FIRST BLOOD"<<endl;
fh37:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,切换武器:Q"<<endl;
				cout<<"指令:";
				cin>>s;
				if (s!="A" && s!="W" && s!="S" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh37;
				}
				if (s=="A")
				{
					if (x>1)
					{
						cout<<"请先缩短距离!"<<endl;
						goto fh37;
					}
					h-=50;
					cout<<"~~咔~噗~~"<<endl;
					cout<<"敌减50HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-50..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="Q") goto fh31;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=10;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="PKP")
		{
			if (pk==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh31;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:PKP,当前弹药:"<<pkd<<endl;
fh38:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,扫射:X,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (pkd==0) cout<<"警告!弹匣为空!请换弹"<<endl; else
				if (pkd<3) cout<<"警告!弹药不足扫射所需"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((pkd==0 && s=="A" || (pkd==0 && s=="X")) || (pkd<3 && s=="X")) goto fh38;
				if (s!="A" && s!="X" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh38;
				}
				if (s=="A")
				{
					h-=45;
					pkd--;
					cout<<"~~~嗡~~~~"<<endl;
					cout<<"敌减45HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-45..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="X")
				{
					int v=2+rand()%(2-1+1);
					if (v==2) h-=90; else h-=135;
					pkd-=3;
					cout<<"~~~嗡~~~~"<<endl;
					if (v==2) cout<<"敌减90HP~"<<endl; else cout<<"敌减135HP"<<endl;
					cout<<"........."<<endl;
					if (v==2) cout<<"...-90..."<<endl; else cout<<"..-135..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") pkd=60;
				if (s=="Q") goto fh31;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="MINIGUN")
		{
			if (mi==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh31;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:MINIGUN,当前弹药:"<<mid<<endl;
fh39:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,扫射:X,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (mid==0) cout<<"警告!弹匣为空!请换弹"<<endl; else
				if (mid<6) cout<<"警告!弹药不足扫射所需"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((mid==0 && s=="A" || (mid==0 && s=="X")) || (mid<6 && s=="X")) goto fh39;
				if (s!="A" && s!="X" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh39;
				}
				if (s=="A")
				{
					h-=35;
					mid--;
					cout<<"~~~隆~~~~"<<endl;
					cout<<"敌减35HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-35..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="X")
				{
					srand(time(NULL));
					int v=4+rand()%(3-1+1);
					if (v==4) h-=140; else if (v==5) h-=175; else h-=210;
					mid-=6;
					cout<<"~~~隆~~~~"<<endl;
					if (v==4) cout<<"敌减140HP"<<endl; else
					if (v==5) cout<<"敌减175HP"<<endl; else cout<<"敌减210HP"<<endl;
					cout<<"........."<<endl;
					if (v==4) cout<<"..-140..."<<endl; else
					if (v==5) cout<<"..-175..."<<endl; else cout<<"..-210..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") mid=120;
				if (s=="Q") goto fh31;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="LYNX")
		{
			if (ly==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh31;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:LYNX,当前弹药:"<<lyd<<endl;
fh40:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,狙击:E,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (lyd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((lyd==0 && s=="A") || (lyd==0 && s=="E")) goto fh40;
				if (s!="A" && s!="E" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh40;
				}
				if (s=="A")
				{
					h-=125;
					lyd--;
					cout<<"~~~咻~~~~"<<endl;
					cout<<"敌减125HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-125..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="E")
				{
					if (x<5)
					{
						cout<<"请先增长距离!"<<endl;
						goto fh40;
					}
					srand(time(NULL));
					int v=1+rand()%(3-1+1);
					if (v==1) h-=250; else h-=185;
					lyd--;
					cout<<"~~~咻~~~~"<<endl;
					if (v==1) cout<<"~~爆头~~~"<<endl;
					if (v==1) cout<<"敌减250HP"<<endl; else cout<<"敌减185HP"<<endl;
					cout<<"........."<<endl;
					if (v==1) cout<<"..-250..."<<endl; else cout<<"..-185..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") lyd=8;
				if (s=="Q") goto fh31;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="L115")
		{
			if (l1==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh31;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:L115,当前弹药:"<<l1d<<endl;
fh41:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,狙击:E,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (l1d==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((l1d==0 && s=="A") || (l1d==0 && s=="E")) goto fh41;
				if (s!="A" && s!="E" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh41;
				}
				if (s=="A")
				{
					h-=175;
					l1d--;
					cout<<"~~咔~咻~~"<<endl;
					cout<<"敌减175HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-175..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="E")
				{
					if (x<5)
					{
						cout<<"请先增长距离!"<<endl;
						goto fh41;
					}
					srand(time(NULL));
					int v=1+rand()%(2-1+1);
					if (v==1) h-=350; else h-=260;
					l1d--;
					cout<<"~~咔~咻~~"<<endl;
					if (v==1) cout<<"~~爆头~~~"<<endl;
					if (v==1) cout<<"敌减350HP"<<endl; else cout<<"敌减260HP"<<endl;
					cout<<"........."<<endl;
					if (v==1) cout<<"..-350..."<<endl; else cout<<"..-260..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") l1d=6;
				if (s=="Q") goto fh31;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		sc[3]++;
		if (sc[3]>3) sc[3]=3;
		if (j==3) cout<<"升级!"<<endl;
		cout<<"恭喜过关!"<<endl;
		if (j==3)
		{
			jq+=200;
			cout<<"获得200$"<<endl;
		} else
		{
			jq+=100;
			cout<<"获得100$"<<endl;
		}
		if (j==3) j=4;
		cout<<"损失血量:"<<a-hp<<endl;
	}
	if (s=="4")
	{
		if (j<4)
		{
			cout<<"请先通过第3关!"<<endl;
			goto fh0;
		}
		int a=hp,x=3;
		system("color d9");
		h=500;
fh46:	cout<<"如果挑战关卡,请输入使用武器,否则请输入NULL"<<endl;
		cout<<"使用武器:";
		cin>>s;
		if (s=="NULL") goto fh0;
		if (s!="M4" && s!="AK47" && s!="USP" && s!="DESERTEAGLE" && s!="USP" && s!="KATANA" && s!="FIRSTBLOOD" && s!="PKP" && s!="MINIGUN" && s!="LYNX" && s!="L115")
		{
			cout<<"输入无效,请重新输入"<<endl;
			goto fh46;
		}
		if (s=="M4")
		{
			if (m4==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh46;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:M4,当前弹药:"<<m4d<<endl;
fh47:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (m4d==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (m4d==0 && s=="A") goto fh47;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh47;
				}
				if (s=="A")
				{
					h-=50;
					m4d--;
					cout<<"嗒~嗒~嗒~"<<endl;
					cout<<"敌减50HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-50..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") m4d=30;
				if (s=="Q") goto fh46;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="AK47")
		{
			if (ak==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh46;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:AK47,当前弹药:"<<akd<<endl;
fh48:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (akd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (akd==0 && s=="A") goto fh48;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh48;
				}
				if (s=="A")
				{
					h-=60;
					akd--;
					cout<<"~~当~当~~"<<endl;
					cout<<"敌减60HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-60..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") akd=30;
				if (s=="Q") goto fh46;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="USP")
		{
			if (us==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh46;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:USP,当前弹药:"<<usd<<endl;
fh49:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (usd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (usd==0 && s=="A") goto fh49;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh49;
				}
				if (s=="A")
				{
					h-=75;
					usd--;
					cout<<"~~~乒~~~~"<<endl;
					cout<<"敌减75HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-75..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") usd=9;
				if (s=="Q") goto fh46;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="DESERTEAGLE")
		{
			if (de==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh46;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:DESERT EAGLE,当前弹药:"<<ded<<endl;
fh50:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (ded==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (ded==0 && s=="A") goto fh50;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh50;
				}
				if (s=="A")
				{
					h-=100;
					ded--;
					cout<<"~~~轰~~~~"<<endl;
					cout<<"敌减100HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-100..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") ded=7;
				if (s=="Q") goto fh46;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="KATANA")
		{
			if (ka==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh46;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:KATANA"<<endl;
fh51:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"砍击:A,前进:W,后退:S,切换武器:Q"<<endl;
				cout<<"指令:";
				cin>>s;
				if (s!="A" && s!="W" && s!="S" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh51;
				}
				if (s=="A")
				{
					if (x>1)
					{
						cout<<"请先缩短距离!"<<endl;
						goto fh51;
					}
					h-=75;
					cout<<"~~~噗~~~~"<<endl;
					cout<<"敌减75HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-75..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="Q") goto fh46;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="FIRSTBLOOD")
		{
			if (fi==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh46;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:FIRST BLOOD"<<endl;
fh52:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"砍击:A,前进:W,后退:S,切换武器:Q"<<endl;
				cout<<"指令:";
				cin>>s;
				if (s!="A" && s!="W" && s!="S" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh52;
				}
				if (s=="A")
				{
					if (x>1)
					{
						cout<<"请先缩短距离!"<<endl;
						goto fh52;
					}
					h-=50;
					cout<<"~~咔~噗~~"<<endl;
					cout<<"敌减50HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-50..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="Q") goto fh46;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="PKP")
		{
			if (pk==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh46;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:PKP,当前弹药:"<<pkd<<endl;
fh53:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,扫射:X,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (pkd==0) cout<<"警告!弹匣为空!请换弹"<<endl; else
				if (pkd<3) cout<<"警告!弹药不足扫射所需"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((pkd==0 && s=="A" || (pkd==0 && s=="X")) || (pkd<3 && s=="X")) goto fh53;
				if (s!="A" && s!="X" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh53;
				}
				if (s=="A")
				{
					h-=45;
					pkd--;
					cout<<"~~~嗡~~~~"<<endl;
					cout<<"敌减45HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-45..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="X")
				{
					int v=2+rand()%(2-1+1);
					if (v==2) h-=90; else h-=135;
					pkd-=3;
					cout<<"~~~嗡~~~~"<<endl;
					if (v==2) cout<<"敌减90HP~"<<endl; else cout<<"敌减135HP"<<endl;
					cout<<"........."<<endl;
					if (v==2) cout<<"...-90..."<<endl; else cout<<"..-135..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") pkd=60;
				if (s=="Q") goto fh46;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="MINIGUN")
		{
			if (mi==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh46;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:MINIGUN,当前弹药:"<<mid<<endl;
fh54:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,扫射:X,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (mid==0) cout<<"警告!弹匣为空!请换弹"<<endl; else
				if (mid<6) cout<<"警告!弹药不足扫射所需"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((mid==0 && s=="A" || (mid==0 && s=="X")) || (mid<6 && s=="X")) goto fh54;
				if (s!="A" && s!="X" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh54;
				}
				if (s=="A")
				{
					h-=35;
					mid--;
					cout<<"~~~隆~~~~"<<endl;
					cout<<"敌减35HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-35..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="X")
				{
					srand(time(NULL));
					int v=4+rand()%(3-1+1);
					if (v==4) h-=140; else if (v==5) h-=175; else h-=210;
					mid-=6;
					cout<<"~~~隆~~~~"<<endl;
					if (v==4) cout<<"敌减140HP"<<endl; else
					if (v==5) cout<<"敌减175HP"<<endl; else cout<<"敌减210HP"<<endl;
					cout<<"........."<<endl;
					if (v==4) cout<<"..-140..."<<endl; else
					if (v==5) cout<<"..-175..."<<endl; else cout<<"..-210..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") mid=120;
				if (s=="Q") goto fh46;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="LYNX")
		{
			if (ly==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh46;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:LYNX,当前弹药:"<<lyd<<endl;
fh55:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,狙击:E,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (lyd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((lyd==0 && s=="A") || (lyd==0 && s=="E")) goto fh55;
				if (s!="A" && s!="E" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh55;
				}
				if (s=="A")
				{
					h-=125;
					lyd--;
					cout<<"~~~咻~~~~"<<endl;
					cout<<"敌减125HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-125..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="E")
				{
					if (x<5)
					{
						cout<<"请先增长距离!"<<endl;
						goto fh55;
					}
					srand(time(NULL));
					int v=1+rand()%(3-1+1);
					if (v==1) h-=250; else h-=185;
					lyd--;
					cout<<"~~~咻~~~~"<<endl;
					if (v==1) cout<<"~~爆头~~~"<<endl;
					if (v==1) cout<<"敌减250HP"<<endl; else cout<<"敌减185HP"<<endl;
					cout<<"........."<<endl;
					if (v==1) cout<<"..-250..."<<endl; else cout<<"..-185..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") lyd=8;
				if (s=="Q") goto fh46;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="L115")
		{
			if (l1==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh46;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:L115,当前弹药:"<<l1d<<endl;
fh56:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,狙击:E,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (l1d==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((l1d==0 && s=="A") || (l1d==0 && s=="E")) goto fh56;
				if (s!="A" && s!="E" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh56;
				}
				if (s=="A")
				{
					h-=175;
					l1d--;
					cout<<"~~咔~咻~~"<<endl;
					cout<<"敌减175HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-175..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="E")
				{
					if (x<5)
					{
						cout<<"请先增长距离!"<<endl;
						goto fh56;
					}
					srand(time(NULL));
					int v=1+rand()%(2-1+1);
					if (v==1) h-=350; else h-=260;
					l1d--;
					cout<<"~~咔~咻~~"<<endl;
					if (v==1) cout<<"~~爆头~~~"<<endl;
					if (v==1) cout<<"敌减350HP"<<endl; else cout<<"敌减260HP"<<endl;
					cout<<"........."<<endl;
					if (v==1) cout<<"..-350..."<<endl; else cout<<"..-260..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") l1d=6;
				if (s=="Q") goto fh46;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=25;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减25HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-25###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		sc[4]++;
		if (sc[4]>3) sc[4]=3;
		if (j==4) cout<<"升级!"<<endl;
		cout<<"恭喜过关!"<<endl;
		if (j==4)
		{
			jq+=350;
			cout<<"获得350$"<<endl;
		} else
		{
			jq+=180;
			cout<<"获得180$"<<endl;
		}
		if (j==4) j=5;
		cout<<"损失血量:"<<a-hp<<endl;
	}
	if (s=="5")
	{
		if (j<5)
		{
			cout<<"请先通过第4关!"<<endl;
			goto fh0;
		}
		int a=hp,x=3;
		system("color e9");
		h=750;
fh61:	cout<<"如果挑战关卡,请输入使用武器,否则请输入NULL"<<endl;
		cout<<"使用武器:";
		cin>>s;
		if (s=="NULL") goto fh0;
		if (s!="M4" && s!="AK47" && s!="USP" && s!="DESERTEAGLE" && s!="USP" && s!="KATANA" && s!="FIRSTBLOOD" && s!="PKP" && s!="MINIGUN" && s!="LYNX" && s!="L115")
		{
			cout<<"输入无效,请重新输入"<<endl;
			goto fh61;
		}
		if (s=="M4")
		{
			if (m4==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh61;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:M4,当前弹药:"<<m4d<<endl;
fh62:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (m4d==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (m4d==0 && s=="A") goto fh62;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh62;
				}
				if (s=="A")
				{
					h-=50;
					m4d--;
					cout<<"嗒~嗒~嗒~"<<endl;
					cout<<"敌减50HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-50..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") m4d=30;
				if (s=="Q") goto fh61;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="AK47")
		{
			if (ak==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh61;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:AK47,当前弹药:"<<akd<<endl;
fh63:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (akd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (akd==0 && s=="A") goto fh63;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh63;
				}
				if (s=="A")
				{
					h-=60;
					akd--;
					cout<<"~~当~当~~"<<endl;
					cout<<"敌减60HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-60..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") akd=30;
				if (s=="Q") goto fh61;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="USP")
		{
			if (us==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh61;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:USP,当前弹药:"<<usd<<endl;
fh64:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (usd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (usd==0 && s=="A") goto fh64;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh64;
				}
				if (s=="A")
				{
					h-=75;
					usd--;
					cout<<"~~~乒~~~~"<<endl;
					cout<<"敌减75HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-75..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") usd=9;
				if (s=="Q") goto fh61;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="DESERTEAGLE")
		{
			if (de==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh61;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:DESERT EAGLE,当前弹药:"<<ded<<endl;
fh65:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"射击:A,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (ded==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if (ded==0 && s=="A") goto fh65;
				if (s!="A" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh65;
				}
				if (s=="A")
				{
					h-=100;
					ded--;
					cout<<"~~~轰~~~~"<<endl;
					cout<<"敌减100HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-100..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") ded=7;
				if (s=="Q") goto fh61;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="KATANA")
		{
			if (ka==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh61;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:KATANA"<<endl;
fh66:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"砍击:A,前进:W,后退:S,切换武器:Q"<<endl;
				cout<<"指令:";
				cin>>s;
				if (s!="A" && s!="W" && s!="S" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh66;
				}
				if (s=="A")
				{
					if (x>1)
					{
						cout<<"请先缩短距离!"<<endl;
						goto fh66;
					}
					h-=75;
					cout<<"~~~噗~~~~"<<endl;
					cout<<"敌减75HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-75..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="Q") goto fh61;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="FIRSTBLOOD")
		{
			if (fi==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh61;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:FIRST BLOOD"<<endl;
fh67:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"砍击:A,前进:W,后退:S,切换武器:Q"<<endl;
				cout<<"指令:";
				cin>>s;
				if (s!="A" && s!="W" && s!="S" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh67;
				}
				if (s=="A")
				{
					if (x>1)
					{
						cout<<"请先缩短距离!"<<endl;
						goto fh67;
					}
					h-=50;
					cout<<"~~咔~噗~~"<<endl;
					cout<<"敌减50HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-50..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="Q") goto fh61;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="PKP")
		{
			if (pk==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh61;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:PKP,当前弹药:"<<pkd<<endl;
fh68:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,扫射:X,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (pkd==0) cout<<"警告!弹匣为空!请换弹"<<endl; else
				if (pkd<3) cout<<"警告!弹药不足扫射所需"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((pkd==0 && s=="A" || (pkd==0 && s=="X")) || (pkd<3 && s=="X")) goto fh68;
				if (s!="A" && s!="X" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh68;
				}
				if (s=="A")
				{
					h-=45;
					pkd--;
					cout<<"~~~嗡~~~~"<<endl;
					cout<<"敌减45HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-45..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="X")
				{
					srand(time(NULL));
					int v=2+rand()%(2-1+1);
					if (v==2) h-=90; else h-=135;
					pkd-=3;
					cout<<"~~~嗡~~~~"<<endl;
					if (v==2) cout<<"敌减90HP~"<<endl; else cout<<"敌减135HP"<<endl;
					cout<<"........."<<endl;
					if (v==2) cout<<"...-90..."<<endl; else cout<<"..-135..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") pkd=60;
				if (s=="Q") goto fh61;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="MINIGUN")
		{
			if (mi==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh61;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:MINIGUN,当前弹药:"<<mid<<endl;
fh69:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,扫射:X,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (mid==0) cout<<"警告!弹匣为空!请换弹"<<endl; else
				if (mid<6) cout<<"警告!弹药不足扫射所需"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((mid==0 && s=="A" || (mid==0 && s=="X")) || (mid<6 && s=="X")) goto fh69;
				if (s!="A" && s!="X" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh69;
				}
				if (s=="A")
				{
					h-=35;
					mid--;
					cout<<"~~~隆~~~~"<<endl;
					cout<<"敌减35HP~"<<endl;
					cout<<"........."<<endl;
					cout<<"...-35..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="X")
				{
					srand(time(NULL));
					int v=4+rand()%(3-1+1);
					if (v==4) h-=140; else if (v==5) h-=175; else h-=210;
					mid-=6;
					cout<<"~~~隆~~~~"<<endl;
					if (v==4) cout<<"敌减140HP"<<endl; else
					if (v==5) cout<<"敌减175HP"<<endl; else cout<<"敌减210HP"<<endl;
					cout<<"........."<<endl;
					if (v==4) cout<<"..-140..."<<endl; else
					if (v==5) cout<<"..-175..."<<endl; else cout<<"..-210..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") mid=120;
				if (s=="Q") goto fh61;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=10;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减10HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-10###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="LYNX")
		{
			if (ly==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh61;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:LYNX,当前弹药:"<<lyd<<endl;
fh70:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,狙击:E,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (lyd==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((lyd==0 && s=="A") || (lyd==0 && s=="E")) goto fh70;
				if (s!="A" && s!="E" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh70;
				}
				if (s=="A")
				{
					h-=125;
					lyd--;
					cout<<"~~~咻~~~~"<<endl;
					cout<<"敌减125HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-125..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="E")
				{
					if (x<5)
					{
						cout<<"请先增长距离!"<<endl;
						goto fh70;
					}
					srand(time(NULL));
					int v=1+rand()%(3-1+1);
					if (v==1) h-=250; else h-=185;
					lyd--;
					cout<<"~~~咻~~~~"<<endl;
					if (v==1) cout<<"~~爆头~~~"<<endl;
					if (v==1) cout<<"敌减250HP"<<endl; else cout<<"敌减185HP"<<endl;
					cout<<"........."<<endl;
					if (v==1) cout<<"..-250..."<<endl; else cout<<"..-185..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") lyd=8;
				if (s=="Q") goto fh61;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		if (s=="L115")
		{
			if (l1==0)
			{
				cout<<"请先购买此武器!"<<endl;
				goto fh61;
			}
			while (h>0)
			{
				cout<<"你的血量:"<<hp<<" "<<"敌人血量:"<<h<<endl;
				cout<<"当前武器:L115,当前弹药:"<<l1d<<endl;
fh71:			cout<<"请按以下提示输入指令:"<<endl;
				cout<<"点射:A,狙击:E,前进:W,后退:S,换/上弹:R,切换武器:Q"<<endl;
				if (l1d==0) cout<<"警告!弹匣为空!请换弹"<<endl;
				cout<<"指令:";
				cin>>s;
				if ((l1d==0 && s=="A") || (l1d==0 && s=="E")) goto fh71;
				if (s!="A" && s!="E" && s!="W" && s!="S" && s!="R" && s!="Q")
				{
					cout<<"输入无效,请重新输入"<<endl;
					goto fh71;
				}
				if (s=="A")
				{
					h-=175;
					l1d--;
					cout<<"~~咔~咻~~"<<endl;
					cout<<"敌减175HP"<<endl;
					cout<<"........."<<endl;
					cout<<"..-175..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="E")
				{
					if (x<5)
					{
						cout<<"请先增长距离!"<<endl;
						goto fh71;
					}
					srand(time(NULL));
					int v=1+rand()%(2-1+1);
					if (v==1) h-=350; else h-=260;
					l1d--;
					cout<<"~~咔~咻~~"<<endl;
					if (v==1) cout<<"~~爆头~~~"<<endl;
					if (v==1) cout<<"敌减350HP"<<endl; else cout<<"敌减260HP"<<endl;
					cout<<"........."<<endl;
					if (v==1) cout<<"..-350..."<<endl; else cout<<"..-260..."<<endl;
					cout<<"........."<<endl;
				}
				if (s=="W")
				{
					x--;
					b=0;
				}
				if (s=="S")
				{
					x++;
					c=0;
				}
				if (s=="R") l1d=6;
				if (s=="Q") goto fh61;
				if (x==1 && b==0)
				{
					cout<<"你可以使用近战武器了!"<<endl;
					b=1;
				}
				if (x==5 && c==0)
				{
					cout<<"你可以使用狙击武器了!"<<endl;
					c=1;
				}
				if (h>0)
				{
					hp-=15;
					cout<<"砰~砰~砰~"<<endl;
					cout<<"你减15HP~"<<endl;
					cout<<"#########"<<endl;
					cout<<"###-15###"<<endl;
					cout<<"#########"<<endl;
					if (hp<=0) return;
				}
			}
		}
		sc[5]++;
		if (sc[5]>3) sc[5]=3;
		if (j==5) cout<<"升级!"<<endl;
		cout<<"恭喜过关!"<<endl;
		if (j==5)
		{
			jq+=450;
			cout<<"获得450$"<<endl;
		} else
		{
			jq+=230;
			cout<<"获得230$"<<endl;
		}
		if (j==5) j=6;
		cout<<"损失血量:"<<a-hp<<endl;
	}
	if (s=="6") system("color f9");
	if (s=="7") system("color 4c");
fhm:system("color ce");
	cout<<"请按以下提示输入指令:"<<endl;
	cout<<"如果返回,请输入YES,否则请输入NO"<<endl;
	cout<<"指令:";
	cin>>s;
	if (s=="NO") goto fh0;
	if (s!="YES")
	{
		cout<<"输入无效,请重新输入"<<endl;
		goto fhm;
	}
}
void HOSPITAL(int & j,int & hp,int & jq)
{
	system("color fc");
	cout<<"小回血包 10$"<<endl;
	cout<<"效果:回血5滴"<<endl;
	if (j>=2)
	{
		cout<<"中回血包 50$"<<endl;
		cout<<"效果:回血30滴"<<endl;
	}
	if (j>=3)
	{
		cout<<"大回血包 80$"<<endl;
		cout<<"效果:回血50滴"<<endl;
	}
	if (j>=4)
	{
		cout<<"打针疗伤 150$"<<endl;
		cout<<"效果:回血100滴"<<endl;
	}
	if (j>=5)
	{
		cout<<"服药疗伤 300$"<<endl;
		cout<<"效果:回血210滴"<<endl;
	}
fhi:cout<<"如果购买回血装备,请输入回血装备名称,否则请输入NULL"<<endl;
	cout<<"购买:";
	cin>>s;
	if (s=="NULL") return;
	if (s!="小回血包" && s!="中回血包" && s!="大回血包" && s!="打针疗伤" && s!="服药疗伤")
	{
		cout<<"输入无效,请重新输入"<<endl;
		goto fhi;
	}
	if (s=="小回血包")
	{
fh_1:	cout<<"如果购买小回血包,请输入小回血包数量,否则请输入0"<<endl;
		cout<<"数量:";
		cin>>s;
		for (int i=0; i<s.size(); i++)
		if ('0'>s[i] || s[i]>'9')
		{
			cout<<"输入无效,请重新输入"<<endl;
			goto fh_1;
		}
		int x=0;
		for (int i=0; i<s.size(); i++) x=x*10+int(s[i]-'0');
		if (x==0) goto fht;
		if (jq<x*10) cout<<"金钱不足,"<<x<<"个小回血包购买失败!"<<endl; else
		{
			cout<<x<<"个小回血包购买成功!"<<endl;
			hp+=x*5;
			jq-=x*10;
		}
	}
	if (s=="中回血包")
	{
		if (j<2) cout<<"等级不足,中回血包购买失败!"<<endl;
fh_2:	cout<<"如果购买中回血包,请输入中回血包数量,否则请输入0"<<endl;
		cout<<"数量:";
		cin>>s;
		for (int i=0; i<s.size(); i++)
		if ('0'>s[i] || s[i]>'9')
		{
			cout<<"输入无效,请重新输入"<<endl;
			goto fh_2;
		}
		int x=0;
		for (int i=0; i<s.size(); i++) x=x*10+int(s[i]-'0');
		if (x==0) goto fhi;
		if (jq<x*50) cout<<"金钱不足,"<<x<<"个中回血包购买失败!"<<endl; else
		{
			cout<<x<<"个中回血包购买成功!"<<endl;
			hp+=x*30;
			jq-=x*50;
		}
	}
	if (s=="大回血包")
	{
		if (j<3) cout<<"等级不足,大回血包购买失败!"<<endl;
fh_3:	cout<<"如果购买大回血包,请输入大回血包数量,否则请输入0"<<endl;
		cout<<"数量:";
		cin>>s;
		for (int i=0; i<s.size(); i++)
		if ('0'>s[i] || s[i]>'9')
		{
			cout<<"输入无效,请重新输入"<<endl;
			goto fh_3;
		}
		int x=0;
		for (int i=0; i<s.size(); i++) x=x*10+int(s[i]-'0');
		if (x==0) goto fhi;
		if (jq<x*80) cout<<"金钱不足,"<<x<<"个大回血包购买失败!"<<endl; else
		{
			cout<<x<<"个大回血包购买成功!"<<endl;
			hp+=x*50;
			jq-=x*80;
		}
	}
	if (s=="打针疗伤")
	{
		if (j<4) cout<<"等级不足,打针疗伤实施失败!"<<endl;
fh_4:	cout<<"如果实施打针疗伤,请输入打针疗伤次数,否则请输入0"<<endl;
		cout<<"次数:";
		cin>>s;
		for (int i=0; i<s.size(); i++)
		if ('0'>s[i] || s[i]>'9')
		{
			cout<<"输入无效,请重新输入"<<endl;
			goto fh_4;
		}
		int x=0;
		for (int i=0; i<s.size(); i++) x=x*10+int(s[i]-'0');
		if (x==0) goto fhi;
		if (jq<x*150) cout<<"金钱不足,"<<x<<"次打针疗伤实施失败!"<<endl; else
		{
			cout<<x<<"次打针疗伤实施成功!"<<endl;
			hp+=x*100;
			jq-=x*150;
		}
	}
	if (s=="服药疗伤")
	{
		if (j<5) cout<<"等级不足,服药疗伤实施失败!"<<endl;
fh_5:	cout<<"如果实施服药疗伤,请输入服药疗伤次数,否则请输入0"<<endl;
		cout<<"次数:";
		cin>>s;
		for (int i=0; i<s.size(); i++)
		if ('0'>s[i] || s[i]>'9')
		{
			cout<<"输入无效,请重新输入"<<endl;
			goto fh_5;
		}
		int x=0;
		for (int i=0; i<s.size(); i++) x=x*10+int(s[i]-'0');
		if (x==0) goto fhi;
		if (jq<x*300) cout<<"金钱不足,"<<x<<"次服药疗伤实施失败!"<<endl; else
		{
			cout<<x<<"次服药疗伤实施成功!"<<endl;
			hp+=x*210;
			jq-=x*300;
		}
	}
fht:cout<<"请按以下提示输入指令:"<<endl;
	cout<<"如果返回,请输入YES,否则请输入NO"<<endl;
	cout<<"指令:";
	cin>>s;
	if (s=="NO") goto fhi;
	if (s!="YES")
	{
		cout<<"输入无效,请重新输入"<<endl;
		goto fht;
	}
}
void BAG(int & j,int & hp,int & jq,int & m4,int & m4d,int & ak,int & akd,int & us,int & usd,int & de,int & ded,int & ka,int & fi,int & pk,int & pkd,int & mi,int & mid)
{
	string s;
	system("color 3f");
	cout<<"背包:"<<endl;
	if (m4==1 || ak==1) cout<<"步枪:"<<endl;
	if (m4==1) cout<<"M4 弹药:"<<m4d<<endl;
	if (ak==1) cout<<"AK47 弹药:"<<akd<<endl;
	if (pk==1 || mi==1) cout<<"机枪:"<<endl;
	if (pk==1) cout<<"PKP 弹药:"<<pkd<<endl;
	if (mi==1) cout<<"MINIGUN 弹药:"<<mid<<endl;
	if (ly==1 || l1==1) cout<<"狙击枪:"<<endl;
	if (ly==1) cout<<"LYNX 弹药:"<<lyd<<endl;
	if (l1==1) cout<<"L115 弹药:"<<l1d<<endl;
	if (us==1 || de==1) cout<<"手枪:"<<endl;
	if (us==1) cout<<"USP 弹药:"<<usd<<endl;
	if (de==1) cout<<"DESERT EAGLE 弹药:"<<ded<<endl;
	if (ka==1 || fi==1) cout<<"刀:"<<endl;
	if (ka==1) cout<<"KATANA"<<endl;
	if (fi==1) cout<<"FIRST BLOOD"<<endl;
fhb:cout<<"请按以下提示输入指令:"<<endl;
	cout<<"如果返回,请输入YES,否则请输入NO"<<endl;
	cout<<"指令:";
	cin>>s;
	if (s=="NO") goto fhb;
	if (s!="YES")
	{
		cout<<"输入无效,请重新输入"<<endl;
		goto fhb;
	}
}
void SCORE(int sc[],int & j,int & hp,int & jq,int & m4,int & m4d,int & ak,int & akd,int & us,int & usd,int & de,int & ded,int & ka,int & fi,int & pk,int & pkd,int & mi,int & mid)
{
	cout<<"胜利条件:"<<endl;
	cout<<"拥有所有武器且打通所有关卡三次"<<endl;
	cout<<"失败条件:"<<endl;
	cout<<"血量低于或等于0"<<endl;
	system("color f0");
	cout<<"关卡:"<<endl;
	for (int i=1; i<=5; i++)
	{
		cout<<"第"<<i<<"关:";
		if (sc[i]==0) cout<<"未通关";
		for (int j=1; j<=sc[i]; j++) cout<<"★";
		cout<<endl;
	}
	cout<<"武器:"<<endl;
	cout<<"M4:";
	if (m4==1) cout<<"已拥有"<<endl; else cout<<"未拥有"<<endl;
	cout<<"AK47:";
	if (ak==1) cout<<"已拥有"<<endl; else cout<<"未拥有"<<endl;
	cout<<"USP:";
	if (us==1) cout<<"已拥有"<<endl; else cout<<"未拥有"<<endl;
	cout<<"DESERT EAGLE:";
	if (de==1) cout<<"已拥有"<<endl; else cout<<"未拥有"<<endl;
	cout<<"KATANA:";
	if (ka==1) cout<<"已拥有"<<endl; else cout<<"未拥有"<<endl;
	cout<<"FIRST BLOOD:";
	if (fi==1) cout<<"已拥有"<<endl; else cout<<"未拥有"<<endl;
	cout<<"PKP:";
	if (pk==1) cout<<"已拥有"<<endl; else cout<<"未拥有"<<endl;
	cout<<"MINIGUN:";
	if (mi==1) cout<<"已拥有"<<endl; else cout<<"未拥有"<<endl;
	cout<<"LYNX:";
	if (ly==1) cout<<"已拥有"<<endl; else cout<<"未拥有"<<endl;
	cout<<"L115:";
	if (l1==1) cout<<"已拥有"<<endl; else cout<<"未拥有"<<endl;
fhc:cout<<"请按以下提示输入指令:"<<endl;
	cout<<"如果返回,请输入YES,否则请输入NO"<<endl;
	cout<<"指令:";
	cin>>s;
	if (s=="NO") goto fhc;
	if (s!="YES")
	{
		cout<<"输入无效,请重新输入"<<endl;
		goto fhc;
	}
}
int main()
{
	cout<<"※※※※※※※※※※※※※※※※※※※※※※※※"<<endl;
	cout<<"※VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV※"<<endl;
	cout<<"※    ### ┏========================┓ ###    ※"<<endl;
	cout<<"※   #####┃★★★★★游戏★★★★★┃#####   ※"<<endl;
	cout<<"※    ### ┗========================┛ ###    ※"<<endl;
	cout<<"※+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=※"<<endl;
	cout<<"※VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV※"<<endl;
	cout<<"※※※※※※※※※※※※※※※※※※※※※※※※"<<endl;
	while (s!="BEGIN")
	{
		cout<<"请按以下提示输入指令:"<<endl;
		cout<<"请输入BEGIN开始游戏"<<endl;
		cout<<"指令:";
		for (int i=1; i<=5; i++)
		{
			system("color a9");
			system("color b9");
			system("color c9");
			system("color d9");
			system("color e9");
			system("color f9");
	    }
	    cin>>s;
	    if (s!="BEGIN") cout<<"输入无效,请重新输入"<<endl;
    }
    while (s!="END")
    {
    	for (int i=1; i<=5; i++)
		{
			if (sc[i]!=3)
			{
				b=false;
				break;
			}
			b=true;
		}
		if (b && m4==1 && ak==1 && us==1 && de==1 && ka==1 && fi==1 && pk==1 && mi==1 && ly==1 && l1==1)
		{
			system("color ce");
			cout<<"游戏结束,玩家胜利"<<endl;
			system("pause");
			break;
		}
    	if (hp<=0)
		{
			system("color 6f");
			cout<<"游戏结束,玩家失败"<<endl;
			system("pause");
			break;
		}
	    system("color 9f");
	    cout<<"军阶:";
	    for (int i=1; i<=j; i++) cout<<"★";
	    cout<<endl;
	    cout<<"血量:"<<hp<<endl;
	    cout<<"金钱:"<<jq<<endl;
	    cout<<"请按以下提示输入指令:"<<endl;
	    cout<<"商店:SHOP,关卡:MISSON,医院:HOSPITAL,背包:BAG,成绩:SCORE,退出:END"<<endl;
	    cout<<"指令:";
	    cin>>s;
	    if (s!="SHOP" && s!="MISSON" && s!="HOSPITAL" && s!="BAG" && s!="SCORE" && s!="END")
		cout<<"输入无效,请重新输入"<<endl;
	    if (s=="SHOP") SHOP(j,jq,m4,m4d,ak,akd,us,usd,de,ded,ka,fi,pk,pkd,mi,mid,ly,lyd,l1,l1d);
	    if (s=="MISSON") MISSON(sc,j,hp,jq,m4,m4d,ak,akd,us,usd,de,ded,ka,fi,pk,pkd,mi,mid);
	    if (s=="HOSPITAL") HOSPITAL(j,hp,jq);
	    if (s=="BAG") BAG(j,hp,jq,m4,m4d,ak,akd,us,usd,de,ded,ka,fi,pk,pkd,mi,mid);
	    if (s=="SCORE") SCORE(sc,j,hp,jq,m4,m4d,ak,akd,us,usd,de,ded,ka,fi,pk,pkd,mi,mid);
    }
    return 0;
}
