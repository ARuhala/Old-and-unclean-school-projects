// Datastructures.cc

#include "datastructures.hh"

#include <random>
#include <algorithm>
#include <vector>
#include <iostream>

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

unsigned int Datastructures::size()
{
    return TownList_.size();
}

void Datastructures::clear()
{
    TownList_.clear();
    AlphapeticalTownList_.clear();
    DistanceTownList_.clear();
    DISTUnsortedIndex_ = 1;
    ALPHUnsortedIndex_ = 1;
    DISTFLAG_ = false;
    ALPHFLAG_ = false;
    MinDist_ = nullptr;
    MaxDist_ = nullptr;
}

std::vector<TownData*> Datastructures::all_towns()
{
    return TownList_;
}
bool DISTCompareSmallerOrEqual(TownData*& Left, TownData*& Right) {
    return ((abs(Left->x)+abs(Left->y)) <= (abs(Right->x)+abs(Right->y)));
}

bool ALPHCompareSmallerOrEqual(TownData*& Left, TownData*& Right) {
    return Left->name <= Right->name;
}

bool DISTCompareSmaller(TownData*& Left, TownData*& Right) {
    return ((abs(Left->x)+abs(Left->y)) < (abs(Right->x)+abs(Right->y)));
}

bool ALPHCompareSmaller(TownData*& Left, TownData*& Right) {
    return Left->name < Right->name;
}

TownData* Datastructures::add_town(const std::string& name, int x, int y)
{
    TownData* TempTown = new TownData;
    TempTown->name = name;
    TempTown->x = x;
    TempTown->y = y;


    // adding the town to our lists
    TownList_.push_back(TempTown);
    AlphapeticalTownList_.push_back((TempTown));
    DistanceTownList_.push_back(TempTown);

    // setting the sort flags off so we know to sort them next time they're needed
    // the idea why we dont just sort them right now - is that we'll first add all the towns
    // and then sort them all at once when needed
    ALPHFLAG_ = false;
    DISTFLAG_ = false;

    // updating min and max dist
    if (MinDist_ == nullptr or DISTCompareSmaller(TempTown, MinDist_)){
        MinDist_ = TempTown;
    }
    if (MaxDist_ == nullptr or not(DISTCompareSmaller(TempTown, MaxDist_))){
        MaxDist_ = TempTown;
    }


    return TempTown;


}



std::vector<TownData*> Merge(std::vector<TownData*>& Left, std::vector<TownData*>& Right, bool (*COMPARE)(TownData*&, TownData*&)){
    // this is a try at merge (part of merge sort that puts parts back together)
    std::vector<TownData*> Result;

    while((Left.size() > 0) or (Right.size() > 0)){ // "lets do operations until both sides are empty"
        if ((Left.size() > 0) and (Right.size() > 0)) {
            // comparisons and adding the smaller to the beginning of Result
            if (COMPARE(Left.front(), Right.front())) {
                Result.push_back(Left.front());
                Left.erase(Left.begin());

            }
            else {
                Result.push_back(Right.front());
                Right.erase(Right.begin());
            }
        }
        // checking if at least one side isn't empty and needs to be "loaded" to Result
        else if (Left.size() > 0) {
            for (int i = 0; i < ((int)(Left.size())); i++) {
                Result.push_back(Left[i]);
            }
            break;
        }
        else if (Right.size() > 0) {
            for (int i = 0; i < ((int)(Right.size())); i++) {
                Result.push_back(Right[i]);
            }
            break;
        }
    }
    // returning Result (this function is called by MergeSort)
    return Result;


}

std::vector<TownData*> MergeSort(std::vector<TownData*>& TownVector,bool (*COMPARE)(TownData*&, TownData*&)) {
    // this is a try at a recursive Mergesort for comparing stuff (compare is a selfmade bool function)
    // this is the splitting stuff up part and the final return
    // recursion ends if this is true
    if (((int)(TownVector.size())) <= 1) {
        return TownVector;
    }
    std::vector<TownData*> Left;
    std::vector<TownData*> Right;
    std::vector<TownData*> Result;

    // we split the Townvector in half so we can fill Left and Right
    int MiddlePoint = (((int)(TownVector.size())) + 1)/2;
    // lets fill the left side up until middle point
    for (int i = 0; i < MiddlePoint; i++) {
        Left.push_back(TownVector[i]);
    }
    // and Right starting from middle point
    for(int i = MiddlePoint; i < ((int)(TownVector.size())); i++) {
        Right.push_back(TownVector[i]);
    }

    Left = MergeSort(Left, COMPARE); // at the end of recursion the first return value will be of size 1
    Right = MergeSort(Right, COMPARE); // same with right side
    Result = Merge(Left, Right, COMPARE); // the size 1 vectors are merged


    return Result; // and returned to the calling Left and Right, until the list is complete and
                    // the last caller was the alphabet sort

}

