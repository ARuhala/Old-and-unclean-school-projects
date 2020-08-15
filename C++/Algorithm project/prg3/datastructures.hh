// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <unordered_map>
#include <utility>
#include <limits>

// Type for town IDs
using TownID = std::string;

// Return value for cases where required town was not found
TownID const NO_ID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
std::string const NO_NAME = "-- unknown --";




// Type for a coordinate (x, y)
using Coord = std::pair<int, int>;

// Return value for cases where coordinates were not found
Coord const NO_COORD{NO_VALUE, NO_VALUE};

// Type for distance
using Dist = int;

// Return value for cases where distance is unknown
Dist const NO_DIST = NO_VALUE;


struct Road;

// OUR OWN TOWN STRUCT FROM PRG2
struct TownData
{
    TownID id = NO_ID;
    std::string name = NO_NAME;
    int x = NO_VALUE;
    int y = NO_VALUE;
    int tax = NO_VALUE;
    TownData* host = nullptr;
    std::unordered_map<TownID, TownData*> vassalsDATA = {};
    std::vector<TownID> vassalsID = {};

    // prg3 stuff
    // a roadvector to the neighbouring towns
    std::vector<Road> neighbours = {};
    // BFS
    bool flag = false;
    TownData* lastcomein = nullptr;
    Dist distance = INT8_MAX;


};

// OUR OWN ROAD STRUCT
struct Road
{
    TownData* endtown = nullptr;
};

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: constant
    // Short rationale for estimate: uses .size()
    unsigned int size();

    // Estimate of performance: O(n)
    // Short rationale for estimate: overwrites a bunch of datastructures with {}
    void clear();

    // Estimate of performance: O(n)
    // Short rationale for estimate: has to find() to see if id exists
    std::string get_name(TownID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: has to find() to see if id exists
    Coord get_coordinates(TownID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: has to find() to see if id exists
    int get_tax(TownID id);

    // Estimate of performance: O(nlogn(vassal amount))
    // Short rationale for estimate: does sort()
    std::vector<TownID> get_vassals(TownID id);

    // Estimate of performance: O(1)
    // Short rationale for estimate: returns from memory
    std::vector<TownID> all_towns();

    // Estimate of performance: O(n)
    // Short rationale for estimate: does find() and adds to many places
    bool add_town(TownID id, std::string const& name, int x, int y, int tax);

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: has to find() to see if id exists,
    // worst case also sorts
    bool change_town_name(TownID id, std::string const& newname);

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: may have to sort
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance: O(nlog(n))
    // Short rationale for estimate: may have to sort
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance: O(n)
    // Short rationale for estimate: iterates trough the entire thing until find hits
    std::vector<TownID> find_towns(std::string const& name);

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: may have to sort
    TownID min_distance();

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: may have to sort
    TownID max_distance();

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: may have to sort
    TownID nth_distance(unsigned int n);

    // Estimate of performance: O(n)
    // Short rationale for estimate: iterates to find if ids are valid
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance: O(n)
    // Short rationale for estimate: pointer path
    std::vector<TownID> taxer_path(TownID id);

    // Estimate of performance: O(n²)
    // Short rationale for estimate: worst case all towns are eachothers neighbours
    std::vector<std::pair<TownID, TownID>> all_roads();

    // Estimate of performance: O(n)
    // Short rationale for estimate: iterates trough neighbours
    std::vector<TownID> get_roads_from(TownID id);

    // Estimate of performance: O(n)
    // Short rationale for estimate: checks if ids are valid
    bool add_road(TownID town1, TownID town2);

    // Estimate of performance: O(n)
    // Short rationale for estimate: iterates to check ids, many find ifs
    bool remove_road(TownID town1, TownID town2);

    // Estimate of performance: O(n)
    // Short rationale for estimate: overwrites a certain attribute of every town
    void clear_roads();

    // Estimate of performance: O(vertixes + edges)
    // Short rationale for estimate: BFS
    std::vector<TownID> any_route(TownID fromid, TownID toid);

    // Non-compulsory operations

    // Estimate of performance: O (nlog(size+n)
    // Short rationale for estimate: alot of inserts, findifs, erase,removes
    bool remove_town(TownID id);

    // Estimate of performance: O(nlogn)
    // Short rationale for estimate: sort()
    std::vector<TownID> towns_distance_increasing_from(int x, int y);

    // Estimate of performance: very bad, O(n + every towns vassal host list)
    // Short rationale for estimate: iterates trough everything and every towns lists
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance: w(n)
    // Short rationale for estimate: checks every town if it owns ID money
    int total_net_tax(TownID id);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> least_towns_route(TownID fromid, TownID toid);

    // Estimate of performance: O(vertixes + edges)
    // Short rationale for estimate: Djikstra
    std::vector<TownID> shortest_route(TownID fromid, TownID toid);

    // Estimate of performance:
    // Short rationale for estimate:
    std::vector<TownID> road_cycle_route(TownID startid);

    // Estimate of performance:
    // Short rationale for estimate:
    Dist trim_road_network();

private:
    // Add stuff needed for your class implementation here

    // map of all towns corresponding to their IDs
    std::unordered_map<TownID, TownData*> townmap_ = {};
    // vector of town ids
    std::vector<TownID> townidvector_ = {};
    // vector of town ids in alphapetical order
    // and the corresponding sortflag
    bool alphaflag_ = false;
    std::vector<TownData*> alphasortedvectorDATA_ = {};
    std::vector<TownID> alphasortedvectorID_ = {};

    // vector of town ids in distance order
    bool distflag_ = false;
    std::vector<TownData*> distsortedvectorDATA_ = {};
    std::vector<TownID> distsortedvectorID_ = {};

    // vector of town ids in distance order related to a given X and Y
    std::vector<TownData*> distCOMPLEXsortedvectorDATA_ = {};
    std::vector<TownID> distCOMPLEXsortedvectorID_ = {};

    // min and max distance pointers
    TownData* mindist_ = nullptr;
    TownData* maxdist_ = nullptr;





};

#endif // DATASTRUCTURES_HH
