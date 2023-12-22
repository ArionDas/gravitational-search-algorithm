#include<bits/stdc++.h>
using namespace std;
#define new_line cout<<endl;

const int battle_clusters = 6;
const int resources = 8;
const int uavs = 5;

vector<vector<int>> resource_request;
vector<vector<int>> uav_capacity;
vector<vector<int>> round_trip_service_time(uavs, vector<int> (battle_clusters,0));
vector<int> time_taken(battle_clusters,0);
vector<pair<int,int>> time_required(battle_clusters);

unordered_map<int,vector<int>> um;

int generateRandomInt() {
    int y = rand() % 100;
    return y;
}

void provide_resource_requests() {
    for(int i=0; i<battle_clusters; i++) {
        vector<int> temp;
        cout << "Enter resource request for W - " << i+1; 
        new_line;
        for(int j=0; j<resources; j++) {
            int x;
            cin>>x;
            temp.push_back(x);
        }
        resource_request.push_back(temp);
    }
}

void provide_uav_capacity() {
    for(int i=0; i<uavs; i++) {
        vector<int> temp;
        cout << "Enter uav capacity for UAV - " << i+1;
        new_line;
        for(int j=0; j<resources; j++) {
            int x;
            cin>>x;
            temp.push_back(x);
        }
        uav_capacity.push_back(temp);
    }
}

void get_round_trip_service_time() {
    for (int i = 0; i < uavs; i++) {
        for (int j = 0; j < battle_clusters; j++) {
            round_trip_service_time[i][j] = generateRandomInt();
        }
    }
}

void print_resource_request() {
    new_line;
    for(int i=0; i<battle_clusters; i++) {
        for(int j=0; j<resources; j++) {
            cout << resource_request[i][j] << " ";
        }
        cout << endl;
    }
    new_line;
}

void calculate_time_required() {
    for(int i=0; i<uavs; i++) {
        cout << "hey" << endl;
        for(int j=0; j<battle_clusters; j++) {
            time_required[j].first += round_trip_service_time[i][j];
            time_required[j].second = j;
            cout << "hi" << " ";
        }
    }
    sort(time_required.begin(),time_required.end());
}

void shortest_job_first() {
    /*
    Tackling the places in a customized order to address the place taking the shortest time first.
    */
    cout << "Order of resolving the battle clusters : ";
    for(int m=0; m<time_required.size(); m++) {
        //print_resource_request();
        bool flag = 0;
        int i = time_required[m].second;
        int sum = accumulate(resource_request[i].begin(),resource_request[i].end(),0);
        cout << i << " " << endl;
        while(sum>0) {
            for(int j=0; j<resources; j++) {
                if(resource_request[i][j]==1) {
                    int k=0;
                    for(; k<uavs; k++) {
                        if(uav_capacity[k][j]==1) {
                            um[i].push_back(k+1);
                            resource_request[i][j] = 0;
                            time_taken[i] += round_trip_service_time[k][i];
                            break;
                        }
                    }
                    if(k!=uavs) {
                        for(; j<resources; j++) {
                            if(resource_request[i][j]==1 && uav_capacity[k][j]==1) {
                                resource_request[i][j] = 0;
                            }
                        }
                    }
                }
            }
            sum = accumulate(resource_request[i].begin(),resource_request[i].end(),0);
        }
    }
}

int main() {

    srand(time(0));

    provide_resource_requests();
    provide_uav_capacity();
    get_round_trip_service_time();
    calculate_time_required();

    print_resource_request();

    cout << "The round service time is represented by the matrix : " << endl;
    for(int i=0; i<uavs; i++) {
        for(int j=0; j<battle_clusters; j++)
            cout << round_trip_service_time[i][j] << " ";
        new_line;
    }

    new_line;
    shortest_job_first();
    new_line;
    
    for(int i=0; i<battle_clusters; i++) {
        cout << "Battle Cluster - " << i+1 << " : ";
        for(auto x:um[i]) {
            cout << x << " ";
        }
        new_line;
    }

    new_line;
    for(int i=0; i<battle_clusters; i++) {
        cout << "Time taken by Battle Cluster - " << i+1 << " : " << time_taken[i] << endl;
    }
    new_line;
    cout << "Maximum time required for a battle cluster is : " << *max_element(time_taken.begin(),time_taken.end());
    new_line;

    //print_resource_request();
    return 0;
}
