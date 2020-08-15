// Datastructures.cc

#include "datastructures.hh"

#include <random>
#include <algorithm>
#include <cmath>
#include <set>
#include <queue>


std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}


Datastructures::Datastructures()
{
 // Replace with actual implementation
}

Datastructures::~Datastructures()
{
 // Replace with actual implementation
}


bool DISTCompareSmaller(TownData*& Left, TownData*& Right) {
    return ((abs(Left->x)+abs(Left->y)) < (abs(Right->x)+abs(Right->y)));
}

bool ALPHCompareSmaller(TownData*& Left, TownData*& Right) {
    return Left->name < Right->name;
}




unsigned int Datastructures::size()
{
    return townmap_.size();
}

void Datastructures::clear()
{
    townmap_ = {};
    townidvector_ = {};
    alphaflag_ = false;
    alphasortedvectorDATA_ = {};
    alphasortedvectorID_ = {};
    distflag_ = false;
    distsortedvectorDATA_ = {};
    distsortedvectorID_ = {};
    distCOMPLEXsortedvectorDATA_ = {};
    distCOMPLEXsortedvectorID_ = {};
    mindist_ = nullptr;
    maxdist_ = nullptr;
}

std::string Datastructures::get_name(TownID id)
{
    // if town already exists, returns the name property, else NO_NAME;
    if ( townmap_.find(id) == townmap_.end() ) {
        // not found
        return NO_NAME;
    }
    else {
        // found
        return townmap_[id]->name;
    }
}

Coord Datastructures::get_coordinates(TownID id)
{
    // if town already exists, returns the x and y properties, else NO_VALUE, NO_VALUE
    if ( townmap_.find(id) == townmap_.end() ) {
        // not found
        return {NO_VALUE, NO_VALUE};
    }
    else {
        // found
        return {townmap_[id]->x, townmap_[id]->y};
    }
}

int Datastructures::get_tax(TownID id)
{
    // if town already exists, returns the tax property, else NO_VALUE
    if ( townmap_.find(id) == townmap_.end() ) {
        // not found
        return NO_VALUE;
    }
    else {
        // found
        return townmap_[id]->tax;
    }
}

std::vector<TownID> Datastructures::get_vassals(TownID id)
{
    // if town already exists, returns the vassals property, else {NO_ID};
    if ( townmap_.find(id) == townmap_.end() ) {
        // not found
        return {NO_ID};
    }
    else {
        // found
        sort(townmap_[id]->vassalsID.begin(), townmap_[id]->vassalsID.end());
        return townmap_[id]->vassalsID;
    }
}

std::vector<TownID> Datastructures::all_towns()
{
    return townidvector_;
}

bool Datastructures::add_town(TownID id, const std::string& name, int x, int y, int tax)
{
    // if town already exists, returns false, else true
    if ( townmap_.find(id) == townmap_.end() ) {
        // not found

        TownData* temptown = new TownData;
        temptown->id = id;
        temptown->name = name;
        temptown->x = x;
        temptown->y = y;
        temptown->tax = tax;

        townmap_[id] = temptown;
        townidvector_.push_back(id);
        alphasortedvectorDATA_.push_back(temptown);
        distsortedvectorDATA_.push_back(temptown);
        distCOMPLEXsortedvectorDATA_.push_back(temptown);

        alphaflag_ = false;
        distflag_ = false;

        // updating min and max dist
        if (mindist_ == nullptr or DISTCompareSmaller(temptown, mindist_)){
            mindist_ = temptown;
        }
        if (maxdist_ == nullptr or not(DISTCompareSmaller(temptown, maxdist_))){
            maxdist_ = temptown;
        }

        return true;
    }
    else {
        // found
        return false;
    }
}

bool Datastructures::change_town_name(TownID id, const std::string& newname)
{
    // if town already exists, changes name value, returns true, else false
    if ( townmap_.find(id) == townmap_.end() ) {
        // not found
        return false;
    }
    else {
        // found
        alphaflag_ = false;
        townmap_[id]->name = newname;
        return true;
    }
}

