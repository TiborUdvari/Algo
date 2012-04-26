/********************************************************************************************
 *
 * 	 	 	 	     Tibor Udvari
 *                             Haute Ecole Arc Ingénierie
 * 	 	 	       Année académique 2011-2012
 * 	 	 	 	      25 avr. 2012
 *
 * 	 	 	       Cours d'algorithmes et SDD
 *                                      Graphes
 *
 *   Description:
 *   Implémentation
 ********************************************************************************************/
#include <iostream>
#include <string>
#include <list>

using namespace std;

/******************************************************************************************
 *
 * 	 	 	 	 Globals / Typedefs / Constants
 *
 ******************************************************************************************/
const int maxVertexes = 50;

/**
 * Typedef for non directed, non weighted graph
 */
typedef struct Vertex
    {
    char label;
    Vertex *next;
    } TYPEVERTEX;

Vertex *vertexes[maxVertexes];

/******************************************************************************************
 *
 * 	 	 	 	 Function prototypes
 *
 ******************************************************************************************/

/******************************************************************************
 * Fonction permettant d'introduire des sommets et des arcs sous forme
 * de liste d'adjacence
 ******************************************************************************/
void adjacencyList(int &vertexNumber, int &arcNumber);
void printAdjacencyList(int vertexNumber);

void parcoursProfondeurRecursif(int vertexNumber);
void visiterSommetProfondeurRecursif(Vertex* vertex, bool* visited);
/*------------------------------------------------------------------*\
|*			  Helper Functions		            *|
\*------------------------------------------------------------------*/
int map(char label, int vertexNumber);
void buildDefaultTestGraphe(int &vertexNumber, int &arcNumber);

/******************************************************************************************
 *
 * 	 	 	 	 Beginning of the program
 *
 ******************************************************************************************/
int main()
    {
    int vertexNumber, arcNumber;

    //adjacencyList(vertexNumber, arcNumber);
    //buildDefaultTestGraphe(vertexNumber, arcNumber);
    //printAdjacencyList(vertexNumber);

    parcoursProfondeurRecursif(10);

    //	ParcoursProfondeurRecursifLA(NombreSommets);
    return 0;
    }

/******************************************************************************************
 *
 * 	 	 	 	 Function declarations
 *
 ******************************************************************************************/

void adjacencyList(int &vertexNumber, int &arcNumber)
    {
    arcNumber = 0;
    do
	{
	cout << "How many vertexes would you like ? ( < 26 )";
	cin >> vertexNumber;
	}
    while (vertexNumber < 2 || vertexNumber > 26);
    char firstVertexLabel = 'A';
    char lastVertexLabel = 'A' + vertexNumber - 1;
    for (char i = firstVertexLabel; i <= lastVertexLabel; i++)
	{
	Vertex* vertex = new Vertex();
	vertex->next = NULL;
	vertex->label = i;
	cout << map(i, vertexNumber);
	vertexes[map(i, vertexNumber)] = vertex;
	}
    cout << "Created vertexes from " << firstVertexLabel << " to " << lastVertexLabel << "." << endl;
    cout << "Input arcs in the following fashion : X X, type end to finish";
    string connection = "";
    char vertex1Label;
    char vertex2Label;
    cin.ignore(1000, '\n');
    while (true)
	{
	getline(cin, connection);
	if (connection == "end")
	    {
	    break;
	    }

	cout << "This is the connection :" << connection << endl;
	vertex1Label = connection[0];
	vertex2Label = connection[2];
	//TODO refactoring here
	Vertex* newVertex1 = new Vertex();
	newVertex1->next = NULL;
	newVertex1->label = vertex2Label;
	Vertex* vertexToAdd1 = vertexes[map(vertex1Label, vertexNumber)];
	while (vertexToAdd1->next != NULL)
	    {
	    vertexToAdd1 = vertexToAdd1->next;
	    }
	vertexToAdd1->next = newVertex1;

	Vertex* newVertex2 = new Vertex();
	newVertex2->next = NULL;
	newVertex2->label = vertex1Label;
	Vertex* vertexToAdd2 = vertexes[map(vertex2Label, vertexNumber)];
	while (vertexToAdd2->next != NULL)
	    {
	    vertexToAdd2 = vertexToAdd2->next;
	    }
	vertexToAdd2->next = newVertex2;
	arcNumber++;
	}

    }

