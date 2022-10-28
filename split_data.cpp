#include <iostream>
#include <fstream>

#include <string>

using std::cout;
using std::endl;
using std::getline;

using std::ofstream;
using std::ifstream;

using std::string;
using std::to_string;

const int MAX_LINE_PER_FILE_PARTITION = 100000;

int main()
{
  int lineCount = 0;
  int currPartitionedFileSuffix = 1;

  ifstream originalDataset;
  ofstream partitionedDataset;

  originalDataset.open("dataset.csv");

  string data;

  // Will grab each line in "dataset.csv".
  while(getline(originalDataset, data))
  {
    // If we have not read in any data yet for the current partition, then create that partition as a new output stream.
    if(lineCount == 0)
    {
      // Files will be named: "dataPartition1.csv", "dataPartition2.csv", etc...
      string fileContainingPartition = "./splitDataset/dataPartition" + to_string(currPartitionedFileSuffix) + ".csv";
      partitionedDataset.open(fileContainingPartition.c_str());
      cout << "Partitioning 'dataset.csv' into File #" << currPartitionedFileSuffix << "..." << endl;
    }

    // The "endl" ensures that each row (data) of "dataset.csv" will appear on its own line in
    // "dataPartition{currPartitionedFileSuffix}.csv".
    partitionedDataset << data << endl;
    lineCount++;

    // When 100,000 lines has been reached in the current partition, then we will close the current stream to
    // "dataPartition{currPartitionedFileSuffix}.csv" and go to the next number down to continue partitioning.
    if(lineCount == MAX_LINE_PER_FILE_PARTITION)
    {
      lineCount = 0;
      currPartitionedFileSuffix++;
      partitionedDataset.close();
    }
  }

  originalDataset.close();
  partitionedDataset.close();

  cout << "\nPartitioning Complete!" << endl;

  return 0;
}
