#include <bits/stdc++.h>

#include <vector>
using namespace std;

using ll = long long;
using pi = pair<ll, ll>;
using vi = vector<ll>;
using vpi = vector<pi>;
using vb = vector<bool>;
/*ZERO INDEX FOR ALL PARAMETERS, BUT FENWICK TREE IS ONE INDEXED*/
struct FenwickTree {
    vector<int> arr;
    FenwickTree(int size) {
        arr.assign(size + 1, 0);
    }
    void update(int index, int amt) {
        index++;
        while (index < arr.size()) {
            arr[index] += amt;
            index += (index & -index);
        }
    }
    void build(vector<int>& a) {
        for (int i = 0; i < a.size(); i++) {
            update(i, a[i]);
        }
    }
    void fastBuild(vector<int>& a) {
        for (int i = 1; i <= a.size(); i++) {
            arr[i] += a[i - 1];
            int index = i + (i & -i);  // next index that it contributes to
            if (index <= a.size()) {
                arr[index] += arr[i];
            }
        }
    }
    ll prefixSum(int index) {
        ll res = 0;
        index += 1;
        while (index != 0) {
            res += arr[index];
            index -= (index & -index);
        }
        return res;
    }
    // 0 to n-1
    ll prefixRange(int index1, int index2) {
        index1--;
        index2--;
        return prefixSum(index2) - prefixSum(index1);
    }
};
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    int q;
    q = n;
    vector<int> a(n, 0);
    vector<int> build(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        build[i] = 1;
    }
    FenwickTree ft(n);
    ft.fastBuild(build);
    vector<int> present(n, 1);
    for (int i = 0; i < q; i++) {
        int rem;
        cin >> rem;
        int low = 0;
        int high = n - 1;
        int ans = 0;
        while (low <= high) {
            int mid = (low + high) / 2;
            int sum = ft.prefixSum(mid);
            if (sum < rem) {
                low = mid + 1;
            } else if (sum > rem) {
                high = mid - 1;
            } else {
                // System.out.println(st.sum(1, 0, st.size-1, 0, mid));
                if (present[mid]) {
                    ans = mid;
                    low = mid;
                    break;
                } else {
                    high = mid - 1;
                }
            }
        }
        present[ans] = 0;
        ft.update(ans, -1);
        cout << a[ans] << endl;
    }

    return 0;
}
