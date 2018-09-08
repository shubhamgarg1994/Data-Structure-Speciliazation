#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;
  int parent_node;

  std::vector<Node> nodes;
  nodes.resize(n);
  for (int child_index = 0; child_index < n; child_index++) {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    nodes[child_index].key = child_index;
  }

  Node *v;
  int  i = 0,size = 0,visited = 0,height = 0,layer_size = 0;
  std::queue <int> tree;

  for(int leaf_index = 0; leaf_index < n; leaf_index++){
    v = &nodes[leaf_index];
    if(v->parent == NULL)
    {
      parent_node = leaf_index;
      break;
    }
  }
  v = &nodes[parent_node];
  
  tree.push(v->key);
  layer_size = 1;
  int counter,local_size = 0;
  
  while(!tree.empty())
  {
    v = &nodes[tree.front()];
    //std::cout<<v->key;
    tree.pop();
    local_size = v->children.size();
    size = size + v->children.size();
    //layer_size = size;
    i = 0;
    visited++;
    while(i <= local_size - 1)
    { 
      tree.push(v->children[i]->key);
      i++;
    }
    if((layer_size != 0) && (layer_size == visited))
    {
      height ++;
      visited = 0;
      layer_size = size; 
      //std::cout<<" "<<height<<layer_size<<"\n";
      size = 0;
    }
    counter ++;
  }
  std::cout << height << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