std::vector<TownData*> InsertionSort(std::vector<TownData*>& TownVector,int UnsortedIndex, bool (*COMPARE)(TownData*&, TownData*&)) {
    int i = 0;
    int j = 0;
    TownData* Temp;
    for (i = UnsortedIndex; i < ((int)TownVector.size()); i++)
    {
        Temp = TownVector.at(i);
        j = i-1;

        while (j >= 0 && not(COMPARE(TownVector.at(j),Temp)))
        {
            TownVector.at(j+1) = TownVector.at(j);
            j = j-1;
        }
        TownVector.at(j+1) = Temp;
    }


    return TownVector;
}


std::vector<TownData*> Datastructures::towns_alphabetically()
{
    // we check the ALPHFLAG_ and only sort the list if it's required, otherwise we just
    // return it from the memory
    if (ALPHFLAG_ == false) {
        if (abs(size() - ALPHUnsortedIndex_) < 20){
            AlphapeticalTownList_ = InsertionSort(AlphapeticalTownList_,ALPHUnsortedIndex_,ALPHCompareSmaller);
        }
        else {
            AlphapeticalTownList_ = MergeSort(AlphapeticalTownList_,ALPHCompareSmallerOrEqual);
        }

        ALPHFLAG_ = true;
        ALPHUnsortedIndex_ = size() -1;

    }

    return AlphapeticalTownList_;
}



std::vector<TownData*> Datastructures::towns_distance_increasing()
{
    // we check the DISTFLAG_ and only sort the list if it's required, otherwise we just
    // return it from the memory
    if (DISTFLAG_ == false) {
        if (abs(size() - DISTUnsortedIndex_) < 20){
            DistanceTownList_ = InsertionSort(DistanceTownList_,DISTUnsortedIndex_,DISTCompareSmaller);
        }
        else {
            DistanceTownList_= MergeSort(DistanceTownList_,DISTCompareSmallerOrEqual);
        }

        DISTFLAG_ = true;
        DISTUnsortedIndex_ = size() -1;

    }
    return DistanceTownList_;
}

TownData* Datastructures::find_town(std::string const& name)
{
    // by going at the scenario that add_list is as frquent as find_town, in a random case
    // it is better to look at our randomly ordered TownList_ (n) than go trought the trouble
    // of sometimes having to sort the Alphapetical list (nlogn + n-x)


    // we look trough the TownList_ and return the first one found
    // if we dont find anything we return a nullptr;
    for(std::vector<TownData*>::iterator Iter = TownList_.begin(); Iter != TownList_.end();) {
        if ((*Iter)->name == name) {
            return *Iter;
        }
        Iter++;
    }

    return nullptr;
}

TownData* Datastructures::min_distance()
{
    return MinDist_;
}

TownData* Datastructures::max_distance()
{
    return MaxDist_;
}

TownData* Datastructures::nth_distance(unsigned int n)
{
    if ((n > DistanceTownList_.size()) or (n == 0)){ // n is unsigned so no need to check if its less than 0
        return nullptr;
    }
    else if (DISTFLAG_ == false) {
        if (abs(size() - DISTUnsortedIndex_) < 20){
            DistanceTownList_ = InsertionSort(DistanceTownList_,DISTUnsortedIndex_,DISTCompareSmaller);
        }
        else {
            DistanceTownList_= MergeSort(DistanceTownList_,DISTCompareSmallerOrEqual);
        }

        DISTFLAG_ = true;
        DISTUnsortedIndex_ = size() -1;

    }

    return DistanceTownList_[n-1]; // the command uses indexing from 1



}

