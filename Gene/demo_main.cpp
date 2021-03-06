#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include <cmath>
#include <assert.h>
#include <set>
#include <numeric>
#include <random>
#include <ctime>
#include <jsoncpp/json/json.h>

#define DNA_SIZE        11
#define POP_SIZE        200
#define CROSSOVER_RATE  0.8
#define MUTATION_RATE   0.005
#define N_GENERATIONS   100
#define RADIUS          70
#define NUM_POINTS      2048
#define N               999

using namespace std;

vector<vector<float>> loadFile(const string& path)
{
    Json::Reader reader;
    Json::Value root;
    fstream fileObj(path);

    vector<vector<float>> data(0,vector<float>(2,0));
    list<string> key1(0);

    if(!fileObj)
    {
        cout<<"read file failed"<<endl;
	cout<<path<<endl;
	exit(-1);
    }else{
	    // load your data
	    
			}
		     }
		 }
	     }
	}
    }
     cout<<'\n'<<"success process data "<<data.size()<<" "<<"items."<<'\n';
     return data;
}

vector<vector<float>> computeDist(const vector<vector<float>>& data)
{
    assert(NUM_POINTS == data.size());
    vector<vector<float>> W(NUM_POINTS,vector<float>(NUM_POINTS,0));
    unsigned int row=0;

    for(auto& vec1 : data)
    {
	unsigned int col=0;
        for(auto& vec2 : data)
	{
	    float dist = sqrt(pow((vec1.at(0)-vec2.at(0)),2) + pow((vec1.at(1)-vec2.at(1)),2));
	    W.at(row).at(col) = dist;
	    col++;
	}
	row++;
    }
    return W;
}

void showMatrix(const vector<vector<int>>& pop)
{
    cout<<"please click ENTER to show matrix ";
    cin.get();
    unsigned int popSize=pop.size();
    
    for(int i=0;i<popSize;i++)
    {
        for(int j=0;j<pop.at(i).size();j++)
	{
	    cout<<pop.at(i).at(j)<<" ";
	}
	cout<<'\n';
    }
    cout<<'\n';
}

vector<vector<int>> initMatrix(const int pop_size,const int dna_size)
{
    vector<vector<int>> pop(pop_size,vector<int>(dna_size,0));
    for(int i=0;i<pop_size;i++) 
    {
        for(int j=0;j<dna_size;j++)
	{
	    unsigned int temp = rand()%2;
	    pop.at(i).at(j) = temp;
	}
    }
    return pop;
}

void mutation(vector<int>& child)
{
    float prob=rand()%(N+1)/(float)(N+1);
    unsigned int low = 0;
    unsigned int high = DNA_SIZE*5;

    if(prob<MUTATION_RATE)
    {
        unsigned int pointMutate = rand()%(high-low)+low;
	child.at(pointMutate) = child.at(pointMutate)^1;
    }
}

vector<vector<int>> crossoverAndMutation(const vector<vector<int>>& pop)
{
     unsigned int low = 0;
     unsigned int high = 0;

     vector<vector<int>> new_pop(0);
     for(auto father: pop)
     {
         vector<int>& child=father;
         float prob = rand()%(N+1)/(float)(N+1);
	 if(prob<CROSSOVER_RATE)
	 {
             high = pop.size();
	     unsigned int motherIndex =  rand()%(high-low)+low;
	     vector<int> mother = pop.at(motherIndex);
	     high = mother.size();
	     unsigned int pointIndex = rand()%(high-low)+low;
             for(int j=pointIndex;j<DNA_SIZE*5;j++)
	     {
	         child.at(j) = mother.at(j);
	     }
	 }
	 mutation(child);
	 new_pop.push_back(child);
     }
     return new_pop;
}

vector<vector<int>> translateDNA(const vector<vector<int>>& pop)
{
    assert(POP_SIZE == pop.size());
    vector<vector<int>> X(POP_SIZE,vector<int>(5,0));
    vector<vector<int>>x1_pop(0,vector<int>(DNA_SIZE,0));
    vector<vector<int>>x2_pop(0,vector<int>(DNA_SIZE,0));
    vector<vector<int>>x3_pop(0,vector<int>(DNA_SIZE,0));
    vector<vector<int>>x4_pop(0,vector<int>(DNA_SIZE,0));
    vector<vector<int>>x5_pop(0,vector<int>(DNA_SIZE,0));
    for(auto &dna : pop)
    {
	    x1_pop.push_back(vector<int>(dna.begin() , dna.begin()+DNA_SIZE));
	    x2_pop.push_back(vector<int>(dna.begin()+DNA_SIZE , dna.begin()+DNA_SIZE*2));
	    x3_pop.push_back(vector<int>(dna.begin()+DNA_SIZE*2 , dna.begin()+DNA_SIZE*3));
	    x4_pop.push_back(vector<int>(dna.begin()+DNA_SIZE*3 , dna.begin()+DNA_SIZE*4));
	    x5_pop.push_back(vector<int>(dna.begin()+DNA_SIZE*4 , dna.begin()+DNA_SIZE*5));
    }

    vector<int> range(DNA_SIZE);
    for(int i=0;i<DNA_SIZE;i++)
    {
        range.at(i) = pow(2,i);
    }
    reverse(range.begin(),range.end());
    for(int j=0;j<POP_SIZE;j++)
    {
        for(int k=0;k<DNA_SIZE;k++)
	{
	    X.at(j).at(0) += x1_pop.at(j).at(k)*range.at(k);
	    X.at(j).at(1) += x2_pop.at(j).at(k)*range.at(k);
	    X.at(j).at(2) += x3_pop.at(j).at(k)*range.at(k);
	    X.at(j).at(3) += x4_pop.at(j).at(k)*range.at(k);
	    X.at(j).at(4) += x5_pop.at(j).at(k)*range.at(k);
	 
	}
    }
    return X;
}

