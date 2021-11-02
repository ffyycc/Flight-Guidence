template <typename T>
void DisjointSets<T>::addElement(T ele) {
    if (_innerMapping.count(ele)) cout << "ERROR" << endl;
    int idx = _storage.size();
    _innerMapping[ele] = idx;
    _storage.push_back(-1);
    _outerMapping.push_back(ele);
}

template <typename T>
bool DisjointSets<T>::inSameSet(T a, T b) {
    return _find(_innerMapping[a]) == _find(_innerMapping[b]);
}

template <typename T>
void DisjointSets<T>::setUnion(T a, T b) {
    int rootA = _find(_innerMapping[a]);
    int rootB = _find(_innerMapping[b]);
    if (rootA == rootB) return;
    if (_storage[rootA] > _storage[rootB]) {
        // set containing b has greater size
        _storage[rootB] += _storage[rootA];
        _storage[rootA] = rootB;
    } else {
        // set containing a has greater size or they are equal in size
        _storage[rootA] += _storage[rootB];
        _storage[rootB] = rootA;
    }
}

template <typename T>
int DisjointSets<T>::size(int elem) {
    if (elem >= (int) _storage.size()) return -1;
    return -_storage[_find(elem)];
}

template <typename T>
int DisjointSets<T>::_find(int elem) {
    if (_storage[elem] < 0) return elem;
    _storage[elem] = _find(_storage[elem]);
    return _storage[elem];
}