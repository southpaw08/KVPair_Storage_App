CXX = ../../../clay/host/bin/arm-buildroot-linux-uclibcgnueabi-g++

.PHONY: clean

KVPStorage: KVPStorage.cpp
	$(CXX) -o '$@' '$<' -lstdc++

clean:
	rm -rvf KVPStorage KVPStorageDB
