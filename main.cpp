#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

double N = 13;
double epsilon = 0.3;
double left_limit = -2.5;
double right_limit = 1.5;

double Function(const double x)
{
    return -0.5*cos(0.5*x)+1;
}
int64_t Fibonacci(const size_t &n )
{
    if (n < 1)
    {
        return 0;
    }
    int64_t f1 = 0 , f2 = 1, fn = 0;
    for ( size_t  i = 1; i < n; ++i )
    {
        fn = f1 + f2;
        f1 = f2;
        f2 = fn;
    }
    return fn;
}
vector<double> Fibonacci_values(double& left, double& right, size_t n)
{
    vector<double> values;
    double  x1 = left + (right - left) * Fibonacci(n) / Fibonacci(n + 2);
    double  x2 = left + right - x1;
    double  s1 = Function(x1);
    double  s2 = Function(x2);
    while (n--)
    {
        if (Function(x1) > Function(x2))
        {
            left= x1;
            x1 = x2;
            x2 = right - (x1 - left);
            s1 = s2;
            s2 = Function(x2);
            values.push_back(x2);
        }
        else
        {
            right= x2;
            x2 = x1;
            x1 = left + (right - x2);
            s2 = s1;
            s1 = Function(x1);
            values.push_back(x1);
        }
    }
    return values;
}
vector<pair<double, double>> Optimal_passive_search(const double& left, const double& right, const double& epsilon)
{
    vector<pair<double, double>> values;
    size_t N = 1;
    double delta = (right - left) / (N + 1);
    double min;
    while (delta > epsilon)
    {
        vector<double>Values;
        delta = (right - left) / (N + 1);
        for (size_t k = 1; k <= N; ++k)
        {
            Values.push_back(Function((right - left) / (N + 1) * k + left));
        }
        size_t Min = min_element(Values.begin(), Values.end()) - Values.begin() + 1;
        min= (right - left) / (N + 1) * Min + left;
        values.push_back({ min, delta });
        N++;
    }
    return values;
}
void PrintPart1 (const vector<pair<double, double>>& values)
{
    cout << "Part 1  Optimal_passive_search:"<<endl
         << string(39, '_') << endl
         << '|' << string(4, ' ') << "Number of" << string(3, ' ')
         << '|' << string(3, ' ') << "The value of X" << string(3, ' ') <<"|"<<endl
         << '|' << string(1, ' ') << "the points (N)" << string(1, ' ')
         << '|' << string(3, ' ') << "in the minimum" << string(3, ' ') << "|"<<endl
         << std::string(39, '_') << endl;
    for (size_t i = 0; i < values.size(); i++)
    {
        cout << "|" << setw(9) << i + 1 <<string(7,' ')<< "|" << setw(20)<< to_string(values[i].first) + "+-" + to_string(values[i].second) << "|" << endl;
    }
    cout << string (39, '-') << endl;
}
void PrintPart2 (const vector<double>& values)
{
    cout << "Part 2  Fibonacci_metod:" << endl
         << string(39, '_') << endl
         << '|' << string(3, ' ') << "Number of" << string(3, ' ') << " "
         << '|' << string(3, ' ') << "Fibonacci_metod" << string(2, ' ') << "|" << endl
         << '|' << string(1, ' ') << "the points (N)" << string(1, ' ')
         << '|' << string(1, ' ') << "  the value of X" << string(3, ' ') << "|"<<endl
         << string(39, '_') << endl;
    for (size_t i = 0; i < values.size(); i++)
    {
        cout << "|"  <<setw(9) << i + 1<<string (7,' ')<< "|" <<string(6,' ')<< setw(14) <<setprecision(9) << values[i] << "|" << endl;
    }
    cout << string (39, '-') << endl<< "Minimum value: " << values[values.size()-1] << endl;
}
int main()
{
    cout<<"Variant 9 "<<endl<<"Function: -0.5*cos(0.5*x)+1, interval: [-2.5,1,5] "<<endl;
    vector<pair<double,double>> Optimal_passive_search_metod = Optimal_passive_search(left_limit, right_limit, epsilon);
    PrintPart1(Optimal_passive_search_metod);
    cout<<endl;
    vector<double> Fibonacci_metod  = Fibonacci_values(left_limit, right_limit, N);
    PrintPart2(Fibonacci_metod);
    cout<<endl;
}

