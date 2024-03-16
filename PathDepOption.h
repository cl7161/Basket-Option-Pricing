#pragma once

#include "MCModel.h"

namespace fre {
    class PathDepOption
    {
    protected:
        double Price;
        double T;
        double K;
        int m;
        int d;
        Vector Delta;
    public:
        PathDepOption(double T_, double K_, int m_, int d_) : Price(0.0), T(T_), K(K_), m(m_), d(d_), Delta(d,0.0) {}
        double PriceByMC(MCModel& Model, long N, double epsilon);
        virtual ~PathDepOption() {}
        virtual double Payoff(const SamplePath& S) const = 0;
        Vector GetDelta(){return Delta;}
    };

    class ArthmAsianCall : public PathDepOption
    {
    public:
        ArthmAsianCall(double T_, double K_, int m_, int d_) : PathDepOption(T_, K_, m_, d_) {}
        double Payoff(const SamplePath& S) const;
    };
}

