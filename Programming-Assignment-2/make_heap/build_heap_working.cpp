#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder
{
private:
  vector< int > data_;
  vector< pair< int, int > > swaps_;


  void WriteResponse() const {
    cout << swaps_.size() << "\n";
    for (int i = 0; i < swaps_.size(); ++i) {
       std::cout << swaps_[i].first << " " << swaps_[i].second << "\n";
    }
     for (int i = 0; i < data_.size(); ++i) {
       std::cout << data_[i]<< " ";
    }
  }

  int LeftChild( int i ) { return 2 * i + 1; }

  int RightChild( int i ) { return 2 * i + 2; }

  int Parent( int i )
  {
    if ( i == 0 )
      return 0;
    else
      return ( i - 1 ) / 2;
  }

  void ReadData()
  {
    int n;
    cin >> n;
    data_.resize( n );
    for ( int i = 0; i < n; ++i )
      cin >> data_[ i ];
  }

  void SiftUp( int i )
  {
    int c = i;
    while ( c > 0 && data_[ Parent( c ) ] > data_[ c ] )
    {
      swaps_.push_back( make_pair( Parent( c ), c ) );
      swap( data_[ Parent( c ) ], data_[ c ] );
      c = Parent( c );
    }
  }

  void SiftDown( int i )
  {
    int size = data_.size() - 1;
    int maxIndex = i;
    int left = LeftChild( i );
    if ( left <= size && data_[ left ] < data_[ maxIndex ] )
    {
      maxIndex = left;
    }

    int right = RightChild( i );
    if ( right <= size && data_[ right ] < data_[ maxIndex ] )
    {
      maxIndex = right;
    }

    if ( i != maxIndex )
    {
      swaps_.push_back( make_pair( i, maxIndex ) );
      swap( data_[ i ], data_[ maxIndex ] );
      SiftDown( maxIndex );
    }
  }

  void GenerateSwaps()
  {
    swaps_.clear();
    int n = data_.size();
    int mid = n / 2;
    for ( int i = mid; i >= 0; --i )
    {
      SiftDown( i );
    }
  }

public:
  void Solve()
  {
    ReadData();
    GenerateSwaps();
    WriteResponse();
  }
};

int main()
{
  std::ios_base::sync_with_stdio( false );
  HeapBuilder heap_builder;
  heap_builder.Solve();

  return 0;
}
