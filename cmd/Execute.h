#ifndef EXECUTE_H
#define	EXECUTE_H

class Execute {
private:

public:
	Execute();
	~Execute();
	std::vector<int> run(std::vector<int> Decode_buffer, std::vector<int> F_DM, 
						 std::vector<int> F_WB);
};


#endif
