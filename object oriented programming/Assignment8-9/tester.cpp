#include <bits/stdc++.h>
#include "include/DynamicVector.h"
#include "include/Movie.h"
#include "include/Repository.h"
#include "include/Controller.h"
#include "include/WatchList.h"
#include <assert.h>
#define pb push_back
#define mp make_pair
#define sec second
#define fir first
#define INF 1000000000

void testDynVect()
{
	{
		DynamicVector<int> v;

		for (int i = 1; i <= 11; ++i) {
			v.addElement(i);
		}

		for (int i = 0; i < v.getSize(); ++i) {
			assert(v[i] == i + 1);
		}

		for (int i = 0; i < 8; ++i) {
			v.popElement();
		}

		for (int i = 0; i < v.getSize(); ++i) {
			assert(v[i] == i + 1);
		}

		DynamicVector<int> V2;

		for (int i = 1; i <= 3; ++i) {
			V2.addElement(i);
		}

		assert(v == V2);
		DynamicVector<int> V3{100};
		assert(V3.getCapacity() == 100);
		V3 = v;
		assert(v == V3);
		DynamicVector<int> V4 = V3;
		assert(V4 == V3);
	}
	{
		DynamicVector<int> D;
		int ab = D.popElement();
		int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
		int in = 0;

		for (int i = 1; i <= 9; ++i) {
			D.addElement(i);
		}

		for (auto it : D) {
			//std::cout << it << " " << a[in] << "\n";
			assert(it == a[in]);
			++in;
		}

		in = 0;

		for (auto it : D) {
			//std::cout << it << " " << a[in] << "\n";
			//std::cout << it << " ";
			assert(it == a[in]);
			++in;
		}

		D = D - 2;
		/*
		for (auto it : D) {
		    std::cout << it << " ";
		}
		*/
		assert(D[1] == 9);
	}
}

void testMovie()
{
	{
		Movie m{"Avatar", "Sci-Fi", "2009-10-20", 400,
		        "https://www.youtube.com/watch?v=aVdO-cx-McA"};
		assert(m.getTitle() == "Avatar");
		assert(m.getGenre() == "Sci-Fi");
		assert(m.getReleaseDate() == "2009-10-20");
		assert(m.getNumberOfLikes() == 400);
		assert(m.getLink() == "https://www.youtube.com/watch?v=aVdO-cx-McA");
		//m.playTrailer();
		m.setTitle("Avatar2");
		assert(m.getTitle() == "Avatar2");
		m.setGenre("Sci-Fi2");
		assert(m.getGenre() == "Sci-Fi2");
		m.setReleaseDate("2");
		assert(m.getReleaseDate() == "2");
		m.setLink("2");
		assert(m.getLink() == "2");
		m.setNumbersOfLikes(2);
		assert(m.getNumberOfLikes() == 2);
		Movie m2{"Avatar2", "Sci-Fi2", "2", 2, "2"};
		Movie m3{"Avatar", "Sci-Fi2", "2", 2, "2"};
		assert(m == m2);
		assert(m != m3);
		assert(m.computeString() == "Avatar2;Sci-Fi2;2;2;2\n");
		DynamicVector<Movie> D;
		D.addElement(m);
		D.addElement(m2);
		D = D - m;
		assert(D[0] == m2);
		assert(D.getSize() == 1);
		D = D - m2;
		assert(D.getSize() == 0);
	}
}

void testRepo()
{
	{
		Repository r;
		Movie m{"Avatar", "Sci-Fi", "2009-10-20", 400,
		        "https://www.youtube.com/watch?v=aVdO-cx-McA"};
		assert(r.addMovie(m) == true);
		assert(r.addMovie(m) == false);
		assert(r.updateMovie("Avatar", "2009-10-20", m) == true);
		assert(r.deleteMovie("Avatar", "2009-10-20"));
		assert(r.getList()[0] == m);
	}
	{
		Repository r{"testDatabase.txt"};
		int ind = 0;
		std::string s[6] = {"Avatar", "Batman: The Dark Knight", "The Shawshank Redemption",
		                    "The Godfather", "Inception", "Interstellar"
		                   };

		for (auto it : r.getList()) {
			assert(it.getTitle() == s[ind]);
			++ind;
		}
	}
}

void testController()
{
	{
		Repository r{};
		WatchList w{};
		Controller c{r, w};
		Movie m{"Avatar", "Sci-Fi", "2009-10-20", 400,
		        "https://www.youtube.com/watch?v=aVdO-cx-McA"};
		Movie m2{"Avatar", "Sci-Fi", "2010-10-20", 400,
						"https://www.youtube.com/watch?v=aVdO-cx-McA"};
		assert(c.addToWatchList(m) == true);
		assert(c.addToWatchList(m2) == true);
		assert(c.addToWatchList(m) == false);
		std::string title = m.getTitle();
		std::string releaseDate = m.getReleaseDate();
		c.increaseNumberOfLikes(title, releaseDate);
		assert(c.removeFromWatchList(title, releaseDate) == true);
		assert(c.removeFromWatchList(title, releaseDate) == false);
		DynamicVector<Movie> v = c.getWatchList();
		assert(c.addMovie(m) == true);
		assert(c.addMovie(m) == false);
		std::vector<Movie> vvv2 = c.getByGenre("");
		assert(c.updateMovie(title, releaseDate, m) == true);

		assert(c.deleteMovie(title, releaseDate) == true);
		assert(c.deleteMovie(title, releaseDate) == false);
		assert(c.updateMovie(title, releaseDate, m) == false);
		DynamicVector<Movie> vec = c.getMovies();
		std::string sss = m.toString();
		std::vector<Movie> vvv = c.getByGenre("");
	}
}

int main()
{
	{
		testDynVect();
		testMovie();
		testRepo();
		testController();
	}
	return 0;
}
