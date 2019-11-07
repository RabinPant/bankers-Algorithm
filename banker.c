/*BANKERS ALGORITHM
  Code By RABIN PANT	
*/
#include <stdio.h>

int g_argc;
char **g_argv=NULL; 
int row;
int col;
int processG;
int read_file(int matrixA[row][col],int matrixB[row][col],int available[col],int request[col],int process);

int availableVector(int available[col]);

int requestVector(int request[col]);

int needMatrix(int matrixA[row][col], int matrixB[row][col],int available[col],int request[col]);

int main(int argc , char **argv[]) {
  
  FILE *file;
	int r,c;
	if(argc==2)
	{
		file = fopen(argv[1], "r");
		fscanf(file, "%d", &r);
		printf("There are %d processes in the system.\n",r);
		fscanf(file,"%d",&c);
		printf("There are %d resources types.",c);
		row = r;
		col = c;	
	}
	else{
		printf("ERROR FILE CANNOT BE OPEN\n");
	}
  int matrixA[row][col], matrixB[row][col],available[col],request[col],process;
  g_argc = argc;
  g_argv = argv;
  
  int i, j, k;
  i = j = k = 0;
  
  read_file(matrixA,matrixB,available,request,process);
  
  printf("\n\nThe Allocation Matrix is...\n");
  printf("  ");
  for(i=0; i<col; i++)
  {
  	c = 'A'+i;
  	printf("  %c",c);
  }
  for (i = 0; i < row; i++) {
     printf("\n");
     printf("%d:",i);
     for (j = 0; j < col; j++) {
        printf("  %d", matrixA[i][j]);
     }
  }
  printf("\n");
  printf("\nThe Max Matrix is...\n");
  printf("  ");
  for(i=0; i<col; i++)
  {
  	c = 'A'+i;
  	printf("  %c",c);
  }
  for (i = 0; i < row; i++) {
     printf("\n");
     printf("%d:",i);
     for (j = 0; j < col; j++) {
        printf("  %d", matrixB[i][j]);
     }
  }
  needMatrix(matrixA,matrixB,available,request);
  printf("\n\n");
    
  return 0;
}
int read_file(int matrixA[row][col],int matrixB[row][col],int available[col],int request[col],int process)
{
	FILE *file;
	int i, j, k;
	if(g_argc==2)
	{
		file = fopen(g_argv[1], "r");	
	}
	else{
		printf("Error File cannot be open");
		fclose(file);
	}
	i = j = k = 0;
	
	fseek(file,6, SEEK_SET);
	
  	for (i = 0; i < row; i++) {
    	 for (j = 0; j < col; j++) {
        	fscanf(file, "%d", &matrixA[i][j]);
     	}
  	}	
  

  	fseek(file,53, SEEK_SET);

   	for (i = 0; i < row; i++) {
          
     for (j = 0; j < col; j++) {
        fscanf(file, "%d", &matrixB[i][j]);
     }
   }
  	fseek(file,100, SEEK_SET);
  	for(i=0;i<col;i++){
  		fscanf(file,"%d",&available[i]);
	  }
  	fseek(file,116,SEEK_SET);
	  fscanf(file,"%d",&process);
	  processG=process;
	  
	  fseek(file,118, SEEK_SET);
  	
	  for(i=0;i<col;i++){
  		fscanf(file,"%d",&request[i]);
	  }
	fclose(file);	  
}

int needMatrix(int matrixA[row][col], int matrixB[row][col],int available[col],int request[col])
{
	int i,j,need[row][col],k;
	char c;
	for (i = 0; i < row; i++) {
          
     for (j = 0; j < col; j++) {
        need[i][j] = matrixB[i][j]-matrixA[i][j];
     }
  }
  printf("\n\n");
  printf("The Need Matrix is...\n");
  printf("  ");
  for(i=0; i<col; i++)
  {
  	c = 'A'+i;
  	printf("  %c",c);
  }
  
  for (i = 0; i < row; i++) {
  	printf("\n");
  	printf("%d:",i);
     for (j = 0; j < col; j++) {
        printf("  %d",need[i][j]);
     }
  }
  printf("\n\n");
  
  availableVector(available);
  
  int work[col];
  for(i=0;i<col;i++)
  {
  	work[i] = available[i];
  }
  int finish[row];
  for(i=0;i<row;i++)
  {
  	finish[i]=0;
  }
  int count = 0;
  
  while(count<row)
  {
  	int flag = 0;
  	for(i=0;i<row;i++)
  	{
  		if(finish[i]==0)
  		{
  			for(j=0;j<col;j++)
			  {
				if(need[i][j]>work[j]){
					break;
				}  	
			  }
			if(j==col)
			{
				for(k=0;k<col;k++)
				{
					work[k]=work[k]+matrixA[i][k];			
				}
				count++;
				finish[i] = 1;
				flag =1;		
		    }  	
		}
	  }
	  if(flag==0)
	  {
	  	printf("\n\nTHE SYSTEM IS NOT IN SAFE STATE\n");
	  	break;
	  }
  }
  if(count==row)
  {
  	printf("THE SYSTEM IS IN SAFE STATE\n");
  }
  
  printf("\n\n");
  
  requestVector(request);
  
  int grant = 1;
  for(i=0;i<col;i++)
  {
  	if(request[i]>need[processG][i])
  	{
  		grant=0;
  		break;
    }
  }
  for(i=0;i<col;i++)
  {
	if(request[i]>available[i])
	{
		grant =0;
		break;	
	}  	
  }
  if(grant==0)
  {
	printf("THE REQUEST CANNOT BE GRANTED!");  	
  }
  else{
  	printf("THE REQUEST CAN BE GRANTED!");
  	for(i=0;i<col;i++)
  	{
  		available[i]= available[i]-request[i];
	}
  }
  
  printf("\n\nThe available vector is ..\n");
  
  for(i=0; i<col; i++)
  {
  	c = 'A'+i;
  	printf("  %c",c);
  }
  printf("\n");
  for(i=0;i<col;i++)
  {
	printf("  %d",available[i]);  	
  } 	
}

int availableVector(int available[col])
{
  int i;
  char c;
  printf("The available Vector is...\n");
  for(i=0; i<col; i++)
  {
  	c = 'A'+i;
  	printf("  %c",c);
  }
  printf("\n");
  for(i=0;i<col;i++){
  	printf("  %d",available[i]);
  }	
  printf("\n\n");
}
int requestVector(int request[col])
{
  int i;
  char c;
  printf("The Request Vector is...\n");
  for(i=0; i<col; i++)
  {
  	c = 'A'+i;
  	printf("  %c",c);
  }
  printf("\n");
  printf("%d:",processG);
  for(i=0;i<col;i++){
  	printf("%d  ",request[i]);
  }	
  printf("\n\n");
}

