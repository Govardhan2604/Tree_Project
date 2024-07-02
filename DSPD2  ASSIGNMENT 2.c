#include<stdio.h>
#include<stdlib.h>
#include<string.h>


// course(1)= IOOM (2);
// course(2)= DSPD2 (1);
// course(3)= CO (6);
// course(4)= SW1 (1);
// course(5)= CPL (4);
// course(6)= DCMP (3);
// course(7)= TC (4);
// course(8)= SW2 (5);


// slot(1) = 10:00 AM - 11:00 AM
// slot(2) = 11:00 AM - 12:00 AM
// slot(3) = 12:00 PM - 01:00 PM
// LUNCH   = 01:00 PM - 02:00 PM
// slot(4) = 02:00 PM - 03:00 PM
// slot(5) = 03:00 PM - 04:00 PM
// slot(6) = 04:00PM  - 05:00 PM
//declaring a structure of a student
struct student
{
	char name[20];
	int enrollno;
	int courses[5];
	struct student *left;
	struct student *right;
	int height;
	
};

//declaring a structure of courses
struct course
{
	char coursename[30];
	int course_id;
	int slot_no;
	int numstudents;
	struct student *headstudent;
	struct course *left1;
	struct course *right1;
	int height1;
	
};

struct classrooms
{
	int Roomno;
	int capacity;
	int seatcapacity[10][12];
	struct course *c;
	struct classrooms *left2;
	struct classrooms *right2;
	int height2;
	
};



int getbalancefactor(struct student *n);
int getbalancefactor(struct student *n)
{
	if(n==NULL)
	{
		return 0;
	}
	else
	{
		return getHeight(n->left)-getHeight(n->right);
	}
}


int getHeight(struct student *m);
int getHeight(struct student *m)
{
	if(m==NULL)
	{
		return 0;
	}
	else 
    {
    	return m->height;
	}
}

// RR rotation
struct student* rightRotate(struct student *y)
{
	struct student *x=y->left ;
	struct student *temp=x->right;
	
	
	x->right=y;
	y->left=temp;
	
	y->height=max(getHeight(y->right), getHeight(y->left)) + 1 ;
	x->height=max(getHeight(x->right), getHeight(x->left)) + 1 ;
	
	return x;
	
}

//LL rotate

struct student* leftRotate(struct student *x)
{
	struct student *y=x->right ;
	struct student *temp1=y->left;
	
	
	y->left=x;
	x->right=temp1;
	
	y->height=max(getHeight(y->right), getHeight(y->left)) + 1 ;
	x->height=max(getHeight(x->right), getHeight(x->left)) + 1 ;
	
	return y;
	
}


//creating a student tree
struct student *studentnode(char *stname,int Enrollno,int *co)
{
	struct student *newnode=malloc(sizeof(struct student));
	strcpy(newnode->name,stname);
	newnode->enrollno=Enrollno;
	int i;
	for(i=0;i<=4;i++)
	{
		newnode->courses[i]=co[i];
	}
	newnode->left=NULL;
	newnode->right=NULL;
	newnode->height=1;
	return newnode;
	
}

struct student *findmin(struct student *ptr1);
int checkingstudenttree(struct student *ptrst,int coid) ;


struct student *createstudent_List(struct student *root,char *sname, int enrno, int *c)       
{
	if(root==NULL)
	{
	root = studentnode(sname,enrno,c);	
	}  
	else if(enrno<root->enrollno)
	{
		root->left=createstudent_List(root->left,sname,enrno,c);	
	 
}
else
{
	root->right=createstudent_List(root->right,sname,enrno,c);	
}
return root;

root->height=1+ max(getHeight(root->left),getHeight(root->right));     	

int bf = getbalanceFactor(root);

//LL case
if(bf > 1 && root->enrollno < root->left->enrollno)
{
	rightRotate(root);
}

//RR case
if(bf < -1 && root->enrollno > root->right->enrollno)
{
	leftRotate(root);
	}	
	
//LR case
if(bf > 1 && root->enrollno > root->left->enrollno)
{
	root->left=leftRotate(root->left);
	rightRotate(root);
	}	

//RL case 
if(bf < -1 && root->enrollno < root->right->enrollno)
{
     root->right=rightRotate(root->left);
     leftRotate(root);
	}	
	

}

