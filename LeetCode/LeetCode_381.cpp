class RandomizedCollection {
public:
    /** Initialize your data structure here. */
    RandomizedCollection() {
        sz = 0;    
    }
    
    /** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
    bool insert(int val) {
        bool status = false;
        if (m.find(val) != m.end()) status = false;
        else status = true;
        
        //printf("inserting %d\n", val);
        m.insert(make_pair(val, sz));
        v.push_back(val);
        ++sz;
        return status;   
    }
    
    /** Removes a value from the collection. Returns true if the collection contained the specified element. */
    bool remove(int val) {
        if (m.count(val) == 0) return false;
        
        //printf("removing %d\n", val);
        auto it = m.find(val);
        int idx = it->second;
        if (idx == sz - 1) {
            m.erase(it);
        }
        else {
            auto ret = m.equal_range(v[sz - 1]);
            for (auto it2 = ret.first; it2 != ret.second; ++it2) {
                if (it2->second == sz - 1) {
                    m.erase(it2);
                    break;
                }
            }
            v[idx] = v[sz - 1];   
            m.erase(it);
            m.insert(make_pair(v[idx], idx));
        }

        v.pop_back();
        --sz;
        return true;
    }
    
    /** Get a random element from the collection. */
    int getRandom() {
        return v[rand() % sz];   
    }
    
private:
    vector<int> v;
    unordered_multimap<int, int> m;
    int sz;
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
 
 