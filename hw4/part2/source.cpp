#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;



string getWeaponName(int weapon){
	switch(weapon){
	case 0:
		return "sword";
	case 1:
		return "bomb";
	case 2:
		return "arrow";
	}
	return "";
}

class Warrior{
public:

	int id;
	int strength;
	string groupName;
	Warrior(int strength_, int id_, string group_)
	:strength(strength_), id(id_), groupName(group_)
	{}
	
	void PrintWarrior(int time, const char* type, int size){
		cout << setfill('0') << setw(3) << time << " "
			<< groupName << " "
			<< type << " "
			<< id << " "
			<< "born with strength "<< strength <<","
			<< size << " "
			<< type << " "
			<< "in" << " " << groupName <<" headquarter"<<endl;
	}
};

class Dragon:public Warrior{
public:
	int weapon;
	float morale;

	Dragon(int strength_, int id_, string group_, int weapon_, float morale_)
	:Warrior(strength_, id_, group_), weapon(weapon_), morale(morale_)
	{}

	void PrintDragon(){
		cout << "It has a "<<getWeaponName(weapon)<<","
			<< "and it's morale is "<< morale << endl;
	}
};

class Ninja:public Warrior{
public:
	int weapon[2];

	Ninja(int strength_, int id_, string group_, int weapon1, int weapon2)
	:Warrior(strength_, id_, group_)
	{
		weapon[0] = weapon1;
		weapon[1] = weapon2;
	}

	void PrintNinja(){
		cout << "It has a " << getWeaponName(weapon[0]) << " and a " << getWeaponName(weapon[1]) << endl; 
	}
};

class Iceman:public Warrior{
public:
	int weapon;

	Iceman(int strength_, int id_, string group_,int weapon_)
	:Warrior(strength_, id_,group_), weapon(weapon_)
	{}	

	void PrintIceman(){
		cout << "It has a "<< getWeaponName(weapon) << endl;
	}
};

class Lion:public Warrior{
public:
	int loyalty;

	Lion(int strength_, int id_, string group_, int loyalty_)
	:Warrior(strength_, id_, group_), loyalty(loyalty_)
	{}

	void PrintLion(){
		cout<< "It's loyalty is " << loyalty << endl;
	}
};

class Wolf:public Warrior{
public:
	Wolf(int strength_, int id_, string group_)
	:Warrior(strength_, id_, group_)
	{}
};

class Headquarter{
private:
	string group;//red or blue
	int totalStrength;
	int nWarriors;

	int dragonCost;
	int ninjaCost;
	int lionCost;
	int icemanCost;
	int wolfCost;
		
	vector<Dragon*> vecDragon;
	vector<Ninja*> vecNinja;
	vector<Lion*> vecLion;
	vector<Iceman*> vecIceman;
	vector<Wolf*> vecWolf;

	
public:
	Headquarter(
		int strength_, 
		const char* group_,
		int dragonCost_,
		int ninjaCost_,
		int lionCost_,
		int icemanCost_,
		int wolfCost_

	)
	:group(group_), totalStrength(strength_),nWarriors(0),
	dragonCost(dragonCost_),ninjaCost(ninjaCost_),lionCost(lionCost_),icemanCost(icemanCost_),wolfCost(wolfCost_)
	{}
	
	~Headquarter(){
		for(int i=0;i<vecDragon.size();i++){
			delete vecDragon[i];
		}

		for(int i=0;i<vecNinja.size();i++){
			delete vecNinja[i];
		}

		for(int i=0;i<vecLion.size();i++){
			delete vecLion[i];
		}

		for(int i=0;i<vecIceman.size();i++){
			delete vecIceman[i];
		}

		for(int i=0;i<vecWolf.size();i++){
			delete vecWolf[i];
		}

	}

	bool genDragon(int time){
		if(dragonCost>totalStrength) return false;
		
		totalStrength-=dragonCost;
		nWarriors++;

		int weapon = nWarriors%3;
		float morale = ((float)totalStrength)/((float)dragonCost);

		Dragon* dragon = new Dragon(dragonCost, nWarriors, group, weapon, morale);
		vecDragon.push_back(dragon);
		
		dragon->PrintWarrior(time, "dragon", vecDragon.size());
		dragon->PrintDragon();

		return true;
	}

	bool genNinja(int time){
		if(ninjaCost>totalStrength) return false;

		totalStrength-=ninjaCost;
		nWarriors++;

		int weapon1 = nWarriors%3;
		int weapon2 = (nWarriors+1)%3;

		Ninja* ninja = new Ninja(ninjaCost, nWarriors, group, weapon1, weapon2);
		vecNinja.push_back(ninja);

		ninja->PrintWarrior( time, "ninja", vecNinja.size() );
		ninja->PrintNinja();
		return true;
	}

	bool genIceman(int time){
		if(icemanCost>totalStrength) return false;

		totalStrength-=icemanCost;
		nWarriors++;

		int weapon = nWarriors%3;

		Iceman* iceman = new Iceman(icemanCost, nWarriors, group, weapon);
		vecIceman.push_back(iceman);

		iceman->PrintWarrior(time, "iceman", vecIceman.size() );
		iceman->PrintIceman();

		return true;
	}
	
	bool genLion(int time){
		if(lionCost>totalStrength) return false;

		totalStrength-=lionCost;
		nWarriors++;

		int loyalty = totalStrength;

		Lion* lion = new Lion(lionCost, nWarriors, group, loyalty);
		vecLion.push_back(lion);

		lion->PrintWarrior(time, "lion", vecLion.size() );
		lion->PrintLion();
		
		return true;
	}

