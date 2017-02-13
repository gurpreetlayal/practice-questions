
bool rotateArraySearch (int* a, int b, int e, int s_term) {
    if (a == NULL || b > e) {
        return false;
    }

    if (b == e) {
        if (s_term == a[b]) {
            return true;
        } else {
            return false;
        }
    }

    int m = (b + e)/2;
    if (s_term == a[m]) {
        return m;
    }

    if (a[b] < a[m]) {
        if (s_term >= a[b] && s_term < a[m]) {
            return rotateArraySearch(a, b, mid-1, s_term);
        } else {
            return rotateArraySearch(a, mid+1, e, s_term);
        }
    } else if (a[m] < a[e]) {
        if (s_term > a[m] && s_term <= a[e]) {
            return rotateArraySearch(a, mid+1, e, s_term);
        } else {
            return rotateArraySearch(a, b, mid-1, s_term);
        }
    } else {
        return false;
    }
}

