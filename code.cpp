#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;
int q_gram_size;
int str_len, substr_len;
int* str;
int* substr;
int min(int num1, int num2)
{
	if (num1 < num2)
		return num1;
	return num2;
}

int max(int num1, int num2)
{
	if (num1 > num2)
		return num1;
	return num2;
}

int factorial(int n)
{
	int temp=1;
	while (n>1)
		temp=temp*n--;
	return temp;
}

void make_Qgrams(int* arr1, int** arr2, int outer_counter, int inner_counter)
{
	for(int i=0, j=0, k=0; i<outer_counter; i++)
	{
		for(j=0; j<inner_counter; j++)
		{
			arr2[i][j]=arr1[k++];
		}
		k = k-inner_counter+1;
	}

}

void calculate_mew(int* arr1, int size, int* arr2)
{
	arr2[0]=0;
	if (size<=1)
	{
		return;
	}
	for(int i=1, smaller_count=0; i<size; i++)
	{
		for(int j=0; j<i; j++)
		{
			if (arr1[j] <= arr1[i])
			{
				smaller_count++;
			}
		}
		arr2[i]=smaller_count;
		smaller_count=0;
	}
}

bool Is_same(int* arr1, int* arr2, int length, int mew_choice=0)
{
	if (mew_choice==0)
	{
		for(int i=0; i<length; i++)
		{
			if (arr1[i] != arr2[i])
				return false;
		}
		return true;
	}
	else
	{
		int temp_mew1[length], temp_mew2[length];
		if (mew_choice==1)
		{
			calculate_mew(arr1, length, temp_mew1);
			for(int i=0; i<length; i++)
			{
				if (temp_mew1[i] != arr2[i])
					return false;
			}
			return true;
		}
		else if (mew_choice==2)
		{
			calculate_mew(arr2, length, temp_mew2);
			for(int i=0; i<length; i++)
			{
				if (arr1[i] != temp_mew2[i])
					return false;
			}
			return true;
		}
		else
		{
			calculate_mew(arr1, length, temp_mew1);
			calculate_mew(arr2, length, temp_mew2);		
			for(int i=0; i<length; i++)
			{
				if (temp_mew1[i] != temp_mew2[i])
					return false;
			}
			return true;
		}
		return true;
	}
}

int find_lx(int** Qgrams, int index, int no_of_qgrams, int qgram_size)
{
	int lx=index+qgram_size-1;
	int temp_array[qgram_size];
	int temp_mew_1[qgram_size], temp_mew_2[qgram_size];
	calculate_mew(Qgrams[index], qgram_size, temp_mew_1);
	for(int i=0; i<qgram_size; i++)
		temp_array[i]=Qgrams[index][i];
	for(int i=0; i<no_of_qgrams; i++)
	{
		if (i==index)
			lx=index+qgram_size-1;
		else
		{
			calculate_mew(Qgrams[i], qgram_size, temp_mew_2);
			if (Is_same(temp_mew_1, temp_mew_2, qgram_size))
				lx = i+qgram_size-1;
		}
	}
	return lx;
}

int find_fx(int* arr)
{
	int temp_arr[q_gram_size];
	calculate_mew(arr, q_gram_size, temp_arr);
	int to_ret=0;
	for(int i=0; i<q_gram_size; i++)
		to_ret += (temp_arr[i]) * factorial(i); 
	return to_ret;
}

void calculate_pi(int* arr1, int* arr2, int size)
{
	//first index will always have pi=0
	arr2[0]=0;
	int prefix[size], suffix[size], prefix_mew[size], suffix_mew[size];
	//loop will run for each index of substr except the fisrt one
	for(int i=1, pre_suf_index=0, pre_suf_len=0, pi_counter; i<size; i++)
	{
		//we will calculate how many elements are to be entered in prefix and suffix
		pre_suf_len=(i+1)/2;
		pre_suf_index=0;
		for (int i=0; i<pre_suf_len; i++, pre_suf_index++)
		{
			prefix[i]=arr1[pre_suf_index];
		}
		if (i%2!=1)
			pre_suf_index++;
		for (int i=0; i<pre_suf_len; i++, pre_suf_index++)
		{
			suffix[i]=arr1[pre_suf_index];
		}
		calculate_mew(prefix, pre_suf_len, prefix_mew);
		calculate_mew(suffix, pre_suf_len, suffix_mew);
		for(int j=0; j<pre_suf_len; j++)
		{
			if (prefix_mew[j]==suffix_mew[j])
				pi_counter++;
		}
		arr2[i]=pi_counter;
		pi_counter=0;
	}		
}

