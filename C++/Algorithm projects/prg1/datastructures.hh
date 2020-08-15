// Datastructures.hh

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>

struct TownData
{
    std::string name;
    int x;
    int y;
};

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance: n
    // Short rationale for estimate: it simply counts the elements
    unsigned int size();

    // Estimate of performance: less than n
    // Short rationale for estimate: empties the vector, frees the memory space
    void clear();

    // Estimate of performance: less than n
    // Short rationale for estimate: returns the value of a list from memory, no complex algorithms done
    std::vector<TownData*> all_towns();

    // Estimate of performance: less than n or n
    // Short rationale for estimate: adds an element to a vector, no complex algorithms done
    TownData* add_town(std::string const& name, int x, int y);

    // Estimate of performance: nlogn or trivial
    // Short rationale for estimate: mergesort or just returns the value from memory if already sorted (flags)
    //                               also sets the flag for the other functions to skip sorting completely
    //                               as is done if sorting happens anywhere
    std::vector<TownData*> towns_alphabetically();

    // Estimate of performance: nlogn or trivial
    // Short rationale for estimate: mergesort or just returns the value from memory if already sorted (flags)
    //                               also sets the flag for the other functions to skip sorting completely
    //                               as is done if sorting happens anywhere
    std::vector<TownData*> towns_distance_increasing();

    // Estimate of performance: n
    // Short rationale for estimate: loops trought the unsorted list
    TownData* find_town(std::string const& name);

    // Estimate of performance: nlogn or trivial
    // Short rationale for estimate: mergesort or just returns the first element if sorting has been done (flags)
    TownData* min_distance();

    // Estimate of performance: nlogn or trivial
    // Short rationale for estimate: mergesort or just returns the last element if sorting has been done (flags)
    TownData* max_distance();

    // Estimate of performance: nlogn or trivial
    // Short rationale for estimate: mergesort or returns the nth element by index from an already sorted list (flags)
    TownData* nth_distance(unsigned int n);

    // Non-compulsory operations

    // Estimate of performance: n
    // Short rationale for estimate: iterates trough the vector
    void remove_town(std::string const& town_name);

    // Estimate of performance: nlogn (always) (no flags or memory storage here)
    // Short rationale for estimate: mergesorting by distance
    std::vector<TownData*> towns_distance_increasing_from(int x, int y);

private:
    // Add stuff needed for your class implementation here


    // the rationale here is that town lists are sorted once and stored
    // when a new town is added, it is stored into its place in both lists
    // when lists are needed, they can just be called rather than sorted from the random order
    // on every call

    // we are using both insertion and mergesort, merge if the amount of unordered elements exceeds 20

    // list of added towns in a random order
    std::vector<TownData*> TownList_;
    // list of towns in alphapetical order
    // flag tells if the list has been sorted after the last add_town
    bool ALPHFLAG_ = false;
    std::vector <TownData*> AlphapeticalTownList_;
    // list of towns by distance
    // flag tells if the list has been sorted after the last add_town
    bool DISTFLAG_ = false;
    std::vector <TownData*> DistanceTownList_;

    // amount of added towns since last mergesort
    // turned into corresponding index
        // used to determine if a faster sorting option is viable (insertion sort)
    int ALPHUnsortedIndex_ = 1;
    int DISTUnsortedIndex_ = 1;

    // min and maxdist are updated when add_town is called
    TownData* MinDist_ = nullptr;
    TownData* MaxDist_ = nullptr;


};

#endif // DATASTRUCTURES_HH
