#include <iostream>
#include <vector>
#include <algorithm> // For std::next_permutation and std::iota
#include <numeric>   // For std::iota





void PrintUnoptimizedPath(const std::vector<int>& array_city, const double& distance, const int& counter);





// Route class that will store information about a particular route
// Stores the sequence of cities in this route
// Stores the total distance of this route
class Route 
{
private:

public:

    std::vector<int> cities; 
    double totalDistance;    

    Route(std::vector<int> cities, double distance) : cities(cities), totalDistance(distance) {}
};





// TSPSolver class that contains methods to solve the Traveling Salesman Problem
class TSPSolver 
{
private:

    // 2D vector to store the distance between any two cities, I love using STL...
    std::vector<std::vector<double>> distanceMatrix; 

public:

    TSPSolver(const std::vector<std::vector<double>>& matrix) : distanceMatrix(matrix) 
    {}


    // Function to calculate the total distance of a given route
    double calculateRouteDistance(const std::vector<int>& route) 
    {
        double distance = 0;

        // Loop through each city in the route to calculate the total distance
        for (size_t i = 0; i < route.size() - 1; i++) 
        {
            // Add distance from the current city to the next
            distance += distanceMatrix [ route[i] ] [ route [i+1] ]; 
        }

        // Add distance from the last city back to the first city to complete the loop
        distance += distanceMatrix [route.back()] [route.front()];
        return distance;
    }


    // Function to find the shortest route among all possible permutations of cities
    Route solve() 
    {
        std::vector<int> cities(distanceMatrix.size()); 

        // Fill the vector with consecutive numbers -> 0 : Toronto, 1 : Missi, 2 : Markham, 3 : Brampton, 4 : Etobicoke
        std::iota(cities.begin(), cities.end(), 0); 

        // min <- infinite
        double minDistance = std::numeric_limits<double>::max();

        // KB for shortest path
        std::vector<int> bestRoute; 

        // counter
        size_t counter = 0;

        // Lexicographical permutation
        do 
        {
            // distance of the frontier node
            double currentDistance = calculateRouteDistance(cities); 

            PrintUnoptimizedPath(cities, currentDistance, counter + 1);

            // compares(frontier, min)
            if (currentDistance < minDistance) 
            { 
                minDistance = currentDistance; 
                bestRoute = cities; 
            }

            counter++;
        } 
        // Get the next permutation of cities
        while (std::next_permutation(cities.begin(), cities.end())); 

        // pushes the start node onto KB such that it completes the whole cycle
        bestRoute.push_back(0);

        // Return the best route found along with its total distance
        return Route(bestRoute, minDistance);
    }
};





// this is only an example function to test out STL library's std::next_permutation() function...
void LexicographicalOrder(void)
{
    std::cout << "\nExample for next_permutation() STL function...\n";
    std::vector<int> vec = { 1, 2, 3, 4 };
    int counter = 0;
    do
    {
        std::cout << "current iteration -> " << counter << std::endl;

        for (int i : vec)
        {
            std::cout << i << " ";
        }

        puts(""); puts("");
        counter++;
    } 
    while (std::next_permutation(vec.begin(), vec.end()));
}




void PrintShortestPath(const Route& result)
{
    std::cout << "The shortest route distance is -> " << result.totalDistance << std::endl;

    std::cout << "The route is -> START -> ";

    for (int city : result.cities)
    {
        switch (city)
        {
        case 0:
            std::cout << "Toronto ";
            break;

        case 1:
            std::cout << "Mississauga ";
            break;

        case 2:
            std::cout << "Markham ";
            break;

        case 3:
            std::cout << "Brampton ";
            break;

        case 4:
            std::cout << "Etobicoke ";
            break;

        default:
            std::cout << "Error retrieving city info... ";
            break;
        }
        std::cout << "-> ";
    }
    std::cout << "FINISH";
}





void PrintUnoptimizedPath(const std::vector<int> &array_city, const double &distance, const int &counter)
{
    std::cout << "This is iteration #" << counter << std::endl;

    std::cout << "The current distance of route is -> " << distance << std::endl;

    std::cout << "The route is -> START -> ";

    for (int itr : array_city)
    {
        switch (itr)
        {
        case 0:
            std::cout << "Toronto ";
            break;

        case 1:
            std::cout << "Mississauga ";
            break;

        case 2:
            std::cout << "Markham ";
            break;

        case 3:
            std::cout << "Brampton ";
            break;

        case 4:
            std::cout << "Etobicoke ";
            break;

        default:
            std::cout << "Error retrieving city info... ";
            break;
        }
        std::cout << "-> ";
    }
    std::cout << "FINISH";
    puts("");
    puts("");
}





int main() 
{
    // a tester for debugging...
    // LexicographicalOrder();
    
    std::vector<std::vector<double>> distanceMatrix = 
    {
        {0, 25, 30, 20, 35},
        {25, 0, 40, 15, 30},
        {30, 40, 0, 45, 20},
        {20, 15, 45, 0, 40},
        {35, 30, 20, 40, 0}
    };

    TSPSolver solver(distanceMatrix); 
    Route shortestRoute = solver.solve(); 

    // Print the total distance and the sequence of cities in the shortest route
    /*
    std::cout << "Shortest route distance: " << shortestRoute.totalDistance << std::endl;
    std::cout << "Route: ";
    for (int city : shortestRoute.cities) 
    {
        std::cout << city << " ";
    }
    */

    puts(""); puts(""); puts("");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n\n");
    PrintShortestPath(shortestRoute);
    printf("\n\n+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    puts(""); puts(""); puts("");

    return 0;
}