//max function
int max(int a, int b)
{
	if(a>b)
	{
		return a;
	}
	else
	{
		return b;
	}
}


//creating a course tree

struct course *coursenode(char *coname,int courseids,int slotnum )
{
	struct course *newcoursenode=malloc(sizeof(struct course));
	strcpy(newcoursenode->coursename,coname);
	newcoursenode->course_id=courseids;
	newcoursenode->slot_no=slotnum; 
	newcoursenode->headstudent=NULL;  
	newcoursenode->left1=NULL;
	newcoursenode->right1=NULL;
	newcoursenode->height1=1;
	return newcoursenode;
	
}


struct course *createcourse_List(struct course* root1,char *cname,int courseid,int slotno)
{
	if(root1==NULL)
	{
		root1=coursenode(cname,courseid,slotno);
	}
	else if(courseid<root1->course_id)
	{
		root1->left1=createcourse_List(root1->left1,cname,courseid,slotno);
	}
	else
	{
		root1->right1=createcourse_List(root1->right1,cname,courseid,slotno);	
	}
	return root1;
	
root1->height1=1+ max(getHeight(root1->left1),getHeight(root1->right1));	

int bf1 = getbalanceFactor(root1);

//LL case
if(bf1 > 1 && root1->course_id < root1->left1->course_id)
{
	rightRotate(root1);
}

//RR case
if(bf1 < -1 && root1->course_id > root1->right1->course_id)
{
	leftRotate(root1);
	}	
	
//LR case
if(bf1 > 1 && root1->course_id > root1->left1->course_id)
{
	root1->left1=leftRotate(root1->left1);
	rightRotate(root1);
	}	

//RL case 
if(bf1 < -1 && root1->course_id < root1->right1->course_id)
{
     root1->right1=rightRotate(root1->left1);                                                        
     leftRotate(root1);
	}	
		

	
// creating a classroom tree
	
	
	
	
	
	
	
	
	
}



void printstudentList(struct student *root)
{
	if(root==NULL)
	{
		return;
	}
	else
	{
	printstudentList(root->left);
	printf("%s %d\n",root->name,root->enrollno);
	printstudentList(root->right);
	
}
}

void printcourseList(struct course *root1)
{
	
	if(root1==NULL)
	{
		return;
	}
	else 
	{
	printcourseList(root1->left1);
	printf("%s %d\n",root1->coursename,root1->course_id);
	printcourseList(root1->right1);	
	}
}

struct student *addst_to_course(struct student **, int, struct student *);
struct student *createcs_tree(int, struct student *);
void studenttraverse(struct course *, struct student **);

void printcourse_students(struct course *rooot1, struct student *rooot) {
    if (rooot1 == NULL) {
        return;
    }
    else {
        
        printcourse_students(rooot1->left1, rooot);
        studenttraverse(rooot1, &rooot);
        printcourse_students(rooot1->right1, rooot);
    }
}

void studenttraverse(struct course *rut1, struct student **rut) {
    int i;
    if (*rut == NULL) {
        return;
    }
    else {
       
        studenttraverse(rut1, &(*rut)->left);
        for (i = 0; i <=4; i++) {
            if (rut1->course_id == (*rut)->courses[i]) {
                printf("%s course is taken by %d %s\n", rut1->coursename, (*rut)->enrollno, (*rut)->name);
               // rut1->headstudent = addst_to_course(rut1->headstudent, (*rut)->enrollno, *rut);
            }
        }
        studenttraverse(rut1, &(*rut)->right);
         
        
    }
}





