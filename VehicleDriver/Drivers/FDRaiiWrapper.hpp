#pragma  once

struct FDRaiiWrapper
{
    FDRaiiWrapper();
    explicit FDRaiiWrapper(int, void(*deleter)(int));
    FDRaiiWrapper(FDRaiiWrapper&&) noexcept;
    FDRaiiWrapper& operator=(FDRaiiWrapper&&) noexcept;
    ~FDRaiiWrapper();

    int get() const;
private:
    void conditionallyClose();
    int fd_ = -1;
    void(*deleter_)(int) = nullptr;
};
