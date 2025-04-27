{  // icy's point
    template <typename type>
    struct gpoint {
        const ld PI = acos(-1);
        const ld EPS = 1e-9;
        ld my_sqrt(type x) const {
            return (x >= 0 ? sqrtl(x) : 0);
        }
        type x, y;
        gpoint() : x(0), y(0) {}
        gpoint(type _x, type _y) : x(_x), y(_y) {}

        gpoint operator+(const gpoint &a) const {
            return {x + a.x, y + a.y};
        }
        gpoint operator-(const gpoint &a) const {
            return {x - a.x, y - a.y};
        }
        gpoint operator-() const {
            return {-x, -y};
        }
        gpoint operator*(const type scal) const {
            return {x * scal, y * scal};
        }
        gpoint operator/(const type scal) const {
            return {x / scal, y / scal};
        }
        bool operator==(const gpoint &a) const {
            return x == a.x && y == a.y;
        }
        bool operator!=(const gpoint &a) const {
            return !((*this) == a);
        }
        void operator=(const gpoint &a) {
            x = a.x;
            y = a.y;
        }
        type scl(const gpoint &a) const {
            return x * a.x + y * a.y;
        }
        type vct(const gpoint &a) const {
            return x * a.y - y * a.x;
        }
        ld polar_angle() const {
            ld alpha = atan2(y, x);
            if (alpha < 0) alpha += 2 * PI;
            return alpha;
        }
        ld angle(const gpoint &a) const {
            ld alpha = atan2((*this).vct(a), (*this).scl(a));
            if (alpha < 0) alpha += 2 * PI;
            return alpha;
        }
        ld len() const {
            return my_sqrt(x * x + y * y);
        }
        ld len(const gpoint &a) const {
            return my_sqrt((x - a.x) * (x - a.x) + (y - a.y) * (y - a.y));
        }
        void ort() {
            ld ln = len();
            x /= ln;
            y /= ln;
        }
    };
    //
    using Point = gpoint<ld>;
    //
}

const long double pi = acos(-1), eps = 1e-7;

bool check(long double a, long double b) {
    return abs(a - b) <= eps;
}

long long signInt(long long a) {
    if (a == 0) return 0;
    return (a > 0 ? 1 : -1);
}

struct point {
    long long x, y;

    point() {
        x = 0;
        y = 0;
    }

    point(long long _x, long long _y) {
        x = _x;
        y = _y;
    }

    long long lenQuadro() {
        return x * x + y * y;
    }

    long double len() {
        return sqrtl(lenQuadro());
    }
};

point operator-(point a, point b) {
    return point(a.x - b.x, a.y - b.y);
}

point operator+(point a, point b) {
    return point(a.x + b.x, a.y + b.y);
}

point operator*(point a, long long k) {
    return point(a.x * k, a.y * k);
}

point operator*(long long k, point a) {
    return a * k;
}

void operator-=(point &a, point b) {
    a = a - b;
}

void operator+=(point &a, point b) {
    a = a + b;
}

void operator*=(point &a, long long k) {
    a = a * k;
}

long long operator*(point a, point b) {
    return a.x * b.x + a.y * b.y;
}

long long operator%(point a, point b) {
    return a.x * b.y - a.y * b.x;
}

long double angle(point a, point b, point c) {
    point ab = b - a;
    point cb = b - c;
    long double res = atan2(abs(ab % cb), abs(ab * cb));
    if (res < 0) {
        res += 2 * pi;
    }
    return res;
}

long double anleTwo(long double a) {
    return a * 90 / pi;
}

istream &operator>>(istream &in, point &p) {
    in >> p.x >> p.y;
    return in;
}

ostream &operator<<(ostream &out, point p) {
    out << p.x << " " << p.y;
    return out;
}

bool pointOnSegment(point p, point a, point b) {
    point ap = p - a;
    point ab = b - a;
    point bp = p - b;
    point ba = a - b;
    return (ap % ab == 0 && signInt(ap * ab) >= 0 && signInt(bp * ba) >= 0);
}

bool checkSegment(point p, point a, point b) {
    point ap = p - a;
    point ab = b - a;
    point bp = p - b;
    point ba = a - b;
    return (ab * ap >= 0 && bp * ba >= 0);
}

struct line {
    long long a, b, c;