struct student *addst_to_course(struct student **ptr, int enrollnum, struct student *ptrs) {
    if (*ptr == NULL) {
        *ptr = createcs_tree(enrollnum, ptrs);
    }
    else if ((*ptr)->enrollno > enrollnum) {
        (*ptr)->left = addst_to_course(&(*ptr)->left, enrollnum, ptrs);
    }
    else {
        (*ptr)->right = addst_to_course(&(*ptr)->right, enrollnum, ptrs);
    }
    return *ptr;
}

struct student *createcs_tree(int ern, struct student *sptr) {
    struct student *newcsnode = malloc(sizeof(struct student));
    strcpy(newcsnode->name, sptr->name);
    newcsnode->enrollno = ern;
    newcsnode->left = NULL;
    newcsnode->right = NULL;
    return newcsnode;
}

/*
void studenttraverse(struct student* rut)
{
    int i;
    if (rut == NULL)
    {
        return;
    }
    else
    {
        studenttraverse(rut->left);
        for (i = 0; i < 5; i++)
        {
            printf("%d course is taken by %d %s\n", rut->courses[i], rut->enrollno, rut->name);
        }
        studenttraverse(rut->right);
    }
}

*/
/*
struct student * deletestudent(struct student *ptr,int ennum)
{
	if(ptr==NULL)
	{
		return;
	}
	else if(ennum<ptr->enrollno)
	{
		ptr->left=deletestudent(ptr->left,ennum);
	}
	else if(ennum>ptr->enrollno)
	{
		ptr->right=deletestudent(ptr->right,ennum);
	}
	else
	{
		if(ptr->left==NULL && ptr->right==NULL)
		{
			free(ptr);
			ptr=NULL;
			return ptr;
		}
		else if(ptr->left==NULL)
		{
			struct student *temp=ptr;
			ptr=ptr->right;
			free(temp);
			
		}
		else if(ptr->right==NULL)
		{
			struct student *temp=ptr;
			ptr=ptr->left;
			free(temp);
		}
		else
		{
		struct student *temp=findmin(ptr->right);
		ptr->enrollno=temp->enrollno;
		ptr->right=deletestudent(ptr->right,temp->enrollno);
		
			
		}
	}
	return ptr;
}


struct student * findmin(struct student *ptr1)
{
	if(ptr1==NULL)
	{
		return NULL;
	}
	else
	{
	struct student *temp1=ptr1;
	while(temp1->left!=NULL)
	{
		temp1=temp1->left;
	}
	
}
return temp1;

}
*/


struct student * deletestudent(struct student *ptr,int ennum)
{
	if(ptr==NULL)
	{
		return NULL;
	}
	else if(ennum<ptr->enrollno)
	{
		ptr->left=deletestudent(ptr->left,ennum);
	}
	else if(ennum>ptr->enrollno)
	{
		ptr->right=deletestudent(ptr->right,ennum);
	}
	else
	{
		if(ptr->left==NULL && ptr->right==NULL)
		{
			free(ptr);
			ptr=NULL;
			return ptr;
		}
		else if(ptr->left==NULL)
		{
			struct student *temp=ptr;
			ptr=ptr->right;
			free(temp);
			
		}
		else if(ptr->right==NULL)
		{
			struct student *temp=ptr;
			ptr=ptr->left;
			free(temp);
		}
		else
		{
		struct student *temp=findmin(ptr->right);
		ptr->enrollno=temp->enrollno;
		ptr->right=deletestudent(ptr->right,temp->enrollno);
		
			
		}
	}
	return ptr;
}


struct student *findmin(struct student *ptr1)
{
	if(ptr1==NULL)
	{
		return NULL;
	}
	else
	{
	struct student *temp1=ptr1;
	while(temp1->left!=NULL)
	{
		temp1=temp1->left;
	}
	return temp1;
}

}


