#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using std::cin;
using std::cout;
using std::endl;
using std::max;
using std::vector;

struct childInfo{
	int idx;
	long long int sizeTable;
	childInfo(int idx = -1,int sizeTable = 0):
	idx(idx),sizeTable(sizeTable){}
};

struct DisjointSetsElement {
	int size, parent, rank;
	struct childInfo tableidx;
	
	DisjointSetsElement(long long int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	long long int size;
	long long int max_table_size;

	vector <DisjointSetsElement> sets;

	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
		{
			sets[i].parent = i;
			sets[i].tableidx.idx = -1;
			sets[i].tableidx.sizeTable = 0;
		}
	}

	int getParent(int table) {
		// find parent and compress path
		int i = table, p = 0;
		vector <int> parents_to_update;
		do
		{	
		  p = i;	
		  i = sets[p].parent;
		  //parents_to_update.push_back(p);
		}while(i != p);
		
		for (auto it = parents_to_update.begin(); it != parents_to_update.end(); it++) 
		{
		  sets[*it].parent = p;
		}
		
		return p;
  	}
	childInfo calcTable(int parent){
		long long int sizeTable = 0,i = 0, idx = parent;
		struct childInfo temp;
		do{
			i = idx;
			sizeTable = sizeTable + sets[i].size;
			idx = sets[i].tableidx.idx;
		}while(idx != -1);

		temp.idx = i;
		temp.sizeTable = sizeTable;
	
		return temp;
	}
	int merge(int destination, int source) {

		int realDestination = getParent(destination);
		int realSource = getParent(source);
		int ans = 0;

		if (realDestination != realSource) {
		
			/*
			tempS =  calcTable(realSource);
			tempD = calcTable(realDestination);

			sets[tempD.idx].size = sets[tempD.idx].size + tempS.sizeTable;
			  
			sets[realSource].tableidx.idx = realDestination;
			sets[tempS.idx].size = 0;
			*/

			//cout<<tempD.idx<<sets[tempD.idx].size;
			if(sets[realDestination].rank < sets[realSource].rank)
			{	  	
			  sets[realDestination].parent = realSource;	
			  sets[realSource].size = sets[realSource].size + sets[realDestination].size;
			  sets[realDestination].size = 0;
			  ans = sets[realSource].size;
			}
			else{
			  sets[realSource].parent = realDestination;
			  sets[realDestination].size = sets[realDestination].size + sets[realSource].size;
			  ans = sets[realDestination].size;
			  sets[realSource].size = 0;
			  if(sets[realDestination].rank == sets[realSource].rank)
			  {
			    sets[realDestination].rank = sets[realDestination].rank + 1; 
			  }
			}
		}
		//cout<<sets[realDestination].rank<<sets[realSource].rank;	
		//return sets[tempD.idx].size;	
		//cout<<ans;
		return ans;
	}
};

int main() {
	long long int n, m;
	cin >>n >>m;
	long long int merged_size = 0,max_merged_size = 0;
	DisjointSets tables(n);
	for (auto &table : tables.sets) {
		cin >> table.size;
		if(table.size > tables.max_table_size)
		tables.max_table_size = table.size;
	}
	
	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
                --destination;
                --source;

		merged_size = tables.merge(destination, source);
		//cout << max(tables.max_table_size,tables.sets[destination].size)<< endl;
		max_merged_size =  tables.max_table_size > merged_size ? tables.max_table_size:merged_size;
		cout<<max_merged_size<<endl;
		if(max_merged_size > tables.max_table_size)
		{
			tables.max_table_size = max_merged_size; 
		}
	}

	return 0;
}
