class RandomizedSet {
public:
    /** Initialize your data structure here. */
    RandomizedSet() {
        sz = 0;
    }
    
    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val) {
        if (m.find(val) != m.end()) return false;
        
        //printf("inserting %d\n", val);
        m.insert(make_pair(val, sz));
        v.push_back(val);
        ++sz;
        return true;
    }
    
    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val) {
        if (m.find(val) == m.end()) return false;
        
        //printf("removing %d\n", val);
        if (sz > 1) {
            int idx = m[val];
            v[idx] = v[sz-1];
            m[v[idx]] = idx;

        }
        
        m.erase(val);
        v.pop_back();
        --sz;
        return true;
    }
    
    /** Get a random element from the set. */
    int getRandom() {
        return v[rand() % sz];
    }
private:
    vector<int> v;
    unordered_map<int, int> m;
    int sz;
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
 
 