struct course * deletecourse(struct course *ptrc,int cid,struct student *ptrs)
{
	if(ptrc==NULL)
	{
		return NULL;
	}
	else if(cid<ptrc->course_id)
	{
		ptrc->left1=deletecourse(ptrc->left1,cid,ptrs);
	}
	else if(cid>ptrc->course_id)
	{
		ptrc->right1=deletecourse(ptrc->right1,cid,ptrs);
	}
	else
	{
		if(checkingstudenttree(ptrs,cid)==1)
		{
			printf("%s cannot be deleted \n",ptrc->coursename);
		}
		else
		{
			
		
		if(ptrc->left1==NULL && ptrc->right1==NULL)
		{
			free(ptrc);
			ptrc=NULL;
			return ptrc;
		}
		else if(ptrc->left1==NULL)
		{
			struct course *temp2=ptrc;
			ptrc=ptrc->right1;
			free(temp2);
			
		}
		else if(ptrc->right1==NULL)
		{
			struct course *temp2=ptrc;
			ptrc=ptrc->left1;
			free(temp2);
		}
		else
		{
		struct course *temp2=findmin(ptrc->right1);
		ptrc->course_id=temp2->course_id;
		ptrc->right1=deletecourse(ptrc->right1,temp2->course_id,ptrs);
		
			
		}
	}
	return ptrc;
}

	
}

int checkingstudenttree(struct student *ptrst,int coid) 
{
	if(ptrst==NULL)
	{
		return;
	 } 
	 else
	 {
	 	int i;int flag=1,a;
	 	checkingstudenttree(ptrst->left,coid);
	 	for(i=0;i<=4 && flag==1;i++)
	 	{
	 		if(ptrst->courses[i]==coid)
	 		{
	 		 a=1;
			 }
		 }
		 if(a==1)
		 {
		 	return 1;
		 }
		 else
		 {
		 	return 0;
		 }
		 checkingstudenttree(ptrst->right,coid);
		 
	 }
	 
}

//q1
void checkingslot(struct student *ptrst,struct course*ptrco)
{
	if(ptrst==NULL)
	{
		return ;
	}
	else
	{
		checkingslot(ptrst->left,ptrco);
		int sl[6]; int i,j;int flag=1;
		for(i=0;i<=5;i++)
		{
			sl[i]=checkingcourseslot(ptrco,ptrst->courses[i]);
			
			
		}
		for(i=0;i<5 ;i++)
		{
			for(j=i+1;j<=5;j++)
			{
				if(sl[i]==sl[j])
				{
					
					printf("%s cannot take 2 courses in slot %d\n",ptrst->name,sl[j]);
					
				}
			}
		}
		checkingslot(ptrst->right,ptrco);
		
		
		
		
	}
	
}

int  checkingcourseslot(struct course *courseptr,int cno)
{
	if(courseptr==NULL)
	{
		return;
	}
	else if(courseptr->course_id==cno)
	{
		return courseptr->slot_no;
	}
	else if(cno<courseptr->course_id)
	{
		checkingcourseslot(courseptr->left1,cno);
	}
	else
	{
		checkingcourseslot(courseptr->right1,cno);
	}
	
		
		
	
	
}

	 
void printslotno(struct course *pt)
{
	if(pt==NULL)
	{
		return ;
	}
	else
	{
		printslotno(pt->left1);
		printf("%d\n",pt->slot_no);
		printslotno(pt->right1);
		
		
	}
}

/*
void RangeSearch(struct course *cptr,int cid1, int cid2)
{
	if(cptr==NULL)
	{
		return ;
	}
	else
	{
		if(cptr->course_id<cid1)
		{
			RangeSearch(cptr->right1,cid1,cid2);
		}
		else if(cptr->course_id>cid1)
		{
			RangeSearch(cptr->left1,cid1,cid2);
		}
	
	if(cptr->course_id>cid1 && cptr->course_id<cid2)
	{
		printf(" %d",cptr->course_id);
		printf("\n");
		
		}	
		if(cptr->course_id > cid2)
		{
			RangeSearch(cptr->left1,cid1,cid2);
		}else if(cptr->course_id > cid2)
		{
			RangeSearch(cptr->right1,cid1,cid2);
		}
	   	
		
	}
	
	
}
*/

