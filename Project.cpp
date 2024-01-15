#include <iostream>
using namespace std;
class Passenger     //Class representing passenger with city and ticket information
{
public:
    int city;
    int ticket;
    Passenger* next;
    Passenger()     //Default constructor
    {
        city = 0;
        ticket = 0;
        next = NULL;
    }
    Passenger(int t, int c)     //Parametrized constructor
    {
        city = c;
        ticket = t;
        next = NULL;
    }
};
class Queue     //Class representing a queue of passengers
{
private:
    Passenger** elements;
    int front;
    int rear;
    int capacity;
public:
    Queue(int size)     //Constructor
    {
        capacity = size;
        elements = new Passenger * [size];
        front = -1;
        rear = -1;
    }
    ~Queue()        //Destructor
    {
        while (!isEmpty())
        {
            dequeue();
        }
        delete[] elements;
    }
    bool isEmpty()      //Check if the queue is empty
    {
        return front == -1;
    }
    bool isFull()       //Check if the queue is full
    {
        return (rear + 1) % capacity == front;
    }
    void enqueue(Passenger& ps)     //Enquque the passenger in to the queue
    {
        if (isFull())
        {
            cout << "Queue is full" << endl;
            return;
        }
        if (isEmpty())
        {
            front = rear = 0;
        }
        else
        {
            rear = (rear + 1) % capacity;
        }
        elements[rear] = new Passenger(ps.ticket, ps.city);
    }
    void dequeue()      //Dequeue the passenger from the queue
    {
        if (isEmpty())
        {
            cout << "Queue is empty\n";
            return;
        }
        delete elements[front];
        if (front == rear)
        {
            front = rear = -1;
        }
        else
        {
            front = (front + 1) % capacity;
        }
    }
    Passenger* peekFront()      //Peek at the front passenger
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return NULL;
        }
        return elements[front];
    }
    int size()      //Get the current size of queue
    {
        if (isEmpty())
        {
            return 0;
        }
        if (rear >= front)
        {
            return rear - front + 1;
        }
        else
        {
            return capacity - front + rear + 1;
        }
    }
};
class Graph     //Class representing a graph with adjacency matrix
{
private:
    int** adjacencyList;
    int numVertices;
public:
    Graph(int numVertices)      //Constructor
    {
        this->numVertices = numVertices;
        adjacencyList = new int* [numVertices];
        for (int i = 0; i < numVertices; ++i)
        {
            adjacencyList[i] = new int[numVertices];
        }
        for (int i = 0; i < numVertices; i++)
        {
            for (int j = 0; j < numVertices; j++)
            {
                adjacencyList[i][j] = 0;
            }
        }
    }
    ~Graph()        //Destructor
    {
        for (int i = 0; i < numVertices; ++i)
        {
            delete[] adjacencyList[i];
        }
        delete[] adjacencyList;
    }
    void addEdge(int v, int w)      //Add edge between two vertices
    {
        adjacencyList[v][w] = 1;
    }
    void printGraph()       //Print the graph adjacency matrix
    {
        for (int i = 0; i < numVertices; ++i)
        {
            cout << "Vertex " << i << " is connected to: ";
            for (int j = 0; j < numVertices; ++j)
            {
                if (adjacencyList[i][j] == 1)
                {
                    cout << j << " ";
                }
            }
            cout << endl;
        }
    }
    int countDays(int startCity, int destinationCity)       // Find the minimum number of days required to travel from startCity to destinationCity
    {
        Queue q(numVertices); // Create a queue to perform BFS
        bool* visited = new bool[numVertices]; // Array to track visited cities
        for (int i = 0; i < numVertices; i++)
        {
            visited[i] = false;
        }
        q.enqueue(*new Passenger(0, startCity)); // Enqueue the starting city with day 0
        visited[startCity] = true; // Mark the starting city as visited
        int days = 0; // Initialize the days counter
        int citiesCovered = 0; // Initialize the count of cities covered in a day
        while (!q.isEmpty())        // Perform BFS
        {
            int citiesInCurrentDay = q.size(); // Get the number of cities to be processed on the current day
            for (int i = 0; i < citiesInCurrentDay; ++i)        // Process each city in the current day
            {
                int currentCity = q.peekFront()->city; // Get the current city from the front of the queue
                q.dequeue(); // Dequeue the current city
                if (currentCity == destinationCity)
                {
                    delete[] visited;
                    return days; // If the destination is reached, return the number of days
                }
                for (int j = 0; j < numVertices; ++j)       // Explore adjacent cities
                {
                    if ((adjacencyList[currentCity][j]) == 1 && (!visited[j]))
                    {
                        q.enqueue(*new Passenger(j, j)); // Enqueue the adjacent city
                        visited[j] = true; // Mark the adjacent city as visited
                        if (j != currentCity + 1 || citiesCovered == 6)     // Check if an aerial route or 6 cities have been covered
                        {
                            days++; // Move to the next day
                            citiesCovered = 0; // Reset the count of cities covered for the new day
                        }
                        else
                        {
                            citiesCovered++; // Increment the count of cities covered
                        }
                    }
                }
            }
        }
        delete[] visited;
        return -1; // If the destination is not reachable
    }
};
int main()
{
    int cases;
    cout << "Enter the number of cases: ";
    cin >> cases;
    for (int i = 0; i < cases; i++)     //Loop for each test case
    {
        int cities;
        cout << "Enter the number of cities: ";
        cin >> cities;
        Graph g(cities);        //Creating graph for total no of cities
        for (int j = 0; j < cities - 1; j++)
        {
            g.addEdge(j, j + 1);        //Adding edge for each city
        }
        int aerialRoutes;
        cout << "Enter the number of aerial routes: ";
        cin >> aerialRoutes;
        for (int j = 0; j < aerialRoutes; j++)      //Loop for each aerial route
        {
            int boardingCity, landingCity;
            cout << "Enter boarding city: ";
            cin >> boardingCity;
            cout << "Enter landing city: ";
            cin >> landingCity;
            g.addEdge(boardingCity, landingCity);       //Add a new edge for aerial route
        }
        g.printGraph();     //Printing the graph
        int minDays = g.countDays(0, cities - 1);       //Calculating minimum days to travel from city 0 to city N-1
        if (minDays != -1)      //Will print when the destination is reachable
        {
            cout << "Minimum days required: " << minDays << endl;
        }
        else        //Else it will print not reachable message
        {
            cout << "Destination is not reachable." << endl;
        }
    }
    return 0;
}