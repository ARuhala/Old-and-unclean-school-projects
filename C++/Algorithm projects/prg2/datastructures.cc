// Datastructures.cc

#include "datastructures.hh"

#include <random>
#include <algorithm>

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

}

Datastructures::~Datastructures()
{

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

std::pair<int, int> Datastructures::get_coordinates(TownID id)
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
            maxdist_ = distsortedvectorDATA_.back();
        }
        if (mindist_ == townmap_[id]) {
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
    return mindist_->id;
}

TownID Datastructures::max_distance()
{
    if(maxdist_ == nullptr){
        return NO_ID;
    }
    return maxdist_->id;
}

TownID Datastructures::nth_distance(unsigned int n)
{
    if (n == 0 or n > distsortedvectorID_.size()) {
        return NO_ID;
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