bool Datastructures::remove_town(TownID id)
{
    // if town already exists, delete it from all datastructures, returns true, else false
    // if town has vassals, vassals are moved to become removedtowns host's vassals
    // if removed town is min or max dist, this has to be updated

    if ( townmap_.find(id) == townmap_.end() ) {
        // not found
        return false;
    }
    else {
        // found

        // removing the pointers from memory vectors
        std::vector<TownData*>::iterator removaliter = std::find_if(alphasortedvectorDATA_.begin(), alphasortedvectorDATA_.end(),
                                                                    [&](TownData* Town) {return Town->id == id;});
        alphasortedvectorDATA_.erase(removaliter);

        removaliter = std::find_if(distsortedvectorDATA_.begin(), distsortedvectorDATA_.end(),
                                                                    [&](TownData* Town) {return Town->id == id;});
        distsortedvectorDATA_.erase(removaliter);

        removaliter = std::find_if(distCOMPLEXsortedvectorDATA_.begin(), distCOMPLEXsortedvectorDATA_.end(),
                                                                    [&](TownData* Town) {return Town->id == id;});
        distCOMPLEXsortedvectorDATA_.erase(removaliter);


        // moving vassal data
        // removing id from hosts vassal data
        if (townmap_[id]->host != nullptr) {
            townmap_[id]->host->vassalsDATA.erase(id);
            townmap_[id]->host->vassalsID.erase(std::remove(townmap_[id]->host->vassalsID.begin(),
                                                      townmap_[id]->host->vassalsID.end(), id), townmap_[id]->host->vassalsID.end() );
            // adding this ids vassals to hosts data
            townmap_[id]->host->vassalsDATA.insert(townmap_[id]->vassalsDATA.begin(), townmap_[id]->vassalsDATA.end());
            townmap_[id]->host->vassalsID.insert(townmap_[id]->host->vassalsID.end(),
                                                   townmap_[id]->vassalsID.begin(), townmap_[id]->vassalsID.end());
        }

        // removing id from vassals host attribute
        for (auto it = townmap_[id]->vassalsDATA.begin(); it != townmap_[id]->vassalsDATA.end(); it++ ) {
            ((*it).second)->host = townmap_[id]->host;
        }

        // updating max- min dist
        if (maxdist_ == townmap_[id]) {
            if (distflag_ == false) {
                std::sort(distsortedvectorDATA_.begin(), distsortedvectorDATA_.end(),DISTCompareSmaller);

                distsortedvectorID_ = {};
                for (unsigned int i = 0; i < distsortedvectorDATA_.size(); i++ ) {
                    distsortedvectorID_.push_back(distsortedvectorDATA_[i]->id);
                }
                distflag_ = true;
            }
            maxdist_ = distsortedvectorDATA_.back();
        }
        if (mindist_ == townmap_[id]) {
            if (distflag_ == false) {
                std::sort(distsortedvectorDATA_.begin(), distsortedvectorDATA_.end(),DISTCompareSmaller);

                distsortedvectorID_ = {};
                for (unsigned int i = 0; i < distsortedvectorDATA_.size(); i++ ) {
                    distsortedvectorID_.push_back(distsortedvectorDATA_[i]->id);
                }
                distflag_ = true;
            }
            mindist_ = distsortedvectorDATA_.front();
        }

        // removing from the main datastructure
        townidvector_.erase(std::remove(townidvector_.begin(), townidvector_.end(), id), townidvector_.end() );
        townmap_.erase(id);
        alphaflag_ = false;
        distflag_ = false;

        return true;
    }
}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    if (alphaflag_ == false) {
        std::sort(alphasortedvectorDATA_.begin(), alphasortedvectorDATA_.end(),ALPHCompareSmaller);

        alphasortedvectorID_ = {};
        for (unsigned int i = 0; i < alphasortedvectorDATA_.size(); i++ ) {
            alphasortedvectorID_.push_back(alphasortedvectorDATA_[i]->id);
        }
        alphaflag_ = true;
    }
    return alphasortedvectorID_;

}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    if (distflag_ == false) {
        std::sort(distsortedvectorDATA_.begin(), distsortedvectorDATA_.end(),DISTCompareSmaller);

        distsortedvectorID_ = {};
        for (unsigned int i = 0; i < distsortedvectorDATA_.size(); i++ ) {
            distsortedvectorID_.push_back(distsortedvectorDATA_[i]->id);
        }
        distflag_ = true;
    }
    return distsortedvectorID_;

}

