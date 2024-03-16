#include "PathDepOption.h"
#include <cmath>

namespace fre {
    void Rescale(SamplePath& S, double x, int j)
    {
        int m = S.size();
        for (int k=0; k<m; k++) S[k][j] = S[k][j] * x;
    }
    
    
    double PathDepOption::PriceByMC(MCModel& Model, long N, double epsilon)
    {
        double H = 0.0;
        SamplePath S(m);
        
        // HW12
        Vector Heps(d,0.0);
        // Delta.resize(d,0.0);
        

        for (long i = 0; i < N; i++)
        {
            Model.GenerateSamplePath(T, m, S);
            H = (i * H + Payoff(S)) / (i + 1.0);
            
            
            // HW12: Delta
            Rescale(S, 1.0 + epsilon, 0);
            Heps[0] = (i * Heps[0] + Payoff(S)) / (i + 1.0);
            for (int j = 1; j < d; j++)
            {
                Rescale(S, 1.0/(1.0 + epsilon), j-1);
                Rescale(S, 1.0 + epsilon, j);
                Heps[j] = (i * Heps[j] + Payoff(S)) / (i + 1.0);
            }
            
            
        }
        Price = std::exp(-Model.GetR() * T) * H;
        
        //Delta
        for (int j = 0; j < d; j++)
        {
            Delta[j] = std::exp(-Model.GetR()*T)*(Heps[j]-H)/(Model.GetS0()[j]*epsilon);
        }
        
        return Price;
    }

    double ArthmAsianCall::Payoff(const SamplePath& S) const
    {
        double Ave = 0.0;
        int d = S[0].size();
        Vector one(d);
        for (int i = 0; i < d; i++) one[i] = 1.0;
        for (int k = 0; k < m; k++)
        {
            Ave = (k * Ave + (one ^ S[k])) / (k + 1.0);
        }
        if (Ave < K) return 0.0;
        return Ave - K;
    }
}
