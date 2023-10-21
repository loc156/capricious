#ifdef CONFIL
    #include<fstream>
    #include<vector>
#endif
#ifdef MPRINT
    #include<iostream>
#endif

namespace des{
    namespace{  
        std::ofstream ofile;
        std::ifstream ifile;
        std::fstream iofile;
    }
    inline namespace v_01{
        #ifdef CONFIL
        //ConfigFile class
        class ConfigFile{ 
            private:
            std::string filepath;
            public:
            ConfigFile(std::string path="config.ini"){
                filepath=path;
            }
            void initConFile(){
                ofile.open(filepath,std::ios::out|std::ios::trunc);
                ofile.close();
            }
            bool isConFils(){
                ifile.open(filepath,std::ios::in);
                if(!ifile.fail()){
                    ifile.close();
                    return true;
                }else{
                    ifile.close();
                    return false;
                }
            }
            std::string read(std::string section,std::string key){
                std::string sectname;
                std::string keyname;
                std::string keyvar;
                ifile.open(filepath,std::ios::in);
                while(true){
                    ifile>>sectname;
                    if(sectname=="["+section+"]"){
                        break;
                    }else if(ifile.eof()){
                        ifile.close();
                        return "error";
                    }
                }
                while(true){
                    ifile>>keyname;
                    if(keyname==key){
                        ifile>>keyvar>>keyvar;
                        ifile.close();
                        return keyvar;
                    }else if((keyname[0]=='['&&keyname[keyname.length()-1]==']')||(ifile.eof())){
                        ifile.close();
                        return "error";
                    }
                }
            }
            //void write(std::string section,std::string key,std::string val){}
        };
        #endif
        #ifdef MPRINT
        //Mpint class #define
        #define RIGHTM 1
        #define LEFTM 2
        #define FIXEDM 1
        #define SCIENTIFICM 2
        //Mpint class
        class Mprint {
        public:
            //att struct
            struct att {
            public:
                int width = 0;
                char fill = 0;
                int align = 0;
                int floatflag = 0;
                att& setWidth(int w) {
                    width = w;
                    return *this;
                }
                att& setFill(char f) {
                    fill = f;
                    return *this;
                }
                att& setAlign(int a) {
                    align = a;
                    return *this;
                }
                att& setFloatflag(int ff) {
                    floatflag = ff;
                    return *this;
                }
            };
        private:
            att* atptr = NULL;
        public:
            Mprint& setDefault() {
                std::cout.unsetf(std::ios::right);
                std::cout.unsetf(std::ios::left);
                std::cout.unsetf(std::ios::fixed);
                std::cout.unsetf(std::ios::scientific);
                return *this;
            }
            Mprint& clearState() {
                delete atptr;
                atptr = NULL;
                return *this;
            }
            Mprint() {}
            Mprint(att ptr) {
                atptr = &ptr; 
            }
            Mprint(att* ptr) {
                atptr = ptr;
            }
            Mprint& operator[](att* ptr) {
                atptr = ptr;
                return *this;
            }
            Mprint& operator[](att ptr) {
                atptr = &ptr;
                return *this;
            }
            Mprint& operator()() {
                std::cout << "NONE";
                return *this;
            }
            //cout func args...(end) 
            template<typename T>
            Mprint& operator()(T end_arg) {
                if (atptr == NULL) {
                    std::cout << end_arg;
                }
                else {
                    if (atptr->width) std::cout.width(atptr->width);
                    if (atptr->fill) std::cout.fill(atptr->fill);
                    if (atptr->align) {
                        switch (atptr->align) {
                        case 1:std::cout.setf(std::ios::right);
                            break;
                        case 2:std::cout.setf(std::ios::left);
                            break;
                        default:
                            break;
                        }
                    }
                    if (atptr->floatflag) {
                        switch (atptr->floatflag) {
                        case 1:std::cout.setf(std::ios::fixed);
                            break;
                        case 2:std::cout.setf(std::ios::scientific);
                            break;
                        default:
                            break;
                        }
                    }
                    std::cout << end_arg;
                }
                setDefault();
                return *this;
            }
            //cout func args...(every first)
            template<typename T, typename ...Ty>
            Mprint& operator()(T first_arg,Ty... other_arg) {
                if (atptr == NULL) {
                    std::cout<<first_arg;
                }
                else {
                    if (atptr->width) std::cout.width(atptr->width);
                    if (atptr->fill) std::cout.fill(atptr->fill);
                    if (atptr->align) {
                        switch (atptr->align){
                        case RIGHTM:std::cout.setf(std::ios::right);
                            break;
                        case LEFTM:std::cout.setf(std::ios::left);
                            break;
                        default:
                            break;
                        }
                    }
                    if (atptr->floatflag) {
                        switch (atptr->floatflag) {
                        case FIXEDM:std::cout.setf(std::ios::fixed);
                            break;
                        case SCIENTIFICM:std::cout.setf(std::ios::scientific);
                            break;
                        default:
                            break;
                        }
                    }
                    std::cout << first_arg;
                }
                this->operator()(other_arg...);
                return *this;
            }
        };
        //using
        using atte = des::Mprint::att;
        //init
        atte sta;
        des::Mprint tprints(sta);
        #endif
        //TemLis class
        template<typename T>
        class TemLis{
        private:
            T* list = NULL;
            int point = 0;
            int lengh = 0;
        public:
            template<typename ...Args>
            TemLis(T first,Args... arg){
                add(first);
                add(arg);
            }
            void add(T var){
                if(point == lengh){
                    T* temp = list;
                    list = new T[lengh+5];
                    for(int i=0;i<lengh;i++){
                        list[i]=temp[i];
                    }
                    delete temp;
                    lengh+=5;
                }
                list[point]=var;
                point++;
            }
            //args...(end)
            template<typename ...Args>
            void add(T first,Args... arg){
                add(first);
                add(arg);
            }
        };
        //using
        using pT = TemLis<int>;
        using pF = TemLis<float>;
        using pFD = TemLis<double>;
        //Drop class
        template<class T>
        class Drop {
        private:
            T* drop = NULL;
            int size_len = 0;
            int point = 0;
        public:
            Drop(int n) {
                drop = new T[n];
                size_len = n;
                for (int i = 0; i < n; i++) {
                    drop[i] = 0;
                }
            }
            int& getSpace_postVar(int n) {
                return drop[n];
            }
            template<typename ...args>void setCoordinate(T first, args... arg) {
                if (point < size_len) {
                    drop[point] = first;
                    point++;
                    setCoordinate(arg...);
                }
                point = 0;
            }
            void setCoordinate(T end) {
                if (point < size_len) {
                    drop[point] = end;
                }
            }
        };
        //IVal class
        template<typename T>
        class IVal{
        private:
            T val;
        public:
            IVal(){std::cin>>val;}
            T operator()(){
                return val;
            }
        };
        
    }
}