std::vector<TownID> Datastructures::find_towns(std::string const& name)
{
    // returns all towns with the name "name"
    // first we find an iterator to the first instance of name
    // then we do iter++ until we find a town that has a different name
    // on each same named town we add them to the return list
    auto iter = find_if(alphasortedvectorDATA_.begin(), alphasortedvectorDATA_.end(),
                        [&name](TownData* & m) -> bool { return m->name == name; });

    std::vector<TownID> returnlist = {};
    if (iter == alphasortedvectorDATA_.end()) {
        return returnlist;
    }

    while((*iter)->name == name) {
        returnlist.push_back((*iter)->id);
        iter++;
        if (iter == alphasortedvectorDATA_.end()) {
            break;
        }
    }

    std::sort(returnlist.begin(),returnlist.end());
    return returnlist;
}

TownID Datastructures::min_distance()
{
    if(mindist_ == nullptr){
        return NO_ID;
    }
    if ((distflag_ == false) and (mindist_ = distsortedvectorDATA_.front())) {
        std::sort(distsortedvectorDATA_.begin(), distsortedvectorDATA_.end(),DISTCompareSmaller);

        distsortedvectorID_ = {};
        for (unsigned int i = 0; i < distsortedvectorDATA_.size(); i++ ) {
            distsortedvectorID_.push_back(distsortedvectorDATA_[i]->id);
        }
        distflag_ = true;
        mindist_ = distsortedvectorDATA_.front();
    }

    return mindist_->id;
}

TownID Datastructures::max_distance()
{
    if(maxdist_ == nullptr){
        return NO_ID;
    }
    if ((distflag_ == false) and (maxdist_ != distsortedvectorDATA_.back())) {
        std::sort(distsortedvectorDATA_.begin(), distsortedvectorDATA_.end(),DISTCompareSmaller);

        distsortedvectorID_ = {};
        for (unsigned int i = 0; i < distsortedvectorDATA_.size(); i++ ) {
            distsortedvectorID_.push_back(distsortedvectorDATA_[i]->id);
        }
        distflag_ = true;
        maxdist_ = distsortedvectorDATA_.back();
    }

    return maxdist_->id;
}

TownID Datastructures::nth_distance(unsigned int n)
{
    if (n == 0 or n > distsortedvectorID_.size()) {
        return NO_ID;
    }
    if (distflag_ == false) {
        std::sort(distsortedvectorDATA_.begin(), distsortedvectorDATA_.end(),DISTCompareSmaller);

        distsortedvectorID_ = {};
        for (unsigned int i = 0; i < distsortedvectorDATA_.size(); i++ ) {
            distsortedvectorID_.push_back(distsortedvectorDATA_[i]->id);
        }
        distflag_ = true;
    }

    return distsortedvectorID_[n-1];
}

std::vector<TownID> Datastructures::towns_distance_increasing_from(int x, int y)
{
    std::sort(distCOMPLEXsortedvectorDATA_.begin(),distCOMPLEXsortedvectorDATA_.end(),
              [&x,&y](TownData* & Left, TownData* & Right) -> bool
    {
        return ((abs(Left->x - x)+abs(Left->y - y)) < (abs(Right->x - x)+abs(Right->y - y)));
    });

    for (unsigned int i = 0; i < distCOMPLEXsortedvectorDATA_.size(); i++ ) {
        distCOMPLEXsortedvectorID_.push_back(distCOMPLEXsortedvectorDATA_[i]->id);
    }
    return distCOMPLEXsortedvectorID_;
}

bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{
    if(townmap_.find(vassalid) == townmap_.end() or townmap_.find(masterid) == townmap_.end()
            or townmap_[vassalid]->host != nullptr) {
        return false;
    }
    townmap_[vassalid]->host = townmap_[masterid];
    townmap_[masterid]->vassalsDATA[vassalid] = townmap_[vassalid];
    townmap_[masterid]->vassalsID.push_back(vassalid);
    return true;
}

std::vector<TownID> Datastructures::taxer_path(TownID id)
{
    if(townmap_.find(id) == townmap_.end()){
        return {};
    }
    // returns a vector of hosts so that the return vector is formatted so:
    // {townitself, host, hostofhost, hostofhostofhost}
    std::vector<TownID> returnlist = {id};
    while(townmap_[id]->host != nullptr){
        returnlist.push_back(townmap_[id]->host->id);
        id = townmap_[id]->host->id;
    }

    return returnlist;

}

// ----------------------PRG 3------------------------------------

