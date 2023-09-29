#pragma  once

struct FDRaiiWrapper
{
    FDRaiiWrapper();
    explicit FDRaiiWrapper(int, void(*deleter)(int));
    FDRaiiWrapper(FDRaiiWrapper&&);
    FDRaiiWrapper& operator=(FDRaiiWrapper&&);
    ~FDRaiiWrapper();

    int get();
private:
    void conditionallyClose();
    int fd_;
    void(*deleter_)(int);
};
