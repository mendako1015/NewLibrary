// Binary Indexed Tree
// 0-indexed
// 各操作 O(log n)
// add(pos, x): posの位置にxを加える
// sum(pos): [0, pos)の総和
// sum(l, r): [l, r)の総和

template<class T = int>
struct BIT {
    int N;
    vector<T> bit;

    BIT() : N(0) {}
    BIT(int n) : N(n), bit(n + 1, 0) {}
    BIT(int n, T init) : N(n), bit(n + 1, init) {}

    void add(int pos, T x) {
        pos++;
        while(pos <= N) {
            bit[pos] += x;
            pos += pos & -pos;
        }
    }

    T sum(int pos) {
        T ret = 0;
        while(pos > 0) {
            ret += bit[pos];
            pos -= pos & -pos;
        }
        return ret;
    }

    T sum(int l, int r) {
        return sum(r) - sum(l);
    }

    const T& operator[](const int &pos) const {
        return bit[pos];
    }
};