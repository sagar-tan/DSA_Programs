#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>

using namespace std;

struct Event {
    string type;
    int timestamp;
    vector<string> data;
    int originalIndex;

    Event(const vector<string>& eventData, int index) {
        type = eventData[0];
        timestamp = stoi(eventData[1]);
        data = vector<string>(eventData.begin() + 2, eventData.end());
        originalIndex = index;
    }
};

class Solution {
public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        vector<Event> eventList;

        for (int i = 0; i < events.size(); i++) {
            eventList.emplace_back(events[i], i);
        }

        sort(eventList.begin(), eventList.end(), [](const Event& a, const Event& b) {
            if (a.timestamp != b.timestamp) {
                return a.timestamp < b.timestamp;
            }
            bool aOffline = (a.type == "OFFLINE");
            bool bOffline = (b.type == "OFFLINE");
            if (aOffline != bOffline) {
                return aOffline;
            }
            return a.originalIndex < b.originalIndex;
        });

        vector<int> mentions(numberOfUsers, 0);
        vector<int> offlineUntil(numberOfUsers, 0);

        for (const auto& event : eventList) {
            string type = event.type;
            int timestamp = event.timestamp;
            const vector<string>& data = event.data;

            if (type == "OFFLINE") {
                int userId = stoi(data[0]);
                offlineUntil[userId] = timestamp + 60;
            } else if (type == "MESSAGE") {
                string mentionsStr = data[0];
                stringstream ss(mentionsStr);
                string token;
                while (ss >> token) {
                    if (token == "ALL") {
                        for (int i = 0; i < numberOfUsers; i++) {
                            mentions[i]++;
                        }
                    } else if (token == "HERE") {
                        for (int i = 0; i < numberOfUsers; i++) {
                            if (timestamp >= offlineUntil[i]) {
                                mentions[i]++;
                            }
                        }
                    } else if (token.rfind("id", 0) == 0) { // Check if token starts with "id"
                        int userId = stoi(token.substr(2));
                        if (userId >= 0 && userId < numberOfUsers) {
                            mentions[userId]++;
                        }
                    }
                }
            }
        }

        return mentions;
    }
};
int main() {
    Solution s;

    // Test case 1
    vector<vector<string>> events1 = {
        {"MESSAGE", "2", "HERE"},
        {"OFFLINE", "2", "1"},
        {"OFFLINE", "1", "0"},
        {"MESSAGE", "61", "HERE"}
    };
    vector<int> result1 = s.countMentions(3, events1);
    for (int mention : result1) cout << mention << " ";
    cout << endl; // Expected: [1, 0, 2]

    // Test case 2
    vector<vector<string>> events2 = {
        {"MESSAGE", "10", "id1 id0"},
        {"OFFLINE", "11", "0"},
        {"MESSAGE", "12", "ALL"}
    };
    vector<int> result2 = s.countMentions(2, events2);
    for (int mention : result2) cout << mention << " ";
    cout << endl; // Expected: [2, 2]

    // Test case 3
    vector<vector<string>> events3 = {
        {"OFFLINE", "10", "0"},
        {"MESSAGE", "12", "HERE"}
    };
    vector<int> result3 = s.countMentions(2, events3);
    for (int mention : result3) cout << mention << " ";
    cout << endl; // Expected: [0, 1]

    return 0;
}