void RangeSearch(struct  course* cptr, int cid1, int cid2) {
    if (cptr == NULL) return;
    if(cptr->course_id<cid1)
    {
        RangeSearch(cptr->right1,cid1,cid2);
    }
    else if (cptr->course_id > cid1)
    {
        RangeSearch(cptr->left1, cid1, cid2);
    }

    if (cptr->course_id > cid1 && cptr->course_id < cid2) {
        printf("%d\n", cptr->course_id);
    }

    if (cptr->course_id > cid2)
        RangeSearch(cptr->left1,cid1,cid2);
    else if (cptr->course_id < cid2)
        RangeSearch(cptr->right1, cid1, cid2);
}





int main()
{

	struct student *root;
	root=NULL;
  
   	struct course* root1;
	root1=NULL;
	
	FILE *ptr;
	char line[100];
	
	FILE *courses;
	char *cname;
	int c_id,c_slot;
	char cline[100];
	
	FILE *students;
	int c[5],c1,c2,c3,c4,c5,enrollno;
	char *studentname;
	char Sline[100];
	
	
	/*
	int c1[5]={1,2,4,6,7};
	int c2[5]={1,4,5,3,7};
	int c3[5]={4,2,3,5,7};
	int c4[5]={2,4,5,6,8};
	root=createstudent_List(root,"Govardhan",105,c4);
	root=createstudent_List(root,"Mamatha",103,c2);
	root=createstudent_List(root,"Yaswanth",102,c1);
	root=createstudent_List(root,"Harshitha",107,c3);
	root=createstudent_List(root,"Ashish",109,c1);
	root=createstudent_List(root,"Allu_vamsi",101,c3);
	root=createstudent_List(root,"Vyshnavi",108,c4);                          
	root=createstudent_List(root,"Manoj",104,c2);
	
	
	//courselist ptr root1    
	
	
	root1=createcourse_List(root1,"CPL",5,4);
	root1=createcourse_List(root1,"CO",3,6);
	root1=createcourse_List(root1,"TC",7,4);
	root1=createcourse_List(root1,"DCMP",6,3);
	root1=createcourse_List(root1,"DSPD2",2,1);
	root1=createcourse_List(root1,"SW1",4,5);	
	root1=createcourse_List(root1,"IOOM",1,2);
	root1=createcourse_List(root1,"SW2",8,5);		
	

	
	
	
	printf("The courses List is:\n");
	printf("\n");
	printcourseList(root1);
	printf("\n");
	printcourse_students(root1,root);
	printf("\n");
	
	//deleting a student 
	deletestudent(root,108);
	printf("The students List after Deleting :\n");
	printf("\n");
	printstudentList(root); 
	
	printcourse_students(root1,root);
	//deleting a course
	
	deletecourse(root1,6,root);
	printf("The course List after deleting a course :\n");
	printf("\n");
	printcourseList(root1);
	printf("\n");
	
	checkingslot(root,root1);
*/
 
 
  int q_no;
  printf("Enter 1 if you want to Add a student in a List :\n");
  printf("Enter 2 if you want to Delete a student in a List :\n");
  printf("Enter 3 if you want to Add a course in a List :\n");
  printf("Enter 4 if you want to delete a course in a List :\n");
  printf("Enter 5 if you want to Range Searching of Courses :\n");
  
  printf("\n");
  printf("Enter your choice");
  scanf("%d",&q_no);
  printf("\n");
  	
	
	
	
	switch(q_no)
	{
		case 1:
			
			
			
			students=fopen("STUDENTLIST.txt","r");
			while(fgets(Sline,100,students)!=NULL)
			{
			  studentname = (char *)malloc(20*sizeof(char));
			  sscanf(Sline, "%s %d %d %d %d %d %d", studentname, &enrollno, &c1, &c2, &c3, &c4, &c5);
			  c[0]=c1;
			  c[1]=c2;
			  c[2]=c3;
			  c[3]=c4;
			  c[4]=c5;
			  
			  root=createstudent_List(root, studentname, enrollno, c);
			  	
			}
		
			printf("The student List is:\n");
	        printf("\n");
	        printstudentList(root); 
	        printf("\n");
	        fclose(students);
	        
	        courses=fopen("COURSESLIST.txt","r");
			while(fgets(cline,100,courses)!=NULL)
			{
				cname= (char *)malloc(30*sizeof(char));
				sscanf(cline,"%s %d %d",cname,&c_id,&c_slot);
				root1= createcourse_List(root1, cname, c_id, c_slot);
	
			}
			
		//	printf("The courses List is:\n");
	        printf("\n");
	      //  printcourseList(root1);
	        printf("\n");
	      //  printcourse_students(root1,root);
	        printf("\n");
	        fclose(courses);
			
	       
			
			break;
			
		case 2:
			
			
				students=fopen("STUDENTLIST.txt","r");
			while(fgets(Sline,100,students)!=NULL)
			{
			  studentname = (char *)malloc(20*sizeof(char));
			  sscanf(Sline, "%s %d %d %d %d %d %d", studentname, &enrollno, &c1, &c2, &c3, &c4, &c5);
			  c[0]=c1;
			  c[1]=c2;
			  c[2]=c3;
			  c[3]=c4;
			  c[4]=c5;
			  
			  root=createstudent_List(root, studentname, enrollno, c);
			  	
			}
		
			printf("The student List is:\n");
	        printf("\n");
	        printstudentList(root); 
	        printf("\n");
	        fclose(students);
	        
	        courses=fopen("COURSESLIST.txt","r");
			while(fgets(cline,100,courses)!=NULL)
			{
				cname= (char *)malloc(30*sizeof(char));
				sscanf(cline,"%s %d %d",cname,&c_id,&c_slot);
				root1= createcourse_List(root1, cname, c_id, c_slot);
	
			}
			
			printf("The courses List is:\n");
	        printf("\n");
	        printcourseList(root1);
	        printf("\n");
	        printcourse_students(root1,root);
	        printf("\n");
	        fclose(courses);
			int eno;
			printf("The student u wish to delete is:\n");
	        scanf("%d",&eno);    
			
			deletestudent(root,eno);
			
		
			printf("The students List after Deleting :\n");
	        printf("\n");
	        printstudentList(root); 
	        printcourse_students(root1,root);
	        fclose(ptr);
				
				
			break;
			
			
	
	case 3:
		 courses=fopen("COURSESLIST.txt","r");
			while(fgets(cline,100,courses)!=NULL)
			{
				cname= (char *)malloc(30*sizeof(char));
				sscanf(cline,"%s %d %d",cname,&c_id,&c_slot);
				root1= createcourse_List(root1, cname, c_id, c_slot);
	
			}
			
			printf("The courses List is:\n");
	        printf("\n");
	        printcourseList(root1);
	        printf("\n");
	        fclose(courses);
		
             break;
             
             case 4:
             	
             	 courses=fopen("COURSESLIST.txt","r");
			while(fgets(cline,100,courses)!=NULL)
			{
				cname= (char *)malloc(30*sizeof(char));
				sscanf(cline,"%s %d %d",cname,&c_id,&c_slot);
				root1= createcourse_List(root1, cname, c_id, c_slot);
	
			}
			fclose(courses);
			int  cno;
			printf("Enter the Course no to delete:\n");
			scanf("%d",&cno);
			deletecourse(root1,cno,root);
			printf("The courses List after deleting course is:\n");
	        printf("\n");
	        printcourseList(root1);
	        printf("\n");
	        
	        
	        break ;
	        
	        
	        case 5:
	        	courses=fopen("COURSESLIST.txt","r");
			while(fgets(cline,100,courses)!=NULL)
			{
				cname= (char *)malloc(30*sizeof(char));
				sscanf(cline,"%s %d %d",cname,&c_id,&c_slot);
				root1= createcourse_List(root1, cname, c_id, c_slot);
	
			}
			fclose(courses);
			 int cid_1,cid_2;
			 printf("The Range Of Courses Is :\n");
			 scanf("%d %d",&cid_1,&cid_2);
			 printf("Range searching of Courses :\n");
			 RangeSearch(root1,cid_1,cid_2);
  
}

}
    
	 



