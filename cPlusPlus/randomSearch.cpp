#include <iostream>
#include <vector>
#include <utility>
#include <random>
#include <functional>

using namespace std;

// Function we optimize
double objective(const vector<double>& inputX) {
    return(100 - (((inputX[0] + 1) * (inputX[1] + 1)) * ((inputX[2] + 2) * (inputX[3] + 1)) + inputX[4]));
}

vector<double> randomVector(const vector<pair<double, double>>& bounds) {
    vector<double> result(bounds.size());

    static random_device rd;        
    static mt19937 gen(rd());        

    for (size_t i = 0; i < bounds.size(); i++) {
        double low = bounds[i].first;
        double high = bounds[i].second;

        uniform_real_distribution<double> dist(low, high);
        result[i] = dist(gen);
    }

    return(result);
}

void printVector(const vector<double>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) {
        cout << v[i];
        if (i + 1 < v.size()) cout << ", ";
    }
    cout << "]";
}

vector<double> randomSearch(
    std::function<double(const vector<double>&)> objective,
    int numIterations
){
    vector<pair<double, double>> ranges = {{-10,10}, {-10,10}, {-10,10}, {-10,10}, {-10,10}};
    vector<double> bestX = randomVector(ranges);
    double bestY = objective(bestX);

    vector<double> newX;
    double newY;
    for (int i = 0; i < numIterations; i++){
        newX = randomVector(ranges);
        newY = objective(newX);
        if (newY > bestY){
            bestY = newY;
            bestX = newX;
        }
    }
    return bestX;
}

int main(){
    int numIterations = 10000;
    vector<double> bestX = randomSearch(objective, numIterations);
    printVector(bestX);
}