std::vector<std::pair<TownID, TownID>> Datastructures::all_roads()
{
    // reutns a vector of pairs
    // pairs are roads as TownID1 < TownID2
    // no duplicate roads are accepted (we stored them both ways)

    // loop trough townmap and on each town add the road pairs to a return value vector
    // we will use an approach where we first add everything to a set
    // then we convert it into a vector
    std::set<std::pair<TownID, TownID>> tempset = {};

    auto mapiter = townmap_.begin();
    while(mapiter != townmap_.end()){
        auto roaditer = ((*mapiter).second)->neighbours.begin();
            while (roaditer != ((*mapiter).second)->neighbours.end()) {
                std::pair<TownID, TownID> temppair = {};
                if (((*roaditer).endtown)->id < ((*mapiter).second)->id) {
                    temppair={((*roaditer).endtown)->id, ((*mapiter).second)->id};
                }
                else{
                    temppair={((*mapiter).second)->id,((*roaditer).endtown)->id};
                }
                tempset.insert(temppair);
                roaditer++;
        }
        mapiter++;
    }

    // converting our set into a vector
    std::vector<std::pair<TownID, TownID>> returnvector = {};
    returnvector.assign( tempset.begin(), tempset.end() );


    return returnvector;
}

std::vector<TownID> Datastructures::get_roads_from(TownID id)
{
    // returns a vector of neighbours IDs in an ascending order
    // if no neighbours are found returns NO_ID
    auto towniter = townmap_.find(id);
    if ( towniter == townmap_.end() ) {
        // not found
        return {NO_ID};
    }

    std::vector<TownID> returnvector = {};


    auto neighboursvector = ((*towniter).second)->neighbours;
    auto neighbouriterator = neighboursvector.begin();
    while (neighbouriterator != neighboursvector.end()) {
        returnvector.push_back( ((*neighbouriterator).endtown)->id );
        neighbouriterator++;
    }

    // we sort the returnvecotor to get the wanted ascending order
    // using TownID = std::string
    std::sort(returnvector.begin(), returnvector.end());
    return returnvector;

}

bool Datastructures::add_road(TownID town1, TownID town2)
{
    // adds a road between towns, 2 ways
    // adds a road to roadvector of the towndata stuct of town1 and town2

    // if either town doesnt exist return false
    if ( townmap_.find(town1) == townmap_.end() ) {
        // not found
        return false;
    }
    if ( townmap_.find(town2) == townmap_.end() ) {
        // not found
        return false;
    }

    // if road between towns already exists return false
    // its enough to check for just one way connection because they're added in pairs
    if (std::find_if(townmap_[town1]->neighbours.begin(), townmap_[town1]->neighbours.end(),
                  [&town2](Road m) -> bool { return m.endtown->id == town2; })
            != townmap_[town1]->neighbours.end()) {
        // found
        return false;
    }

    // else add roads and return true


    Road temp1;
    temp1.endtown = townmap_[town2];


    Road temp2;
    temp2.endtown = townmap_[town1];


    townmap_[town1]->neighbours.push_back(temp1);
    townmap_[town2]->neighbours.push_back(temp2);

    return true;
}

bool Datastructures::remove_road(TownID town1, TownID town2)
{
    // removes a road between towns, 2 ways
    // removes a road from roadvector of the towndata stuct of town1 and town2

    // if either town doesnt exist return false
    if ( townmap_.find(town1) == townmap_.end() ) {
        // not found
        return false;
    }
    if ( townmap_.find(town2) == townmap_.end() ) {
        // not found
        return false;
    }

    // if road between towns already does not exist return false
    // its enough to check for just one way connection because they're added in pairs
    if (std::find_if(townmap_[town1]->neighbours.begin(), townmap_[town1]->neighbours.end(),
                  [&town2](Road m) -> bool { return m.endtown->id == town2; })
            == townmap_[town1]->neighbours.end()) {
        // not found
        return false;
    }

    // else remove roads and return true
    auto it = find_if(townmap_[town1]->neighbours.begin(), townmap_[town1]->neighbours.end(),
                      [&town2](Road m) -> bool { return m.endtown->id == town2; });
    if (it != townmap_[town1]->neighbours.end() ) {
        townmap_[town1]->neighbours.erase(it);
    }

    auto it2 = find_if(townmap_[town2]->neighbours.begin(), townmap_[town2]->neighbours.end(),
                      [&town1](Road m) -> bool { return m.endtown->id == town1; });

    if (it2 != townmap_[town2]->neighbours.end() ) {
        townmap_[town2]->neighbours.erase(it2);
    }
   return true;
}