void Datastructures::remove_town(const std::string& town_name)
{
    // removes a town from the list if it has been previously added
    // if the town doesn't exist, the function does nothing

    // since only one town of that name needs to be deleted, we can use vector.find_if()
    // since finding the value of name is a bit tricky, we are using a lambda function as an argument for find_if
    std::vector<TownData*>::iterator RemovalIter = std::find_if(TownList_.begin(), TownList_.end(),
                                                                [&](TownData* Town) {return Town->name == town_name;});

    // setting the flags to false so we know to sort the lists again
    if (RemovalIter != TownList_.end()) {
        TownList_.erase(RemovalIter);
        // lets do the same operation for the other lists

        std::vector<TownData*>::iterator RemovalIter = std::find_if(AlphapeticalTownList_.begin(), AlphapeticalTownList_.end(),
                                                                    [&](TownData* Town) {return Town->name == town_name;});
        if (RemovalIter != AlphapeticalTownList_.end()){
            AlphapeticalTownList_.erase(RemovalIter);

            std::vector<TownData*>::iterator RemovalIter = std::find_if(DistanceTownList_.begin(), DistanceTownList_.end(),
                                                                        [&](TownData* Town) {return Town->name == town_name;});
            if (RemovalIter != DistanceTownList_.end()) {
                DistanceTownList_.erase(RemovalIter);
                MinDist_ = DistanceTownList_[0];
                MaxDist_ = DistanceTownList_.back();



                ALPHFLAG_ = false;
                DISTFLAG_ = false;

                ALPHUnsortedIndex_ = 1; // we can no longer be sure where the sorted part ends
                DISTUnsortedIndex_ = 1;
            }
        }




}


}


// HERE STARTS THE IMPLEMENTATION FOR SORTING TOWNS BY DISTANCE TO SPESIFIC X AND Y
// I did not find a way to implement a default for the parameters so that i wouldn't have to pass unneccessary
// parameters to the alphapetical sort, also making X2 and Y2 class parameters gave problems with
// the compare function being non-static, and static compare couldn't use class parameters
// so we are making a whole new merge sort for this


bool DISTComplexCompareSmallerOrEqual(TownData* Left, TownData* Right, int X2, int Y2) {
    return ((abs(Left->x - X2)+abs(Left->y - Y2)) <= (abs(Right->x - X2)+abs(Right->y - Y2)));
}

std::vector<TownData*> ComplexDISTMerge(std::vector<TownData*> Left, std::vector<TownData*> Right, int X2, int Y2, bool (*COMPARE)(TownData*, TownData*, int, int)){
    // this is a try at merge (part of merge sort that puts parts back together)
    std::vector<TownData*> Result;

    while((Left.size() > 0) or (Right.size() > 0)){ // "lets do operations until both sides are empty"
        if ((Left.size() > 0) and (Right.size() > 0)) {
            // comparisons and adding the smaller to the beginning of Result
            if (COMPARE(Left.front(), Right.front(), X2, Y2)) {
                Result.push_back(Left.front());
                Left.erase(Left.begin());

            }
            else {
                Result.push_back(Right.front());
                Right.erase(Right.begin());
            }
        }
        // checking if at least one side isn't empty and needs to be "loaded" to Result
        else if (Left.size() > 0) {
            for (int i = 0; i < ((int)(Left.size())); i++) {
                Result.push_back(Left[i]);
            }
            break;
        }
        else if (Right.size() > 0) {
            for (int i = 0; i < ((int)(Right.size())); i++) {
                Result.push_back(Right[i]);
            }
            break;
        }
    }
    // returning Result (this function is called by MergeSort)
    return Result;


}

std::vector<TownData*> ComplexDISTMergeSort(std::vector<TownData*> TownVector, int X2, int Y2, bool (*COMPARE)(TownData*, TownData*, int, int)) {
    // this is a try at a recursive Mergesort for comparing stuff (compare is a selfmade bool function)
    // this is the splitting stuff up part and the final return
    // recursion ends if this is true
    if (((int)(TownVector.size())) <= 1) {
        return TownVector;
    }
    std::vector<TownData*> Left;
    std::vector<TownData*> Right;
    std::vector<TownData*> Result;

    // we split the Townvector in half so we can fill Left and Right
    int MiddlePoint = (((int)(TownVector.size())) + 1)/2;
    // lets fill the left side up until middle point
    for (int i = 0; i < MiddlePoint; i++) {
        Left.push_back(TownVector[i]);
    }
    // and Right starting from middle point
    for(int i = MiddlePoint; i < ((int)(TownVector.size())); i++) {
        Right.push_back(TownVector[i]);
    }

    Left = ComplexDISTMergeSort(Left,X2,Y2, COMPARE); // at the end of recursion the first return value will be of size 1
    Right = ComplexDISTMergeSort(Right,X2,Y2, COMPARE); // same with right side
    Result = ComplexDISTMerge(Left, Right,X2,Y2, COMPARE); // the size 1 vectors are merged


    return Result;

}
std::vector<TownData*> Datastructures::towns_distance_increasing_from(int x, int y)
{
    // no need to store this in the memory as the point will most likely be different everytime
    return ComplexDISTMergeSort(DistanceTownList_, x, y, DISTComplexCompareSmallerOrEqual);
}
