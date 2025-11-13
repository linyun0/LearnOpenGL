#pragma once

struct Info {
	int id;
	bool state;
	float val;
};

class Control {

public:
	Control() {};
public:
	virtual void Active(Info& info)=0;

};
