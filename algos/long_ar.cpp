struct LongInt {
    const int base = 1e8;
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
            int temp = lhs.number[i] + rhs.number[i] + carry;
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
            swap(lhs, rhs);
        }
        negative = (lhs < rhs);
        if (negative) {
            swap(lhs, rhs);
        }
        deque <int> new_number(lhs.size());
        int carry = 0;
        for (size_t i = 0; i < lhs.size(); i++) {
            new_number[i] = lhs.number[i] - carry - rhs.number[i];
            if (new_number[i] < 0) {
                carry = 1;
                new_number[i] += base;
            }
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
        swap(*this, res);
        return *this;
    }

    void swap(LongInt& other) {
        std::swap(number, other.number);
        std::swap(negative, other.negative);
    }

    void swap(LongInt& lhs, LongInt& rhs) {
        lhs.swap(rhs);
    }

    friend bool operator<(const LongInt& left, const LongInt& right) {
        int i = max(left.size(), right.size()) - 1;
        while (i >= 0) {
            int l = (i < left.size()) ? left.number[i] : 0;
            int r = (i < right.size()) ? right.number[i] : 0;
            if (l < r) {
                return 1;
            } else if (l > r) {
                return 0;
            }
            i--;
        }
        return 0;
    }

    friend bool operator==(const LongInt& left, const LongInt& right) {
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
            os.width(8); 
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