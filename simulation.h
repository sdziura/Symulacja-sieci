#include< iostream >
#include< vector >
#include< map >

enum class Type {
	Basic,
	Recipient,
	Worker,
	Ramp,
	Storehouse;
};

enum class COLLECTION_TYPE {
	FIFO,
	LIFO;
};

class BasicElement{
	private:
		int id;
		Type type;
	public:
		BasicElement(int b_id=0, Type b_type = Type::Basic){
			id = b_id;
			type = b_type;
				}
		 void setId();
};

class Queue{
	private:
		std::vector<Product*> list;
	public:
		bool getType();
		bool collectProduct(Product product);
		virtual bool push_product(Product product);
		
};

class FIFO: public Queue{
	puclic:
	virtual	bool push_product(Product product);
};

class LIFO: public Queue{
	public:
	virtual	bool push_product(Product product);
};


class Sender{
	private:
		map<BasicElement, double> recipients_list;
		
	public:
	
		bool addRecipient(BasicElement a_basic,double prob);
		bool deleteRecipient(BasicElemnt r_basic );			
		
};

class Ramp: public Sender, public BasicElement{
	private:
		int sending_frequency;
	public:
		Ramp(int r_id = 1, Type r_type = Type::Ramp, int send_freq = 1):BasicElement(r_id, r_type),{
			sending_frequency=send_freq;
		} 
		bool send_product();
		
};

class Worker: public Sender, public BasicElement{
	private:
		int processing_time;
		int products_in_Queue;
		COLLECTION_TYPE collection_type;
	public:
		bool send_product();
		bool collect_product();
		Worker(int w_id = 1, Type w_type = Type::Worker, int w_pr_time=0, int w_pr_in_Q=0, COLLECTION_TYPE coll_t=COLLECTION_TYPE::FIFO)
		:BasicElement(w_id, w_type){
			processing_time = w_pr_time;
			products_in_Queue = w_pr_in_Q;
			collection_type = coll_t;
			
		}
		
};

class Storehouse: public BasicElement{
	private:
		State s_state;
	public:
		bool collect_product(product);
		Storehouse(int s_id = 1, Type s_type = Storehouse, State st = State::EMPTY): BasicElement(s_id, s_type){
			
			s_state = st;
		}
};

class Product{
	private:
		int basic_id;
	public:
		Product( int p_id = 1){
			basic_id = p_id;
		}
		void get_id(int g_id);
};

bool read();
bool simulation_state_report();
bool structure_report();

class Network{
	private:
		std::vector<Ramp> Ramps;
		std::vector<Worker> Workers;
		std::vector<Storehouse> Storehouses;
	public:
		Network(Ramp r1, Worker w1, Storehouse s1){
			Ramps.std::push_back(r1);
			Workers.std::push_back(w1);
			Storehouse.std:push_back(s1);
		}
		bool check_integrity();
};

class Prezes{
	public::
		Prezes();
		void watch();
};

std:: map tablica asocjacyjna unikalny klucz wartoœæ


integralnoœæ sieci do network

klasa network która zawiera rampy, pracowników i magazyny zamiast enuma
metoda typu gettype storehouse i worker 
stowrzyæ wspólny interfejs dla worker i storehouse metoda do uzyskiwania typu obiektu i odbierania paczek
interfejs kolejka (metody push pop view get type) i dwie  albo fifo albo lifo i te¿ yo get type robotnik nie musi wiedziec czy ma lifo czy fifo 
