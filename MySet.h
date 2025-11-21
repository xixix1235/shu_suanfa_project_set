//
// Created by 21718 on 2025/11/18.
//

#ifndef CPP_LEARN_MYSET_H
#define CPP_LEARN_MYSET_H
#include "string"
#include "iostream"
#include "vector"
using namespace std;
namespace MySet{
    class SetException {
    public:
        SetException(const string& i) :info(i) {}
        string getInfo() const { return info; }
    private:
        string info;
    };
    enum class Couleur { rouge, mauve, vert };
    enum class Nombre { un = 1, deux = 2, trois = 3 };
    enum class Forme { ovale, vague, losange };
    enum class Remplissage { plein, vide, hachure };
    const vector<Couleur> allCouleurs = {
            Couleur::rouge,
            Couleur::mauve,
            Couleur::vert
    };const vector<Nombre> allNombre = {
            Nombre::un,
            Nombre::deux,
            Nombre::trois
    };const vector<Forme> allForme = {
            Forme::ovale,
            Forme::vague,
            Forme::losange
    };const vector<Remplissage> allRemplissage = {
            Remplissage::plein,
            Remplissage::vide,
            Remplissage::hachure
    };
    string toString(Couleur c);
    string toString(Nombre v);
    string toString(Forme f);
    string toString(Remplissage v);
    ostream &operator<<(ostream&cout,Couleur c);
    ostream &operator<<(ostream&cout,Nombre n);
    ostream &operator<<(ostream&cout,Forme f);
    ostream &operator<<(ostream&cout,Remplissage r);
    class Jeu;
    //卡牌类
    class Carte{
        friend Jeu;
        friend ostream & operator<<(ostream&cout,const Carte& e);
    private:
        Couleur couleur;
        Nombre nombre;
        Forme forme;
        Remplissage remplissage;
        Carte(const Carte&) = default;//显式要求编译器为Carte类生成 “默认拷贝构造函数
        Carte& operator=(const Carte&) = default;//默认赋值运算符
        Carte(Couleur c, Nombre n, Forme f, Remplissage r) :
                couleur(c), nombre(n), forme(f), remplissage(r) {}
    public:
        bool operator==(const Carte& autre)const;
        Couleur getCouleur() const { return couleur; }
        Nombre getNombre() const { return nombre; }
        Forme getForme() const { return forme; }
        Remplissage getRemplissage() const { return remplissage; }
        ~Carte() = default;
        bool operator!=(const Carte& autre);
    };
    ostream & operator<<(ostream&cout,const Carte& e);
    //游戏类
    class Jeu{
    private:
        const Carte* cartes[81];
        //禁止对象之间的拷贝和赋值操作
        Jeu(const Jeu&) = delete;
        Jeu& operator=(const Jeu&) = delete;
        Jeu();
        static Jeu* obj;
        const Carte& getCarte(size_t i) const;
    public:
        static Jeu& GetInstance();
        ~Jeu();
        static void DestroyInstance();
        class Iterator{
        protected:
            int index;
            bool isDone();
            void next();
            const Carte* currentItem();
        public:
            Iterator(){index=0;}
            Iterator(int i):index(i){}
            bool operator==(const Iterator& it){return this->index==it.index;}
            Iterator operator++();
            const Carte& operator*();
        };
        Iterator begin(){return Iterator();}
        Iterator end(){return Iterator(81);}
        class Iterator_std{
        private:
            const Carte**p;
        public:
            Iterator_std(const Carte** piont):p(piont){};
            const Carte& operator*(){return *(*this->p);}
            Iterator_std operator++(){return this->p++;}
            bool operator!=(Iterator_std it){return it.p!=this->p;}
        };
        Iterator_std begin_std(){return Iterator_std(&cartes[0]);}
        Iterator_std end_std(){return Iterator_std(&cartes[81]);}
        class FormeIterator:public Iterator{
        private:
            Forme f;
            void next();
        public:
            FormeIterator(Forme form):f(form){};
            Iterator operator++();
            FormeIterator(Forme form,int ind): Iterator(ind),f(form){};
        };
        FormeIterator begin(Forme f){return FormeIterator(f);}
        FormeIterator end(Forme f);
    };
    //牌堆
    class Pioche{
    private:
        const Carte**cartes;//和Jeu类中的数组的指向是一致的，只是这里是用指针的方式表示的动态数组
        int nb;
        Pioche(const Pioche&)=delete;//禁止拷贝构造函数
        Pioche& operator=(const Pioche&)=delete;//禁止赋值操作
    public:
        Pioche();
        int getNbCartes(){return nb;}
        bool estVide(){return nb==0;}
        const Carte& piocher();
        ~Pioche();
    };
    class Controleur;
    //游戏面板
    class Plateau{
        friend Controleur;
    private:
        const Carte** cartes;
        int nb;
        int MaxNb;
    public:
        Plateau(){
            cartes=new const Carte*[5];
            MaxNb=5;
            nb=0;
        };
        ~Plateau() { delete[] cartes; }
        Plateau(const Plateau&p);//拷贝构造函数
        Plateau& operator=(Plateau& p);
        void ajouter(const Carte& carte);
        void DeleteSet(int i,int j,int k);
        void DeleteCarte(int i);
        void print(ostream&cout);
        void DisplaySet();
        bool CheckSet();
        class Iterator{
        private:
            int index;
            Plateau* plateau;
            bool isDone();
            const Carte*CurrentCarte(){return plateau->cartes[index];};
            void next(){index++;};
        public:
            Iterator(Plateau* p):index(0),plateau(p){};
            Iterator(Plateau* p,int i):index(i),plateau(p){};
            const Iterator&operator++();
            const Carte&operator*();
            bool operator!=(const Iterator& it);
        };
        const Iterator begin(){return Iterator(this);}
        const Iterator end(){return Iterator(this,nb);}
    };
    ostream& operator<<(ostream&cout,Plateau p);
    //组合类，表示玩家选出的三张卡牌构成的组合
    class Combinaison{
    private:
        const Carte*c1;
        const Carte*c2;
        const Carte*c3;
    public:
        Combinaison(const Carte*a,const Carte*b,const Carte*c):c1(a),c2(b),c3(c){};
        const Carte* getCarte1(){return c1;}
        const Carte* getCarte2(){return c2;}
        const Carte* getCarte3(){return c3;}
        bool estUnSET();
        Combinaison(const Combinaison&)=default;
        Combinaison& operator=(const Combinaison&)=default;

    };
    class Jouer;
    //游戏控制器：管理 SET! 游戏的对局流程
    class Controleur{
        friend Jouer;
    private:
        Plateau plateau;//游戏面板
        Pioche* pioche;//牌堆
        vector<Jouer*>v;//当前游戏里的玩家
        vector<const Jouer*>v_l;//游戏里的玩家
        static Controleur* controleur;
        void initGame();//初始化游戏
        void gameLoop();//游戏主循环
        Controleur();
    public:
        Plateau& getPlateau(){return plateau;}
        static Controleur* GetInstance();
        static void DestroyInstance();
        void distribuer();
        ~Controleur();
        Controleur(const Controleur&)=delete;
        Controleur& operator=(const Controleur&)=delete;
        void ShowRemainJouer();
        void ShowAllJouer();
        void jouer();
    };
    ostream &operator<<(ostream&cout,Combinaison c);
    class Jouer{
    private:
        string nom;
        int score;
    public:
        Jouer(string name):nom(name),score(0){
            if (Controleur::GetInstance()){
                Controleur::GetInstance()->v.push_back(this);
                Controleur::GetInstance()->v_l.push_back(this);
            }
        };
        void AjouterScore(){this->score++;}
        const string& getNom() const { return nom;}
        int getScore() const { return score;}
        Jouer operator=(const Jouer&)=delete;//禁用赋值构造器
        ~Jouer()=default;

    };
    ostream &operator<<(ostream&cout,const Jouer&j);
}

#endif //CPP_LEARN_MYSET_H
