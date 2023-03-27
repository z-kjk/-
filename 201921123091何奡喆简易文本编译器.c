#include<stdio.h>
#include<stdlib.h>
typedef struct _node{
    int num;//用于保存链表的号码，用于查找相应的行数 
	char content[1000];//用于保存每行的内容 
    struct _node *next;
}node;//链表内部结构 
node *p;//建立链表
int page;// 用于保存要添加行的那一页 
char filename[20];//保存文件名 
void choose();//显示选择 
FILE *openfile();//打开文件
node *create(FILE *fp); //创建链表 
void printffile(node *head);//显示文件内容 
node *pos1(node *head);//找到相应页数 
node *pos2(node *head);//用于找到要查找的前一行 
node *add(node *head);//插入行
node *del(node *head);//删除行  
node *copy(node *head);//拷贝行 
node *revise(node *head);//修改行 
char *search(char ch1, char* ch2);//用于一个链表中字符的查找 
node* seek(node* head); //用于查找字符 
int count(char* str);//统计字符串的字符个数 
char* strcpy(char* s1, char* s2);//字符串复制函数 
int strcmp(char *ch1,char *ch2);//字符串比较函数 
char* change(char *ch1,char *ch2,char *ch3);//进行替换 
node* replace(node* head);//替换字符串
void closefile(FILE *fp,node *head);//存盘退出 
void freelist(node *head);//释放链表 
void closeeditor();//放弃编辑
int main()
{
	FILE *fp;
	int n;
	while(1){
		choose();
		scanf("%d",&n);
		if(n==1){
			fp=openfile();
			p=create(fp);//因为需要先打开文件才能建立链表 
		}else if(n==2){
			printffile(p);
		}else if(n==3){
			p=add(p);
		}else if(n==4){
			p=del(p);
		}else if(n==5){
			p=copy(p);
		}else if(n==6){
			p=revise(p);
		}else if(n==7){
			p=seek(p);
		}else if(n==8){
			p=replace(p);
		}else if(n==9){
			closefile(fp,p);
		}else if(n==0){
			closeeditor();
		}
	}
}
void choose()
{
	printf("请选择：1.打开文件<新或旧>  2.显示文件内容\n");
	printf("        3.插入行  4.删除行  5.拷贝行  6.修改行\n"); 
	printf("        7.查找字符串        8.替换字符串\n");
	printf("        9.存盘退出          0.放弃编辑\n"); 
}
FILE *openfile()
{
	FILE *fp;
	printf("请输入文件名<可包括盘符、路径，不超过19个字符>:"); 
	getchar();
	gets(filename);
	fp=fopen(filename,"a+");
	return fp;
}
node *create(FILE *fp)
{
    int a=1,b;
	node *head=NULL,*pre,*z;
    char i,x='\n';
    while(fscanf(fp,"%c",&i)!=EOF){
	    if(i==x)
		a++; 
	}
	rewind(fp);
	for(b=0;b<a;b++){
		z=(node*)malloc(sizeof(node));
		z->next=NULL;
		z->num=b+1;
		fscanf(fp,"%s",z->content);
		if(!head)//确定是否为第一个 ；要保存最开始的才能进行返回 
            head=z;
	    else pre->next=z;
	    pre=z;
	}
	return head;
}
void printffile(node *head)
{
	int b=1;
	while(head){
		printf("%d：%s\n",b,head->content);
		head=head->next;
		b++;
	}
}
node *pos1(node *head)
{
	int a;
	node *tag=head;
	scanf("%d",&a);
	while(tag){
		if(tag->num==a)
		    return tag;//若找到页数，输出页数 
		tag=tag->next; 
	}
	return NULL;//若没找到，则输出没有 
}
node *pos2(node *head)//根据题目要求是在某行前而定义的寻找函数 
{
	node *tag=head;
	scanf("%d",&page); 
	while(tag){
		if(page>1){//判断前面有行 
			if(tag->num==page-1)
			    return tag;//则返回前一行 
			tag=tag->next;
		}else if(page==1){ 
			if(tag->num==page)
			    return tag;//若前面无行，则返回这一行 
			tag=tag->next;
		}
	}
	return NULL;
}
node *add(node *head)
{
	int b,c;
	printf("在第n行前插m行，请输入n m:");
	node *tag1=pos2(head),*tag2,*pre,*z;//一个用于保持要到的页数，一个用于保存前后的结点 
	if(page!=1)//保存原本的下一结点
	    tag2=tag1->next; 
	else tag2=tag1;
	scanf("%d",&b);
	printf("请顺序输入待插入内容：\n");
	for(c=1;c<=b;c++){//因为直接是某行前，所以那行肯定存在，就不进行判断了 ；循环创建结点 
		z=(node*)malloc(sizeof(node));
		scanf("%s",z->content);
		z->num=page-1+c;
		z->next=NULL;
		if(c==1){//第一次分配需要进行独立的判断，因为如果页数为一的话，要进行类似从头开始创建新的链表的步骤 
			if(page!=1){
				tag1->next=z;
			}else head=z;	
			pre=z;
		}else{
            pre->next=z;//指向下一个 
            pre=z;
	    }
    }//因为要求是某行前，所以不需要进行判断 
    z->next=tag2;
    while(tag2){
    	tag2->num=tag2->num+b;//改变页数 
    	tag2=tag2->next;//因为要求是某行前，所以不需要对最后的指向进行赋值 
	}
	return head;
}
node *del(node *head)
{
    int b,c;
	printf("从第m行起删除n行，请输入m n:");
	node *tag1=pos1(head),*tag2;
	scanf("%d",&b);
	tag2=tag1;//因为是由跳过结点来实现删除，所以要保留原本的结点 
	for(c=0;c<=b;c++){//因为是从某行开始，所以肯定存在不进行判断 ，直接进入循环；因为由演算可知，由于是从第某行起，而直接指向下一个，而不是自己指针指向的下一个，所以要多加一次次数 
		if(tag2->next)//判断下一行是否还存在 
		    tag2=tag2->next; 
		else break;
	}
	if(c>b)//确定删除完是否还存在行数 
	    tag1->next=tag2;
	else tag1->next=NULL;
	while(tag1->next){ 
		tag1=tag1->next;//从删除后的第一行开始 
		tag1->num=tag1->num-b;//改变后面的页数 
	}
	return head;
}
node *copy(node *head)
{
	int b,c;
	printf("在第n行开始的m行插在原k行之前，请输入n m k:");
	node *tag1,*tag2,*tag3,*pre,*z;//一个用于拷贝后面行，一个用于前后联系，一个用于创建新的结点 
	tag1=pos1(head);//用于保存要开始的行 
	scanf("%d",&b);	
	tag2=pos2(head);//用于要插入的位置 
	tag1=tag1->next;//变为要开始拷贝的行 
	if(page!=1)
	    tag3=tag2->next;
	else tag3=tag2;
	for(c=1;c<=b;c++){//因为直接是某行前，所以那行肯定存在，就不进行判断了 
		z=(node*)malloc(sizeof(node));
		strcpy(z->content,tag1->content);//将原本的行数内容复制于新创建的结点中 
		z->num=page-1+c;
		z->next=NULL;
		if(c==1){
			if(page!=1){
				tag2->next=z;
			}else head=z;	
			pre=z;
		}else{
            pre->next=z;
            pre=z;
	    }
	    tag1=tag1->next;//因为要拷贝，所以被拷贝的行也要变 
    }//因为要求是某行前，所以不需要进行判断 
    z->next=tag3;//与添加差不多 
    while(tag3){
    	tag3->num=tag3->num+b;
    	tag3=tag3->next;//因为要求是某行前，所以不需要对最后的指向进行赋值 
	}
	return head;
}
node *revise(node *head)
{
	node *pag;
	printf("请输入待修改的行号：");
	pag=pos1(head);
	printf("%d：%s\n",pag->num,pag->content);
	printf("请输入新内容：");
	scanf("%s",pag->content);
	return head;
}
char *search(char ch1, char* ch2)
{
	int y;
	for (y = 0; ch2[y]; y++) {
		if (ch2[y] == ch1) {
			return (ch2+y);
		}
	}
	return NULL;
}
node* seek(node* head)
{
	int x=0,m=1,y,j,k,sign = 1;
	char str1[1000],str2[1000], *ch,c;
	node* tag = head;
	printf("请输入待查找的字符串：");
	getchar();
	gets(str1);
	j=count(str1);
	while(sign) {
		while (tag) {
			ch= search(str1[0], tag->content);//判断有没有找到 
			strcpy(str2,tag->content);//保留原字符串 
			if (ch) {
				for(k=0;k<j;k++){//判断后面是否相应的字符个数 
				    if(ch[k]=='\0')
					   break; 
				}
				if(k==j){
					ch[k]='\0';//原字符串改变 
					y=strcmp(ch,str1);//判断是否相同 
					if(y==0){
						printf("第%d行：%s\n",tag->num,str2);
						printf("第%d个字符处找到。",m++);
						strcpy(tag->content,str2);//变回原字符串 
						x++;
						printf("继续查找吗<Y/N>?");
						scanf("%c",&c);
						getchar();
						if(c=='Y'){
							x=0;
                            tag=tag->next;//无法实现同行后面字符串的查找 
							continue;						
						}else {
							sign=0;
							break;
						} 
				    }else strcpy(tag->content,str2);
			    }
			}
			tag=tag->next;
		}
		if(x==0){
		    printf("没找到\n");
		    sign=0;
		} 
	}
	return head;
}
int count(char* str)
{
	int y, j = 0;
	for (y = 0; str[y]; y++)
		j++;
	return j;
}
char* strcpy(char* s1, char* s2)//字符串复制函数 
{
	int y;
	for (y = 0; s2[y]; y++) {
		s1[y] = s2[y];
	}
	s1[y] = '\0';
	return s1;
}
int strcmp(char *ch1,char *ch2)//字符串比较函数 
{
    int x=0,y;
	y=count(ch1);
	for(x=0;x<y;x++){
		if(ch1[x]!=ch2[x])
		   break;
	}
	if(x==y)
	    return 0;
	else return 1;
}
char* change(char *ch1,char *ch2,char *ch3)
{
	int x,y,i;
	x=count(ch1);
	for (y = 0; ch3[y]; y++) {
		if(ch3[y] == ch1[0]) {
            for(i=0;i<x;i++){
            	ch3[y++]=ch2[i];
			}
			return ch3;
		}
	}
}
node* replace(node* head)
{
	int x=0,m=1,y,j,k,sign = 1;
	char str1[1000], str2[1000],str3[1000],*ch,c,*late;
	node* tag = head;
	printf("请输入待替换的字符串：");
	getchar();
	gets(str1);
	printf("替换为：");
	gets(str2);
	j = count(str1);
	while(sign){
		while (tag) {
			ch= search(str1[0], tag->content);//判断有没有找到 
			strcpy(str3,tag->content);
			if (ch) {
				for(k=0;k<j;k++){
				    if(ch[k]=='\0')
					   break; 
				}
				if(k==j){
					ch[k]='\0';
					y=strcmp(ch,str1);
					if(y==0){
						printf("第%d行：%s\n",tag->num,str3);
						printf("第%d个字符处找到。",m++);
						strcpy(tag->content,str3);
						x++;
						printf("是否替换<Y/N>？");
						scanf("%c",&c);
						getchar();
						if(c=='Y'){
							late=change(str1,str2,tag->content);
							strcpy(tag->content,late);
						}else strcpy(tag->content,str3);
						printf("继续替换吗<Y/N>?");
						scanf("%c",&c);
						getchar();
						if(c=='Y'){
							x=0;
                            tag=tag->next;//无法实现同行后面字符串的查找 
							continue;						
						}else {
							sign=0;
							break;
						} 
				    }else strcpy(tag->content,str3);//因为字符串会改变，所以在会进行截止但不符合条件的情况也要返回原本的文本内容 
			    }
			}
			tag=tag->next;
		}
		if(x==0){
		    printf("没找到\n");
		    sign=0;
	    }
    }
	return head;
}
void closefile(FILE *fp,node *head)
{
	node *pre=head;
	int i=0,x;
	fclose(fp);//因为上面的操作格式是“a+"，只是从后面添加上去，所以先关闭函数 
	fp=fopen(filename,"w+");//然后用“w+”操作，则会删除原本文件内容 
	while(pre){
		i++;//统计行数，用于后面输出 
		pre=pre->next;
	}
	pre=head;
	for(x=0;x<i;x++){
		if(x==i-1){
			fprintf(fp,"%s",pre->content);//虽然文件关闭，但链表还未释放，保留的数据还存在，所以可以输出编辑后的 
		}else {
            fprintf(fp,"%s\n",pre->content);
            pre=pre->next;
        }
	}
	fclose(fp);
	free(head);
	printf("Press any key to continue\n");
	system("pause>>nul"); 
}
void freelist(node *head)
{
	node *pre;
	while(head){
		pre=head;
		head=head->next;
		free(pre);
	}
 } 
void closeeditor()
{
    exit(0);	
}

