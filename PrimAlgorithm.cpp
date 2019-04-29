#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
using namespace std;
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#define NumOfCities 128
#define NUMOFEDGES 128
					// Finding minimum spanning tree between     //
					// 128 major cities in the U.S using Prim's  //
					// algorithm				     //
					// -Christian Lopez			     //


//Fucntion prototypes
void readData(int[NUMOFEDGES][NUMOFEDGES], string[]);
void print(int parent[], int n, const string city[], int graph[][NUMOFEDGES]);
int minKey(int key[], bool mstSet[]);
void primMST(int[NUMOFEDGES][NUMOFEDGES], string[]);


/*
Function to open file and store the weights
*/
void readData(int Adj[NUMOFEDGES][NUMOFEDGES], string V[]) {
	stringstream iss;
	ifstream ifs;
	ofstream ofs;
	ifs.open("miles.dat");
	if (ifs.fail()) { //Check for error states
		cout << "Error! File not found!" << endl;
		system("PAUSE");
		exit(1);
	}
	int v = -1;
	int e = 0;
	while (!ifs.eof()) {
		string data;
		getline(ifs, data);

		data = data.substr(0, data.find('['));//keep the name of the city by delimiting out string with the char '['
		if (isdigit(data[0])) {
			istringstream ss(data);
			int weight;
			while (ss >> weight) {
				Adj[v][e] = weight; //Build a mirrored adjecency matrix
				Adj[e][v] = weight;
				e--;
			}
		}
		else if (isalpha(data[0])) {
			V[++v] = data;
			e = v - 1;
		}
	}
	//Open a text file of the adjecency matrix
	ofs.open("ADJMATRIX.txt");

	for (int i = 0; i < NUMOFEDGES; i++) {
		for (int j = 0; j < NUMOFEDGES; j++) {
			ofs << Adj[i][j] << "\t";
		}
		ofs << "\n";
	}
	ofs.close();
}

/*
minKey return the index of the minimum wwight for every cut
*/
int minKey(int key[], bool mstSet[])
{
	int min = INT_MAX, min_index = 0;

	for (int v = 0; v < NumOfCities; v++)
		if (mstSet[v] == false && key[v] < min)
			min = key[v], min_index = v;
	return min_index;
}


void print(int parent[], int n, const string city[], int graph[][NUMOFEDGES])
{
	ofstream ofs;
	int totalMinWeight = 0;
	cout << '\n';
	for (int i = NumOfCities - 1; i > 1; i--) {
		totalMinWeight += graph[i][parent[i]];
		cout << city[parent[i]] << "\t->\t" << city[i] << '\n';
	}
	cout << "\nTotal Minimum Weight = " << totalMinWeight << '\n';
}

void primMST(int graph[NUMOFEDGES][NUMOFEDGES], string V[])
{
	int parent[NumOfCities]; //to keep the MST
	int key[NumOfCities];
	bool mstSet[NumOfCities];  //Set all vertices not yet included in the MST are set to false


	/*
	Precondition: Assume all of the distances are infinitely large until they are relaxed
	set mstSet to false for all nodes as none ar part of the MST
	*/
	for (int i = 0; i < NumOfCities; i++) {
		key[i] = INT_MAX, mstSet[i] = false;
	}
	//Now we have an array with INT_MAX stored for every location

	//We include the first node in the MST as this is the starting point
	key[0] = 0;
	parent[0] = -1; //The starting point has no predecessor

	/*
	In the following statements we define the MST by inspecting each node city
	and comparing the distances of adjacent nodes.
	*/
	for (int city = 0; city < NumOfCities - 1; city++)
	{

		int temp = minKey(key, mstSet);
		// Set a temporary int to pick the current
		// by finding the minimum adjecent
		mstSet[temp] = true;


		//Look at the vertices that remain outside of the MST
		//and update the key and its parent
		for (int v = 0; v < NumOfCities; v++)

			//If mstSt[v] is false then it not
			//if graph[temp][v] is smaller then update
			if (graph[temp][v] && mstSet[v] == false && graph[temp][v] < key[v])
				parent[v] = temp, key[v] = graph[temp][v];
	}
	print(parent, NumOfCities, V, graph);
}


int main() {

	int Adj[NUMOFEDGES][NUMOFEDGES] = { 0 };
	//Build matrix 128X128
	string cities[NumOfCities];
	//Array to hold the name of the cities

	readData(Adj, cities);
	primMST(Adj, cities);

	
        cin.get(); // Prevent terminal window to close prematurely
	return 0;
}
#endif
