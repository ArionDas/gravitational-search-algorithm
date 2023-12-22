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
    new_line;
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

void first_come_first_serve() {
    /*
    Providing the resources to battle clusters serially, as we need the request coming first to be executed first.
    */
    for(int i=0; i<battle_clusters; i++) {
        //print_resource_request();
        bool flag = 0;
        int sum = accumulate(resource_request[i].begin(),resource_request[i].end(),0);

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

    print_resource_request();

    cout << "The round service time is represented by the matrix : " << endl;
    for(int i=0; i<uavs; i++) {
        for(int j=0; j<battle_clusters; j++)
            cout << round_trip_service_time[i][j] << " ";
        new_line;
    }
    new_line;

    first_come_first_serve();

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

    cout << "Maximum time required for a battle cluster is : " << *max_element(time_taken.begin(),time_taken.end());
    new_line;

    //print_resource_request();
    return 0;
}

/*

INPUT:
1 1 1 0 0 1 0 0
1 1 0 0 1 0 0 1
0 1 1 1 0 1 1 0
0 0 1 1 1 1 1 1
1 0 0 1 1 0 1 1
0 0 1 1 0 0 0 1
1 1 0 0 1 1 0 0
0 1 0 1 1 1 0 1
1 0 1 0 0 1 0 0
1 1 0 1 1 1 0 1
0 1 1 1 0 1 1 1

*/
