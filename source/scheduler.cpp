#include "scheduler.h"
#include <algorithm>

scheduler::scheduler(scheduler_policy policy)
:policy(policy)
{
    switch (policy)
    {
    case scheduler_policy::deny :
        this->policy_fun = &scheduler::deny_policy;
        break;
    //////////////////////////////////////////////////
    default:
        break;
    }
}

bool scheduler::find_relative(task_t item, chrono::seconds after_before, time_t end, time_t min_dur)
{
    return false;
}

optional<vector<task_t>> scheduler::get_range(time_t start, time_t end){
    vector<task_t> range_vec;
    const auto & range =boost::make_iterator_range(
            this->m_interval_map.equal_range(
                time_interval::closed(
                    start, 
                    end)));
    for (auto & element : range)
    {
        range_vec.push_back(element.second);
    }
    
    return range_vec.empty() ? nullopt : make_optional(range_vec);
}

//No check we assume checked
bool scheduler::add_single(const task_t && task_)
{
    const auto &interval_ = task_->get_interval();
    if(find_range(interval_.start, interval_.end)){
        this->m_interval_map.set(make_pair(time_interval::closed(interval_.start, interval_.end), task_));
        return true;
    }else{
        return false;
    }
}

bool scheduler::find_range(time_t start, time_t end){
    return policy_fun(this, policy_relevant_data{
        .start = start,
        .end = end
    });
}

void scheduler::print_out() const
{
    for ( const auto & [k,v] : m_interval_map){
        cout << k << " interval : Task " << v->id << endl;
    }
}

bool scheduler::deny_policy(policy_relevant_data && task_info_for_scheduler ) {
        const auto & range = boost::make_iterator_range(
            this->m_interval_map.equal_range(
                time_interval::closed(
                    task_info_for_scheduler.start, 
                    task_info_for_scheduler.end)));

        if (!range.empty())
        {
            return false;
        }
        return true;
    }