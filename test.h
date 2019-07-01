//检测是否复原的函数
bool test()
{
	bool bprimet=true;
	for(int i=0;i<M;i++)
	   {
	   	for(int j=0;j<N;j++)
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
