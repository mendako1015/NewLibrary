template<class T>
class SegmentTree {
    private:
    int leaf_num = 1;
    vector<T> data, lazy; // lazy: 遅延評価用
    vector<bool> changed; // 遅延評価にて

    void evaluation(int pos, int btm, int tp) {
        if(!changed[pos]) return ;
        if(tp - btm > 1) {
            lazy[pos * 2 + 1] += lazy[pos], changed[pos * 2 + 1] = true;
            lazy[pos * 2 + 2] += lazy[pos], changed[pos * 2 + 2] = true;
        }
        data[pos] += lazy[pos] * (tp - btm);
        lazy[pos] = 0;
        changed[pos] = false;
    }

    void range_update(int l, int r, T x, int pos, int btm, int tp) {
        evaluation(pos, btm, tp);
        if(r <= btm || tp <= l) return ;
        if(l <= btm && tp <= r) {
            lazy[pos] += x, changed[pos] = true;
            evaluation(pos, btm, tp);
        } else {
            int mid = (btm + tp) / 2;
            range_update(l, r, x, pos * 2 + 1, btm, mid);
            range_update(l, r, x, pos * 2 + 2, mid, tp);
            data[pos] = data[pos * 2 + 1] + data[pos * 2 + 2];
        }
    }

    T get_interval(int l, int r, int pos, int btm, int tp) {
        if(r <= btm || tp <= l) return 0;
        evaluation(pos, btm, tp);
        if(l <= btm && tp <= r) return data[pos];
        int mid = (btm + tp) / 2;
        T l_child = get_interval(l, r, pos * 2 + 1, btm, mid);
        T r_child = get_interval(l, r, pos * 2 + 2, mid, tp);
        return l_child + r_child;
    }

    public:
    SegmentTree(int n) {
        while(leaf_num < n) leaf_num *= 2;
        data = vector<T>(leaf_num * 2 - 1);
        lazy = vector<T>(leaf_num * 2 - 1);
        changed = vector<bool>(leaf_num * 2 - 1);
    }

    void update(int l, int r, T x) {
        range_update(l, r, x, 0, 0, leaf_num);
    }

    T get(int l, int r) {
        return get_interval(l, r, 0, 0, leaf_num);
    }
};