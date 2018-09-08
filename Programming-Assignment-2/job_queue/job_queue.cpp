#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using std::vector;
using std::cin;
using std::cout;
using std::swap;

class JobQueue {
 private:
  int num_workers_;
  vector<int> jobs_;
  int changes;
  vector<int> assigned_workers_;
  vector<long long> start_times_;

  void WriteResponse() const {
    for (int i = 0; i < jobs_.size(); ++i) {
      cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
    }
  }

  void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
      cin >> jobs_[i];
  }
  
  void ShiftUp(vector<long long> &next_free_time)
  {
    int last_i;
    for(int i = next_free_time.size(); i > 0; i--)
    {
      last_i = i;
      while(i > 0)
      {
        if(next_free_time[i/2 - 1] > next_free_time[i - 1])
        {
          swap(next_free_time[i/2 - 1],next_free_time[i - 1]);
        }
        i = i/2;
      }
      i = last_i;
    }
  }
  
  void Insert(long long next_processing_time, vector<long long> &next_free_time,vector<int> &thread)
  {
    next_free_time.push_back(next_processing_time);
    ShiftUp(next_free_time);
  }
  void priority_shift(int i, vector<long long> &next_free_time,vector<int> &thread)
  {
     int left, right;
     int min_thread = i;

       left = 2*i + 1;
       right = 2*i + 2;  

       if(right <= (next_free_time.size() - 1) && next_free_time[min_thread] == next_free_time[right] && thread[min_thread] > thread[right])
       {
          min_thread = right;
       }
     
       if(left <= (next_free_time.size() - 1) && next_free_time[min_thread] == next_free_time[left] && thread[min_thread] > thread[left])
       {
          min_thread = left;
       }
     
       if(i!= min_thread)
       {
         swap(thread[i],thread[min_thread]);
         i = min_thread;
         priority_shift(min_thread,next_free_time,thread);
       }
     /*
     if(changes >= thread.size()/2)
     {
       changes = 0;
       priority_shift(0,next_free_time,thread);
     }   
     */
  }

  void ShiftDown(int i, vector<long long> &next_free_time,vector<int> &thread)
  {
     int left, right;
     int min_idx = i;
    
     left = 2*i + 1;
     right = 2*i + 2;
     
     if(right <= (next_free_time.size() - 1)) 
     { 
        if(next_free_time[min_idx] > next_free_time[right])
        {
          min_idx = right;
        }
        else if(next_free_time[min_idx] == next_free_time[right] && thread[min_idx] > thread[right])
        {
          min_idx = right;
        }
     }
        
     if(left <= (next_free_time.size() - 1)) 
     {
        if(next_free_time[min_idx] > next_free_time[left])
        {
          min_idx = left;
        }
        else if(next_free_time[min_idx] == next_free_time[left] && thread[min_idx] > thread[left])
        {
          min_idx = left;
        }
     }
          
     if(i!= min_idx)
     {
        swap(next_free_time[i],next_free_time[min_idx]);
        swap(thread[i],thread[min_idx]);
        ShiftDown(min_idx,next_free_time,thread);
     }
  }

  void AssignJobs() {

    vector<long long> next_free_time;
    vector<int> thread;
    long long next_processing_time = 0;
    
    assigned_workers_.resize(jobs_.size());
    start_times_.resize(jobs_.size());

    next_free_time.resize(num_workers_);
    thread.resize(num_workers_);
    
    for(int i = 0; i< num_workers_; i++)
    {
      thread[i] = i;
      next_free_time[i] = 0;
    }
    for(int i = 0; i < jobs_.size(); ++i)
    {
    /*
      for(int k = 0;k <= 3 ; k++)
        std::cout<<thread[k];
        std::cout<<": "<<i<<"\n";

      for(int k = 0;k <= 3 ; k++)
        std::cout<<next_free_time[k];
        std::cout<<": "<<i<<"\n";
     */ 

      start_times_[i] = next_free_time[0];
      assigned_workers_[i] = thread[0];

      next_processing_time = jobs_[i] + start_times_[i];
      next_free_time[0] = next_processing_time;

      ShiftDown(0,next_free_time,thread);     
      //for(int i = thread.size(); i >= 0; i--)
      //priority_shift(0,next_free_time,thread);      
    }
  }

 public:
  void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  JobQueue job_queue;
  job_queue.Solve();
  return 0;
}