    line(point p1, point p2) {
        a = p1.y - p2.y;
        b = p2.x - p1.x;
        c = p1.x * p2.y - p2.x * p1.y;
        if (a == 0 && b == 0) {
            a = 1;
        }
    }

    line(long long _a, long long _b, long long _c) {
        a = _a;
        b = _b;
        c = _c;
        if (a == 0 && b == 0) {
            a = 1;
        }
    }

    long double distpoint(point p) {
        return ((long double)abs(a * p.x + b * p.y + c)) / (sqrt(a * a + b * b));
    }

    long long val(point p) {
        return p.x * a + p.y * b + c;
    }

    point intersectLines(line l) {
        return point((long double)(b * l.c - c * l.b) / (long double)(a * l.b - b * l.a),
                     (long double)(c * l.a - a * l.c) / (long double)(a * l.b - b * l.a));
    }
};

bool checkBeam(point p, point a, point b) {
    point ab = b - a;
    point ap = p - a;
    return (ab * ap >= 0);
}

bool isCol(point a, point b, point c, point d) {
    line l1(a, b);
    line l2(c, d);
    return l1.a * l2.b - l2.a * l1.b == 0;
}

bool segmentOnLine(point a, point b, point c, point d) {
    point ca = a - c;
    point cb = b - c;
    point cd = d - c;
    point da = a - d;
    point db = b - d;
    point dc = c - d;
    return signInt(cd % ca) * signInt(cd % cb) <= 0 || signInt(dc % da) * signInt(dc % db) <= 0;
}

long double one(point A, point B, point C, point D) {  // A -> C
    return (A - C).len();
}

long double two(point A, point B, point C, point D) {  // A -> CD (segment)
    if (checkSegment(A, C, D)) {
        return line(C, D).distpoint(A);
    } else {
        return min((A - C).len(), (A - D).len());
    }
}

long double three(point A, point B, point C, point D) {  // A -> CD (Beam)
    if (checkBeam(A, C, D)) {
        return line(C, D).distpoint(A);
    } else {
        return (A - C).len();
    }
}

long double four(point A, point B, point C, point D) {  // A -> CD (line)
    return line(C, D).distpoint(A);
}

long double eight(point A, point B, point C, point D) {  // AB (segment) -> CD (line)
    if (segmentOnLine(A, B, C, D)) {
        return 0;
    }
    return min(four(A, B, C, D), four(B, A, C, D));
}

bool checkTwoSegments(point a, point b, point c, point d) {
    if (isCol(a, b, c, d)) {
        return min({two(a, b, c, d), two(b, a, c, d), two(c, d, a, b), two(d, c, a, b)}) == 0;
    }
    return (eight(a, b, c, d) == 0 && eight(c, d, a, b) == 0);
}

long double five(point A, point B, point C, point D) {  // AB (segment) -> C
    return two(C, D, A, B);
}

long double six(point A, point B, point C, point D) {  // AB (segment) -> CD (segment)
    if (checkTwoSegments(A, B, C, D)) {
        return 0;
    } else {
        return min({two(A, B, C, D), two(B, A, C, D), two(C, D, A, B), two(D, C, A, B)});
    }
}

long double nine(point A, point B, point C, point D) {  // AB (beam) -> C
    return three(C, D, A, B);
}

long double twelve(point A, point B, point C, point D) {  // AB (beam) -> CD (line)
    if (isCol(A, B, C, D)) {
        if (line(C, D).distpoint(A) == 0) {
            return 0;
        }
        return line(C, D).distpoint(A);
    }
    if (signInt((C - A) % (C - D)) * signInt((C - B) % (C - D)) <= 0 &&
        signInt((D - A) % (D - C)) * signInt((D - B) % (D - C)) <= 0) {
        return 0;
    }
    if (four(A, B, C, D) < four(B, A, C, D)) {
        return four(A, B, C, D);
    }
    return 0;
}

long double eleven(point A, point B, point C, point D) {  // AB (beam) -> CD (beam)
    if (isCol(A, B, C, D)) {
        return min({three(A, B, C, D), three(B, A, C, D), three(C, D, A, B), three(D, C, A, B)});
    }
    if (twelve(A, B, C, D) == 0 && twelve(C, D, A, B) == 0) {
        return 0;
    }
    return min({three(A, B, C, D), three(B, A, C, D), three(C, D, A, B), three(D, C, A, B)});
}

