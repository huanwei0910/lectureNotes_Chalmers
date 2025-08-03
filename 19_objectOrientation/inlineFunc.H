class inlineFunc
{
private:
    double value_;

public:
inlineFunc(double v) : value_(v) {}

    inline double getInlineFunc() const
    {
        return value_ * value_;
    }
};
