//
// Created by 21718 on 2025/11/18.
//
#include <set>
#include "MySet.h"
namespace MySet{
    string toString(Couleur c){
        switch (c) {
            case Couleur::rouge:return "rouge";
            case Couleur::vert:return "vert";
            case Couleur::mauve:return "mauve";
            default: throw SetException("Couleur inconnue");
        }
    }
    string toString(Nombre v){
        switch (v) {
            case Nombre::un:return "1";
            case Nombre::deux:return "2";
            case Nombre::trois:return "3";
            default: throw SetException("Numbre inconnue");
        }
    }
    string toString(Forme f){
        switch (f) {
            case Forme::ovale:return "ovale";
            case Forme::vague:return "vague";
            case Forme::losange:return "losange";
            default: throw SetException("Forme inconnue");
        }
    }
    string toString(Remplissage v){
        switch (v) {
            case Remplissage::plein:return "plein";
            case Remplissage::vide:return "vide";
            case Remplissage::hachure:return "hachure";
            default: throw SetException("Remplissage inconnue");
        }
    }
    ostream &operator<<(ostream&cout,Couleur c){cout<<toString(c);return cout;}
    ostream &operator<<(ostream&cout,Nombre n){ cout<<toString(n);return cout;}
    ostream &operator<<(ostream&cout,Forme f){ cout<<toString(f);return cout;}
    ostream &operator<<(ostream&cout,Remplissage r){ cout<<toString(r);return cout;}
    Jeu::~Jeu() {
        for (size_t i = 0; i < 81; i++) delete cartes[i];
    }
   void Jeu::DestroyInstance() {
        if (obj!= nullptr) {
            delete obj;
            obj= nullptr;
        }
    }
    Jeu::Jeu() {
        int num=0;
        for(auto it=allCouleurs.begin();it!=allCouleurs.end();it++){
            for(auto it1=allNombre.begin();it1!=allNombre.end();it1++){
                for(auto it2=allForme.begin();it2!=allForme.end();it2++){
                    for(auto it3=allRemplissage.begin();it3!=allRemplissage.end();it3++){
                        cartes[num++]=new Carte(*it,*it1,*it2,*it3);
                    }
                }
            }
        }
    }
    Jeu*Jeu::obj= nullptr;
    Jeu& Jeu::GetInstance(){
        if(obj== nullptr){obj=new Jeu;}
        return *obj;
    }
    //const 修饰的对象（如 const Carte carte）只能调用被 const 修饰的成员函数
    const Carte& Jeu::getCarte(size_t i) const{
        //用于获取 cartes 数组中第 i 个指针所指向的卡牌的引用。若 i 大于或等于 81，该方法会抛出异常。
        if(i>=81) throw SetException("carte inexistante");//throw是异常处理的核心关键字
        return *cartes[i];
    }
    bool Jeu::Iterator::isDone(){
        if(index==80)return true;
        return false;
    }
    void Jeu::Iterator::next(){
        index++;
    }
    void Jeu::FormeIterator::next(){
        while(index<80){
            index++;
            if(obj->cartes[index]->forme==f)break;
        }
    }
    const Carte* Jeu::Iterator::currentItem(){
        return obj->cartes[index];
    }
    Jeu::Iterator Jeu::Iterator::operator++(){
        this->next();
        return *(this);
    }
    Jeu::Iterator Jeu::FormeIterator::operator++(){
        this->next();
        return *(this);
    }
    const Carte& Jeu::Iterator::operator*(){
        return *currentItem();
    }
    Jeu::FormeIterator Jeu::end(Forme f){
        int num=0;
        for(int i=80;i>=0;i--){
            if(obj->cartes[i]->forme==f){
                num=i;
                break;
            }
        }
        return FormeIterator(f,num);
    }
    bool Carte::operator==(const Carte& autre)const{
        if(this->remplissage==autre.remplissage&&this->forme==autre.forme&&this->nombre==autre.nombre&&this->couleur==autre.couleur)
            return true;
        return false;
    }
    bool Carte::operator!=(const Carte& autre){
        if(autre.remplissage==this->remplissage)return false;
        if(autre.forme==this->forme)return false;
        if(autre.nombre==this->nombre)return false;
        if(autre.couleur== this->couleur)return false;
        return true;
    }
    ostream & operator<<(ostream&cout,const Carte& e){
        cout<<'['<<e.couleur<<" "<<e.nombre<<" "<<e.forme<<" "<<e.remplissage<<']';
        return cout;
    }
    Pioche::Pioche():nb(81){
        cartes=new const Carte*[81];
        int num=0;
        for(auto i=Jeu::GetInstance().begin();!(i==Jeu::GetInstance().end());++i)
        {
            cartes[num++]=&(*i);
        };
    }
    const Carte& Pioche::piocher(){
        //用于随机抽取一张卡牌：若牌堆为空，该方法会抛出异常；否则返回从牌堆中移除的卡牌的引用
        if(estVide())throw SetException("empty pioche");
        int i=rand()%nb;
        const Carte* ChooseCarte=cartes[i];
        cartes[i]=cartes[nb-1];
        nb--;
        return *ChooseCarte;
    }
    Pioche::~Pioche(){
        delete[] cartes;
    }
    void Plateau::ajouter(const Carte& carte){
        if(nb==MaxNb){
            const Carte**NewCartes=new const Carte*[nb*2];
            const Carte** Old=cartes;
            cartes=NewCartes;
            for(int i=0;i<nb;i++){
                cartes[i]=Old[i];
            }
            delete[]Old;
            MaxNb=nb*2;
        }
        cartes[nb]=&carte;
        nb++;
    }
    void Plateau::DeleteSet(int i,int j,int k){
        cartes[i]=cartes[nb-1];
        nb--;
        cartes[j]=cartes[nb-1];
        nb--;
        cartes[k]=cartes[nb-1];
        nb--;
    }
    void Plateau::DeleteCarte(int i){
        cartes[i]=cartes[nb-1];
        nb--;
    }
    void Plateau::print(ostream&cout) {
        cout<<"== PLATEAU ==";
        for(int i=0;i<nb;i++){
            if(i%3==0)cout<<endl;
            cout<<*cartes[i];
        }
        cout<<endl;
    }
    Plateau::Plateau(const Plateau&p){
        cartes=new const Carte*[p.MaxNb];
        MaxNb=p.MaxNb;
        nb=p.nb;
        for(int i=0;i<nb;i++){
            cartes[i]=p.cartes[i];
        }
    }
    Plateau& Plateau::operator=(Plateau& p){
        if(this==&p)return *this;
        delete[] this->cartes;
        this->nb=p.nb;
        this->MaxNb=p.MaxNb;
        this->cartes=new const Carte*[p.MaxNb];
        for(int i=0;i<nb;i++){
            cartes[i]=p.cartes[i];
        }
        return *this;
    }
    ostream& operator<<(ostream&cout,Plateau p){
        p.print(cout);
        return cout;
    }
    const Plateau::Iterator& Plateau::Iterator:: operator++(){
        next();
        return *(this);
    }
    const Carte& Plateau::Iterator::operator*(){
        return *CurrentCarte();
    }
    bool Plateau::Iterator::operator!=(const Iterator& it){
        if(this->index!=it.index)return true;
        return false;
    }
    bool Combinaison::estUnSET(){
        // 检查颜色维度
        bool colorValid = ((c1->getCouleur() == c2->getCouleur() && c2->getCouleur() == c3->getCouleur()) || // 全部相同
                           (c1->getCouleur() != c2->getCouleur() && c2->getCouleur() != c3->getCouleur() &&
                            c1->getCouleur() != c3->getCouleur())); // 全部不同
        // 检查数量维度
        bool numberValid = ((c1->getNombre() == c2->getNombre() && c2->getNombre() == c3->getNombre()) || // 全部相同
                            (c1->getNombre() != c2->getNombre() && c2->getNombre() != c3->getNombre() &&
                             c1->getNombre() != c3->getNombre())); // 全部不同
        // 检查形状维度
        bool shapeValid = ((c1->getForme() == c2->getForme() && c2->getForme() == c3->getForme()) || // 全部相同
                           (c1->getForme() != c2->getForme() && c2->getForme() != c3->getForme() &&
                            c1->getForme() != c3->getForme())); // 全部不同
        // 检查填充维度
        bool fillValid = ((c1->getRemplissage() == c2->getRemplissage() && c2->getRemplissage() == c3->getRemplissage()) || // 全部相同
                          (c1->getRemplissage() != c2->getRemplissage() && c2->getRemplissage() != c3->getRemplissage() &&
                           c1->getRemplissage() != c3->getRemplissage())); // 全部不同
        // 只有当所有维度都满足SET规则时，才返回true
        return colorValid && numberValid && shapeValid && fillValid;
    }
    ostream &operator<<(ostream&cout,Combinaison c){
        cout<<"=====Combinaison=====";
        cout<<'['<<*c.getCarte1()<<endl;
        cout<<*c.getCarte2()<<endl;
        cout<<*c.getCarte3()<<endl<<']';
        return cout;
    }
    Controleur::Controleur(){
        pioche=new Pioche();
    }
    Controleur* Controleur::GetInstance(){
        if(controleur== nullptr){
            controleur=new Controleur;
        }
        return controleur;
    }
    void Controleur::distribuer(){
        /*
         *若游戏面板中的卡牌数量少于 12 张，distribuer() 会尝试补充卡牌，使面板最终包含 12 张卡牌；
          若游戏面板中的卡牌数量不少于 12 张，distribuer() 会尝试仅向面板添加 1 张卡牌。
          */
        if(plateau.nb>=12&&!pioche->estVide())plateau.ajouter(pioche->piocher());
        while(plateau.nb<12&&!pioche->estVide()){
            plateau.ajouter(pioche->piocher());
        }

    }
    Controleur::~Controleur(){
        delete pioche;
        for (auto* joueur : v) {
            delete joueur;
        }
    }
    void Controleur:: DestroyInstance() {
        if (controleur != nullptr) {
            delete controleur;
            controleur = nullptr;
        }
    }
    ostream &operator<<(ostream&cout,const Jouer&j){
        cout<<"姓名："<<j.getNom()<<"分数："<<j.getScore();
        return cout;
    }
    void Controleur::ShowRemainJouer(){
        cout<<"==========RemainJouer========="<<endl;
        for(auto it=v.begin();it!=v.end();++it){
            cout<<**it<<endl;
        }
    }
    void Controleur::ShowAllJouer(){
        cout<<"==========AllJouer========="<<endl;
        for(auto it=v_l.begin();it!=v_l.end();it++){
            cout<<**it<<endl;
        }
    }
    void afficherCartes(){
        for(auto i=Jeu::GetInstance().begin();!(i==Jeu::GetInstance().end());++i)
        {
            cout<<*i<<endl;
        }
    }
    void afficherCartes_std(){
        for(auto i=Jeu::GetInstance().begin_std();i!=Jeu::GetInstance().end_std();++i)
        {
            cout<<*i<<endl;
        }
    }
    void afficherCartes(Forme f){
        int num=1;
        for(auto i=Jeu::GetInstance().begin(f);!(i==Jeu::GetInstance().end(f));++i){
            cout<<*i<<endl;
        }
    }
    void afficherCartes(Plateau& p) {
        int num=1;
        for (auto it = p.begin(); it != p.end(); ++it) {
            std::cout << num << "." << *it << "\n";
            num++;
        }
    }
    bool Plateau::CheckSet(){
        for(int i=0;i<this->nb;i++){
            for(int j=i+1;j<this->nb;j++){
                for(int k=j+1;k<this->nb;k++){
                    if(Combinaison(this->cartes[i],this->cartes[j],this->cartes[k]).estUnSET())return true;
                }
            }
        }
        return false;
    }
    void Plateau::DisplaySet(){
        set<int>v;
        for(int i=0;i<this->nb;i++){
            for(int j=i+1;j<this->nb;j++){
                for(int k=j+1;k<this->nb;k++){
                    if(Combinaison(this->cartes[i],this->cartes[j],this->cartes[k]).estUnSET()){
                        cout<<"======可以组成set的卡是======"<<endl;
                        cout<<i+1<<"."<<*(this->cartes[i])<<endl;
                        cout<<j+1<<"."<<*(this->cartes[j])<<endl;
                        cout<<k+1<<"."<<*(this->cartes[k])<<endl;
                        v.insert(i);
                        v.insert(j);
                        v.insert(k);
                    }
                }
            }
        }
        for(auto i:v){
            DeleteCarte(i);
        }
    }
    void Controleur::initGame(){
        // 1. 创建玩家
        // 2. 初始发牌（发满12张）
        // 3. 显示初始牌桌
        cout<<"请输入参与游戏的玩家个数"<<endl;
        int num;
        cin>>num;
        while(num--){
            cout<<"请输入玩家姓名：";
            string xxx;
            cin>>xxx;
            new Jouer(xxx);
        }
        distribuer();
        //检查游戏面板上有没有set
        while(!controleur->getPlateau().CheckSet()){
            distribuer();
        }
    }
    void Controleur::gameLoop(){
        int num=0;
        while(!pioche->estVide()&&!v.empty()){
            for(auto it=v.begin();it!=v.end();){
                num++;
                //查看牌桌状态
                if(plateau.nb<12){distribuer();}
                //查看当前牌桌上是否存在set
                while(!controleur->plateau.CheckSet()){
                    distribuer();
                }
                cout<<"=====当前游戏面板上卡牌展示====="<<endl;
                afficherCartes(plateau);
                //玩家选择
                cout<<(*it)->getNom()<<","<<"请进行选择：(请输入展示的游戏卡牌的序号)"<<endl;
                int i,j,k;
                cin>>i>>j>>k;
                if(i==0&&j==0&&k==0){
                    cout<<"玩家"<<(*it)->getNom()<<"退出游戏"<<endl;
                    it=it = v.erase(it);
                    if(v.empty()){
                        cout<<"当前没有玩家游戏"<<endl;
                        break;
                    }
                    cout<<"当前玩家还剩"<<endl;
                    ShowRemainJouer();
                } else{
                    if(Combinaison(plateau.cartes[i-1],plateau.cartes[j-1],plateau.cartes[k-1]).estUnSET()){
                        cout<<"恭喜你成功找到set"<<endl;
                        (*it)->AjouterScore();
                        plateau.DeleteSet(i-1,j-1,k-1);
                        num=0;
                    }
                    it++;
                }
            }
            if(num==2){
                cout<<"由于两轮都没有人找到set，我将给你们提供答案"<<endl;
                controleur->getPlateau().DisplaySet();
                num=0;
            }
        }
    }
    void Controleur::jouer(){
        initGame();
        cout << "===== Début du jeu SET! =====" << endl;
        gameLoop();
        cout<<"游戏结束";
        ShowAllJouer();
        Jeu::DestroyInstance();
        Controleur::DestroyInstance();
    }
    Controleur* Controleur::controleur = nullptr;
}

