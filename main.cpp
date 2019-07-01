#include<iostream>
#include<windows.h>
#include<fstream>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<cmath>
#include<iomanip>
using namespace std;

unsigned char *pBmpBuf;//读入图像数据的指针
unsigned char *pBmpBuf0;
unsigned char *pBmpBuf1;
int bmpWidth;//图像的宽
int bmpHeight;//图像的高
RGBQUAD *pColorTable;//颜色表指针
int biBitCount;//图像类型，每像素位数

char name[100];

long long int step=0,step1=0,step2=0,step3=0;
int M=0,N=0;// 定义难度系数（M代表高度，N代表宽度）
int lx=0,ly=0;
int lx0=0,ly0=0;
int lx1=0,ly1=0;
int lx2=0,ly2=0;
int lx3=0,ly3=0;
int game[1000][1000];//定义初始数组，用于打乱顺序的操作 
int now[1000][1000];//定义表示当前状态的数组 
int begin[1000][1000];//定义保存最初始状态的数组 

#include"feasibility.h"
#include"read.h"
#include"save.h"
#include"test.h"
#include"test1.h"
#include"test2.h"
#include"W.h"
#include"A.h"
#include"S.h"
#include"D.h"
#include"autorecover.h"
#include"autorecover1.h"
#include"autorecover2.h"


