struct LongInt {
    inline static const int base = 1e8;
    inline static const int base_len = 8;
    deque <int> number;
    bool negative = 0;

    size_t size() const {
        return number.size();
    }

    LongInt(ll v = 0) {
        do {
            number.push_back(v % base);
            v /= base;
        } while (v > 0);
    }

    LongInt(string s) {
        if (s[0] == '-') {
            negative = 1;
            s.erase(0, 1);
        }
        reverse(s.begin(), s.end());
        for (int it = 0; it < s.length(); it += base_len) {
            string temp = s.substr(it, min(base_len, (int)s.length() - it));
            reverse(temp.begin(), temp.end());
            number.push_back(stoi(temp));
        }
    }

    LongInt copy() const {
        return *this;
    }

    bool is_negative() const {
        return negative;
    }

    LongInt& operator+=(const LongInt& other) {
        LongInt rhs = other.copy();
        LongInt lhs = this->copy();
        normalize(lhs, rhs);
        if (lhs.is_negative() && !rhs.is_negative()) {
            lhs.negative = 0;
            rhs -= lhs;
            swap(*this, rhs);
            return *this;
        }
        if (!lhs.is_negative() && rhs.is_negative()) {
            rhs.negative = 0;
            lhs -= rhs;
            swap(*this, lhs);
            return *this;
        }
        deque <int> new_number(lhs.size());
        int carry = 0;
        for (size_t i = 0; i < lhs.size(); i++) {
            ll temp = 1ll * lhs.number[i] + rhs.number[i] + carry;
            new_number[i] = temp % base;
            carry = temp / base;
        }
        if (carry) {
            new_number.push_back(carry);
        }
        std::swap(number, new_number);
        return *this;
    }

    LongInt& operator-=(const LongInt& other) {
        LongInt rhs = other.copy();
        LongInt lhs = this->copy();
        normalize(lhs, rhs);
        if (lhs.is_negative() && !rhs.is_negative()) {
            rhs.negative = 1;
            rhs += lhs;
            swap(*this, rhs);
            return *this;
        }
        if (!lhs.is_negative() && rhs.is_negative()) {
            rhs.negative = 0;
            lhs += rhs;
            swap(*this, lhs);
            return *this;
        }
        if (lhs.is_negative() && rhs.is_negative()) {
            rhs.negative = 0;
            lhs.negative = 0;
            swap(lhs, rhs);
        }
        negative = (lhs < rhs);
        if (negative) {
            swap(lhs, rhs);
        }
        deque <int> new_number(lhs.size());
        int carry = 0;
        for (size_t i = 0; i < lhs.size(); i++) {
            ll temp = 1ll * lhs.number[i] - carry - rhs.number[i];
            carry = 0;
            if (temp < 0) {
                carry = 1;
                temp += base;
            }
            new_number[i] = temp;
        }
        while (new_number.size() > 1 && !new_number.back()) {
            new_number.pop_back();
        }
        std::swap(number, new_number);
        return *this;
    }

    LongInt& operator*=(const int& other) {
        negative = (*this).is_negative() ^ (other < 0);
        deque <int> new_number(size());
        int carry = 0;
        for (size_t i = 0; i < size(); i++) {
            ll temp = 1ll * number[i] * other + carry;
            new_number[i] = temp % base;
            carry = temp / base;
        }
        if (carry) {
            new_number.push_back(carry);
        }
        while (new_number.size() > 1 && !new_number.back()) {
            new_number.pop_back();
        }
        std::swap(number, new_number);
        return *this;
    }

    LongInt& operator*=(const LongInt& other) {
        negative = (*this).is_negative() ^ other.is_negative();
        LongInt rhs = other.copy();
        LongInt lhs = this->copy();
        if (lhs.number.size() < rhs.number.size()) {
            swap(lhs, rhs);
        }
        LongInt res(0);
        for (int i = 0; i < rhs.number.size(); i++) {
            LongInt temp = lhs * rhs.number[i];
            for (int j = 0; j < i; j++) {
                temp.number.push_front(0);
            }
            res += temp;
        }
        swap(res);
        return *this;
    }

    LongInt& operator%=(const int& other) {
        pair <LongInt, int> res = div_mod(*this, other);
        LongInt temp(res.second * (is_negative() ? -1 : 1));
        swap(temp);
        return *this;
    }

    LongInt& operator/=(const int& other) {
        negative = (*this).is_negative() ^ (other < 0);
        pair <LongInt, int> res = div_mod(*this, abs(other));
        swap(res.first);
        return *this;
    }

    pair <LongInt, int> div_mod(LongInt& left, int rhs) {
        LongInt lhs = left.copy();
        int carry = 0;
        for (int i = lhs.number.size() - 1; i >= 0; i--) {
            ll temp = lhs.number[i] + 1ll * carry * base;
	        lhs.number[i] = temp / rhs;
	        carry = temp % rhs;
        }
        while (lhs.number.size() > 1 && !lhs.number.back()) {
            lhs.number.pop_back();
        }
        return make_pair(lhs, carry);
    }

    void swap(LongInt& other) {
        std::swap(number, other.number);
        std::swap(negative, other.negative);
    }

    void swap(LongInt& lhs, LongInt& rhs) {
        lhs.swap(rhs);
    }

    friend bool operator<(const LongInt& left, const LongInt& right) {
        if (left.negative && !right.negative) return true;
        if (!left.negative && right.negative) return false;
        int i = max(left.size(), right.size()) - 1;
        while (i >= 0) {
            int l = (i < left.size()) ? left.number[i] : 0;
            int r = (i < right.size()) ? right.number[i] : 0;
            if (left.negative) {
                if (l > r) return true;
                if (l < r) return false;
            } else {
                if (l < r) return true;
                if (l > r) return false;
            }
            i--;
        }
        return 0;
    }

    friend bool operator==(const LongInt& left, const LongInt& right) {
        if (left.negative != right.negative) return false;
        int i = max(left.size(), right.size()) - 1;
        while (i >= 0) {
            int l = (i < left.size()) ? left.number[i] : 0;
            int r = (i < right.size()) ? right.number[i] : 0;
            if (l < r) {
                return 0;
            } else if (l > r) {
                return 0;
            }
            i--;
        }
        return 1;
    }

    friend LongInt operator+(const LongInt& left, const LongInt& right) {
        LongInt result = left;
        result += right;
        return result;
    }

    friend LongInt operator-(const LongInt& left, const LongInt& right) {
        LongInt result = left;
        result -= right;
        return result;
    }

    friend LongInt operator*(const LongInt& left, const int& right) {
        LongInt result = left;
        result *= right;
        return result;
    }

    friend LongInt operator*(const LongInt& left, const LongInt& right) {
        LongInt result = left;
        result *= right;
        return result;
    }

    friend LongInt operator/(const LongInt& left, const int& right) {
        LongInt result = left;
        result /= right;
        return result;
    }

    friend LongInt operator%(const LongInt& left, const int& right) {
        LongInt result = left;
        result %= right;
        return result;
    }

    friend std::ostream& operator<<(std::ostream& os, const LongInt& num) {
        if (num.negative) {
            os << "-";
        }

        if (!num.number.empty()) {
            os << num.number.back();
        } else {
            os << "0";
            return os;
        }

        for (int i = num.number.size() - 2; i >= 0; i--) {
            os.width(base_len);
            os.fill('0');
            os << num.number[i];
        }

        return os;
    }

    private:
        void normalize(LongInt& left, LongInt& right) {
            while (left.size() > right.size()) {
                right.number.push_back(0);
            }
            while (left.size() < right.size()) {
                left.number.push_back(0);
            }
        }
};