void Datastructures::clear_roads()
{
    // removes all roads
    // sets all neighbours vectors to {}
    auto mapiter = townmap_.begin();
    while(mapiter != townmap_.end()){
        ((*mapiter).second)->neighbours = {};
        mapiter++;
    }
}

std::vector<TownID> Datastructures::any_route(TownID fromid, TownID toid)
{
    // finds any route from fromid to toid
    // if either town doesnt exist return false
    if ( townmap_.find(fromid) == townmap_.end() ) {
        // not found
        return {NO_ID};
    }
    if ( townmap_.find(toid) == townmap_.end() ) {
        // not found
        return {NO_ID};
    }

     //towns themselves have a boolean flag that represents if the town has already been seen by this algorithm
     //at the end we must set to booleans back to false

     //we start at town fromid
    TownData* startpointtown = ((*(townmap_.find(fromid))).second);
    // we are using BFS (breadth-first)
    // implemented based on the course material pseudocode
    std::queue<TownData*> Q;
    (startpointtown)->flag = true;
    (startpointtown)->distance = 0;
    Q.push(startpointtown);

    TownData* u = nullptr;
    while(not Q.empty()) {
        u = Q.front();
        Q.pop();
        auto neighbouriterator = u->neighbours.begin();
        while (neighbouriterator != u->neighbours.end()){

            if ( ((*neighbouriterator).endtown)->flag == false) {
                ((*neighbouriterator).endtown)->flag = true;
                ((*neighbouriterator).endtown)->distance = u->distance + 1;
                ((*neighbouriterator).endtown)->lastcomein = u;
                Q.push(((*neighbouriterator).endtown));


            }
            neighbouriterator++;

        }

        u->flag = true;


    }

    // now the lastcomein pointers give us the route... backwards
    // we search for the toid from the townmap
    TownData* endpointtown = (*(townmap_.find(toid))).second;
    std::vector<TownID> routelist = {};
    TownData* reverseroutepointer = endpointtown;

    while(reverseroutepointer != nullptr) {
        routelist.push_back(reverseroutepointer->id);
        reverseroutepointer = reverseroutepointer->lastcomein;

    }

    std::reverse(routelist.begin(), routelist.end());

    // resetting the values of flags etc
    auto mapiter = townmap_.begin();
    while(mapiter != townmap_.end()) {
        ((*mapiter).second)->flag = false;
        ((*mapiter).second)->lastcomein = nullptr;
        ((*mapiter).second)->distance = INT8_MAX;
        mapiter++;
    }

    if (routelist.size() == 0 or routelist.at(0) != startpointtown->id) {
            return {};
    }


    return routelist;

}
// ^^^^^^^^^^^^^^^^^^^^^^^^^^PRG 3^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{
    if(townmap_.find(id) == townmap_.end()){
        return {};
    }
    // returns the longest vector of vassals so that the return vector is formatted so:
    // {townitself, vassal, vassalofvassal, vassalofvassalofvassal}

    // we loop trough every town in townmap and see if the taxer_path returns a vector
    // which contains the id we were given
    // taxer_path conveniently gives us a full path as a vector, but it's in reverse order
    // at the end we reverse the longest vector we got and return it
    std::vector<TownID> sofarlongest = {};

    auto mapiter = townmap_.begin();
    while(mapiter != townmap_.end()){
        std::vector<TownID> v = taxer_path(((*mapiter).second)->id);
        if(std::find(v.begin(),v.end(),id) != v.end()){
            if (v.size() > sofarlongest.size()) {
                sofarlongest = v;
            }
        }
        mapiter++;
    }
    // we now have a vector of taxers starting with lowest vassal and ending at the top
    // we have to remove every town that is ID's taxer from the end of the vector
    int extrataxers = taxer_path(id).size() - 1;
    sofarlongest.erase(sofarlongest.end() - extrataxers, sofarlongest.end());
    std::reverse(sofarlongest.begin(),sofarlongest.end());
    return sofarlongest;
}

