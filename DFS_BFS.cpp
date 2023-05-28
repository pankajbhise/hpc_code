#include<iostream>
#include<omp.h>
#include<bits/stdc++.h>

using namespace std;

vector<vector<int>>graph;
vector<bool>visited;

void visited_init(int v){
	
	for(int i=0;i<v;i++){
		visited.assign(i,false);
	}
}

void dfs(int i){
	stack<int>s;
	s.push(i);
	visited[i]=true;
	
	while(s.empty()==false){
		int cur= s.top();
		cout<<cur<<" ";
		

		s.pop();
		

		for(int i=0;i<graph[cur].size();i++){
			int child=graph[cur][i];
			if(visited[child]==false){
				s.push(child);
				visited[child]=true;
			}
		}
	}
}

void parallel_dfs(int i){
	
	omp_set_num_threads(5);
	
	stack<int>s;
	s.push(i);
	visited[i]=true;
	
	while(s.empty()==false){
		int cur= s.top();
		cout<<cur<<" ";
		

		s.pop();
		
		#pragma omp parallel for
		for(int i=0;i<graph[cur].size();i++){
//			cout<<endl<<"thread_id "<<omp_get_thread_num()<<" i "<<i<<endl;
			int child=graph[cur][i];
			if(visited[child]==false){
				s.push(child);
				visited[child]=true;
			}
		}
	}
}

void bfs(int i){
	queue<int>q;
	q.push(i);
	visited[i]=true;
	
	while(q.empty()==false){
		int cur=q.front();
		
		cout<<cur<<" ";
		

		q.pop();
		
	
		for(int i=0;i<graph[cur].size();i++){
			int child=graph[cur][i];
			if(visited[child]==false){
				q.push(child);
				visited[child]=true;
			}
		}
	}
}


void parallel_bfs(int i){
	queue<int>q;
	q.push(i);
	visited[i]=true;
	
	while(q.empty()==false){
		int cur=q.front();
		
		cout<<cur<<" ";
		

		q.pop();
		
		#pragma omp parallel for
		for(int i=0;i<graph[cur].size();i++){
			int child=graph[cur][i];
			if(visited[child]==false){
				q.push(child);
				visited[child]=true;
			}
		}
	}
}

int main(){
	int v,e;
	cout<<"Enter the number of vertices: ";
	cin>>v;
	
	cout<<"Enter the number of edges: ";
	cin>>e;
	
	int x,y;
	graph.resize(v);
	cout<<"Enter the pair of edge:\n";
	for(int i=0;i<e;i++){
	
		cin>>x>>y;
		graph[x].push_back(y);
		graph[y].push_back(x);
	
	}
	
	
	// sequential dfs
	cout<<"Sequential DFS"<<endl;
	visited_init(v);
	auto start1 = chrono::high_resolution_clock::now();
   	dfs(0);
    cout << endl;
    auto end1 = chrono::high_resolution_clock::now();
    cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(end1- start1).count() << " microseconds" << endl;
	
	
	
	//parallel dfs
	cout<<"Parallel DFS"<<endl;
	visited_init(v);
	auto start2 = chrono::high_resolution_clock::now();
   	parallel_dfs(0);
    cout << endl;
    auto end2 = chrono::high_resolution_clock::now();
    cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(end2 - start2).count() << " microseconds" << endl;
	
	
	

	// sequential bfs
	cout<<"Sequential BFS"<<endl;
	visited_init(v);
	auto start3 = chrono::high_resolution_clock::now();
   	bfs(0);
    cout << endl;
    auto end3 = chrono::high_resolution_clock::now();
    cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(end3 - start3).count() << " microseconds" << endl;
	
	
	
	//parallel bfs
	cout<<"Parallel BFS"<<endl;
	visited_init(v);
	auto start4 = chrono::high_resolution_clock::now();
   	parallel_bfs(0);
    cout << endl;
    auto end4 = chrono::high_resolution_clock::now();
    cout << "Time taken: " << chrono::duration_cast<chrono::microseconds>(end4 - start4).count() << " microseconds" << endl;
}