bool segmentOnBeam(point a, point b, point c, point d) {
    if (isCol(a, b, c, d)) {
        if (line(c, d).distpoint(a) == 0) {
            return min(three(a, b, c, d), three(b, a, c, d)) == 0;
        } else {
            return false;
        }
    }
    if (eight(a, b, c, d) == 0 && twelve(c, d, a, b) == 0) {
        return true;
    }
    return false;
}

long double seven(point A, point B, point C, point D) {  // AB (segment) -> CD (beam)
    if (segmentOnBeam(A, B, C, D)) {
        return 0;
    }
    return min({three(A, B, C, D), three(B, A, C, D), two(C, D, A, B)});
}

long double ten(point A, point B, point C, point D) {  // AB (beam) -> CD (segment)
    return seven(C, D, A, B);
}

long double thirteen(point A, point B, point C, point D) {  // AB (line) -> C
    return four(C, D, A, B);
}

long double fourteen(point A, point B, point C, point D) {  // AB (line) -> CD (segment)
    return eight(C, D, A, B);
}

long double fiveteen(point A, point B, point C, point D) {  // AB (line) -> CD (beam)
    return twelve(C, D, A, B);
}

long double sixteen(point A, point B, point C, point D) {  // AB (line) -> CD (line)
    if (isCol(A, B, C, D)) {
        return four(A, B, C, D);
    }
    return 0;
}

bool point_in_segment(point p, point a, point b) {
    point ab = b - a;
    point ap = p - a;
    point bp = p - b;
    return ab % ap == 0 && ap * bp <= 0;
}

bool point_in_angle(point p, point a, point o, point b) {
    point oa = a - o;
    point ob = b - o;
    point op = p - o;
    return sign(oa % op) * sign(oa % ob) >= 0 && sign(ob % op) * sign(ob % oa) >= 0;
}

bool point_in_triangle(point p, point a, point b, point c) {
    return point_in_angle(p, a, b, c) && point_in_angle(p, b, c, a) && point_in_angle(p, a, c, b);
}

bool point_in_polygon1(point p, vector<point> &polygon) {
    int n = (int)polygon.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (point_in_segment(p, polygon[i], polygon[j])) return true;
    }
    ld ang = 0;
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        ang += angle(polygon[i] - p, polygon[j] - p);
    }
    ang = fabs(ang);
    return check(ang, 2 * pi);
}

int point_in_polygon2(point p, vector<point> &polygon) {
    int n = (int)polygon.size();
    point start = polygon[0];
    int l = 1, r = n - 1;
    if (!point_in_angle(p, polygon[l], start, polygon[r])) return 0;
    while (r - l > 1) {
        int mid = (l + r) / 2;
        if (point_in_angle(p, polygon[mid], start, polygon[r]))
            l = mid;
        else
            r = mid;
    }
    point lf = polygon[l];
    point rg = polygon[r];
    if ((point_in_segment(p, start, lf) && (l == 1)) ||
        (point_in_segment(p, start, rg) && (r == n - 1)) ||
        point_in_segment(p, lf, rg))
        return 1;
    if (point_in_triangle(p, lf, start, rg)) return 2;
    return 0;
}

vector<point> convex_hull(vector<point> &points) {
    point first = points[0];
    for (int i = 0; i < (int)points.size(); i++) {
        first = min(first, points[i]);
    }
    sort(points.begin(), points.end(), [first](point a, point b) {
        point pa = a - first;
        point pb = b - first;
        return (pb % pa) > 0 || (pa % pb == 0 && pa.len2() < pb.len2());
    });
    vector<point> res;
    res.push_back(first);
    for (int i = 1; i < (int)points.size(); i++) {
        point p = points[i];
        while (res.size() > 1) {
            point a = res[res.size() - 2];
            point b = res[res.size() - 1];
            point ap = p - a;
            point ab = b - a;
            if (ab % ap >= 0) {
                res.pop_back();
            } else {
                break;
            }
        }
        res.push_back(p);
    }
    return res;
}

ld per(vector<point> &polygon) {
    ld res = 0;
    int n = (int)polygon.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        point cur = polygon[i] - polygon[j];
        res += cur.len();
    }
    return res;
}

ld area(vector<point> &polygon) {
    ll res = 0;
    int n = (int)polygon.size();
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        res += polygon[i] % polygon[j];
    }
    return (ld)res / 2;
}