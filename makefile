build:
	g++ src/main.cpp src/FunnyjsonExplorer.cpp src/Container.cpp src/cJSON.cpp -o fje -Ofast

run:
	./fje -f json_testcase/class.json -s tree
	./fje -f json_testcase/class.json -s rectangle
	
all:
	g++ src/main.cpp src/FunnyjsonExplorer.cpp src/Container.cpp src/cJSON.cpp -o fje -Ofast
	./fje -f json_testcase/class.json -s tree
	./fje -f json_testcase/class.json -s rectangle
