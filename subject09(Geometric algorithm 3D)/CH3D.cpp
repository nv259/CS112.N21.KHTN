#include <iostream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <array>
#include <cmath>
#include<tuple>
#define ldouble long double

using namespace std;

struct Point2D {
    ldouble x, y;

    Point2D(ldouble x = 0, ldouble y = 0) {
        this->x = x;
        this->y = y;
    }

    bool operator < (const Point2D &other) const {
        return x < other.x || (x == other.x && y < other.y);
    }
};

Point2D operator + (const Point2D &A, const Point2D &B) {
    return {A.x + B.x, A.y + B.y};
}

Point2D operator - (const Point2D &A, const Point2D &B) {
    return {A.x - B.x, A.y - B.y};
}

double cross(const Point2D &A, const Point2D &B) {
    return A.x * B.y - B.x * A.y;
}

double cross(const Point2D &A, const Point2D &B, const Point2D &C) {
    return cross(B - A, C - A);
}

bool CW(const Point2D &A, const Point2D &B, const Point2D &C) {
    return cross(A, B, C) < 0;
}

bool CCW(const Point2D &A, const Point2D &B, const Point2D &C) {
    return cross(A, B, C) > 0;
}

vector<Point2D> ConvexHull2D(vector<Point2D> &P) {
    sort(P.begin(), P.end());

    vector<int> Top, Down;
    Top.push_back(0);
    Down.push_back(0);
    int n = P.size();

    for(int i = 1; i < n; ++i) {
        if (i == n - 1 || CW(P[0], P[i], P[n - 1])) {
            while (Top.size() > 1 && !CW(P[Top[Top.size() - 2]], P[Top.back()], P[i])) Top.pop_back();
            Top.push_back(i);
        }

        if (i == n - 1 || CCW(P[0], P[i], P[n - 1])) {
            while (Down.size() > 1 && !CCW(P[Down[Down.size() - 2]], P[Down.back()], P[i])) Down.pop_back();
            Down.push_back(i);
        }
    }

    vector<Point2D> ans;
    for(int i = 0; i < (int) Down.size(); ++i) ans.push_back(P[Down[i]]);
    for(int i = Top.size() - 2; i > 0; --i) ans.push_back(P[Top[i]]);

    return ans;
}

ldouble Area(const vector<Point2D> &P) {
    ldouble ans = 0;
    for(int i = 1; i < (int) P.size() - 1; ++i) ans += fabs(cross(P[0], P[i], P[i + 1]));
    return ans / 2;
}

struct Point3D {
    ldouble x, y, z;

    Point3D(ldouble x = 0, ldouble y = 0, ldouble z = 0) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void operator -= (const Point3D &other) {
        x -= other.x;
        y -= other.y;
        z -= other.z;
    }

    void operator += (const Point3D &other) {
        x += other.x;
        y += other.y;
        z += other.z;
    }

