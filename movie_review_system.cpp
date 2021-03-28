#include <bits/stdc++.h>
using namespace std;

class Movie
{
public:
    string name;
    int year;
    vector<string> genre;
    float avg_review;
    float avg_critics_review;
    float num_reviews;
    float num_critics_reviews;
};

class User
{
public:
    string name;
    int level; // level 0 for user and level 1 for Critic
    map<string, int> rev;
};

int curr_year = 2020;

vector<User> users;
vector<Movie> movies;

void add_user(string us)
{
    User req_user;
    req_user.name = us;
    req_user.level = 0;
    map<string, int> m2;
    req_user.rev = m2;
    for (auto i : users)
    {
        if (i.name == us)
        {
            cout << "Error:" << endl;
            cout << "User " << us << "  already added." << endl;
            return;
        }
    }

    users.push_back(req_user);
    cout << "User " << us << " Added Successfully" << endl;
    return;
}

void add_movie(string mv, int yr, vector<string> gn)
{
    Movie req_movie;
    req_movie.name = mv;
    req_movie.year = yr;
    req_movie.genre = gn;
    req_movie.avg_critics_review = 0;
    req_movie.avg_review = 0;
    req_movie.num_reviews = 0;
    req_movie.num_critics_reviews = 0;

    for (auto i : movies)
    {
        if (i.name == mv)
        {
            cout << "Error:" << endl;
            cout << "Movie " << mv << " already added." << endl;
            return;
        }
    }
    movies.push_back(req_movie);
    cout << "Movie " << mv << " Added Successfully" << endl;
    return;
}

void add_review(string us, string mv, int val)
{
    User req_user;
    req_user.name = "Not_Available";
    for (auto &i : users)
    {
        if (i.name == us)
        {
            req_user = i;
            break;
        }
    }
    Movie req_movie;
    req_movie.name = "Not_Available";
    for (auto &i : movies)
    {
        if (i.name == mv)
        {
            req_movie = i;
            break;
        }
    }
    if (req_movie.name == "Not_Available" || req_user.name == "Not_Available")
    {
        cout << "Error:" << endl;
        cout << "User " << us << " or Movie " << mv << " not Available." << endl;
        return;
    }
    if (req_user.rev.find(req_movie.name) != req_user.rev.end())
    {
        cout << "Error:" << endl;
        cout << "Multiple Reviews for user (for same movie) " << us << " Detected" << endl;
        return;
    }
    if (curr_year < req_movie.year)
    {
        cout << "Error:" << endl;
        cout << "Movie " << mv << " yet to be released" << endl;
        return;
    }
    if (req_user.level == 1)
    {
        req_user.rev[mv] = 2 * val;
        req_movie.num_critics_reviews += 1;
        req_movie.num_reviews += 1;
        req_movie.avg_critics_review = (req_movie.avg_critics_review * (req_movie.num_critics_reviews - 1) + val) / (req_movie.num_critics_reviews);
        req_movie.avg_review = ((req_movie.avg_review) * (req_movie.num_reviews - 1) + 2 * val) / (req_movie.num_reviews + 1);
    }
    else
    {
        req_user.rev[mv] = val;
        req_movie.num_reviews += 1;
        req_movie.avg_review = ((req_movie.avg_review) * (req_movie.num_reviews - 1) + val) / (req_movie.num_reviews);
        if (req_user.rev.size() >= 3)
        {
            req_user.level = 1;
            cout << "User " << us << " updated to CRITIC level" << endl;
        }
    }
    for (auto &i : users)
    {
        if (i.name == us)
        {
            i = req_user;
            break;
        }
    }
    for (auto &i : movies)
    {
        if (i.name == mv)
        {
            i = req_movie;
            break;
        }
    }
    cout << "Review Updated Successfully" << endl;
    return;
}

void top_n(string gen, int n)
{
    vector<pair<float, string>> ans;
    for (auto i : movies)
    {
        vector<string> v1 = i.genre;
        if (find(v1.begin(), v1.end(), gen) != v1.end())
        {
            ans.push_back({i.avg_review, i.name});
        }
    }
    sort(ans.begin(), ans.end());
    reverse(ans.begin(), ans.end());
    int cnt = 0;
    for (auto i : ans)
    {
        cnt++;
        cout << i.second << " " << i.first << endl;
        if (cnt >= n)
            break;
    }
}
void rating_year(int yr)
{
    vector<pair<float, string>> ans;
    for (auto i : movies)
    {
        if (yr == i.year)
        {
            ans.push_back({i.avg_review, i.name});
        }
    }
    sort(ans.begin(), ans.end());
    reverse(ans.begin(), ans.end());
    for (auto i : ans)
    {
        cout << i.second << " " << i.first << endl;
    }
    return;
}

void avg_review(string mv)
{
    for (auto i : movies)
    {
        if (i.name == mv)
        {
            cout << "Average rating for " << i.name << " is " << i.avg_review << endl;
            return;
        }
    }
}



int main()
{
    cout << endl;
    cout << "MOVIES ADDITION" << endl;
    add_movie("Don", 2006, {"Action", "Comedy"});
    add_movie("Don", 2006, {"Action"});
    add_movie("Tiger", 2008, {"Drama"});
    add_movie("Padmaavat", 2006, {"Comedy"});
    add_movie("Lunchbox", 2021, {"Drama"});
    add_movie("Guru", 2006, {"Drama"});
    add_movie("Metro", 2006, {"Romance"});

    cout << endl;
    cout << "USER ADDITION" << endl;
    add_user("SRK");
    add_user("Salman");
    add_user("Salman");
    add_user("Deepika");

    cout << endl;
    cout << "REVIEW ADDITION" << endl;
    add_review("SRK", "Don", 2);
    add_review("SRK", "Padmaavat", 8);
    add_review("Salman", "Don", 5);
    add_review("Deepika", "Don", 9);
    add_review("Deepika", "Guru", 6);
    add_review("SRK", "Don", 10);
    add_review("Deepika", "Lunchbox", 5);
    add_review("SRK", "Tiger", 5);
    add_review("SRK", "Metro", 7);

    return 0;
}