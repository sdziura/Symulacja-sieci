/*
 * simulation.h
 *
 *  Created on: 5 sty 2018
 *      Author: aleksandra
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_



#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iterator>
#include <sstream>
#include <fstream>
#include <set>
//#include <conio.h>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::deque;
using std::ostringstream;
using std::set;
using std::fstream;

enum class Type {
	Basic,
	Recipient,
	Worker,
	Ramp,
	Storehouse,
};
Type convert(int i);

enum class QUEUE_TYPE {
	FIFO,
	LIFO,
};
typedef int ElementID;

class Product{
	private:
	ElementID basic_id;
	public:
		Product( ElementID p_id = 1){
			basic_id = p_id ;
		}
		int get_id();
};




class BasicElement{
	private:
	ElementID id;
		Type type;
	public:

		BasicElement(ElementID b_id=0, Type b_type = Type::Basic){
			id = b_id;
			type = b_type;
				}
		 int get_id();
		 Type return_type() ;
};

class Recipients{
	private:
		map<BasicElement*, double > probabilities;
	public:
		Recipients(map<BasicElement* , double > map_given){
			probabilities = map_given;
		}
		Recipients(BasicElement* basic=NULL, double probab_given=0){
			map<BasicElement*, double> probabilities;
			probabilities.insert( pair<BasicElement* , double >(basic, probab_given)) ;
		}
		map<BasicElement*, double > getProbabilities();
		void setProbabilities(map<BasicElement* , double> map_given );
		bool addRecipient(BasicElement* basic);
		bool addRecipientwithProbability(BasicElement& basic, double probability);
		bool removeRecipient(BasicElement* basic);
		void view_list();
		double get_probability(BasicElement* basic);

};

class Sender{
	private:
		Recipients recipients_list;

	public:
		Sender( Recipients list_given){
			recipients_list = list_given;
		};
		Sender( BasicElement* basic, double prob_given):recipients_list(basic, prob_given){
		}
		bool addRecipient(BasicElement& a_basic,double prob_given=0);//tu zmiana zamiast BasicElement*
		bool deleteRecipient(BasicElement* r_basic );
		void show_list();
		Recipients get_list();
		double get_probability(BasicElement* basic);
		Product send_product();
};
/*class QueueInterface{
	private:
		deque<Product> products_deque;
	public:

		virtual void push(Product product)=0;
		virtual void pop()=0;
		virtual bool empty()=0;
		virtual int size()=0;
		virtual void view()=0;
		virtual QUEUE_TYPE get_Type()=0;
		virtual Product at(int i)=0;
};*/

class Queue {
	private:
	deque<Product> products_deque;
		QUEUE_TYPE queue_type;
	public:

		virtual void push(const Product & product);
		virtual void pop();
		virtual bool empty();
		virtual int size();
		virtual void view();
		virtual QUEUE_TYPE get_Type();
		virtual ostringstream at();
};

class Ramp: public Sender, public BasicElement{
	private:
		int sending_frequency;
	public:
		Ramp(ElementID r_id = 1, Type r_type = Type::Ramp, int send_freq = 1, Recipients recp = 0):BasicElement(r_id, r_type),Sender(recp){
			sending_frequency = send_freq;
		}
		int get_sending_frequency();


};

class Worker: public Sender, public BasicElement{
	private:
		int processing_time;
		Queue* queue;

	public:

		void receive_product(const Product & new_product);
		void doProduct();
		Worker(ElementID w_id = 1, Type w_type = Type::Worker, int w_pr_time = 0, Queue* q_given = nullptr,  Recipients list_given = 0)
		: BasicElement(w_id, w_type), Sender( list_given ){
			processing_time = w_pr_time;
			queue = q_given;

		}
		int get_processing_time();
		auto get_queue_type();
		Queue get_Queue();



};

class Storehouse: public BasicElement{
	private:
		vector< Product > products_in_storehouse;

	public:
		void receive_product(const Product & product);
		Storehouse(ElementID s_id = 1, Type s_type = Type::Storehouse, vector<Product> pr_given ) : BasicElement(s_id, s_type){
			products_in_storehouse = pr_given;
		}
		vector< Product >get_products();


};

class Network{
	private:
		vector<Ramp> Ramps;
		vector<Worker> Workers;
		vector<Storehouse> Storehouses;
	public:
		Network(Ramp r1 = 0, Worker w1 = 0, Storehouse s1 = 0){
			Ramps.push_back(r1);
			Workers.push_back(w1);
			Storehouses.push_back(s1);
		}
		Network(vector<Ramp> r1 ,vector<Worker> w1 , vector<Storehouse> s1 = 0){
			Ramps = r1;
			Workers = w1;
			Storehouses = s1;
		}

		vector<Worker> getWorkers();
		bool addWorker(Worker & new_worker);
		bool removeWorker(ElementID id);

		vector<Ramp> getRamps();
		bool addRamp(Ramp & new_ramp);
		bool removeRamp(ElementID id);

		vector<Storehouse> getStorehouses();
		bool addStorehouse(Storehouse & new_storehouse);
		bool removeStorehouse(ElementID id);

		bool check_integrity();
};

class Interface_Report{
	public:
		virtual bool should_generate_raport(int time)=0;

};

class Structure_Report: public Interface_Report{
	private:
	public:
	virtual bool should_generate_raport( bool answer);
	void Structure_Report_Generate( Network network);
};

class Interval_Report: public Interface_Report{
	private:
		int time_interval;

	public:
		Interval_Report(int time = 1){
			time_interval = time;
		}
		virtual bool should_generate_raport(int round_numer) override;
		void Interval_Report_Generate(int timeinterval, Network network, int turn_number);
};

class Turns_Report: public Interface_Report{
	private:
		set<int> turns;

	public:
		Turns_Report(set<int> turns_given){
			turns = turns_given;
		}
		virtual bool should_generate_raport(int round_number)override;
		void Turns_Report_Generate(set<int> turns, Network network);
};

class Prezes{
	public:
		Prezes();
		void watch();
};


void simulate(Network network, int turns);
void LoadData(  fstream file );

void showMenu();
void createNetwork();

#endif /* SIMULATION_H_ */
