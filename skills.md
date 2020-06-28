------
### A way to save the memory in DP problems

This skill can help you **save the memory** just using a one-dimension array instead of a two-dimension array when you are solving problems where *dynamic programming* is used. Check the two points listed as follows and then you can use the skill.

> [1] In your problem, you can get a new state of your solution space just by ***sequentially*** updating the last state in a way.
> [2] You don't care about the intermediate states. You only need the ***result*** .

#### Examples

[1] The 0-1 Knapsack Problem

There're n items w1,w2,...,wn whose values are v1,v2,...,vn and a knapsack whose capacity is C. Find a way to put some items in the knapsack and make it most valuable.

```cpp
/*Use a 2-dimension array
  dp[i][j]= the most value you can get when you are only allowed to use 0~ith items and a knapsack whose capacity is j, j<=C.
  w[i]= the storage the ith item will take up. 
  v[i]= the value of the ith item.*/
  
//The main part of the algorithm
//Initialize
for(int i=0;i<=n;++i)
	dp[i][0]=0;
for(int j=0;j<=C;++j)
	dp[0][j]=0;
//Update
for(int i=1;i<=n;++i)
	for(int j=1;j<=C;++j){
		if(w[i]<=j)
		//To pack or not
			dp[i][j]=max(dp[i-1][j-w[i]]+v[i],dp[i-1][j]);
		else
			dp[i][j]=dp[i-1][j];
	}
```
------
```cpp
/*Use a 1-dimension array
	dp[j]= the most value you can get when you are only allowed to use a knapsack whose capacity is j.
	w[i]= the storage the ith item will take up. 
	v[i]= the value of the ith item.*/

//The main part of the algorithm
//Initialize
for(int j=0;j<=C;++j)
	dp[j]=0;
/*Update
  When using a 2-dimension array, because you only need the information of the last row i-1 and the columns before j, you can actually update the 1-dimension array backwards so that the necessary information is not erased.*/
for(int i=1;i<=n;++i)
	for(int j=C;j>=w[i];--j){
		//To pack or not 
		dp[j]=max(dp[j-w[i]]+v[i],dp[j]);
	}
```

[2] The kth row in Yang Hui's Triangle

> The first 4 lines of Yang Hui's Triangle:
>                                                  1
>                                               1    1
>                                             1   2   1
>                                          1   3   3   1
```cpp
/*We use num[i][j] to present the number in ith row, jth column.(started from 0)
  As is known to all, num[i][j]=num[i-1][j-1]+num[i-1][j] for j=1,2,...,i-1 and num[i][0]=num[i][i]=1.
  We need the kth row of the Triangle*/

//Use a 2-dimension array
//The main part of the algorithm
for(int i=0;i<=k;++i)
	for(int j=0;j<=i;++j){
		if(j==0||j==i)
			num[i][j]=1;
		else{
			num[i][j]=num[i-1][j-1]+num[i-1][j];
		}
	}
```
------
```cpp
//Use a 1-dimension array
//The main part of the algorithm
/*When using a 2-dimension array, because you only need the information of the last row i-1 and the columns before j, you can actually update the 1-dimension array backwards so that the necessary information is not erased.*/
std::vector<int> num;
for(int i=0;i<=k;++i){
	num.push_back(1);//To match the number of elements in the ith row
	for(int j=i-1;j>=1;--j){
		num[j]+=num[j-1];
	}
}
```