    bool operator == (const Point3D &other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    bool operator != (const Point3D &other) const {
        return x != other.x || y != other.y || z != other.z;
    }
};

Point3D operator - (const Point3D &A, const Point3D &B) {
    return {A.x - B.x, A.y - B.y, A.z - B.z};
}

Point3D operator / (const Point3D &A, const ldouble &B) {
    return {A.x / B, A.y / B, A.z / B};
}

Point3D operator + (const Point3D &A, const Point3D &B) {
    return {A.x + B.x, A.y + B.y, A.z + B.z};
}

ldouble dot(const Point3D &A, const Point3D &B) {
    return A.x * B.x + A.y * B.y + A.z * B.z;
}

Point3D cross(const Point3D &A, const Point3D &B) {
    return {A.y * B.z - B.y * A.z, A.z * B.x - B.z * A.x, A.x * B.y - B.x * A.y};
}

Point3D cross(const Point3D &A, const Point3D &B, const Point3D &C) {
    return cross(B - A, C - A);
}

ldouble orient(const Point3D &A, const Point3D &B, const Point3D &C, const Point3D &P) {
    return dot(cross(A, B, C), P - A);
}

bool above(const Point3D &A, const Point3D &B, const Point3D &C, const Point3D &P) {
    return orient(A, B, C, P) > 0;
}

bool coplanar(const Point3D &A, const Point3D &B, const Point3D &C, const Point3D &P) {
    return orient(A, B, C, P) == 0;
}

bool collinear(const Point3D &A, const Point3D &B, const Point3D &C) {
    return cross(A, B, C) == Point3D(0.0, 0.0, 0.0);
}

double abs(const Point3D &p) {
    return sqrt(p.x * p.x + p.y * p.y + p.z * p.z);
}

typedef array<int, 3> Face;

int Dim(vector<Point3D> &P) {
    int n = P.size();
    random_shuffle(P.begin(), P.end());

    int dim = 1;
    for(int i = 1; i < n; ++i)
    if (dim == 1) {
        if (P[0] != P[i]) swap(P[1], P[i]), ++dim;
    } else if (dim == 2) {
        if (!collinear(P[0], P[1], P[i])) swap(P[2], P[i]), ++dim;
    } else if (dim == 3) {
        if (!coplanar(P[0], P[1], P[2], P[i])) swap(P[3], P[i]), ++dim;
    }

    return dim;
}

vector<Face> ConvexHull3D(vector<Point3D> &P) {
    random_shuffle(P.begin() + 4, P.end());

    int n = P.size();
    vector<bool> active;
    vector<vector<int>> visible(n), rvisible; /// visible: faces visible from each point; rvisible: points visible from each face
    vector<array<pair<int, int>, 3>> other;
    vector<Face> hull;
    vector<int> label(n, -1);

    auto add_face = [&] (const int &a, const int &b, const int &c) {
        hull.push_back({a, b, c});
        active.push_back(true);
        rvisible.emplace_back();
        other.emplace_back();
    };

    auto add_visible = [&] (const int &a, const int &b) {
        visible[b].push_back(a);
        rvisible[a].push_back(b);
    };

    auto check_above = [&] (const int &i, const int &p) {
        Face face = hull[i];
        return above(P[face[0]], P[face[1]], P[face[2]], P[p]);
    };

    auto edge = [&] (const int &p, const int &i) -> pair<int, int> {
        return {hull[p][i], hull[p][(i + 1) % 3]};
    };

    auto glue = [&] (const pair<int, int> &a, const pair<int, int> &b) {
        pair<int, int> F = edge(a.first, a.second); assert(edge(b.first, b.second) == make_pair(F.second, F.first));
        other[a.first][a.second] = b, other[b.first][b.second] = a;
    };

    add_face(0, 1, 2); add_face(0, 2, 1);
    if (check_above(1, 3)) swap(P[1], P[2]);

    for(int i = 0; i < 3; ++i) glue({0, i}, {1, 2 - i});
    for(int i = 3; i < n; ++i) add_visible(check_above(1, i), i);

    for(int i = 3; i < n; ++i) {
        vector<int> tmp;
        for(int f: visible[i])
        if (active[f]) {
            active[f] = false;
            tmp.push_back(f);
        }

        if (tmp.empty()) continue;

        int st = -1;
        for(int f: tmp)
        for(int j = 0; j < 3; ++j) {
            int of = other[f][j].first;
            if (active[of]) {
                /// create new face
                int a, b; tie(a, b) = edge(f, j);
                add_face(a, b, i);
                st = a;

                int cur = rvisible.size() - 1; label[a] = cur;
                vector<int> ttmp; set_union(rvisible[f].begin(), rvisible[f].end(), rvisible[of].begin(), rvisible[of].end(), back_inserter(ttmp));

                for(int x: ttmp)
                if (check_above(cur, x)) add_visible(cur, x);

                glue({cur, 0}, other[f][j]);
            }
        }

        for(int x = st, y;; x = y) {
            int lb = label[x]; glue({lb,1}, {label[y = hull[lb][1]], 2});
            if (y == st) break;
        }
    }


    vector<Face> ans;
    for(int i = 0; i < (int) hull.size(); ++i)
    if (active[i]) ans.push_back(hull[i]);

    return ans;
}

pair<ldouble, ldouble> SaVol(const vector<Point3D> &P, const vector<Face> &F) {
    ldouble s = 0, v = 0;
    for(Face f: F) {
        Point3D a = P[f[0]], b = P[f[1]], c = P[f[2]];
        s += abs(cross(a, b, c)), v += dot(cross(a, b), c);
    }

    return {s / 2, v / 6};
}

Point3D normalizeVector(const Point3D &A) {
    return A / abs(A);
}

Point3D triangleNormal(const Point3D &A, const Point3D &B, const Point3D &C) {
    return normalizeVector(cross(A, C, B));
}

int main() {
    ios_base::sync_with_stdio(0); cin.tie(NULL);

    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<Point3D> P(n, {0, 0, 0});
        for(Point3D &p: P) cin >> p.x >> p.y >> p.z;

        if (P.size() < 3) {
            (cout << fixed).precision(4);
            cout << 0 << ' ' << 0 << '\n';
            continue;
        } else if (P.size() == 3) {
            (cout << fixed).precision(4);
            cout << abs(cross(P[0], P[1], P[2])) << ' ' << 0 << '\n';
            continue;
        }

        int dim = Dim(P);
        if (dim < 3) {
            (cout << fixed).precision(4);
            cout << 0 << ' ' << 0 << '\n';
            continue;
        }

        if (dim == 4) {
            assert(!coplanar(P[0], P[1], P[2], P[3]));
            vector<Face> F = ConvexHull3D(P);
            pair<ldouble, ldouble> ans = SaVol(P, F);

            (cout << fixed).precision(4);
            cout << ans.first << ' ' << ans.second << '\n';
        } else {
            Point3D N = triangleNormal(P[0], P[1], P[2]);
            Point3D U = normalizeVector(P[1] - P[0]);
            Point3D V = normalizeVector(cross(U, N));

            vector<Point2D> P2D;
            for(int i = 0; i < n; ++i) P2D.push_back({dot(P[i] - P[0], U), dot(P[i] - P[0], V)});

            (cout << fixed).precision(4);
            cout << 2 * Area(ConvexHull2D(P2D)) << ' ' << 0 << '\n';
        }
    }

    return 0;
}
