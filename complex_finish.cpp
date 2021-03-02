//
//  Complex.cpp
//  潮流计算
//
//  Created by 张頔 on 2019/5/9.
//  Edition 2019/5/15
//  Copyright © 2019年 CIEE. All rights reserved.
//

#include <iostream>
#include "complex.h"
#include <cmath>
#define epsilon 1e-5
#define SIZE 5 
using namespace std;

int main()
{
    int n;
    cin >> n;
    double g[SIZE][SIZE]; 
    double b[SIZE][SIZE];
    for (int i=0; i<n; i++)
    {
        for (int j=0; j<n; j++)
        {
            cin >> g[i][j] >> b[i][j];
        }
    }
    
    double p[SIZE];
    double q[SIZE];
    for (int i=0; i<n; i++)
    {
        cin >> p[i] >> q[i];
    }

    double c[SIZE]; // Ge - Bf = c
    double d[SIZE]; // Gf + Be = d
    double e[SIZE]; // X-axis
    double f[SIZE]; // Y-axis

    for (int i=0; i<n; i++)
    {
        // initializing e & f
        e[i] = 1.0;
        f[i] = 0.0;
    }
    e[n-1] = p[n-1];

    double dp[SIZE];
    double dq[SIZE];
    double def[2*SIZE];
    double dpq[2*SIZE];
    double Jacob[2*SIZE][2*SIZE];
    
    while (true)
    {
        int i=0;
        for (i=0; i<n; i++)
        {
            c[i] = 0;
            d[i] = 0;
            for (int j=0; j<n; j++)
            {
                c[i] += g[i][j]*e[j] - b[i][j]*f[j];
                d[i] += g[i][j]*f[j] + b[i][j]*e[j];
            }
        }
        for (i=0; i<n-1; i++)
        {
            dp[i] = p[i] - e[i]*c[i] - f[i]*d[i];
            dq[i] = q[i] - f[i]*c[i] + e[i]*d[i];
        }
        for (i=0; i<n-1; i++)
        {
            dpq[2*i] = dp[i];
            dpq[2*i+1] = dq[i];
        }

        int flag = 0;
        for (i=0; i<n-1; i++)
        {
            if (fabs(dp[i]) >= epsilon || fabs(dq[i]) >= epsilon)
            {
                // printf("%lf %lf\n", e[i], f[i]);
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            break;
        }

        for (i=0; i<n-1; i++)
        {
            for (int j=0; j<n-1; j++)
            {
                double H, L, N, M;
                // double R, S;
                if (i != j)
                {
                    H = b[i][j]*e[i] - g[i][j]*f[i];
                    L = H;
                    M = g[i][j]*e[i] + b[i][j]*f[i];
                    N = -M;
                }
                else
                {
                    H = -d[i] - (g[i][i]*f[i] - b[i][i]*e[i]);
                    N = -c[i] - (g[i][i]*e[i] + b[i][i]*f[i]);
                    M = -c[i] + (g[i][i]*e[i] + b[i][i]*f[i]);
                    L = d[i] - (g[i][i]*f[i] - b[i][i]*e[i]); 
                }
                Jacob[2*i][2*j] = H;
                Jacob[2*i][2*j+1] = N;
                Jacob[2*i+1][2*j] = M;
                Jacob[2*i+1][2*j+1] = L;
            }
        }

        for (int i=0; i<2*(n-1); i++)
        {
            for (int j=i+1; j<2*(n-1); j++)
            {
                if (Jacob[j][i] == 0)
                    continue;
                double proportion = Jacob[j][i] / Jacob[i][i];
                Jacob[j][i] = 0;
                for (int k=i+1; k<2*(n-1); k++)
                {
                    Jacob[j][k] -= Jacob[i][k] * proportion;
                }
                dpq[j] -= dpq[i] * proportion;
            }
        }
        // for (i=0; i<2*(n-1); i++)
        //     printf("%lf ", dpq[i]);
        //     printf("\n");
        // break;
        for (int i=2*(n-1)-1; i>=0; i--)
        {
            for (int j=2*(n-1)-1; j>i; j--)
            {
                dpq[i] -= Jacob[i][j] * Jacob[j][j];
            }
            Jacob[i][i] = dpq[i] / Jacob[i][i];
            def[i] = Jacob[i][i];
        }
        // for (int i=0; i<2*(n-1); i++)
        // {
        //     printf("%lf ", def[i]);
        // }
        // break;
        for (int i=0; i<2*(n-1); i++)
        {
            if (i%2 == 0)
            {
                f[i/2] -= def[i];
            }
            else
            {
                e[i/2] -= def[i];
            }
        }
        // for (int i=0; i<n-1; i++)
        // {
        //     printf("%lf %lf\n", e[i], f[i]);
        // }
        // break;
    }

    // for (int i=0; i<2*(n-1); i++)
    // {
    //     for (int j=0; j<2*(n-1); j++)
    //     {
    //         printf("%8.2f ", Jacob[i][j]);
    //     }
    //     printf("\n");
    // }

    for (int i=0; i<n; i++)
    {
        c[i] = 0;
        d[i] = 0;
        for (int j=0; j<n; j++)
        {
            c[i] += g[i][j]*e[j] - b[i][j]*f[j];
            d[i] += g[i][j]*f[j] + b[i][j]*e[j];
        }
    }
    p[n-1] = e[n-1]*c[n-1] + f[n-1]*d[n-1];
    q[n-1] = f[n-1]*c[n-1] - e[n-1]*d[n-1];

    Complex u[SIZE];
    Complex s[SIZE][SIZE];
    Complex y[SIZE][SIZE];
    Complex y0[SIZE][SIZE];
    Complex ds[SIZE][SIZE];
    for (int i=0; i<n; i++)
    {
        u[i].input(e[i], f[i]);
    }
    // y的初始化
    for (int i=0; i<n; i++)
    {
        for (int j=i; j<n; j++)
        {
            double t1, t2;
            cin >> t1 >> t2;
            y[i][j].input(t1, t2);
            y[j][i].input(t1, t2);
        }
    }
    for (int i=0; i<n; i++)
    {
        for (int j=i; j<n; j++)
        {
            double t1, t2;
            cin >> t1 >> t2;
            y0[i][j].input(t1, t2);
            y0[j][i].input(t1, t2);
        }
    }
    for (int i=0; i<n; i++)
    {
        for (int j=i+1; j<n; j++)
        {
            s[i][j] = u[i]*(u[i]*y0[i][j] + (u[i] - u[j])*y[i][j]).conjugate();
            s[j][i] = u[j]*(u[j]*y0[j][i] + (u[j] - u[i])*y[i][j]).conjugate();
            ds[i][j] = s[i][j] + s[j][i];
        }
    }
    cout << "------------------------------------------------" << endl;
    cout << "          U           d           e           f      " << endl;
    for (int i=0; i<n; i++)
    {
        u[i].getNum();
    }
    cout << "------------------------------------------------" << endl;
    printf("P%d+jQ%d = ", n-1, n-1);
    printf("%lf+j%lf\n", p[n-1], q[n-1]);
    cout << "------------------------------------------------" << endl;
    for (int i=0; i<n; i++)
    {
        for (int j=i+1; j<n; j++)
        {
            if (s[i][j].getLen() < epsilon)
                continue;
            printf("P%d%d+jQ%d%d=",i+1,j+1,i+1,j+1);
            s[i][j].display_rmPart();
            printf("P%d%d+jQ%d%d=",j+1,i+1,j+1,i+1);
            s[j][i].display_rmPart();
            printf("δS%d%d=",i+1, j+1);
            ds[i][j].display_rmPart();
            printf("\n");
        }
    }
    cout << "------------------------------------------------" << endl;
    return 0;
}