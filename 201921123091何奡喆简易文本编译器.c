#include<stdio.h>
#include<stdlib.h>
typedef struct _node{
    int num;//���ڱ�������ĺ��룬���ڲ�����Ӧ������ 
	char content[1000];//���ڱ���ÿ�е����� 
    struct _node *next;
}node;//�����ڲ��ṹ 
node *p;//��������
int page;// ���ڱ���Ҫ����е���һҳ 
char filename[20];//�����ļ��� 
void choose();//��ʾѡ�� 
FILE *openfile();//���ļ�
node *create(FILE *fp); //�������� 
void printffile(node *head);//��ʾ�ļ����� 
node *pos1(node *head);//�ҵ���Ӧҳ�� 
node *pos2(node *head);//�����ҵ�Ҫ���ҵ�ǰһ�� 
node *add(node *head);//������
node *del(node *head);//ɾ����  
node *copy(node *head);//������ 
node *revise(node *head);//�޸��� 
char *search(char ch1, char* ch2);//����һ���������ַ��Ĳ��� 
node* seek(node* head); //���ڲ����ַ� 
int count(char* str);//ͳ���ַ������ַ����� 
char* strcpy(char* s1, char* s2);//�ַ������ƺ��� 
int strcmp(char *ch1,char *ch2);//�ַ����ȽϺ��� 
char* change(char *ch1,char *ch2,char *ch3);//�����滻 
node* replace(node* head);//�滻�ַ���
void closefile(FILE *fp,node *head);//�����˳� 
void freelist(node *head);//�ͷ����� 
void closeeditor();//�����༭
int main()
{
	FILE *fp;
	int n;
	while(1){
		choose();
		scanf("%d",&n);
		if(n==1){
			fp=openfile();
			p=create(fp);//��Ϊ��Ҫ�ȴ��ļ����ܽ������� 
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
	printf("��ѡ��1.���ļ�<�»��>  2.��ʾ�ļ�����\n");
	printf("        3.������  4.ɾ����  5.������  6.�޸���\n"); 
	printf("        7.�����ַ���        8.�滻�ַ���\n");
	printf("        9.�����˳�          0.�����༭\n"); 
}
FILE *openfile()
{
	FILE *fp;
	printf("�������ļ���<�ɰ����̷���·����������19���ַ�>:"); 
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
		if(!head)//ȷ���Ƿ�Ϊ��һ�� ��Ҫ�����ʼ�Ĳ��ܽ��з��� 
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
		printf("%d��%s\n",b,head->content);
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
		    return tag;//���ҵ�ҳ�������ҳ�� 
		tag=tag->next; 
	}
	return NULL;//��û�ҵ��������û�� 
}
node *pos2(node *head)//������ĿҪ������ĳ��ǰ�������Ѱ�Һ��� 
{
	node *tag=head;
	scanf("%d",&page); 
	while(tag){
		if(page>1){//�ж�ǰ������ 
			if(tag->num==page-1)
			    return tag;//�򷵻�ǰһ�� 
			tag=tag->next;
		}else if(page==1){ 
			if(tag->num==page)
			    return tag;//��ǰ�����У��򷵻���һ�� 
			tag=tag->next;
		}
	}
	return NULL;
}
node *add(node *head)
{
	int b,c;
	printf("�ڵ�n��ǰ��m�У�������n m:");
	node *tag1=pos2(head),*tag2,*pre,*z;//һ�����ڱ���Ҫ����ҳ����һ�����ڱ���ǰ��Ľ�� 
	if(page!=1)//����ԭ������һ���
	    tag2=tag1->next; 
	else tag2=tag1;
	scanf("%d",&b);
	printf("��˳��������������ݣ�\n");
	for(c=1;c<=b;c++){//��Ϊֱ����ĳ��ǰ���������п϶����ڣ��Ͳ������ж��� ��ѭ��������� 
		z=(node*)malloc(sizeof(node));
		scanf("%s",z->content);
		z->num=page-1+c;
		z->next=NULL;
		if(c==1){//��һ�η�����Ҫ���ж������жϣ���Ϊ���ҳ��Ϊһ�Ļ���Ҫ�������ƴ�ͷ��ʼ�����µ�����Ĳ��� 
			if(page!=1){
				tag1->next=z;
			}else head=z;	
			pre=z;
		}else{
            pre->next=z;//ָ����һ�� 
            pre=z;
	    }
    }//��ΪҪ����ĳ��ǰ�����Բ���Ҫ�����ж� 
    z->next=tag2;
    while(tag2){
    	tag2->num=tag2->num+b;//�ı�ҳ�� 
    	tag2=tag2->next;//��ΪҪ����ĳ��ǰ�����Բ���Ҫ������ָ����и�ֵ 
	}
	return head;
}
node *del(node *head)
{
    int b,c;
	printf("�ӵ�m����ɾ��n�У�������m n:");
	node *tag1=pos1(head),*tag2;
	scanf("%d",&b);
	tag2=tag1;//��Ϊ�������������ʵ��ɾ��������Ҫ����ԭ���Ľ�� 
	for(c=0;c<=b;c++){//��Ϊ�Ǵ�ĳ�п�ʼ�����Կ϶����ڲ������ж� ��ֱ�ӽ���ѭ������Ϊ�������֪�������Ǵӵ�ĳ���𣬶�ֱ��ָ����һ�����������Լ�ָ��ָ�����һ��������Ҫ���һ�δ��� 
		if(tag2->next)//�ж���һ���Ƿ񻹴��� 
		    tag2=tag2->next; 
		else break;
	}
	if(c>b)//ȷ��ɾ�����Ƿ񻹴������� 
	    tag1->next=tag2;
	else tag1->next=NULL;
	while(tag1->next){ 
		tag1=tag1->next;//��ɾ����ĵ�һ�п�ʼ 
		tag1->num=tag1->num-b;//�ı�����ҳ�� 
	}
	return head;
}
node *copy(node *head)
{
	int b,c;
	printf("�ڵ�n�п�ʼ��m�в���ԭk��֮ǰ��������n m k:");
	node *tag1,*tag2,*tag3,*pre,*z;//һ�����ڿ��������У�һ������ǰ����ϵ��һ�����ڴ����µĽ�� 
	tag1=pos1(head);//���ڱ���Ҫ��ʼ���� 
	scanf("%d",&b);	
	tag2=pos2(head);//����Ҫ�����λ�� 
	tag1=tag1->next;//��ΪҪ��ʼ�������� 
	if(page!=1)
	    tag3=tag2->next;
	else tag3=tag2;
	for(c=1;c<=b;c++){//��Ϊֱ����ĳ��ǰ���������п϶����ڣ��Ͳ������ж��� 
		z=(node*)malloc(sizeof(node));
		strcpy(z->content,tag1->content);//��ԭ�����������ݸ������´����Ľ���� 
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
	    tag1=tag1->next;//��ΪҪ���������Ա���������ҲҪ�� 
    }//��ΪҪ����ĳ��ǰ�����Բ���Ҫ�����ж� 
    z->next=tag3;//����Ӳ�� 
    while(tag3){
    	tag3->num=tag3->num+b;
    	tag3=tag3->next;//��ΪҪ����ĳ��ǰ�����Բ���Ҫ������ָ����и�ֵ 
	}
	return head;
}
node *revise(node *head)
{
	node *pag;
	printf("��������޸ĵ��кţ�");
	pag=pos1(head);
	printf("%d��%s\n",pag->num,pag->content);
	printf("�����������ݣ�");
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
	printf("����������ҵ��ַ�����");
	getchar();
	gets(str1);
	j=count(str1);
	while(sign) {
		while (tag) {
			ch= search(str1[0], tag->content);//�ж���û���ҵ� 
			strcpy(str2,tag->content);//����ԭ�ַ��� 
			if (ch) {
				for(k=0;k<j;k++){//�жϺ����Ƿ���Ӧ���ַ����� 
				    if(ch[k]=='\0')
					   break; 
				}
				if(k==j){
					ch[k]='\0';//ԭ�ַ����ı� 
					y=strcmp(ch,str1);//�ж��Ƿ���ͬ 
					if(y==0){
						printf("��%d�У�%s\n",tag->num,str2);
						printf("��%d���ַ����ҵ���",m++);
						strcpy(tag->content,str2);//���ԭ�ַ��� 
						x++;
						printf("����������<Y/N>?");
						scanf("%c",&c);
						getchar();
						if(c=='Y'){
							x=0;
                            tag=tag->next;//�޷�ʵ��ͬ�к����ַ����Ĳ��� 
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
		    printf("û�ҵ�\n");
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
char* strcpy(char* s1, char* s2)//�ַ������ƺ��� 
{
	int y;
	for (y = 0; s2[y]; y++) {
		s1[y] = s2[y];
	}
	s1[y] = '\0';
	return s1;
}
int strcmp(char *ch1,char *ch2)//�ַ����ȽϺ��� 
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
	printf("��������滻���ַ�����");
	getchar();
	gets(str1);
	printf("�滻Ϊ��");
	gets(str2);
	j = count(str1);
	while(sign){
		while (tag) {
			ch= search(str1[0], tag->content);//�ж���û���ҵ� 
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
						printf("��%d�У�%s\n",tag->num,str3);
						printf("��%d���ַ����ҵ���",m++);
						strcpy(tag->content,str3);
						x++;
						printf("�Ƿ��滻<Y/N>��");
						scanf("%c",&c);
						getchar();
						if(c=='Y'){
							late=change(str1,str2,tag->content);
							strcpy(tag->content,late);
						}else strcpy(tag->content,str3);
						printf("�����滻��<Y/N>?");
						scanf("%c",&c);
						getchar();
						if(c=='Y'){
							x=0;
                            tag=tag->next;//�޷�ʵ��ͬ�к����ַ����Ĳ��� 
							continue;						
						}else {
							sign=0;
							break;
						} 
				    }else strcpy(tag->content,str3);//��Ϊ�ַ�����ı䣬�����ڻ���н�ֹ�����������������ҲҪ����ԭ�����ı����� 
			    }
			}
			tag=tag->next;
		}
		if(x==0){
		    printf("û�ҵ�\n");
		    sign=0;
	    }
    }
	return head;
}
void closefile(FILE *fp,node *head)
{
	node *pre=head;
	int i=0,x;
	fclose(fp);//��Ϊ����Ĳ�����ʽ�ǡ�a+"��ֻ�ǴӺ��������ȥ�������ȹرպ��� 
	fp=fopen(filename,"w+");//Ȼ���á�w+�����������ɾ��ԭ���ļ����� 
	while(pre){
		i++;//ͳ�����������ں������ 
		pre=pre->next;
	}
	pre=head;
	for(x=0;x<i;x++){
		if(x==i-1){
			fprintf(fp,"%s",pre->content);//��Ȼ�ļ��رգ�������δ�ͷţ����������ݻ����ڣ����Կ�������༭��� 
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

