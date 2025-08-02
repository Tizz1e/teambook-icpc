struct ModInt {
    int value;
    const int mod;

    ModInt(int v = 0, int mod = 1e9 + 7) : mod(mod) {
        value = v % mod;
        if (value < 0) value += mod;
    }

    ModInt& operator+=(const ModInt& other) {
        value = (value + other.value) % mod;
        if (value < 0) value += mod;
        return *this;
    }

    ModInt& operator-=(const ModInt& other) {
        value = (value - other.value) % mod;
        if (value < 0) value += mod;
        return *this;
    }

    ModInt& operator*=(const ModInt& other) {
        value = (1LL * value * other.value) % mod;
        if (value < 0) value += mod;
        return *this;
    }

    friend ModInt operator+(ModInt left, const ModInt& right) {
        left += right;
        return left;
    }

    friend ModInt operator-(ModInt left, const ModInt& right) {
        left -= right;
        return left;
    }

    friend ModInt operator*(ModInt left, const ModInt& right) {
        left *= right;
        return left;
    }

    operator int() const { return value; }
};