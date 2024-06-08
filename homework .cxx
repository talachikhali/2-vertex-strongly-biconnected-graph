#include <iostream>
#include <list>
#include<vector>
#include <stack>
#include <string>
#include <algorithm> 
using namespace std;

/* Huda Najjar : constructer and add function
   Patricia Rustom : printGraph and init function 
   Nagham Ajeeb & Mariam Kazzour : dfs function
   Tala Chikhali : gabow function
   Elie Istebrian: copy function
   Hadi Kanjo and Karam Donia : underlying graph function
   Inanna Jabbour and seren Ahmad : biconnected function
   Ali Mousa and Sahar Mehrez : twoVertrxBionnected function 

*/



class graph {
private:
  int V_count;
  list <int>* adj;
public :
  vector <string> state;
  vector<int> dfs_num;
  vector<int> finish_num;
  int dfs_counter = 0;
  int fin_counter = 0;
  int connected = 0;
  vector<int> comp;
  stack <int> OStack;
  stack <int> RStack;
  
  graph(int v) {
    this->V_count = v;
    adj = new list <int>[V_count];
  }
  void add(int v, int w) {
    adj[v].push_back(w);
  }
  void printGraph() {
    for (int i = 0; i < V_count; i++) {
      cout << "Vertex " << i << " : ";
      for (int j : adj[i]) {
        cout << " -> " << j;
      }
      cout << endl;
    }
  }
  void init() {
    dfs_counter = 0;
    fin_counter = 0;
    connected = 0;
    comp.resize(V_count, -1);
    state.resize(V_count, "new");
    dfs_num.resize(V_count, -1);
    finish_num.resize(V_count, -1);
  }
  void dfs(int v) {
    state[v] = "active";
    dfs_num[v] = dfs_counter;
    dfs_counter++;
    OStack.push(v);
    RStack.push(v);
    for (int w : adj[v]) {
      if (state[w] == "new") {
        dfs(w);
      }
      else if (w != OStack.top()) {
        while (dfs_num[w] < dfs_num[RStack.top()]) {

          RStack.pop();
        }
      }
    }
    finish_num[v] = fin_counter;
    fin_counter++;
    state[v] = "finished";
    if (v == RStack.top()) {
      RStack.pop();
      connected++;
      int w = -1;
      while (w != v) {
        w = OStack.top();
        OStack.pop();
        comp[w] = v;
      }
    }
  }
  bool gabow() {
    this->init();
    for (int i = 0; i < V_count; i++) {
      if (state[i] == "new") {
        dfs(i);
      }
    }
  if (connected == 1) {
    return true;
  }
  else {
    return false;
  }
  }

  graph copy() {
    graph g1(this->V_count);
    for (int i = 0; i < V_count; i++) {
      for (int j : adj[i]) {
        g1.add(i, j);
      }
    }
    return g1;
  }

  graph underlying() {
    graph g1 = this->copy();
    for (int i = 0; i < V_count; i++)
      for (int w : g1.adj[i]) {
        if (find(g1.adj[w].begin(), g1.adj[w].end(), i) == g1.adj[w].end())
          g1.add(w, i);
      }
    return g1;
  }
  bool biconnected() {
    if (!gabow()) return false;
    graph underGraph = this->underlying();
    int nodeInProgress = 0;
    graph subGraph(V_count - 1);
    int index = -1;
    while (nodeInProgress < V_count) {
      for (int i = 0; i < V_count; i++) {
        index++;
        if (i == nodeInProgress) {
          index--;
          continue;
        }
        for (int j : underGraph.adj[i]) {
          if (j == nodeInProgress)
            continue;
          else {
            if (j > nodeInProgress)
              subGraph.add(index, j-1);
            else subGraph.add(index, j);
          }
        }
      }
      if (!subGraph.gabow())
        return false;
      nodeInProgress++;
      delete [] subGraph.adj;
      subGraph.adj = new list <int>[V_count-1];
    }
    return true;
  }
  
  bool twoVertrxBionnected() {
    if (!biconnected()) return false;
    graph testGraph =this->copy();
    int nodeInProgress = 0;
    graph subGraph(V_count);
    while (nodeInProgress < V_count) {
      for (int i = 0; i < V_count; i++) {
        if (i == nodeInProgress) {
          continue;
        }
        else
          for (int j : testGraph.adj[i])
            if (j == nodeInProgress)
              continue;
            else subGraph.add(i, j);
      }
      if (!subGraph.biconnected())
        return false;
      nodeInProgress++;
      delete[] subGraph.adj;
      subGraph.adj = new list <int>[V_count];
    }
    return true;
  }
  

};

  int main() {
    graph g(4);
    g.add(0, 1);
    g.add(1, 2);
    g.add(2, 3);
    g.add(3, 0);

  }