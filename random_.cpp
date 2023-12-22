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

int get_random_decision() {
    int y = rand() % 1;
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

void random_iterations() {
    /*
    Providing the resources randomly, as we need every iteration to be executed randomly.
    */
   unordered_map<int,int> clusters_map;
    
    while(clusters_map.size() < battle_clusters){
        //print_resource_request();
        int i = rand() % battle_clusters;
        if(clusters_map.find(i)!=clusters_map.end())
            continue;
        
        clusters_map[i] = 1;
        int sum = accumulate(resource_request[i].begin(),resource_request[i].end(),0);

        unordered_map<int,int> uav_map;

        while(sum>0) {
            bool flag = 0;
            int k = rand() % uavs;
            if(uav_map.find(k)!=uav_map.end())
                continue;
            uav_map[k] = 1;

            for(int j=0; j<resources; j++) {
                if(resource_request[i][j]==1) {
                    if(uav_capacity[k][j]==1) {
                        resource_request[i][j] = 0;
                        flag = 1;
                    }
                }
            }
            if(flag) {
                um[i].push_back(k+1);
                time_taken[i] += round_trip_service_time[k][i];
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

    random_iterations();

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
