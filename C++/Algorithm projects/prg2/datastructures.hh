// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <map>
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

struct TownData
{
    TownID id = NO_ID;
    std::string name = NO_NAME;
    int x = NO_VALUE;
    int y = NO_VALUE;
    int tax = NO_VALUE;
    TownData* host = nullptr;
    std::map<TownID, TownData*> vassalsDATA = {};
    std::vector<TownID> vassalsID = {};
};

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: constant
    // Short rationale for estimate: uses map.size()
    unsigned int size();

    // Estimate of performance: less than n
    // Short rationale for estimate: overwrites a bunch of datastructures with {}
    void clear();

    // Estimate of performance:n + log(n)
    // Short rationale for estimate: has to find() to see if id exists
    std::string get_name(TownID id);

    // Estimate of performance: n + log(n)
    // Short rationale for estimate: has to find() to see if id exists
    std::pair<int, int> get_coordinates(TownID id);

    // Estimate of performance: n + log(n)
    // Short rationale for estimate: has to find() to see if id exists
    int get_tax(TownID id);

    // Estimate of performance: nlogn(vassal amount)
    // Short rationale for estimate: does sort()
    std::vector<TownID> get_vassals(TownID id);

    // Estimate of performance: 1
    // Short rationale for estimate: returns from memory
    std::vector<TownID> all_towns();

    // Estimate of performance: n + big constant
    // Short rationale for estimate: does find() and adds to many places
    bool add_town(TownID id, std::string const& name, int x, int y, int tax);

    // Estimate of performance: n + log(n)
    // Short rationale for estimate: has to find() to see if id exists
    bool change_town_name(TownID id, std::string const& newname);

    // Estimate of performance: nlogn
    // Short rationale for estimate: sort() is O(nlogn) since c++11
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance: nlogn
    // Short rationale for estimate: sort() is O(nlogn) since c++11
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance: n or less
    // Short rationale for estimate: iterates trough the entire thing until find hits
    std::vector<TownID> find_towns(std::string const& name);

    // Estimate of performance: less than n
    // Short rationale for estimate: compared on add town
    TownID min_distance();

    // Estimate of performance: less than n
    // Short rationale for estimate: compared on add town
    TownID max_distance();

    // Estimate of performance: constant
    // Short rationale for estimate: vector[]
    TownID nth_distance(unsigned int n);

    // Estimate of performance: n
    // Short rationale for estimate: iterates to find if ids are valid
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance: less than n
    // Short rationale for estimate: going by pointer path
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory operations

    // Estimate of performance: nlog(size + n)
    // Short rationale for estimate: bunch of insert()
    bool remove_town(TownID id);

    // Estimate of performance: nlogn
    // Short rationale for estimate: sort() is O(nlogn) since c++11
    std::vector<TownID> towns_distance_increasing_from(int x, int y);

    // Estimate of performance: n + some constant
    // Short rationale for estimate: iterates and find()
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance: n + some constant
    // Short rationale for estimate: iterates and find()
    int total_net_tax(TownID id);

private:
    // Add stuff needed for your class implementation here


    // map of all towns corresponding to their IDs
    std::map<TownID, TownData*> townmap_ = {};
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
