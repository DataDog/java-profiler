#include "DogFood.h"

int main() {
    DogFood::Metric(
    	"DogFood.MetricTest",
    	49.5555,
    	DogFood::Counter,
    	0.75,
    	DogFood::Tags({{"f", "9"}, {"g", "8"}})
	);

	DogFood::Event(
		"DogFood Event",
		"The event was invoked",
		time(NULL)
	);

	DogFood::ServiceCheck(
		"DogFood Service Check",
		DogFood::Status::Warning,
		time(NULL)
	);
}