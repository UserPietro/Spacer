//g++ spacer.cpp ./DuoHash/src/Spaced/*.cpp -I./DuoHash/include -o programma
//compilatore, file con il main, file cpp da dove pesca i metodi (dichiarati con include .h), da dove prende l'include, l'output nomeexe

#include <DuoHash.h>
#include <chrono>
#include <iomanip>
#include <iostream>


int main()
{
    //carico le sequenze
    std::string dataset = "paired_small.txt";
	std::vector<std::string> sequences;
	if (!loadFile(dataset, sequences))
        std::exit(1);

    //carico i seeds
	std::string seedset = "./DuoHash/example/Seeds/W22L31.fna";
	std::vector<SpacedQmer> multi_spaced;
	{
		std::vector<std::string> tmp;
		if (!loadFile(seedset, tmp))
			std::exit(1);

		for (auto seed : tmp)
			multi_spaced.push_back(SpacedQmer(seed, 0));
	}

    std::cerr << "\nTest with single seed\n";
	DuoHash test(sequences, multi_spaced[0]);
	std::vector<Encoding_V> encodings;
	std::vector<Hashing_V> hashes;
	std::vector<SpacedKmer_V> spacedKmers;

    // GetEncoding_naive  /  get only forward & reverse hashing
	{
		std::cerr << "GetEncoding_naive... ";
		
		auto t1 = std::chrono::steady_clock::now();
		test.GetEncoding_naive(encodings, hashes, spacedKmers);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

	// PrintFASTA
	{
		std::cerr << "PrintFASTA... ";

		auto t1 = std::chrono::steady_clock::now();
		//test.PrintFASTA(spacedKmers, "single");
		//test.PrintFASTA(spacedKmers);
		auto t2 = std::chrono::steady_clock::now();

		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

	// GetEncoding_ISSH  /  get only forward & reverse hashing
	{
		std::cerr << "GetEncoding_ISSH... ";
		
		auto t1 = std::chrono::steady_clock::now();
		test.GetEncoding_ISSH(encodings, hashes, spacedKmers);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

	// PrintFASTA
	{
		std::cerr << "PrintFASTA... ";

		auto t1 = std::chrono::steady_clock::now();
		//test.PrintFASTA(spacedKmers, "single");
		//test.PrintFASTA(spacedKmers);
		auto t2 = std::chrono::steady_clock::now();

		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}


	


	std::cerr << "\nTest with multiple seed\n";
	DuoHash_multi test_multi(sequences, multi_spaced);
	std::vector<Encoding_V_V> encodings_multi;
	std::vector<Hashing_V_V> hashes_multi;
	std::vector<SpacedKmer_V_V> spacedKmers_multi;

    // GetEncoding_naive
	{
		std::cerr << "GetEncoding_naive... ";

		auto t1 = std::chrono::steady_clock::now();
		test_multi.GetEncoding_naive(encodings_multi, hashes_multi, spacedKmers_multi);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

	// PrintFASTA
	{
		std::cerr << "PrintFASTA... ";

		auto t1 = std::chrono::steady_clock::now();
        //test_multi.PrintFASTA(spacedKmers_multi, "multi");
		//test_multi.PrintFASTA(spacedKmers_multi);
		auto t2 = std::chrono::steady_clock::now();

		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

	// GetEncoding_MISSH_v1
	{
		std::cerr << "GetEncoding_MISSH_v1... ";

		auto t1 = std::chrono::steady_clock::now();
		test_multi.GetEncoding_MISSH_v1(encodings_multi, hashes_multi, spacedKmers_multi);
		auto t2 = std::chrono::steady_clock::now();
		
		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

	// PrintFASTA
	{
		std::cerr << "PrintFASTA... ";

		auto t1 = std::chrono::steady_clock::now();
        //test_multi.PrintFASTA(spacedKmers_multi, "multi");
		//test_multi.PrintFASTA(spacedKmers_multi);
		auto t2 = std::chrono::steady_clock::now();

		auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1);
		std::cerr << "OK. Executed in " << (double)t.count() / 1000 << "ms\n";
	}

}