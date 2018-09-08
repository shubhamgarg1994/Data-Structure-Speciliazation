#include <iostream>
#include <vector>
#include <algorithm>
#include <tgmath.h> 

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
 private:
  vector<int> data_;
  vector< pair<int, int> > swaps_;

  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    
    for (int i = 0; i < swaps_.size(); ++i) {
      std::cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
   
  }
  void ReadData() {
    int n;
    cin >> n;
    data_.resize(n);
    for(int i = 0; i < n; ++i)
      cin >> data_[i];
  }
  void ShiftUp()
  {
    int last_i;
    for(int i = data_.size(); i > 0; i--)
    {
      last_i = i;
      while(i > 0)
      {
        if(data_[i/2 - 1] > data_[i - 1])
        {
          std::cout<<" "<<last_i;
          swap(data_[i/2 - 1],data_[i - 1]);
          swaps_.push_back(make_pair((i/2 - 1),i - 1));
        }
        i = i/2;
      }
      i = last_i;
    }
  }
  void ShiftDown(int i)
  {
     int left, right;
     int flag = 1; 
     while(flag != 0)
     {
        flag = 0;
        left = 2*i + 1;
        right = 2*i + 2;
        if(right <= (data_.size() - 1) && data_[left] > data_[right])
        {
          if(data_[i] > data_[right])
          {
            swap(data_[i],data_[right]);
            swaps_.push_back(make_pair((i),right));
            flag = right;
          }
        }
        else
        {
          if(left <= (data_.size() - 1) && data_[i] > data_[left])
          {
            swap(data_[i],data_[left]);
            swaps_.push_back(make_pair((i),left));
            flag = left;
          }
        }
        i = flag;
     }
  }
  void GenerateSwaps() {
    swaps_.clear();
    // The following naive implementation just sorts 
    // the given sequence using selection sort algorithm
    // and saves the resulting sequence of swaps.
    // This turns the given array into a heap, 
    // but in the worst case gives a quadratic number of swaps.
    //
    // TODO: replace by a more efficient implementation
    
    for(int i = data_.size()/2; i >= 0; i--)
    {
      ShiftDown(i);
    }
  }

 public:
  void Solve() {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  HeapBuilder heap_builder;
  heap_builder.Solve();
  return 0;
}