void printAdjacencyList(int vertexNumber)
    {
    for (int i = 0; i < vertexNumber; ++i)
	{
	cout << vertexes[i]->label << " : ";
	Vertex* placeholder = vertexes[i];
	while (placeholder->next != NULL)
	    {
	    placeholder = placeholder->next;
	    cout << placeholder->label << " -- ";
	    }
	cout << endl;
	}
    }

int map(char label, int vertexNumber)
    {
    return label - 'A';
    }

void addArc(char labelToAddTo, char labelToAdd, int vertexNumber)
    {
    cout << "Attemtimg connection " << labelToAdd << " - " << labelToAddTo << endl;
    Vertex* newVertex = new Vertex();
    newVertex->next = NULL;
    newVertex->label = labelToAdd;
    Vertex* placeFinder = vertexes[map(labelToAddTo, vertexNumber)];
    while (placeFinder->next != NULL)
	{
	cout << "Placefinder is at " << placeFinder->label << endl;
	placeFinder = placeFinder->next;
	cout << "Moving placeFinder" << endl;
	}
    cout << "Adding newVertex to " << placeFinder->label << endl;
    placeFinder->next = newVertex;
    }

void buildDefaultTestGraphe(int& vertexNumber, int& arcNumber)
    {
    arcNumber = 0;
    arcNumber = 11;
    vertexNumber = 11;
    char firstVertexLabel = 'A';
    char lastVertexLabel = 'A' + vertexNumber - 1;
    for (char i = firstVertexLabel; i <= lastVertexLabel; i++)
	{
	Vertex* vertex = new Vertex();
	vertex->next = NULL;
	vertex->label = i;
	cout << map(i, vertexNumber);
	vertexes[map(i, vertexNumber)] = vertex;
	}
    cout << "Created vertexes from " << firstVertexLabel << " to " << lastVertexLabel << "." << endl;

    addArc('A', 'B', vertexNumber);
    addArc('A', 'F', vertexNumber);
    addArc('A', 'G', vertexNumber);
    addArc('A', 'C', vertexNumber);
    addArc('B', 'A', vertexNumber);
    addArc('C', 'A', vertexNumber);
    addArc('D', 'E', vertexNumber);
    addArc('D', 'F', vertexNumber);
    addArc('E', 'G', vertexNumber);
    addArc('E', 'F', vertexNumber);
    addArc('E', 'D', vertexNumber);
    addArc('F', 'A', vertexNumber);
    addArc('F', 'D', vertexNumber);
    addArc('F', 'E', vertexNumber);
    addArc('G', 'A', vertexNumber);
    addArc('G', 'E', vertexNumber);
    addArc('I', 'J', vertexNumber);
    addArc('I', 'K', vertexNumber);
    addArc('J', 'K', vertexNumber);
    addArc('J', 'I', vertexNumber);
    addArc('K', 'I', vertexNumber);
    addArc('K', 'J', vertexNumber);
    }

void parcoursProfondeurRecursif(int vertexNumber)
    {
    bool visited[vertexNumber];
    for (int i = 0; i < vertexNumber; ++i)
	{
	visited[i] = false;
	}

    for (int recursionTarget = 0; recursionTarget < vertexNumber; ++recursionTarget)
	{
	if(! visited[recursionTarget])
	    {
	    visiterSommetProfondeurRecursif(vertexes[recursionTarget], &visited[recursionTarget]);
	    }
	}

    }

void visiterSommetProfondeurRecursif(Vertex* vertex, bool* visited)
    {
    if(vertex-> next == NULL)
	{

	}
    visited = true;
    cout << vertex->label << " ";
    visiterSommetProfondeurRecursif(vertex->next, visited);




    }


