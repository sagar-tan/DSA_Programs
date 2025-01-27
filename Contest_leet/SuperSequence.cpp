#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <climits>

using namespace std;

void generateAllSCS(vector<string>& words, int index, string current, unordered_set<string>& result);
string merge(const string& current, const string& word, int i, int j);
vector<int> computeFrequency(const string& scs);
string getFrequencyKey(const vector<int>& freq);

class Solution {
public:
    vector<vector<int>> supersequences(vector<string>& words) {
        unordered_set<string> allSCS;
        generateAllSCS(words, 0, "", allSCS);

        int minLength = INT_MAX;
        for (const auto& scs : allSCS) {
            if (scs.length() < minLength) {
                minLength = scs.length();
            }
        }

        unordered_set<string> minimalSCS;
        for (const auto& scs : allSCS) {
            if (scs.length() == minLength) {
                minimalSCS.insert(scs);
            }
        }

        unordered_map<string, vector<int>> freqMap;
        for (const auto& scs : minimalSCS) {
            vector<int> freq = computeFrequency(scs);
            string freqKey = getFrequencyKey(freq);
            if (freqMap.find(freqKey) == freqMap.end()) {
                freqMap[freqKey] = freq;
            }
        }

        vector<vector<int>> result;
        for (const auto& entry : freqMap) {
            result.push_back(entry.second);
        }
        return result;
    }
};

void generateAllSCS(vector<string>& words, int index, string current, unordered_set<string>& result) {
    if (index == words.size()) {
        result.insert(current);
        return;
    }

    string word = words[index];
    for (size_t i = 0; i <= current.length(); ++i) {
        for (size_t j = 0; j <= word.length(); ++j) {
            string merged = merge(current, word, i, j);
            generateAllSCS(words, index + 1, merged, result);
        }
    }
}

string merge(const string& current, const string& word, int i, int j) {
    return current.substr(0, i) + word + current.substr(i);
}

vector<int> computeFrequency(const string& scs) {
    vector<int> freq(26, 0);
    for (char c : scs) {
        freq[c - 'a']++;
    }
    return freq;
}

string getFrequencyKey(const vector<int>& freq) {
    string key;
    for (int f : freq) {
        key += to_string(f) + "#";
    }
    return key;
}

int main() {
    vector<string> words = {"ab", "ba"};
    Solution sol;
    vector<vector<int>> result = sol.supersequences(words);
    for (const auto& freq : result) {
        for (int f : freq) {
            cout << f << " ";
        }
        cout << endl;
    }
    return 0;
}
