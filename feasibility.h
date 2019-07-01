int feasibility()
{
	int t=0;
	for(int i=0;i<M;i++)
	   {
		  for(int j=0;j<N;j++)
	   	     {
	   	     	if(game[i][j]==-1)
	   	     	  {
	   	     	  	continue;
	   	     	  }
	   	     	for(int k=0;k<=i;k++)
	   	     	   {
	   	     	   	for(int l=0;l<N;l++)
	   	     	   	   {
	   	     	   	   	if(k<i)
	   	     	   	   	  {
	   	     	   	   	  	if(game[k][l]==-1)
	   	     	   	   	  	  {
	   	     	   	   	  	  	continue;
	   	     	   	   	  	  }
	   	     	   	   	  	else
	   	     	   	   	  	  {
	   	     	   	   	  	  	if(game[k][l]>game[i][j])
	   	     	   	   	  	  	  {
	   	     	   	   	  	  	  	t++;
	   	     	   	   	  	  	  }
	   	     	   	   	  	  }
	   	     	   	   	  }
	   	     	   	   	else
	   	     	   	   	  {
	   	     	   	   	  	if(l<j)
	   	     	   	   	  	  {
	   	     	   	   	  	  	if(game[k][l]==-1)
	   	     	   	   	  	  	  {
	   	     	   	   	  	  	  	continue;
	   	     	   	   	  	  	  }
	   	     	   	   	  	  	else
	   	     	   	   	  	  	  {
	   	     	   	   	  	  	  	if(game[k][l]>game[i][j])
	   	     	   	   	  	  	  	  {
	   	     	   	   	  	  	  	  	t++;
	   	     	   	   	  	  	  	  }
	   	     	   	   	  	  	  }
	   	     	   	   	  	  }
	   	     	   	   	  }
	   	     	   	   }
	   	     	   }
	   	     	  
	   	     }
	   }
	return t;
}
