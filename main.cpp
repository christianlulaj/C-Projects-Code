#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <numeric>

//using namespace std;
using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::stringstream;
using std::min;
using std::accumulate;

// split a string into a vector of words
vector<string> split(string str) {
    vector<string> result;
    stringstream ss(str);
    string substring;
    while (ss >> substring) result.push_back(substring);
    return result;
}

// concatenate a vector of strings into a single string with spaces in-between
string join(vector<string> words) {
    if (words.empty()) return "";
    auto join_two = [] (string s1, string s2) -> string {
        return s1 + " " + s2;
    };
    return accumulate(next(words.begin()), words.end(), words.front(), join_two);
}

// return the number of characters at the end of s1 and the beginning of s2 that match
int num_matching_chars(string s1, string s2) {
    int s1_len = s1.size();
    int s2_len = s2.size();
    int max_len = min(s1_len, s2_len);
    for (int num = max_len; num > 0; --num) { // num goes from max_len to 1
        if (s1.substr(s1_len - num) == s2.substr(0, num)) return num;
    }
    return 0;
}

// squeeze a pair of words if they have
// identical beginning and ending (respectively) character sequences
vector<string> squeeze_words(string s1, string s2) {
    vector<string> result;
    int matching_char_count = num_matching_chars(s1, s2);
    if (matching_char_count == 0) {
        result.push_back(s1);
        result.push_back(s2);
    } else {
        result.push_back(s1 + s2.substr(matching_char_count));
    }
    return result;
}

// squeeze all squeezable words on a line
string squeeze_line(string line) {
    vector<string> words = split(line);
    auto it = words.begin();
    while (it != words.end() && next(it) != words.end()) {
        string s1 = *it;
        string s2 = *next(it);
        vector<string> squeezed = squeeze_words(s1, s2); // returns vector of 1 or 2 strings
        *it = squeezed[0];
        if (squeezed.size() == 1) {
            words.erase(next(it));
        } else {
            *next(it) = squeezed[1];
            ++it;
        }
    }
    return join(words);
}


int main() {
    string str;
    while (getline(cin, str)) {
        if (str.empty()) continue;
        cout << squeeze_line(str) << endl;
    }
    return 0;
}