int Datastructures::total_net_tax(TownID id)
{
    double totalnettaxsofar = 0;
    // vector<TownData*> alreadypaid = {};
    if(townmap_.find(id) == townmap_.end()){
        return NO_VALUE;
    }
    // returns the total net tax of the given id
    // a host town gets 10% of its vassal towns net tax
    // a host town also pays 10% to it's own host

    // a host town will evetually get its total_net_tax if every vassal that owes it money
    // even indirectly pays it's own 0.1^something
    auto mapiter = townmap_.begin();
    while(mapiter != townmap_.end()){
        std::vector<TownID> v = taxer_path(((*mapiter).second)->id);
        if(std::find(v.begin(),v.end(),id) != v.end()){
            // given id was found in this towns taxlist
            int owntax = ((*mapiter).second)->tax;
            int positioninpyramid = distance(v.begin(), std::find(v.begin(),v.end(),id));
            if(owntax/10 == 0) {
                continue;
            }
            totalnettaxsofar = totalnettaxsofar + owntax*(pow(0.1,positioninpyramid));
            // !!!!!!there is something here that makes us lose taxes in the process!!!!!!!
            }

        mapiter++;
    }

    if(townmap_[id]->host != nullptr){
        totalnettaxsofar = totalnettaxsofar*0.90;
    }

    int returnvalue = totalnettaxsofar;
    return returnvalue;

}

std::vector<TownID> Datastructures::least_towns_route(TownID fromid, TownID toid)
{
    return {NO_ID}; // Replace with actual implementation
}


std::vector<TownID> Datastructures::shortest_route(TownID fromid, TownID toid)
{

    // finds any route from fromid to toid
    // if either town doesnt exist return false
    if ( townmap_.find(fromid) == townmap_.end() ) {
        // not found
        return {NO_ID};
    }
    if ( townmap_.find(toid) == townmap_.end() ) {
        // not found
        return {NO_ID};
    }

     //towns themselves have a boolean flag that represents if the town has already been seen by this algorithm
     //at the end we must set to booleans back to false

     //we start at town fromid
    TownData* startpointtown = ((*(townmap_.find(fromid))).second);
    // we are using Djikstra
    // implemented based on the course material pseudocode
    auto cmp = [] (TownData* left, TownData* right) { return left->distance > right->distance;};
    std::priority_queue<TownData*,  std::vector<TownData*>, decltype (cmp) > Q (cmp);
    (startpointtown)->flag = true;
    (startpointtown)->distance = 0;
    Q.push(startpointtown);

    TownData* u = nullptr;
    while(not Q.empty()) {
        u = Q.top();
        Q.pop();
        auto neighbouriterator = u->neighbours.begin();
        while (neighbouriterator != u->neighbours.end()){

            if ( ((*neighbouriterator).endtown)->flag == false) {
                ((*neighbouriterator).endtown)->flag = true;


                // relax
                if ( ((*neighbouriterator).endtown)->distance > u->distance + ( abs(u->x - ((*neighbouriterator).endtown)->x)
                                                                                + abs(u->y - ((*neighbouriterator).endtown)->y) )){

                    ((*neighbouriterator).endtown)->distance = u->distance + ( abs(u->x - ((*neighbouriterator).endtown)->x)
                                                                               + abs(u->y - ((*neighbouriterator).endtown)->y) );
                    ((*neighbouriterator).endtown)->lastcomein = u;
                }
                Q.push(((*neighbouriterator).endtown));




            }
            neighbouriterator++;

        }

        u->flag = true;


    }

    // now the lastcomein pointers give us the route... backwards
    // we search for the toid from the townmap
    TownData* endpointtown = (*(townmap_.find(toid))).second;
    std::vector<TownID> routelist = {};
    TownData* reverseroutepointer = endpointtown;

    while(reverseroutepointer != nullptr) {
        routelist.push_back(reverseroutepointer->id);
        reverseroutepointer = reverseroutepointer->lastcomein;

    }

    std::reverse(routelist.begin(), routelist.end());

    // resetting the values of flags etc
    auto mapiter = townmap_.begin();
    while(mapiter != townmap_.end()) {
        ((*mapiter).second)->flag = false;
        ((*mapiter).second)->lastcomein = nullptr;
        ((*mapiter).second)->distance = INT8_MAX;
        mapiter++;
    }

    if (routelist.size() == 0 or routelist.at(0) != startpointtown->id) {
            return {};
    }


    return routelist;

}

std::vector<TownID> Datastructures::road_cycle_route(TownID startid)
{
    return {NO_ID}; // Replace with actual implementation
}

Dist Datastructures::trim_road_network()
{
    return NO_DIST; // Replace with actual implementation
}
