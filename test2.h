bool test2()
{
	bool bprimet=true;
	for(int i=M-2;i<M;i++)
	   {
	   	for(int j=0;j<N-2;j++)
	   	   {
	   	   	if(now[i][j]!=begin[i][j])
	   	   	  {
	   	   	  	bprimet=false;
	   	   	  	break;
	   	   	  }
	   	   	if(bprimet==false)
	   	   	  {
	   	   	  	break;
	   	   	  }
	   	   }
	   }
	return bprimet;
} 