void Algo_1(int** q_grams_str, int** q_grams_substr, int* shift)
{
	int* substr_mew = new int [substr_len];
	calculate_mew(substr, substr_len, substr_mew);
	int m=substr_len;
	int n=str_len;
	int t=find_fx( q_grams_substr[substr_len-q_gram_size] );
//	cout<<"\n\n\n\nF(P[m-q]) = F(P["<<substr_len<<"-"<<q_gram_size
	int i=m-1;
	int c=0;
	int s=0;
	int* temp_arr;
	while (i<n)
	{
		c=find_fx(q_grams_str[i-q_gram_size+1]);	
		if (c==t)
		{
			temp_arr = &str[i-m+1];
			if (Is_same(temp_arr, substr_mew, substr_len, 1));
				cout<<"Pattern occurs at index#="<<i-substr_len+1<<"-"<<i<<" of the original string"<<endl;
		}
		i = i+shift[c];
	}
}

void Algo_2(int** q_grams_str, int** q_grams_substr, int* shift)
{
	int* substr_mew = new int [substr_len];
	calculate_mew(substr, substr_len, substr_mew);
	int* Pi=new int [substr_len];
	calculate_pi(substr, Pi, substr_len);
	int m=substr_len;
	int n=str_len;
	int t=find_fx(q_grams_substr[m-q_gram_size]);
	int i=m-1;
	int j=1;
	int c=0;
	int s=0;
	int* temp_arr;
	while (i<n)
	{
		if (j==1)
		{
			while ( ( find_fx(q_grams_str[i-q_gram_size+1]) ) != t )
			{
				c=find_fx(q_grams_str[i-q_gram_size+1]);
				i = i+shift[c];
				if (i>=n)
				{
					return;
				}
			}
		}
		s=i-m+1;
		temp_arr = &str[s];
		while ( (j<m) && (Is_same(substr_mew, temp_arr, j, 2) ) )
		{
			j=j+1;
		}
		if (j==m)
		{
			cout<<"\t\tPattern occurs at index#="<<i-substr_len+1<<"-"<<i<<" of the original string"<<endl;
			break;
		}
		i=i+(j-Pi[j-1]);		
		j=max(1, Pi[j-1]);
	}
}

int main()
{
	fstream fileObject;
	string filename;
	int algo_number;
	cout<<"Enter the name of file you want to read from: ";
	getline(cin, filename);
	fileObject.open(filename.c_str(), ios::in);
	//taking input the original string
	if (!(fileObject>>str_len))
	{
		cout<<"file reading failed\n";
		exit(0);
	}
	str=new int [str_len];
	for(int i=0; i<str_len; i++)		
		fileObject>>str[i];


	//taking input the pattern we want to search in the string
	fileObject>>substr_len;
	substr=new int [substr_len];
	for(int i=0; i<substr_len; i++)		
		fileObject>>substr[i];
	cout<<"----------------------------Successfully read data from file---------------------------------------------\n";

	//assigning size to q_grams
	q_gram_size=substr_len;

	
	//allocating the space
	int* str_mew=new int [str_len];
	int* substr_mew= new int [substr_len];

	calculate_mew(str, str_len, str_mew);
	calculate_mew(substr, substr_len, substr_mew);
	int* Pi = new int [substr_len];
	calculate_pi(substr, Pi, substr_len);
//	int Pi[]={0, 1, 1, 2, 1, 1, 2};

	//assigning memory for q_grams of original string
	int str_no_of_Qgrams=str_len-q_gram_size+1;
	int** q_grams_str=new int* [str_no_of_Qgrams];				
	for(int i=0; i<str_no_of_Qgrams; i++)
		q_grams_str[i]=new int[q_gram_size];
	//assigning memory for q_grams of substring
	int substr_no_of_Qgrams=substr_len-q_gram_size+1;
	int** q_grams_substr=new int* [substr_no_of_Qgrams];
	for(int i=0; i<substr_no_of_Qgrams; i++)
		q_grams_substr[i]=new int[q_gram_size];

	//assigining the values to qgrams for string and substring
	make_Qgrams(substr, q_grams_substr, substr_no_of_Qgrams, q_gram_size);
	make_Qgrams(str, q_grams_str, str_no_of_Qgrams, q_gram_size);

	int shift[factorial(q_gram_size)];
	for(int i=0; i<factorial(q_gram_size); i++)
		shift[i]=1;
	
	
	for(int i=q_gram_size-1, temp_fx=0, temp_lx=0, temper=0; i<substr_len-1; i++)
	{
		temp_lx=find_lx(q_grams_substr, i-2, substr_no_of_Qgrams, q_gram_size);
		temp_fx=find_fx(q_grams_substr[i-2]);
		shift[temp_fx] = min(substr_len - q_gram_size + 1, substr_len - temp_lx - 1); 
	}
	fileObject.close();	

	cout<<"Which algo you want to perform\n1.\tAlgorithm#1\n2.\tAlgorithm#2\n";
	cin>>algo_number;	
	if (algo_number==1)
		Algo_1(q_grams_str, q_grams_substr, shift);
	else if (algo_number==2)
		Algo_1(q_grams_str, q_grams_substr, shift);
	else
		cout<<"Invalid option selected\n";
	return 0;
}

