//Evan Chen and Daniel Chen

#include <iostream> //cout
#include <iomanip>
#include <sstream> //istringstream
#include <string> //string
#include <fstream> //ifstream
#include <vector>
using namespace std;

class Line {
public:
	int data[4]; //4 bytes per line
	bool dirty;
	int tag;
	int address;

	Line();
};

class Cache {
public:
	Line lines[64]; //64 lines in cache
	int ram[65536];	//2^16 addresses

	Cache(); //I misunderstood the prompt and wasted my life

	void read(int address, int offset, int lineNumber, int tag, int dataByte, int hit);
	void write(int address, int offset, int lineNumber, int tag, int dataByte, int hit);

	void print(int data, int hit, bool dirty); // hit if found in cache, write to dm-out.txt
	int bits(int address, string type); //type is tag, line, or offset
};

Line::Line() {
	for(int i = 0; i < 4; i++)
		data[i] = 0;

	dirty = false;
	tag = -1;
}

Cache::Cache() {
	remove("dm-out.txt");
	for(int i = 0; i < 65536; i++){
		ram[i] = 0;
	}
}

//write to dm-out.txt if there's a read input or if there's a writeback
void Cache::print(int data, int hit, bool dirty){ 
	ofstream outfile;
	outfile.open("dm-out.txt", ios::out | ios::app );
	outfile << setw(2) << std::setfill('0') << setiosflags( ios::uppercase ) << std::hex 
			<< data;
	outfile << ' ' << hit << ' ' << (int)dirty << endl;
	outfile.close();
}

int Cache::bits(int address, string type){
	int mask, result;

	if(type == "offset"){
		mask = 0x0003; //0000 0000 0000 0011
	} else if(type == "line"){
		address = address >> 2; // shift address right two bits
		mask = 0x003F; //select original bits 0000 0000 1111 1100
	} else if(type == "tag"){
		address = address >> 8; // shift address right 8 bits
		mask = 0x00FF; //select original bits 1111 1111 0000 0000
	} else{
		cout << "you done fucked up" << endl; //explain that you done fucked up boy
	}

	result = address & mask; // get the selected bits as an int

	return result;
}

void Cache::read(int address, int offset, int lineNumber, int tag, int dataByte, int hit){
	if(hit == 1){
		this->print(this->lines[lineNumber].data[offset],hit,this->lines[lineNumber].dirty);
	}else{

		address = address & 0xFFFC;//set last two bits of address to 0

		if(this->lines[lineNumber].dirty == false){
			this->lines[lineNumber].address = address;
			this->lines[lineNumber].tag = tag;				
			for(int i = 0; i < 4; i++){
				this->lines[lineNumber].data[i] = this->ram[address++]; //replace cache
			}
		}
		else{
			for(int i = 0; i < 4; i++){
				this->ram[this->lines[lineNumber].address++] = this->lines[lineNumber].data[i]; //writeback
			}

			this->lines[lineNumber].address = address;
			this->lines[lineNumber].tag = tag;	
			for(int i = 0; i < 4; i++){
				this->lines[lineNumber].data[i] = this->ram[address++]; //replace cache
			}		
		}
		this->lines[lineNumber].dirty = false;

		this->print(this->lines[lineNumber].data[offset],hit,this->lines[lineNumber].dirty);
	}
}

void Cache::write(int address, int offset, int lineNumber, int tag, int dataByte, int hit){
	if(hit == 1){
		this->lines[lineNumber].dirty = true;
		this->lines[lineNumber].data[offset] = dataByte;
	}else{

		address = address & 0xFFFC;//set last two bits of address to 0

		if(this->lines[lineNumber].dirty == false){
			this->lines[lineNumber].address = address;
			this->lines[lineNumber].tag = tag;			
			for(int i = 0; i < 4; i++){
				this->lines[lineNumber].data[i] = this->ram[address++]; //replace cache
			}
			this->lines[lineNumber].dirty = true;
			this->lines[lineNumber].data[offset] = dataByte;
		}
		else{
			this->lines[lineNumber].address = this->lines[lineNumber].address & 0xFFFC;
			for(int i = 0; i < 4; i++){
				this->ram[this->lines[lineNumber].address++] = this->lines[lineNumber].data[i]; //writeback
			}

			this->lines[lineNumber].address = address;
			this->lines[lineNumber].tag = tag;	
			for(int i = 0; i < 4; i++){
				this->lines[lineNumber].data[i] = this->ram[address++]; //replace cache
			}
			this->lines[lineNumber].dirty = true;
			this->lines[lineNumber].data[offset] = dataByte;	
		}
	}
}

int main(int argc, char* argv[]){
	Cache cache;

	ifstream infile;
	infile.open(argv[1]);
	
	string currentLine;
	int address, dataByte, readWrite, offset, lineNumber, tag, hit; //for read or write

	while(getline(infile, currentLine)){
		istringstream iss(currentLine);
		iss >> std::hex >> address;
		iss >> std::hex >> readWrite;
		iss >> std::hex >> dataByte;
		
		offset = cache.bits(address, "offset");
		//cout << "Offset: " << offset;
		lineNumber = cache.bits(address, "line");
		//cout << " Line #: " << lineNumber;
		tag = cache.bits(address, "tag");
		//cout << " Tag: " << tag << endl;

		if(cache.lines[lineNumber].tag == tag){
			hit = 1;
		} else{
			hit = 0;
		}

		if(readWrite == 0xFF){ //write
			cache.write(address,offset,lineNumber,tag,dataByte,hit);
		}
		else if(readWrite == 0x00){ //read
			cache.read(address,offset,lineNumber,tag,dataByte,hit);
		}
	}	

	infile.close();	
	return 0;
}