list<int> F(const vector<vector<int>>& X,const vector<vector<float>>& W)
{
    assert(POP_SIZE == X.size());
    list<int> total(0);
    for(int i=0;i<POP_SIZE;i++)
    {
	    float x1 = X.at(i).at(0);
	    float x2 = X.at(i).at(1);
	    float x3 = X.at(i).at(2);
	    float x4 = X.at(i).at(3);
	    float x5 = X.at(i).at(4);

            list<int>x1_list(0);
            list<int>x2_list(0);
            list<int>x3_list(0);
            list<int>x4_list(0);
            list<int>x5_list(0);

	    for(int j=0;j<NUM_POINTS;j++)
	    {
	        float tempVal1 = W.at(x1).at(j);
		if (tempVal1 < RADIUS)
	        {
		    x1_list.push_back(j);    
		}

	        float tempVal2 = W.at(x2).at(j);
		if (tempVal2 < RADIUS)
	        {
		    x2_list.push_back(j);    
		}

		float tempVal3 = W.at(x3).at(j);
		if (tempVal3 < RADIUS)
	        {
		    x3_list.push_back(j);    
		}

	        float tempVal4 = W.at(x4).at(j);
		if (tempVal4 < RADIUS)
		{
		    x4_list.push_back(j);
		}

		float tempVal5 = W.at(x5).at(j);
		if (tempVal5 < RADIUS)
		{
		    x5_list.push_back(j);
		}
	    }

            list<int>total_list(0);
	    total_list.merge(x1_list);
	    total_list.merge(x2_list);
	    total_list.merge(x3_list);
	    total_list.merge(x4_list);
	    total_list.merge(x5_list);

	    set<int>se(total_list.begin(),total_list.end());
	    list<int>l(se.begin(),se.end());
	    int length = l.size()-5;
	    total.push_back(length);
    }
    return total;
}

vector<int> get_fitness(const vector<vector<int>>& pop,const vector<vector<float>>& W)
{
   vector<vector<int>>X = translateDNA(pop);
   list<int> predList = F(X,W);
   vector<int> pred(predList.begin(),predList.end());
   return pred;
}

vector<vector<int>> select(const vector<vector<int>>& pop,const vector<int>& fitness)
{	
	assert(POP_SIZE == fitness.size());
	assert(POP_SIZE == pop.size());

        vector<vector<int>> newPop(POP_SIZE,vector<int>(DNA_SIZE*5,0));
        vector<int>idx(0); 
	int sum=accumulate(fitness.begin(),fitness.end(),0);
	if(sum!=0)
	{
            default_random_engine generator;
            discrete_distribution<int> distribution(fitness.begin(),fitness.end());
	    for(int i=0;i<POP_SIZE;i++)
	    {
	        int number = distribution(generator);
		idx.push_back(number);
	    }
	}else{
	    for(int i=0;i<POP_SIZE;i++)
	    {
	        idx.push_back(i);
	    }
	}
	
	for(int i=0;i<POP_SIZE;i++)
	{
	    int num = idx[i];
	    newPop[i] = pop[num];
	}
	return newPop; 
}

int searchMaxVal(const vector<int>& fitness)
{
    assert(POP_SIZE == fitness.size());

    unsigned  int maxPos=0;
    unsigned int maxValue = fitness.at(maxPos);
    for(int pos=1;pos<POP_SIZE;pos++)
    {
	    unsigned int curValue = fitness.at(pos);
	    if (curValue>maxValue)
	    {
	        maxValue = curValue;
		maxPos=pos;
	    }
    }
    return maxPos;
}

void printInfo(const vector<vector<int>>& pop,const vector<vector<float>>& W)
{
    vector<int> fitness = get_fitness(pop,W);
    unsigned int pos = searchMaxVal(fitness);
    vector<vector<int>> X = translateDNA(pop);

    cout<<"optimization DNA Index: "<<pos<<endl;
    cout<<"max fitness Value: "<<fitness.at(pos)<<endl;
    cout<<"optimization (x1,x2,x3,x4,x5): ";
    cout<<X.at(pos).at(0)<<" ";
    cout<<X.at(pos).at(1)<<" ";
    cout<<X.at(pos).at(2)<<" ";
    cout<<X.at(pos).at(3)<<" ";
    cout<<X.at(pos).at(4)<<" "<<endl;
}

int main()
{
    srand(time(NULL));
    const string path = "your data";
    const vector<vector<float>>data = loadFile(path);
    const vector<vector<float>>W = computeDist(data);
    vector<vector<int>> pop = initMatrix(POP_SIZE,DNA_SIZE*5);

    for(int n=0;n<N_GENERATIONS;n++)
    {
	cout<<"generations="<<n<<":"<<'\n';
        //showMatrix(pop);
        vector<vector<int>>pop1 = crossoverAndMutation(pop);
        //showMatrix(pop1);
        vector<int> fitness = get_fitness(pop1,W);
        pop=select(pop1,fitness);
        printInfo(pop,W);
	cout<<"\n";
    }
    return 0;
}