	bool genWolf(int time){
		if(wolfCost>totalStrength) return false;

		totalStrength-=wolfCost;
		nWarriors++;

		Wolf* wolf = new Wolf(wolfCost, nWarriors, group);
		vecWolf.push_back(wolf);

		wolf->PrintWarrior(time, "wolf", vecWolf.size());

		return true;
	}

};


int main(int argc, char** argv){
	int caseNum;
	int M;
	int dragon, ninja, iceman, lion, wolf;

	cin >> caseNum;
	
	for(int i = 0; i<caseNum; i++){
		cout << "Case:" << i+1 << endl;
		cin >> M;
		cin >> dragon >> ninja >> iceman >> lion >> wolf; 
		
		Headquarter	headRed(M, "red", dragon, ninja, lion, iceman, wolf);
		Headquarter headBlue(M, "blue", dragon, ninja, lion, iceman, wolf);
		
		int time = 0;


		while(1){
			bool flagRed = false, flagBlue = false;

			if(time%5==0){
				if(headRed.genIceman(time)){
					
				}else if(headRed.genLion(time)){
				
				}else if(headRed.genWolf(time)){
						
				}else if(headRed.genNinja(time)){
						
				}else if(headRed.genDragon(time)){
						
				}else{
					if(!flagRed){
						cout << setfill('0')<< setw(3) << time << " red headquarter stops making warriors"<< endl;	
						flagRed = true;
					}
				}
				
				if(headBlue.genLion(time)){
					
				}else if(headBlue.genDragon(time)){
				
				}else if(headBlue.genNinja(time)){
						
				}else if(headBlue.genIceman(time)){
						
				}else if(headBlue.genWolf(time)){
						
				}else{
					if(!flagBlue){
						cout << setfill('0')<< setw(3) << time << " blue headquarter stops making warriors"<< endl;	
						flagBlue = true;
					}
				}

			}else if(time%5==1){
				if(headRed.genLion(time)){
				
				}else if(headRed.genWolf(time)){
						
				}else if(headRed.genNinja(time)){
						
				}else if(headRed.genDragon(time)){
						
				}else if(headRed.genIceman(time)){
					
				}else {
					if(!flagRed) {
						cout << setfill('0')<< setw(3) << time << " red headquarter stops making warriors"<< endl;	
						flagRed = true;
					}	
				}
				
				if(headBlue.genDragon(time)){
				
				}else if(headBlue.genNinja(time)){
						
				}else if(headBlue.genIceman(time)){
						
				}else if(headBlue.genWolf(time)){
						
				}else if(headBlue.genLion(time)){
					
				}else {
					if(!flagBlue){
						cout << setfill('0')<< setw(3) << time << " blue headquarter stops making warriors"<< endl;	
						flagBlue = true;
					}
				}
				
			}else if(time%5==2){
				if(headRed.genWolf(time)){
						
				}else if(headRed.genNinja(time)){
						
				}else if(headRed.genDragon(time)){
						
				}else if(headRed.genIceman(time)){
					
				}else if(headRed.genLion(time)){
				
				}else {
					if(!flagRed) 
					{
						cout << setfill('0')<< setw(3) << time << " red headquarter stops making warriors"<< endl;	
						flagRed = true;
					}
				}
				
				if(headBlue.genNinja(time)){
						
				}else if(headBlue.genIceman(time)){
						
				}else if(headBlue.genWolf(time)){
						
				}else if(headBlue.genLion(time)){
					
				}else if(headBlue.genDragon(time)){
				
				}else {
					if(!flagBlue) {
						cout << setfill('0')<< setw(3) << time << " blue headquarter stops making warriors"<< endl;	
						flagBlue = true;
					}	
				}
			}else if(time%5==3){
				if(headRed.genNinja(time)){
						
				}else if(headRed.genDragon(time)){
						
				}else if(headRed.genIceman(time)){
					
				}else if(headRed.genLion(time)){
				
				}else if(headRed.genWolf(time)){
						
				}else {
					if(!flagRed) {
						cout << setfill('0')<< setw(3) << time << " red headquarter stops making warriors"<< endl;	
						flagRed = true;
					}	
				}
				
				if(headBlue.genIceman(time)){
						
				}else if(headBlue.genWolf(time)){
						
				}else if(headBlue.genLion(time)){
					
				}else if(headBlue.genDragon(time)){
				
				}else if(headBlue.genNinja(time)){
						
				}else {
					if(!flagBlue) {
						cout << setfill('0')<< setw(3) << time << " blue headquarter stops making warriors"<< endl;	
						flagBlue = true;
					}
				}
			}else if(time%5==4){
				if(headRed.genDragon(time)){
						
				}else if(headRed.genIceman(time)){
					
				}else if(headRed.genLion(time)){
				
				}else if(headRed.genWolf(time)){
						
				}else if(headRed.genNinja(time)){
						
				}else  {
					if(!flagRed) {
						cout << setfill('0')<< setw(3) << time << " red headquarter stops making warriors"<< endl;	
						flagRed = true;
					}
				}
				
				if(headBlue.genWolf(time)){
						
				}else if(headBlue.genLion(time)){
					
				}else if(headBlue.genDragon(time)){
				
				}else if(headBlue.genNinja(time)){
						
				}else if(headBlue.genIceman(time)){
						
				}else {
					if(!flagBlue) {
						cout << setfill('0')<< setw(3) << time << " blue headquarter stops making warriors"<< endl;	
						flagBlue = true;
					}
				}
			}


			if(flagRed && flagBlue) break;
			time++;
		}


	
	}
	
	return 0;
}
