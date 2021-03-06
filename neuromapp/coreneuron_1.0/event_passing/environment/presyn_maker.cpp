#include <boost/range/algorithm_ext/iota.hpp>
#include <iostream>
#include <time.h>
#include <ctime>
#include <numeric>
#include <boost/range/algorithm/random_shuffle.hpp>
#include <boost/range/algorithm_ext/iota.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random.hpp>

#include "coreneuron_1.0/event_passing/environment/presyn_maker.h"

namespace environment {

void presyn_maker::operator()(int nprocs, int ngroups, int rank){
    //assign input and output gid's
    assert(nprocs >= 1);

    //used for random presyn and netcon selection
    boost::mt19937 rng(time(NULL) + rank);
    boost::random::uniform_int_distribution<> uni_d(0, n_cells_);

    //neuron distribution
    const int offset = n_cells_ % nprocs;
    const bool hasonemore = offset > rank;
    int cells_per = n_cells_ / nprocs + hasonemore;

    int start = rank * cells_per;
    if (!hasonemore)
        start += offset;
    int cur;

    //create local presyns with empty vectors
    for(int i = 0; i < cells_per; ++i){
        outputs_[start + i];
    }

    if (degree_==fixedindegree) {
        //foreach gid, select srcs
        for(int i = 0; i < cells_per; ++i){
            for(int j = 0; j < fan_; ++j){
                cur = uni_d(rng);
                //local GID
                if(cur >= start && cur < (start + cells_per)){
                    //add self to src gid
                    outputs_[cur].push_back(start + i);
                }
                //remote GID
                else{
                    //add self to input presyn for gid
                    inputs_[cur].push_back(start + i);
                }
            }
        }
    }
    else if (degree_==fixedoutdegree) {
        for(int cur = 0; cur < cells_per; ++cur){
            for(int j = 0; j < fan_; ++j){
                int picked = uni_d(rng);
                //local GID
                if(cur >= start && cur < (start + cells_per)){
                    //add self to src gid
                    outputs_[cur].push_back(picked);
                }
                //remote GID
                else{
                    //add self to input presyn for gid
                    inputs_[cur].push_back(picked);
                }
            }
        }
    }
}

const presyn* presyn_maker::find_input(int key) const{
    std::map<int, std::vector<int> >::const_iterator it = inputs_.begin();
    const presyn* input_ptr = NULL;
    it = inputs_.find(key);
    if(it != inputs_.end()){
        input_ptr = &(it->second);
    }
    return input_ptr;
}

const presyn* presyn_maker::find_output(int key) const{
    std::map<int, std::vector<int> >::const_iterator it = outputs_.begin();
    const presyn* output_ptr = NULL;
    it = outputs_.find(key);
    if(it != outputs_.end()){
        output_ptr = &(it->second);
    }
    return output_ptr;
}

} //end of namespace