int main(int argc, char** argv) 
{
	cout << "Welcome to jigsaw puzzle" <<endl;
	cout << "Please input the address of the image" << endl; 
	 
	int num=0; // 定义操作数 
	cin >> name;
	
	bool bprime=readbmp(name);
	while(bprime!=1)
	  {
	  	cout << "The address is wrong, please give another one"<< endl;
	  	cin >> name;
	  	bprime=readbmp(name);
	  }
	  
	cout << "Image inputed successfully, please choose the difficulty"<< endl;	
	cin >> M >>N;
	
	for(int i=0;i<M;i++)
	   {
	   	  for(int j=0;j<N;j++)
	   	     {
	   	     	if(i!=M-1 || j!=N-1)
				  {
				      game[i][j]=j+i*N;
				      begin[i][j]=j+i*N;
			      }
			    else
			      {
			      	  game[i][j]=-1;
			      	  begin[i][j]=-1;
			      }
	   	     }
	   }
	//定义分块的高和宽 
	int m1=bmpHeight/M;
	int n1=bmpWidth/N;
	int linebyte =(bmpWidth * biBitCount/8+3)/4*4;
	int linebyte1=(n1*biBitCount/8+3)/4*4/3*3;
	for(int i=0;i<linebyte * bmpHeight;i++)
	   {
	   	pBmpBuf0[i]=pBmpBuf[i];
	   }
	for(int x=0;x<m1;x++)
		{
		 for(int y=0;y<linebyte1;y++)
			{
			  pBmpBuf0[x*linebyte+(N-1)*linebyte1+y] = 255;
			}
		}
	//随机打乱图片顺序 
	srand((unsigned)time(NULL));		    
	for(int i=0;i<M; i++)    
	{        
	    for(int j=0;j<N;j++)
		   {
		       int ran1=rand() % M;        
		       int ran2=rand() % N;
			   int temp = game[i][j];        
			   game[i][j] =game[ran1][ran2];        
		       game[ran1][ran2]= temp;
		       for(int x=0;x<m1;x++)
				  {
					   for(int y=0;y<linebyte1;y++)
						  {
						      unsigned char temp1 = pBmpBuf[((N-i-1)*m1+x)*linebyte+j*linebyte1+y];
						      pBmpBuf[((N-i-1)*m1+x)*linebyte+j*linebyte1+y] = pBmpBuf[((N-ran1-1)*m1+x)*linebyte+ran2*linebyte1+y];
							  pBmpBuf[((N-ran1-1)*m1+x)*linebyte+ran2*linebyte1+y]=temp1; 
						  }
				  }
	       }
	}      
    for(int i=0;i<M;i++)
       {
		  for(int j=0;j<N;j++)
       	    {
       	   	   if(game[i][j]==-1)
			     {
			     	lx=j;
			     	ly=i;
			     	lx0=lx;
			     	ly0=ly;
			     }   
            }
       }
	for(int x=0;x<m1;x++)
		{
		 for(int y=0;y<linebyte1;y++)
			{
			  pBmpBuf[((N-ly-1)*m1+x)*linebyte+lx*linebyte1+y] = 255;
			  pBmpBuf1[((N-ly-1)*m1+x)*linebyte+lx*linebyte1+y] = 255;
			}
		} 
	for(int i=0;i<linebyte * bmpHeight;i++)
	   {
	   	pBmpBuf1[i]=pBmpBuf[i];
	   }   
    if(N%2==1)
	  {
	   while(0!=feasibility()%2)
	   {
		cout << "Unable to be recovered" << endl;
		cout << "Do you need to redisorganized the jigsaw?" << endl;
		cout << "input 1(redisorganize) or input 0(game over)"<<endl;
		bool bprime1=0;
		cin >> bprime1;
		if(bprime1)
		{
		   srand((unsigned)time(NULL));		    
	       for(int i=0;i<M; i++)    
             {        
	            for(int j=0;j<N;j++)
		  		   {
		    			int ran1=rand() % M;        
		       			int ran2=rand() % N;
			   			int temp = game[i][j];        
			   			game[i][j] =game[ran1][ran2];        
		       			game[ran1][ran2]= temp;
					    for(int x=0;x<m1;x++)
				           {
					           for(int y=0;y<linebyte1;y++)
						          {
						              unsigned char temp1 = pBmpBuf[((N-i-1)*m1+x)*linebyte+j*linebyte1+y];
						              pBmpBuf[((N-i-1)*m1+x)*linebyte+j*linebyte1+y] = pBmpBuf[((N-ran1-1)*m1+x)*linebyte+ran2*linebyte1+y];
							          pBmpBuf[((N-ran1-1)*m1+x)*linebyte+ran2*linebyte1+y]=temp1;
						          }
				  		   }
	       		   }
	         }
	    for(int i=0;i<M;i++)
          {
		  for(int j=0;j<N;j++)
       	    {
       	   	   if(game[i][j]==-1)
			     {
			     	lx=j;
			     	ly=i;
			     	lx0=lx;
			     	ly0=ly;
			     }   
            }
          }
        for(int i=0;i<linebyte * bmpHeight;i++)
	      {
	   	pBmpBuf1[i]=pBmpBuf[i];
	      }
       }
		else
		{
			cout << "Game over" << endl;
			return 0; 
		}
	   }
      }
	else 
	{
	  while(feasibility()%2 != (M-1-ly)%2)
	   {
		cout << "Unable to be recovered" << endl;
		cout << "Do you need to redisorganized the jigsaw?" << endl;
		cout << "input 1(redisorganize) or input 0(game over)"<<endl;
		bool bprime1=0;
		cin >> bprime1;
		if(bprime1)
		{
		   srand((unsigned)time(NULL));		    
	       for(int i=0;i<M; i++)    
             {        
	            for(int j=0;j<N;j++)
		  		   {
		    			int ran1=rand() % M;        
		       			int ran2=rand() % N;
			   			int temp = game[i][j];        
			   			game[i][j] =game[ran1][ran2];        
		       			game[ran1][ran2]= temp;
					    for(int x=0;x<m1;x++)
				           {
					           for(int y=0;y<linebyte1;y++)
						          {
						              unsigned char temp1 = pBmpBuf[((N-i-1)*m1+x)*linebyte+j*linebyte1+y];
						              pBmpBuf[((N-i-1)*m1+x)*linebyte+j*linebyte1+y] = pBmpBuf[((N-ran1-1)*m1+x)*linebyte+ran2*linebyte1+y];
							          pBmpBuf[((N-ran1-1)*m1+x)*linebyte+ran2*linebyte1+y]=temp1; 
						          }
				  		   }
	       		   }
	         }
	    for(int i=0;i<M;i++)
          {
		  for(int j=0;j<N;j++)
       	    {
       	   	   if(game[i][j]==-1)
			     {
			     	lx=j;
			     	ly=i;
			     	lx0=lx;
			     	ly0=ly;
			     }   
            }
          }
       }
		else
		{
			cout << "Game over" << endl;
			return 0; 
		}
	   }	
	}  
    
	cout << "Able to be recovered" << endl;
    bool bprime2=0;
    cout << "Please ensure whether to start the game"<< endl;
    cout << "input 1(start the game) or input 0(game over)"<<endl;
    cin >> bprime2;
	if(bprime2)
	  {
	  	  bool newbmp=savebmp("start.bmp",pBmpBuf,bmpWidth,bmpHeight,biBitCount,pColorTable);
	      if(newbmp)
		  {
		  	cout << "Game start" << endl;
		  }
		  else
		  {
		  	cout << "Image input encounter unfound error"<< endl;
		  	cout << "Game over" << endl; 
		    return 0;
		  }
      }
	else
	{
		cout << "Game over" << endl; 
		return 0;
	}
	int file1[M][N];//定义存档数组 
	int file2[M][N];
	int file3[M][N];
	for(int i=0;i<M;i++) 
	   {
	   	  for(int j=0;j<N;j++)
	   	     {
	   	     	now[i][j]=game[i][j];
	   	     	cout << game[i][j];
	   	     	if(j<N-1)
	   	     	  {
	   	     	  	cout << "\t";
	   	     	  }
	   	     	else
	   	     	  {
	   	     	  	cout << endl;
	   	     	  }
	   	     }  
	   }// 输出初始状态且初始化数组now 
	for(int i=0;i<M;i++)
	   {
	   	for(int j=0;j<N;j++)
	   	   {
	   	   	 file1[i][j]=-2;
	   	   	 file2[i][j]=-2;
	   	   	 file3[i][j]=-2;
	   	   }
	   }//初始化存档数组 
	bool recover=1;
	char command;
	while(recover)
	{
	  cin >> command;
	  if(command=='W')
	    {
	     if(ly<=0)
	       {
	       	cout << "The command cannot be carried out" << endl;
	       	cout << "Please reinput the command" << endl;
	       	continue;
	       }
	     else
		 {
		  for(int x=0;x<m1;x++)
				  {
					   for(int y=0;y<linebyte1;y++)
						  {
						      unsigned char temp1 = pBmpBuf[((N-ly-1)*m1+x)*linebyte+lx*linebyte1+y];
						      pBmpBuf[((N-ly-1)*m1+x)*linebyte+lx*linebyte1+y] = pBmpBuf[((N-ly)*m1+x)*linebyte+lx*linebyte1+y];
							  pBmpBuf[((N-ly)*m1+x)*linebyte+lx*linebyte1+y]=temp1; 
						  }
				  }
		  int tempnow=now[ly][lx];
		  now[ly][lx]=now[ly-1][lx];
		  now[ly-1][lx]=tempnow;
		  ly=ly-1;
		  step++;
	     }
		}
	  else
	    {
	        if(command=='A')
	    	  {
	    	  	if(lx<=0)
	    	  	  {
	    	  	  	cout << "The command cannot be carried out" << endl;
	       			cout << "Please reinput the command" << endl;
	       			continue;
	    	  	  }
	    	  	else
	    	  	  {
	    	  	    for(int x=0;x<m1;x++)
				       {
					     for(int y=0;y<linebyte1;y++)
						    {
						      unsigned char temp1 = pBmpBuf[((N-ly-1)*m1+x)*linebyte+lx*linebyte1+y];
						      pBmpBuf[((N-ly-1)*m1+x)*linebyte+lx*linebyte1+y] = pBmpBuf[((N-ly-1)*m1+x)*linebyte+(lx-1)*linebyte1+y];
							  pBmpBuf[((N-ly-1)*m1+x)*linebyte+(lx-1)*linebyte1+y]=temp1; 
						    }
				  	   }
				  	int tempnow=now[ly][lx];
		  			now[ly][lx]=now[ly][lx-1];
		  			now[ly][lx-1]=tempnow;
					lx=lx-1;
					step++;				  	
	    	  	  } 
	    	  }
	    	else
	    	  {
	    	  	if(command=='S')
	    	  	  {
	    	  	  	if(ly>=M-1)
	    	  	  	  {
	    	  	  	    cout << "The command cannot be carried out" << endl;
	       			    cout << "Please reinput the command" << endl;
	       			    continue;
	    	  	  	  }
	    	  	  	else
	    	  	  	  {
	    	  	  	  	for(int x=0;x<m1;x++)
				           {
					          for(int y=0;y<linebyte1;y++)
						    	 {
						      	   unsigned char temp1 = pBmpBuf[((N-ly-1)*m1+x)*linebyte+lx*linebyte1+y];
						      	   pBmpBuf[((N-ly-1)*m1+x)*linebyte+lx*linebyte1+y] = pBmpBuf[((N-ly-2)*m1+x)*linebyte+lx*linebyte1+y];
							  	   pBmpBuf[((N-ly-2)*m1+x)*linebyte+lx*linebyte1+y]=temp1; 
						    	 }
						   }
						int tempnow=now[ly][lx];
		  			    now[ly][lx]=now[ly+1][lx];
		  			    now[ly+1][lx]=tempnow;
						ly=ly+1;
						step++;					
	    	  	  	  }
	    	  	  }
	    	  	else
	    	  	  {
	    	  	  	if(command=='D')
	    	  	  	  {
	    	  	  	  	if(lx>=N-1)
	    	  	  	  	  {
	    	  	  	  	  	cout << "The command cannot be carried out" << endl;
	       					cout << "Please reinput the command" << endl;
	       					continue;
	    	  	  	  	  }
	    	  	  	  	else
	    	  	  	  	  {
	    	  	  	  	  	for(int x=0;x<m1;x++)
				           	   {
					          	for(int y=0;y<linebyte1;y++)
						    	   {
						      	     unsigned char temp1 = pBmpBuf[((N-ly-1)*m1+x)*linebyte+lx*linebyte1+y];
						      	     pBmpBuf[((N-ly-1)*m1+x)*linebyte+lx*linebyte1+y] = pBmpBuf[((N-ly-1)*m1+x)*linebyte+(lx+1)*linebyte1+y];
							  	     pBmpBuf[((N-ly-1)*m1+x)*linebyte+(lx+1)*linebyte1+y]=temp1; 
						    	   }
						       }
						    int tempnow=now[ly][lx];
		  			        now[ly][lx]=now[ly][lx+1];
		  			        now[ly][lx+1]=tempnow;
							lx=lx+1;
							step++;
	    	  	  	  	  }
	    	  	  	  }
	    	  	  	else
	    	  	  	  {
	    	  	  	  	if(command=='R')
	    	  	  	  	  {
	    	  	  	  	  	for(int i=0;i<M;i++)
	   						   {
	   	  						 for(int j=0;j<N;j++)
	   	     						{
	   	     							now[i][j]=game[i][j];	   	     							
	   	     						}  
	   						   }
	   						lx=lx0;
	   						ly=ly0;
	   						for(int i=0;i<linebyte * bmpHeight;i++)
	   						   {
	   						   	pBmpBuf[i]=pBmpBuf1[i];
	   						   }
	   						step=0;
	    	  	  	  	  }
	    	  	  	  	else
	    	  	  	  	  {
	    	  	  	  	  	if(command=='G')
	    	  	  	  	  	  {
	    	  	  	  	  	  	char path[100];
	    	  	  	  	  	  	cout << "Please input the path through which you want to save the image"<<endl;
	    	  	  	  	  	  	cin >> path;
	    	  	  	  	  	  	savebmp(path,pBmpBuf,bmpWidth,bmpHeight,biBitCount,pColorTable);
	    	  	  	  	  	  }
	    	  	  	  	  	else
	    	  	  	  	  	  {
	    	  	  	  	  	  	if(command=='I')
	    	  	  	  	  	  	  {
	    	  	  	  	  	  	  	cout<< "Please choose a file to save your process(from file 1, 2, 3)"<<endl;
	    	  	  	  	  	  	  	int filetype=0;
	    	  	  	  	  	  	  	bool filebprime=1;
	    	  	  	  	  	  	  	while(filebprime)
	    	  	  	  	  	  	  	{	    	  	  	  	  	  	  	
	    	  	  	  	  	  	  	cin >> filetype;
	    	  	  	  	  	  	  	if(filetype==0)
	    	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	cout << "End the command"<< endl;
	    	  	  	  	  	  	  	  	break;
	    	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	if(filetype==1)
	    	  	  	  	  	  	    {
	    	  	  	  	  	  	     filebprime=0;
	    	  	  	  	  	  	     for(int i=0;i<M;i++)
	    	  	  	  	  	  	  	   {
	    	  	  	  	  	  	  	   	for(int j=0;j<N;j++)
	    	  	  	  	  	  	  	   	   {
	    	  	  	  	  	  	  	   	   	file1[i][j]=now[i][j];
	    	  	  	  	  	  	  	   	   }
	    	  	  	  	  	  	  	   }
	    	  	  	  	  	  	  	  lx1=lx;
	    	  	  	  	  	  	  	  ly1=ly;
	    	  	  	  	  	  	  	  step1=step;
	    	  	  	  	  	  	    }
	    	  	  	  	  	  	    else
	    	  	  	  	  	  	      {
	    	  	  	  	  	  	      	if(filetype==2)
	    	  	  	  	  	  	      	  {
	    	  	  	  	  	  	      	  	filebprime=0;
	    	  	  	  	  	  	      	  	for(int i=0;i<M;i++)
	    	  	  	  	  	  	  	   		   {
	    	  	  	  	  	  	  	   			for(int j=0;j<N;j++)
	    	  	  	  	  	  	  	   	   			{
	    	  	  	  	  	  	  	   	   				file2[i][j]=now[i][j];
	    	  	  	  	  	  	  	   	  		    }
	    	  	  	  	  	  	  	   		   }
	    	  	  	  	  	  	  	   		lx2=lx;
	    	  	  	  	  	  	  	        ly2=ly;
	    	  	  	  	  	  	  	  		step2=step;
	    	  	  	  	  	  	      	  }
	    	  	  	  	  	  	      	else
	    	  	  	  	  	  	      	  {
	    	  	  	  	  	  	      	  	if(filetype==3)
	    	  	  	  	  	  	      	   {
	    	  	  	  	  	  	      	   	filebprime=0;
	    	  	  	  	  	  	      	  	for(int i=0;i<M;i++)
	    	  	  	  	  	  	  	   		   {
	    	  	  	  	  	  	  	   			for(int j=0;j<N;j++)
	    	  	  	  	  	  	  	   	   			{
	    	  	  	  	  	  	  	   	   				file3[i][j]=now[i][j];
	    	  	  	  	  	  	  	   	  		    }
	    	  	  	  	  	  	  	   		   }
	    	  	  	  	  	  	  	   		lx3=lx;
	    	  	  	  	  	  	  	        ly3=ly;
	    	  	  	  	  	  	  	  		step3=step;
	    	  	  	  	  	  	      	   }
	    	  	  	  	  	  	      	   else
	    	  	  	  	  	  	      	     {
	    	  	  	  	  	  	      	     	cout << "The file you choose does not exist"<<endl;
	    	  	  	  	  	  	      	     	cout <<"Please choose another file(from file 1,2,3) "<<endl;	    	  	  	  	  	  	      	     	
	    	  	  	  	  	  	      	     }
	    	  	  	  	  	  	      	  }
	    	  	  	  	  	  	      }
	    	  	  	  	  	  	      }
	    	  	  	  	  	  	      if(filetype!=0)
	    	  	  	  	  	  	      {
	    	  	  	  	  	  	      cout<<"Your process has been saved in the file"<<filetype<< endl;
									  }	    	  	  	  	  	  	  	
	    	  	  	  	  	  	  }
	    	  	  	  	  	  	else
	    	  	  	  	  	  	  {
	    	  	  	  	  	  	  	if(command=='O')
	    	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	cout <<"Please choose the file(from file 1, 2, 3) to load" << endl;
	    	  	  	  	  	  	  	  	int filetype1=0;
	    	  	  	  	  	  	  	  	bool filebprime1=1;
	    	  	  	  	  	  	  	  	while(filebprime1)
	    	  	  	  	  	  	  	  	{
	    	  	  	  	  	  	  	  	cin >>filetype1;
	    	  	  	  	  	  	  	  	if(filetype1==0)
	    	  	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	  	cout<<"End the command"<<endl;
	    	  	  	  	  	  	  	  	  	break;
	    	  	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	  	if(filetype1==1)
										{
										if(file1[0][0]<-1)
	    	  	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	  	cout <<"The file is empty" <<endl;
	    	  	  	  	  	  	  	  	  	cout <<"Please reinput the command"<< endl;
	    	  	  	  	  	  	  	  	  	continue;
	    	  	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	  	else
	    	  	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	  	filebprime1=0;
	    	  	  	  	  	  	  	  	  	for(int i=0;i<M;i++)
	    	  	  	  	  	  	  	   		   {
	    	  	  	  	  	  	  	   			  for(int j=0;j<N;j++)
	    	  	  	  	  	  	  	   	   			 {
	    	  	  	  	  	  	  	   	   				now[i][j]=file1[i][j];
	    	  	  	  	  	  	  	   	   			 }
	    	  	  	  	  	  	  	  		   }
	    	  	  	  	  	  	  	  		lx=lx1;
	    	  	  	  	  	  	  	  		ly=ly1;
	    	  	  	  	  	  	  	  		step=step1;
	    	  	  	  	  	  	  	  		for(int i=0;i<M;i++)
											   {
											   	for(int j=0;j<N;j++)
											   	   {if(now[i][j]!=-1)
											   	   {
											   	   	int i1=now[i][j]/N;
											   	   	int j1=now[i][j]-i1*N;
											   	   	for(int x=0;x<m1;x++)
														           {
															           for(int y=0;y<linebyte1;y++)
																          {
																              pBmpBuf[((N-i-1)*m1+x)*linebyte+j*linebyte1+y]= pBmpBuf0[((N-i1-1)*m1+x)*linebyte+j1*linebyte1+y];
																          }
														  		   }
													}
													else
													{
													  for(int x=0;x<m1;x++)
														           {
															           for(int y=0;y<linebyte1;y++)
																          {
																              pBmpBuf[((N-i-1)*m1+x)*linebyte+j*linebyte1+y]= 255;
																          }
														  		   }	
													}
											   	   }
											   }
	    	  	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	    }
	    	  	  	  	  	  	  	  	else
	    	  	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	  	if(filetype1==2)
	    	  	  	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	  	  	  if(file2[0][0]<-1)
	    	  	  	  	  	  	  	  	            {
	    	  	  	  	  	  	  	  	  			cout <<"The file is empty" <<endl;
	    	  	  	  	  	  	  	  	  		 	cout <<"Please reinput the command"<< endl;
	    	  	  	  	  	  	  	  	  			continue;
	    	  	  	  	  	  	  	  	  			}
	    	  	  	  	  	  	  	  	   		  else
	    	  	  	  	  	  	  	  	 			 {
	    	  	  	  	  	  	  	  	 			 	filebprime1=0;
	    	  	  	  	  	  	  	  	  				for(int i=0;i<M;i++)
	    	  	  	  	  	  	  	   		   				{
	    	  	  	  	  	  	  	   			  				for(int j=0;j<N;j++)
	    	  	  	  	  	  	  	   	   							 {
	    	  	  	  	  	  	  	   	   							now[i][j]=file2[i][j];
	    	  	  	  	  	  	  	   	   			 				 }
	    	  	  	  	  	  	  	  		   				}
	    	  	  	  	  	  	  	  		   			lx=lx2;
	    	  	  	  	  	  	  	  		            ly=ly2;
	    	  	  	  	  	  	  	  					step=step2;
	    	  	  	  	  	  	  	  					for(int i=0;i<M;i++)
														   {
														   	for(int j=0;j<N;j++)
														   	   {if(now[i][j]!=-1)
														   	   {								   	   
														   	   	int i1=now[i][j]/N;
														   	   	int j1=now[i][j]-i1*N;
														   	   	for(int x=0;x<m1;x++)
																	           {
																		           for(int y=0;y<linebyte1;y++)
																			          {
																			              pBmpBuf[((N-i-1)*m1+x)*linebyte+j*linebyte1+y]= pBmpBuf0[((N-i1-1)*m1+x)*linebyte+j1*linebyte1+y];
																			          }
																	  		   }
															   }
															   else
																{
																  for(int x=0;x<m1;x++)
																	           {
																		           for(int y=0;y<linebyte1;y++)
																			          {
																			              pBmpBuf[((N-i-1)*m1+x)*linebyte+j*linebyte1+y]= 255;
																			          }
																	  		   }	
																}
														   	   }
														   }
	    	  	  	  	  	  	  	  	 			 }
	    	  	  	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	  	  	else
	    	  	  	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	  	  	if(filetype1==3)
	    	  	  	  	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	  	  	  	if(file3[0][0]<-1)
	    	  	  	  	  	  	  	  	  			{
	    	  	  	  	  	  	  	  	  				cout <<"The file is empty" <<endl;
	    	  	  	  	  	  	  	  	  				cout <<"Please reinput the command"<< endl;
	    	  	  	  	  	  	  	  	  				continue;
	    	  	  	  	  	  	  	  	  			}
	    	  	  	  	  	  	  	  				else
	    	  	  	  	  	  	  	  	  		    {
	    	  	  	  	  	  	  	  	  		    filebprime1=0;
	    	  	  	  	  	  	  	  	  			for(int i=0;i<M;i++)
	    	  	  	  	  	  	  	   		  		   {
	    	  	  	  	  	  	  	   			  		for(int j=0;j<N;j++)
	    	  	  	  	  	  	  	   	   			 	  {
	    	  	  	  	  	  	  	   	   					now[i][j]=file3[i][j];
	    	  	  	  	  	  	  	   	   			 	  }
	    	  	  	  	  	  	  	  		   		   }
	    	  	  	  	  	  	  	  		   		lx=lx3;
	    	  	  	  	  	  	  	  		        ly=ly3;
	    	  	  	  	  	  	  	  				step=step3;
	    	  	  	  	  	  	  	  				for(int i=0;i<M;i++)
													   {
													   	for(int j=0;j<N;j++)
													   	   {if(now[i][j]!=-1)
														   	{
													   	   	int i1=now[i][j]/N;
													   	   	int j1=now[i][j]-i1*N;
													   	   	for(int x=0;x<m1;x++)
																           {
																	           for(int y=0;y<linebyte1;y++)
																		          {
																		              pBmpBuf[((N-i-1)*m1+x)*linebyte+j*linebyte1+y]= pBmpBuf0[((N-i1-1)*m1+x)*linebyte+j1*linebyte1+y];
																		          }
																  		   }
														    }
														    else
																{
																  for(int x=0;x<m1;x++)
																	           {
																		           for(int y=0;y<linebyte1;y++)
																			          {
																			              pBmpBuf[((N-i-1)*m1+x)*linebyte+j*linebyte1+y]= 255;
																			          }
																	  		   }	
																}
													   	   }
													   }
	    	  	  	  	  	  	  	  	 		  	}
	    	  	  	  	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	  	  	  	else
	    	  	  	  	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	  	  	  	cout << "The file you choose to load cannot be found, please choose another one"<< endl;	    	  	  	  	  	  	  	  	  	  	  	 
	    	  	  	  	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	    }
	    	  	  	  	  	  	  	    cout << "File"<<filetype1<<" has been loaded" <<endl;
	    	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	else
	    	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	if(command=='F')
	    	  	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	  	while(test1()==false)
	    	  	  	  	  	  	  	  	    {
	    	  	  	  	  	  	  	  	     for(int i=0;i<M-2;i++)
	    	  	  	  	  	  	  	  	       {
	    	  	  	  	  	  	  	  	       	for(int j=0;j<N-1;j++)
	    	  	  	  	  	  	  	  	       	   {
	    	  	  	  	  	  	  	  	       	   	if(i<M-2 && j<N-2)
	    	  	  	  	  	  	  	  	       	   	  {	    	  	  	  	  	  	  	  	       	   	 
	    	  	  	  	  	  	  	  	       	   	  	autorecover(j,i);
	    	  	  	  	  	  	  	  	       	   	  }
	    	  	  	  	  	  	  	  	       	   	else
	    	  	  	  	  	  	  	  	       	   	  {
	    	  	  	  	  	  	  	  	       	   	  	if(j==N-2)
	    	  	  	  	  	  	  	  	       	   	  	  {
	    	  	  	  	  	  	  	  	       	   	  	  	autorecover1(j,i);
	    	  	  	  	  	  	  	  	       	   	  	  	break;
	    	  	  	  	  	  	  	  	       	   	  	  }
	    	  	  	  	  	  	  	  	       	   	  }
	    	  	  	  	  	  	  	  	       	   }
	    	  	  	  	  	  	  	  	       }
	    	  	  	  	  	  	  	  	    }
	    	  	  	  	  	  	  	  	   while(test2()==false)
	    	  	  	  	  	  	  	  	         {
	    	  	  	  	  	  	  	  	         	for(int j=0;j<N-2;j++)
	    	  	  	  	  	  	  	  	         	   {
	    	  	  	  	  	  	  	  	         	   	autorecover2(j,M-2);
	    	  	  	  	  	  	  	  	         	   }
	    	  	  	  	  	  	  	  	         }
	    	  	  	  	  	  	  	  	    if(lx==N-2)
												{
												  D();
												  step++;
												}
											if(ly==M-2)
												{
												  S();
												  step++;
												}
	    	  	  	  	  	  	  	  	    while(test()==false)
	    	  	  	  	  	  	  	  	         {
	    	  	  	  	  	  	  	  	            W();
													A();
													S();
													D();
													step=step+4;	
	    	  	  	  	  	  	  	  	         }
	    	  	  	  	  	  	  	  	    cout<< endl;
	    	  	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	  	else
	    	  	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	  	if(command=='P')
	    	  	  	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	  	  	bool bprime3=0;
	    	  	  	  	  	  	  	  	  	  	cout << "Do you want to give up?" << endl;
	    	  	  	  	  	  	  	  	  	  	cin >> bprime3;
	    	  	  	  	  	  	  	  	  	  	if(bprime3)
	    	  	  	  	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	  	  	  	cout <<"Game over" << endl;
	    	  	  	  	  	  	  	  	  	  	  	return 0;
	    	  	  	  	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	  	  	  	else
	    	  	  	  	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	  	  	  	cout << "Come on, please hold on" << endl;
	    	  	  	  	  	  	  	  	  	  	  	continue;
	    	  	  	  	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	  	  	else
	    	  	  	  	  	  	  	  	  	  {
	    	  	  	  	  	  	  	  	  	  	cout << "The command cannot be carried out" << endl;
	    	  	  	  	  	  	  	  	  	  	cout << "Please reinput the command" << endl;
												continue; 
	    	  	  	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  	  }
	    	  	  	  	  	  	  }
	    	  	  	  	  	  }
	    	  	  	  	  }
	    	  	  	  }
	    	  	  }
	    	  }
	    }
	   cout << "Steps:"<<step << endl;
	   for(int i=0;i<M;i++)
	   {
	   	  for(int j=0;j<N;j++)
	   	     {
	   	     	cout << now[i][j];
	   	     	if(j<N-1)
	   	     	  {
	   	     	  	cout << "\t";
	   	     	  }
	   	     	else
	   	     	  {
	   	     	  	cout << endl;
	   	     	  }
	   	     }  
	   }
	  if(test())
	    {
	    	recover=0;
			cout << "Congratuations for solving the puzzle, you are genius" << endl;
			cout << "Please ensure whether to continue the game" << endl;
			cout << "input 1(continue the game) or input 0(game over)"<<endl;
			cin >> recover;
	    }
	}
	cout << "Game over"<<endl;
	return 0;
}

































