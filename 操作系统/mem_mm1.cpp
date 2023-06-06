#include"iostream.h"
#include"string.h"
#include"stdio.h"
#include <iomanip.h>
typedef struct NODE
{
	bool flag;
	char id[10];
	int staddr;
	int size;
    struct NODE *nextptr;
}NODE;
bool Search(NODE* &head,char id[]);
void Allocate(NODE* &head)
{
	NODE *preptr,*curptr,*blanknode;
	preptr=curptr=head;
	int size,sum=0;
	char id[10];
	cout<<"请输入需分配的单元数:";
	cin>>size;
	
	while(curptr)
	{
		if(curptr->flag==true)
		{
			preptr=curptr;
			curptr=curptr->nextptr;
		}
		else
		{
			if(curptr->size>=size)
			{
				cout<<"请输入进程的ID:";
				cin>>id;
				if(Search(head,id))
					cout<<"内存中已存在该ID的进程!"<<endl;
				else
				{
					NODE* newnode=new NODE;
                    newnode->flag=true;
				    strcpy(newnode->id,id);
				    newnode->staddr=curptr->staddr;
			        newnode->size=size;
				    if(curptr==head)
					{
						newnode->nextptr=curptr;
					    head=newnode;
					}
				    else
					{
					    preptr->nextptr=newnode;
				        newnode->nextptr=curptr;
					}
				    curptr->staddr+=size;
				    curptr->size-=size;
				    return;
				}
			}
			else
			{
				preptr=curptr;
				curptr=curptr->nextptr;
			}
		}
	}
	if(curptr==NULL)
	{
		preptr=curptr=head;
		while(curptr)
		{
			if(curptr->flag==true)
			{
				preptr=curptr;
				curptr->staddr-=sum;
				curptr=curptr->nextptr;
			}
			else
			{
				if(curptr==head)
				{
					sum+=curptr->size;
					curptr=curptr->nextptr;
					delete preptr;
					preptr=curptr;
					head=curptr;
				}
				else
				{
					sum+=curptr->size;
				    preptr->nextptr=curptr->nextptr;
				    NODE* temp=curptr;
				    curptr=curptr->nextptr;
				    delete temp;
				}
			}
		}
		if(sum>=size)
		{
			cout<<"请输入进程的ID:";
			cin>>id;
			while(Search(head,id))
			{
				cout<<"内存中已存在该ID的进程!"<<endl;
				cout<<"请输入进程的ID:";
				cin>>id;
			}
			NODE* newnode=new NODE;
			newnode->flag=true;
			strcpy(newnode->id,id);
			newnode->size=size;
			newnode->staddr=preptr->staddr+preptr->size;
			blanknode=new NODE;
			blanknode->flag=false;
			blanknode->id[0]='\0';
			blanknode->size=sum-size;
			preptr->nextptr=newnode;
			newnode->nextptr=blanknode;
			blanknode->nextptr=NULL;
			blanknode->staddr=newnode->staddr+newnode->size;
			
		}
		else
		{
		    blanknode=new NODE;
			blanknode->flag=false;
			blanknode->id[0]='\0';
			blanknode->staddr=preptr->staddr+preptr->size;
			blanknode->size=sum;
			preptr->nextptr=blanknode;
			blanknode->nextptr=NULL;
			cout<<"没有足够的内存可以分配!"<<endl;
		}
	}
}
void Release(NODE* &head)
{
	char id[10];
	NODE *preptr,*curptr,*folptr;
	preptr=curptr=head;
	cout<<"请输入要释放的ID:";
	cin>>id;
	
	while(strcmp(curptr->id,id))
	{
		if((curptr->nextptr)!=NULL)
		{
			preptr=curptr;
		    curptr=curptr->nextptr;
		}
		else
		{
			curptr=curptr->nextptr;
			break;
		}
	}
	if(curptr!=NULL)
	{
		folptr=curptr->nextptr;
		if(curptr==head)
		{
			if(folptr->flag==false)
			{
				curptr->nextptr=folptr->nextptr;
				curptr->size+=folptr->size;
				curptr->flag=false;
				curptr->id[0]='\0';
				delete folptr;
			}
			else
			{
				curptr->flag=false;
				curptr->id[0]='\0';
			}
		}
		
		else if(folptr!=NULL)
		{
			if(preptr->flag==false&&folptr->flag==false)
			{
				preptr->nextptr=folptr->nextptr;
				preptr->size=preptr->size+curptr->size+folptr->size;
				delete curptr;
				delete folptr;
			}
			else if(preptr->flag==true&&folptr->flag==false)
			{
				curptr->nextptr=folptr->nextptr;
				curptr->size+=folptr->size;
				curptr->flag=false;
				curptr->id[0]='\0';
				delete folptr;
			}
			else if(preptr->flag==false&&folptr->flag==true)
			{
				preptr->nextptr=curptr->nextptr;
				preptr->size+=curptr->size;
				delete curptr;
			}
			else
			{
				curptr->flag=false;
				curptr->id[0]='\0';
			}
		}
		else
		{
			if(preptr->flag==false)
			{
				preptr->nextptr=curptr->nextptr;//folptr==curptr->nextptr==NULL
				preptr->size+=curptr->size;
				delete curptr;
			}
			else
			{
				curptr->flag=false;
				curptr->id[0]='\0';
			}
		}
	}
	else
		cout<<"系统中没有对应ID的进程!"<<endl;
}
void Examine(NODE* &head)
{
	NODE* curptr=head;
	while(curptr)
	{
		if(curptr->flag==true)
		{
			cout<<curptr->staddr<<':'<<endl;
            cout<<"   |   pid:"<<curptr->id<<"   |"<<endl;
            cout<<"   |   size:"<<curptr->size<<setw(3)<<"|"<<endl;
			cout<<"    ---------------"<<endl;
		}
		else
		{
			cout<<curptr->staddr<<':'<<endl;
			cout<<"   |   free       |"<<endl;
			cout<<"   |   size:"<<curptr->size<<setw(3)<<"|"<<endl;
			cout<<"    ---------------"<<endl;
		}
		curptr=curptr->nextptr;
	}
}
bool Search(NODE* &head,char id[])
{
	NODE* curptr=head;
	while(curptr)
	{
		if(strcmp(curptr->id,id)==0)
			return true;
		else
			curptr=curptr->nextptr;
	}
	return false;
}
/****************帮助****************/
void Manual()
{
	cout<<"本系统用以模拟内存的请求分配与释放回收,"<<endl;
	cout<<"用户可通过观察内存映像获取内存分配信息."<<endl;

        
}
/****************I/O注意事项****************/
void Attention()
{
	cout<<"WARNING!"<<endl;
	cout<<"在程序提示输入数字信息时,用户"<<endl;
	cout<<"必须保证输入数据的正确与完整,"<<endl;
	cout<<"切勿输入一些与数据无关的信息."<<endl;
	cout<<"这是本程序的一个小BUG,将会在"<<endl;
	cout<<"后续的升级版本中得到修正:）"<<endl;
}
/****************版本及作者信息****************/
void Info()
{
	cout<<"Version:Beta1.0(To be continued...)"<<endl;
	cout<<"Author:YLKing"<<endl;
	cout<<"Tel:0571-88888888"<<endl;
	cout<<"E-mail:123456@163.com"<<endl;
	cout<<"Thank you for using and support!"<<endl;
}
void main()
{
	bool tag=true;
	int option;
	NODE *inispace,*hd;
	inispace=new NODE;
	inispace->flag=false;
    inispace->id[0]='\0';
	inispace->staddr=0;
	inispace->size=1000;
	inispace->nextptr=NULL;
	hd=inispace;
	//Allocate(hd);
	//Release(hd);
	cout<<"*******内存模拟管理系统*******"<<endl;
	do{
		cout<<"option:"<<endl;
		cout<<"0 --------- 退出系统"<<endl;
		cout<<"1 --------- 查看内存"<<endl;
		cout<<"2 --------- 分配内存"<<endl;
		cout<<"3 --------- 释放内存"<<endl;
		cout<<"4 --------- 用户手册"<<endl;
		cout<<"5 --------- I/O注意事项"<<endl;
		cout<<"6 --------- 版本及作者信息"<<endl;
		cout<<"请输入对应操作:";
		cin>>option;
		switch(option)
		{
		case 0:tag=false;break;
		case 1:Examine(hd);break;
		case 2:Allocate(hd);break;
		case 3:Release(hd);break;
		case 4:Manual();break;
		case 5:Attention();break;
        case 6:Info();break;
		default:cout<<"没有对应操作!"<<endl;
		}
	}while(tag==true);
	cout<<"谢谢使用本系统!"<<endl;

}
