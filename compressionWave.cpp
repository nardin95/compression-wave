#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

int main () {
    ifstream file_in;
    string file_name = "tek0015CH3.csv";
    string garb;
    char c = ',';

    //cout << "Enter the name of the file to open: ";
    //cin >> file_name;
    
    file_in.open(file_name.c_str());
        if (file_in.fail()) {
            cout << "Unable to find a file with the name " << file_name << endl;
            exit(1);
        }
    int binSize = 500;
    //cout << "Bin size: ";
    //cin >> binSize;
    double t[50000];
    double v[50000];
    
    ofstream file_out;
    string outputName;
    cout << "Enter a name for your output file: ";
    cin >> outputName;
    file_out.open(outputName.c_str());
    file_out << "time,peak,\n";
    //int lines = 500000;
    //cout << "Number of data points to analyze(int multiple of bin size):";
    //cin >> lines;
    
    //int repeat = lines/binSize;
    bool stopCounting = false;
    int peaks = 0;
    
    for (int i = 0; i < 20; i++) {
        file_in >> garb >> c >> garb;
    }
    double garbT, garbV;
    file_in >> garbT >> c >> garbV;
    while (garbT < 0) {
        file_in >> garbT >> c >> garbV;
    }
    for (int j = 0; j < 10; j++) {
        
        double v_tot = 0;
        double v_max = -100;
        double v_min = 100;    
            
        for (int i = 0; i < 50000; i++) {
            file_in >> t[i] >> c >> v[i];
            v_tot = v_tot + v[i];
            if (v[i] > v_max) {
                v_max = v[i];
            }
            if (v[i] < v_min) {
                v_min = v[i];
            }
        }

        double v_ave = v_tot /50000.0000;
        //double time_passed = t[binSize-1]; 
        double th_up = v_ave + 0.2 * (v_max - v_ave);
        double th_down = v_ave - 0.2 * (v_ave - v_min);
        
        for (int m = 0; m < 100; m++) {
            for (int n = 0; n < binSize; n++) {
                if ((v[500*m+n] > th_up) && (stopCounting == false) ) {
                    stopCounting = true;
                    peaks++;
                }
                if ((v[500*m+n] < th_down) && (stopCounting == true) ) {
                    stopCounting = false;
                    peaks++;
                }
            }
            double time_passed = t[500*m+500];
            cout << time_passed << "\t" << peaks << endl;
            file_out << time_passed << c << peaks << endl;
        }
    }
    
    return 0;
}
