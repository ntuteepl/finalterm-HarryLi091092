#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <iomanip>
#include <limits>
using namespace std;

#define peopleType 6
#define monsterType 3

bool luck(int);

class Character
{
protected:
  static const int EXP_LV = 100;
  static const int levelCap = 50;
  string name;
  string trait;
  int level;
  int hp;
  int speed; // 決定攻擊順序
  int atk;
  int luck; // 有機率將特性效果*2或攻擊力*2
  int def;
  int exp;     // 當前經驗
  int expNeed; // 升級所需經驗
  bool ranged;
  void levelUp(int hUp, int sUp, int aUp, int dUp);

public:
  Character(string n, string t, int lv, int h, int s, int a, int l, int d, bool ranged);
  string getName() { return this->name; };
  string getTrait() { return this->trait; };
  bool getRanged() { return this->ranged; }
  virtual int getLevel() { return this->level; };
  virtual void setHP(int hp) { this->hp = hp; };
  virtual int getHP() { return this->hp; };
  virtual int getSpeed() { return this->speed; };
  virtual int getAttack() { return this->atk; };
  virtual int getLuck() { return this->luck; };
  virtual int getDefense() { return this->def; };
  virtual int getExp() { return this->exp; };
  void levelUp(int);
  virtual void print();
};

Character::Character(string n, string t, int lv, int h, int s, int a, int l, int d, bool r) : name(n), trait(t), level(lv), hp(h), speed(s), atk(a), luck(l), def(d), exp(0), expNeed(pow(level, 2) * EXP_LV), ranged(r) {}

void Character::levelUp(int hUp, int sUp, int aUp, int dUp)
{
  while (this->exp > this->expNeed && this->level < levelCap)
  {
    this->exp -= this->expNeed;
    this->level++;
    this->hp += hUp;
    this->speed += sUp;
    this->atk += aUp;
    this->def += dUp;
    this->expNeed = pow(level, 2) * EXP_LV;
  }
  cout << this->getName() << " Level up!(Lv." << this->getLevel() << " now)" << endl;
}

void Character::levelUp(int exp)
{
  this->exp += exp;
  if (this->exp > pow(this->levelCap, 2) * EXP_LV)
    this->exp = pow(this->levelCap, 2) * EXP_LV;
  else if (this->exp >= pow(this->level, 2) * EXP_LV)
    this->levelUp(this->getHP() / this->getLevel(), this->getSpeed() / this->getLevel(), this->getAttack() / this->getLevel(), this->getDefense() / this->getLevel());
}

void Character::print()
{
  cout << "|\n| HP: " << left << setw(32) << this->hp;
  // 血量是否大於0
  cout << "|\n| SPEED: " << left << setw(29) << this->speed << "|\n| ATK: " << left << setw(31) << this->atk << "|\n| LUCK: " << left << setw(30) << this->luck << "|\n| DEF: " << left << setw(31) << this->def;
}
// 設計戰士class
class Warrior : public Character
{
private:
  static const int HP_LV = 80;
  static const int SP_LV = 3;
  static const int AT_LV = 30;
  static const int LU_LV = 10;
  static const int DE_LV = 10;
  static const bool ranged = 0; // 0為近戰;1為遠攻

public:
  Warrior(string n, string t, int lv = 1) : Character(n, t, lv, lv * HP_LV, lv * SP_LV, lv * AT_LV, LU_LV, lv * DE_LV, ranged) {}
  void print()
  {
    cout << left << setw(24) << "Warrior" << "|\n| name: " << left << setw(this->name.size()) << this->name << left << " (Lv." << setw(2) << this->level << setw(23 - this->name.size()) << ")";
    Character::print();
    cout << "|\n| Need " << left << setw(6) << expNeed - this->exp << left << setw(25) << " to level up" << left << setw(40) << "|\n| Trait: Moderate HP and ATK." << "|" << endl;
  }
};

// 設計法師class
class Wizard : public Character
{
private:
  static const int HP_LV = 70;
  static const int SP_LV = 3;
  static const int AT_LV = 35;
  static const int LU_LV = 10;
  static const int DE_LV = 7;
  static const bool ranged = 1;

public:
  Wizard(string n, string t, int lv = 1) : Character(n, t, lv, lv * HP_LV, lv * SP_LV, lv * AT_LV, LU_LV, lv * DE_LV, ranged) {}
  void print()
  {
    cout << left << setw(24) << "Wizard" << "|\n| name: " << left << setw(this->name.size()) << this->name << left << " (Lv." << setw(2) << this->level << setw(23 - this->name.size()) << ")";
    Character::print();
    cout << "|\n| Need " << left << setw(6) << expNeed - this->exp << left << setw(25) << " to level up" << left << setw(40) << "|\n| Trait: Moderate HP and ATK." << "|" << endl;
  }
};

// 設計刺客class
class Assassin : public Character
{
private:
  static const int HP_LV = 50;
  static const int SP_LV = 5;
  static const int AT_LV = 25;
  static const int LU_LV = 30;
  static const int DE_LV = 5;
  static const bool ranged = 0;

public:
  Assassin(string n, string t, int lv = 1) : Character(n, t, lv, lv * HP_LV, lv * SP_LV, lv * AT_LV, LU_LV, lv * DE_LV, ranged) {}
  void print()
  {
    cout << left << setw(24) << "Assassin" << "|\n| name: " << left << setw(this->name.size()) << this->name << left << " (Lv." << setw(2) << this->level << setw(23 - this->name.size()) << ")";
    Character::print();
    cout << "|\n| Need " << left << setw(6) << expNeed - this->exp << left << setw(25) << " to level up" << left << setw(40) << "|\n| Trait: High SPEED but less DEF." << "|" << endl;
  }
};

// 設計射手class
class Archer : public Character
{
private:
  static const int HP_LV = 50;
  static const int SP_LV = 3;
  static const int AT_LV = 45;
  static const int LU_LV = 15;
  static const int DE_LV = 0;
  static const bool ranged = 1;

public:
  Archer(string n, string t, int lv = 1) : Character(n, t, lv, lv * HP_LV, lv * SP_LV, lv * AT_LV, LU_LV, lv * DE_LV, ranged) {}
  void print()
  {
    cout << left << setw(24) << "Archer" << "|\n| name: " << left << setw(this->name.size()) << this->name << left << " (Lv." << setw(2) << this->level << setw(23 - this->name.size()) << ")";
    Character::print();
    cout << "|\n| Need " << left << setw(6) << expNeed - this->exp << left << setw(25) << " to level up" << left << setw(40) << "|\n| Trait: High ATK but no DEF." << "|" << endl;
  }
};

// 設計坦克class
class Tank : public Character
{
private:
  static const int HP_LV = 120;
  static const int SP_LV = 1;
  static const int AT_LV = 15;
  static const int LU_LV = 5;
  static const int DE_LV = 15;
  static const bool ranged = 0;
  static const bool tank = 1;

public:
  Tank(string n, string t, int lv = 1) : Character(n, t, lv, lv * HP_LV, lv * SP_LV, lv * AT_LV, LU_LV, lv * DE_LV, ranged) {}
  void print()
  {
    cout << left << setw(24) << "Tank" << "|\n| name: " << left << setw(this->name.size()) << this->name << left << " (Lv." << setw(2) << this->level << setw(23 - this->name.size()) << ")";
    Character::print();
    cout << "|\n| Need " << left << setw(6) << expNeed - this->exp << left << setw(25) << " to level up" << left << setw(40) << "|\n| Trait: Prioritize taking damage." << "|" << endl;
  }
};

// 設計補師class
class Healer : public Character
{
private:
  static const int HP_LV = 60;
  static const int SP_LV = 2;
  static const int AT_LV = 0;
  static const int LU_LV = 15;
  static const int DE_LV = 5;
  static const bool ranged = 1;
  static const bool healer = 1;

public:
  Healer(string n, string t, int lv = 1) : Character(n, t, lv, lv * HP_LV, lv * SP_LV, lv * AT_LV, LU_LV, lv * DE_LV, ranged) {}
  void print()
  {
    cout << left << setw(24) << "Healer" << "|\n| name: " << left << setw(this->name.size()) << this->name << left << " (Lv." << setw(2) << this->level << setw(23 - this->name.size()) << ")";
    Character::print();
    cout << "|\n| Need " << left << setw(6) << expNeed - this->exp << left << setw(25) << " to level up" << "|\n| Trait: Choose one person to restore " << left << setw(34) << "|\n|\t 1/4 of Lost HP." << "|" << endl;
  }
};

// 設計石頭怪class
class Rock : public Character
{
private:
  static const int HP = 250;
  static const int SP = 2;
  static const int AT = 20;
  static const int LU = 10;
  static const int DE = 35;
  static const int EXP = 100;

public:
  Rock() : Character("", "Rock", 0, HP, SP, AT, LU, DE, 0) {}
  void print()
  {
    cout << left << setw(29) << "Rock";
    Character::print();
    cout << "|\n| Trait: Prioritize taking damage     |" << endl;
  }
  int getExp() { return this->EXP; }
};
// 設計飛龍class
class Wyvern : public Character
{
private:
  static const int HP = 3000;
  static const int SP = 19;
  static const int AT = 500;
  static const int LU = 15;
  static const int DE = 120;
  static const int EXP = 10000;

public:
  Wyvern() : Character("", "Wyvern", 0, HP, SP, AT, LU, DE, 0) {}
  void print()
  {
    cout << left << setw(29) << "Wyvern";
    Character::print();
    cout << "|\n| Trait: (1)Only ranged attacks can   " << left << setw(34) << "|\n|\t    deal damage." << left << setw(34) << "|\n|\t (2)HP<30%, DEF*2" << "|" << endl;
  }
  int getExp() { return this->EXP; }
};
// 設計撒旦class
class Satan : public Character
{
private:
  static const int HP = 5000;
  static const int SP = 22;
  static const int AT = 1000;
  static const int LU = 20;
  static const int DE = 100;
  static const int EXP = 50000;

public:
  Satan() : Character("", "Satan", 0, HP, SP, AT, LU, DE, 0) {}
  void print()
  {
    cout << left << setw(29) << "Satan";
    Character::print();
    cout << "|\n| Trait: (1)HP>40% , Recover 30% of   " << setw(34) << "|\n|\t    ATK as HP each turn" << "|\n|\t (2)HP<40% , attack changes to|\n|\t    randomly killing a person.|" << endl;
  }
  void recover()
  {
    Character::setHP(this->hp + this->atk / 5);
    // 防止血量溢出
    if (Character::getHP() > HP)
      Character::setHP(HP);
  }
  int getExp() { return this->EXP; }
};

// 人類陣營class
class pTeam
{
protected:
  string teamname;
  int pCount;

public:
  vector<Character *> pMember;
  pTeam();
  int getpCount() { return this->pCount; }
  void setName(string n) { this->teamname = n; }
  string getName() { return this->teamname; }
  void addpMember(string name, string trait, int lv);
  void print();
  bool repeat(string name);
  void pOrder(int[], int);
  void heal(string);
  void winSetHp();
};

pTeam::pTeam() { pCount = 0; }
// 新增成員
void pTeam::addpMember(string n, string t, int l)
{
  if (t == "Warior")
  {
    Warrior *ptr = new Warrior(n, t, l);
    pMember.push_back(ptr);
  }
  if (t == "Wizard")
  {
    Wizard *ptr = new Wizard(n, t, l);
    pMember.push_back(ptr);
  }
  if (t == "Assassin")
  {
    Assassin *ptr = new Assassin(n, t, l);
    pMember.push_back(ptr);
  }
  if (t == "Archer")
  {
    Archer *ptr = new Archer(n, t, l);
    pMember.push_back(ptr);
  }
  if (t == "Tank")
  {
    Tank *ptr = new Tank(n, t, l);
    pMember.push_back(ptr);
  }
  if (t == "Healer")
  {
    Healer *ptr = new Healer(n, t, l);
    pMember.push_back(ptr);
  }
  pCount++;
}

void pTeam::print()
{
  cout << "--------------- Peoples ---------------" << endl;
  cout << "| Team name: " << left << setw(25) << this->getName() << "|\n|" << right << setw(38) << "|";
  for (int i = 0; i < pCount; i++)
  {
    cout << "\n| Member " << left << setw(3) << i + 1 << ": ";
    pMember[i]->print();
    if (i != pCount - 1)
      cout << "| *********************************** |";
  }
  cout << "--------------- Peoples ---------------\n"
       << endl;
}

bool pTeam::repeat(string name)
{
  for (int i = 0; i < pCount; i++)
    if (pMember[i]->getName() == name)
      return true;
  return false;
}
// 根據速度值計算攻擊順序，並將索引值儲存於陣列
void pTeam::pOrder(int order[], int num)
{
  int lastMax = numeric_limits<int>::max(), max;

  for (int i = 0; i < num; i++)
  {
    max = 0;
    // 訪問每個Member
    for (int j = 0; j < this->pCount; j++)
    {
      // 只儲存實際存活人數
      if (pMember[j]->getHP() > 0 && pMember[j]->getSpeed() > max && pMember[j]->getSpeed() <= lastMax)
      {
        // 考慮檢索到相同索引值的情況
        bool same = false;
        for (int k = 0; k < i; k++)
          if (j == order[k])
            same = true;
        if (same)
          continue;
        max = pMember[j]->getSpeed();
        order[i] = j;
      }
    }
    lastMax = max;
  }
}

void pTeam::heal(string name)
{
  string career[6] = {"Warior", "Wizard", "Assassin", "Archer", "Tank", "Healer"};
  int lvWeight[6] = {80, 70, 50, 50, 120, 60};
  for (int i = 0; i < pCount; i++)
    if (pMember[i]->getName() == name)
    {
      for (int j = 0; j < 6; j++)
        if (pMember[i]->getTrait() == career[j])
        {
          int originalHp = pMember[i]->getLevel() * lvWeight[j];

          pMember[i]->setHP(pMember[i]->getHP() + ((originalHp - pMember[i]->getHP()) / 4));
        }
      break;
    }
}

void pTeam::winSetHp()
{
  string career[6] = {"Warior", "Wizard", "Assassin", "Archer", "Tank", "Healer"};
  int lvWeight[6] = {80, 70, 50, 50, 120, 60};
  for (int i = 0; i < pCount; i++)
    for (int j = 0; j < 6; j++)
    {
      if (pMember[i]->getTrait() == career[j])
      {
        pMember[i]->setHP(pMember[i]->getLevel() * lvWeight[j]);
        j = 6;
      }
    }
}

// 怪物陣營class
class mTeam
{
protected:
  int rcount;
  int wcount;
  int scount;
  int mCount;

public:
  vector<Character *> mMember;
  mTeam();
  int getCount(int);
  void addmMember(string trait);
  void print();
  void mOrder(int[], int);
};

mTeam::mTeam()
{
  rcount = 0;
  wcount = 0;
  scount = 0;
  mCount = 0;
}

int mTeam::getCount(int index)
{
  if (index == 0) // Rock
    return this->rcount;
  if (index == 1) // Wyvern
    return this->wcount;
  if (index == 2) // Satan
    return this->scount;
  if (index == 3) // Total
    return this->mCount;
  return 0;
}

// 新增怪物
void mTeam::addmMember(string t)
{
  if (t == "Rock")
  {
    Rock *ptr = new Rock();
    mMember.push_back(ptr);
    rcount++;
  }
  if (t == "Wyvern")
  {
    Wyvern *ptr = new Wyvern();
    mMember.push_back(ptr);
    wcount++;
  }
  if (t == "Satan")
  {
    Satan *ptr = new Satan();
    mMember.push_back(ptr);
    scount++;
  }
  this->mCount++;
}

void mTeam::print()
{
  bool rcheck = 0, wcheck = 0, scheck = 0;
  cout << "--------------- Monster ---------------" << endl;
  for (int i = 0; i < mCount; i++)
  {
    if (mMember[i]->getTrait() == "Rock" && rcheck == 0)
    {
      if (!(rcheck == 0 && wcheck == 0 && scheck == 0))
        cout << "| *********************************** |\n";
      cout << "| " << left << setw(4) << this->rcount << " * ";
      mMember[i]->print();
      rcheck = 1;
    }
    if (mMember[i]->getTrait() == "Wyvern" && wcheck == 0)
    {
      if (!(rcheck == 0 && wcheck == 0 && scheck == 0))
        cout << "| *********************************** |\n";
      cout << "| " << left << setw(4) << this->wcount << " * ";
      mMember[i]->print();
      wcheck = 1;
    }
    if (mMember[i]->getTrait() == "Satan" && scheck == 0)
    {
      if (!(rcheck == 0 && wcheck == 0 && scheck == 0))
        cout << "| *********************************** |\n";
      cout << "| " << left << setw(4) << this->scount << " * ";
      mMember[i]->print();
      scheck = 1;
    }
  }
  cout << "--------------- Monster ---------------" << endl;
}

// 根據速度值計算攻擊順序，並將索引值儲存於陣列
void mTeam::mOrder(int order[], int num)
{
  int lastMax = numeric_limits<int>::max(), max;

  for (int i = 0; i < num; i++)
  {
    max = 0;
    // 訪問每個Member
    for (int j = 0; j < this->mCount; j++)
    {
      // 只儲存實際存活人數
      if (mMember[j]->getHP() > 0 && mMember[j]->getSpeed() > max && mMember[j]->getSpeed() <= lastMax)
      {
        // 考慮檢索到相同索引值的情況
        bool same = false;
        for (int k = 0; k < i; k++)
          if (j == order[k])
            same = true;
        if (same)
          continue;
        max = mMember[j]->getSpeed();
        order[i] = j;
      }
    }
    lastMax = max;
  }
}

bool battle(pTeam pteam, mTeam mteam)
{
  srand(time(NULL));
  int realpCount = pteam.getpCount(), realmCount = mteam.getCount(3), round = 0;
  // 戰鬥直到其中一方人數為0
  while (realpCount > 0 && realmCount > 0)
  {
    // 根據速度值儲存攻擊順序的索引值
    int pOrder[realpCount] = {}, mOrder[realmCount] = {};

    pteam.pOrder(pOrder, realpCount);
    mteam.mOrder(mOrder, realmCount);
    // 攻擊環節
    int p = 0, m = 0;
    while (p < realpCount)
    {
      while (m < realmCount)
      {
        // 戰鬥過程死亡，跳到下一個沒死亡的角色
        while (p < realpCount && pteam.pMember[pOrder[p]]->getHP() <= 0)
          p++;
        while (m < realmCount && mteam.mMember[mOrder[m]]->getHP() <= 0)
          m++;
        // 人類速度值大於怪物且須活著
        if (p != realpCount && m != realmCount && pteam.pMember[pOrder[p]]->getHP() > 0 && pteam.pMember[pOrder[p]]->getSpeed() >= mteam.mMember[mOrder[m]]->getSpeed())
        {
          // 若職業為補師
          bool hcheck = false;
          if (pteam.pMember[pOrder[p]]->getTrait() == "Healer" && round != 0)
          {
            string name;
            hcheck = true;
            cout << "choose a partner to heal(Enter name): ";
            // 防止不合理的輸入
            while (cin >> name)
            {
              bool found = 0;
              for (int i = 0; i < pteam.getpCount(); i++)
                if (pteam.pMember[i]->getName() == name && pteam.pMember[i]->getHP() > 0)
                  found = true;
              if (cin.fail() || !found)
              {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please re-enter: ";
              }
              else
                break;
            }
            pteam.heal(name);
            if (luck(pteam.pMember[pOrder[p]]->getLuck()))
            {
              cout << pteam.pMember[pOrder[p]]->getName() << " triggered good luck! (one more)" << endl;
              cout << "choose a partner to heal(Enter name): ";
              // 防止不合理的輸入
              while (cin >> name)
              {
                bool found = 0;
                for (int i = 0; i < pteam.getpCount(); i++)
                  if (pteam.pMember[i]->getName() == name && pteam.pMember[i]->getHP() > 0)
                    found = true;
                if (cin.fail() || !found)
                {
                  cin.clear();
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
                  cout << "Invalid input, please re-enter: ";
                }
                else
                  break;
              }
              pteam.heal(name);
            }
          }
          if (hcheck)
          {
            p++;
            continue;
          }
          bool rcheck = false, wcheck = false, scheck = false;
          // 確認怪物種類以及其是否存活
          for (int i = 0; i < mteam.getCount(3); i++)
          {
            if (mteam.mMember[i]->getTrait() == "Rock" && mteam.mMember[i]->getHP() > 0)
              rcheck = true;
            else if (mteam.mMember[i]->getTrait() == "Rock" && mteam.mMember[i]->getHP() <= 0)
              rcheck = false;
            if (mteam.mMember[i]->getTrait() == "Wyvern" && mteam.mMember[i]->getHP() > 0)
              wcheck = true;
            else if (mteam.mMember[i]->getTrait() == "Wyvern" && mteam.mMember[i]->getHP() <= 0)
              wcheck = false;
            if (mteam.mMember[i]->getTrait() == "Satan" && mteam.mMember[i]->getHP() > 0)
              scheck = true;
            else if (mteam.mMember[i]->getTrait() == "Satan" && mteam.mMember[i]->getHP() <= 0)
              scheck = false;
          }
          int damage = 0;
          // 場上有石頭怪優先攻擊石頭怪
          if (rcheck)
          {
            if (luck(pteam.pMember[pOrder[p]]->getLuck()))
            {
              cout << pteam.pMember[pOrder[p]]->getName() << " triggered good luck! (ATK * 2)" << endl;
              damage = 2 * (pteam.pMember[pOrder[p]]->getAttack() / mteam.getCount(0));
            }
            else
              damage = pteam.pMember[pOrder[p]]->getAttack() / mteam.getCount(0);
            for (int i = 0; i < mteam.getCount(3); i++)
              if (mteam.mMember[i]->getTrait() == "Rock" && (damage - mteam.mMember[i]->getDefense()) > 0)
                mteam.mMember[i]->setHP(mteam.mMember[i]->getHP() - (damage - mteam.mMember[i]->getDefense()));
          }
          else if (wcheck || scheck)
          {
            // 只有遠程角色可以對飛龍造成傷害
            if (pteam.pMember[pOrder[p]]->getRanged())
            {
              if (luck(pteam.pMember[pOrder[p]]->getLuck()))
              {
                cout << pteam.pMember[pOrder[p]]->getName() << " triggered good luck! (ATK * 2)" << endl;
                damage = 2 * (pteam.pMember[pOrder[p]]->getAttack() / (mteam.getCount(1) + mteam.getCount(2)));
              }
              else
                damage = pteam.pMember[pOrder[p]]->getAttack() / (mteam.getCount(1) + mteam.getCount(2));
              for (int i = 0; i < mteam.getCount(3); i++)
                if (mteam.mMember[i]->getTrait() != "Rock" && mteam.mMember[i]->getHP() > 0 && (damage - mteam.mMember[i]->getDefense()) > 0)
                  // 飛龍血量小於30%防禦力2倍
                  if (mteam.mMember[i]->getTrait() == "Wyvern" && mteam.mMember[i]->getHP() < 900)
                    mteam.mMember[i]->setHP(mteam.mMember[i]->getHP() - (damage - mteam.mMember[i]->getDefense() * 2));
                  else
                    mteam.mMember[i]->setHP(mteam.mMember[i]->getHP() - (damage - mteam.mMember[i]->getDefense()));
            }
            else if (scheck)
            {
              if (luck(pteam.pMember[pOrder[p]]->getLuck()))
              {
                cout << pteam.pMember[pOrder[p]]->getName() << " triggered good luck! (ATK * 2)" << endl;
                damage = 2 * (pteam.pMember[pOrder[p]]->getAttack() / mteam.getCount(2));
              }
              else
                damage = pteam.pMember[pOrder[p]]->getAttack() / mteam.getCount(2);
              for (int i = 0; i < mteam.getCount(3); i++)
                if (mteam.mMember[i]->getTrait() != "Satan" && mteam.mMember[i]->getHP() > 0)
                  mteam.mMember[i]->setHP(mteam.mMember[i]->getHP() - (damage - mteam.mMember[i]->getDefense()));
            }
          }
          p++;
        }

        // 怪物速度值大於人類且須活著
        else if (p != realpCount && m != realmCount && mteam.mMember[mOrder[m]]->getHP() > 0 && mteam.mMember[mOrder[m]]->getSpeed() > pteam.pMember[pOrder[p]]->getSpeed())
        {
          bool scrazy = false;
          // 撒旦狂暴模式隨機處決一名玩家
          if (mteam.mMember[mOrder[m]]->getTrait() == "Satan" && mteam.mMember[mOrder[m]]->getHP() > 0 && mteam.mMember[mOrder[m]]->getHP() < 2000)
          {
            cout << "***Satan crazing*** \n";
            // 產生隨機數
            int num = rand() % realpCount;

            scrazy = true;
            // 防止處決的玩家已經戰死
            while (pteam.pMember[pOrder[num]]->getHP() <= 0)
              num = rand() % realpCount;
            pteam.pMember[pOrder[num]]->setHP(0);
            cout << pteam.pMember[pOrder[num]]->getName() << " is killed" << endl;
            if (luck(mteam.mMember[mOrder[m]]->getLuck()))
            {
              cout << mteam.mMember[mOrder[m]]->getTrait() << " triggered good luck! (kill one more)" << endl;
              // 產生隨機數
              int num = rand() % realpCount;

              scrazy = true;
              // 防止處決的玩家已經戰死
              while (pteam.pMember[pOrder[num]]->getHP() <= 0)
                num = rand() % realpCount;
              pteam.pMember[pOrder[num]]->setHP(0);
              cout << pteam.pMember[pOrder[num]]->getName() << " is killed" << endl;
            }
          }
          if (scrazy)
          {
            m++;
            continue;
          }
          // 確認是否有坦克需優先攻擊坦克
          bool tcheck = false;
          for (int i = 0; i < pteam.getpCount(); i++)
            if (pteam.pMember[i]->getTrait() == "Tank" && pteam.pMember[i]->getHP() > 0)
              tcheck = true;
            else if (pteam.pMember[i]->getTrait() == "Tank" && pteam.pMember[i]->getHP() <= 0)
              tcheck = false;
          // 開始攻擊
          int damage = 0;
          if (tcheck)
          {
            int tcount = 0;

            for (int i = 0; i < pteam.getpCount(); i++)
              if (pteam.pMember[i]->getTrait() == "Tank" && pteam.pMember[i]->getHP() > 0)
                tcount++;
            if (luck(mteam.mMember[mOrder[m]]->getLuck()))
            {
              cout << mteam.mMember[mOrder[m]]->getTrait() << " triggered good luck! (ATK * 2)" << endl;
              damage = 2 * (mteam.mMember[mOrder[m]]->getAttack() / tcount);
            }
            else
              damage = mteam.mMember[mOrder[m]]->getAttack() / tcount;
            for (int i = 0; i < pteam.getpCount(); i++)
              if (pteam.pMember[i]->getTrait() == "Tank" && pteam.pMember[i]->getHP() > 0 && (damage - pteam.pMember[i]->getDefense()) > 0)
                pteam.pMember[i]->setHP(pteam.pMember[i]->getHP() - (damage - pteam.pMember[i]->getDefense()));
          }
          else
          {
            if (luck(mteam.mMember[mOrder[m]]->getLuck()))
            {
              cout << mteam.mMember[mOrder[m]]->getTrait() << " triggered good luck! (ATK * 2)" << endl;
              cout << mteam.mMember[mOrder[m]]->getTrait() << " triggered good luck! (ATK * 2)" << endl;
              damage = 2 * (mteam.mMember[mOrder[m]]->getAttack() / realpCount);
            }
            else
              damage = mteam.mMember[mOrder[m]]->getAttack() / realpCount;
            for (int i = 0; i < pteam.getpCount(); i++)
              if (pteam.pMember[i]->getHP() > 0 && (damage - pteam.pMember[i]->getDefense()) > 0)
                pteam.pMember[i]->setHP(pteam.pMember[i]->getHP() - (damage - pteam.pMember[i]->getDefense()));
          }
          // 撒旦正常模式吸血
          if (mteam.mMember[mOrder[m]]->getTrait() == "Satan" && mteam.mMember[mOrder[m]]->getHP() > 2000)
          {
            if (mteam.mMember[mOrder[m]]->getHP() + 1500 > 5000)
              mteam.mMember[mOrder[m]]->setHP(5000);
            else
              mteam.mMember[mOrder[m]]->setHP(mteam.mMember[mOrder[m]]->getHP() + 1500);
          }
          m++;
        }
        // 結算剩餘未攻擊的怪獸
        while (p == realpCount && m < realmCount)
        {
          // 戰鬥過程死亡
          if (mteam.mMember[mOrder[m]]->getHP() < 0)
            m++;
          else
          {
            bool scrazy = false;
            // 撒旦狂暴模式隨機處決一名玩家
            if (mteam.mMember[mOrder[m]]->getTrait() == "Satan" && mteam.mMember[mOrder[m]]->getHP() > 0 && mteam.mMember[mOrder[m]]->getHP() < 2000)
            {
              cout << "***Satan crazing*** ";
              // 產生隨機數
              int num = rand() % realpCount;

              scrazy = true;
              // 防止處決的玩家已經戰死
              while (pteam.pMember[pOrder[num]]->getHP() <= 0)
                num = rand() % realpCount;
              pteam.pMember[pOrder[num]]->setHP(0);
              cout << pteam.pMember[pOrder[num]]->getName() << " is killed" << endl;
              if (luck(mteam.mMember[mOrder[m]]->getLuck()))
              {
                cout << mteam.mMember[mOrder[m]]->getTrait() << " triggered good luck! (kill one more)" << endl;
                // 產生隨機數
                int num = rand() % realpCount;

                scrazy = true;
                // 防止處決的玩家已經戰死
                while (pteam.pMember[pOrder[num]]->getHP() <= 0)
                  num = rand() % realpCount;
                pteam.pMember[pOrder[num]]->setHP(0);
                cout << pteam.pMember[pOrder[num]]->getName() << " is killed" << endl;
              }
            }
            if (scrazy)
            {
              m++;
              continue;
            }
            // 確認是否有坦克需優先攻擊坦克
            bool tcheck = false;
            for (int i = 0; i < pteam.getpCount(); i++)
              if (pteam.pMember[i]->getTrait() == "Tank" && pteam.pMember[i]->getHP() > 0)
                tcheck = true;
              else if (pteam.pMember[i]->getTrait() == "Tank" && pteam.pMember[i]->getHP() <= 0)
                tcheck = false;
            // 開始攻擊
            int damage = 0;
            if (tcheck)
            {
              int tcount = 0;

              for (int i = 0; i < pteam.getpCount(); i++)
                if (pteam.pMember[i]->getTrait() == "Tank" && pteam.pMember[i]->getHP() > 0)
                  tcount++;
              if (luck(mteam.mMember[mOrder[m]]->getLuck()))
              {
                cout << mteam.mMember[mOrder[m]]->getTrait() << " triggered good luck! (ATK * 2)" << endl;
                cout << mteam.mMember[mOrder[m]]->getTrait() << " triggered good luck! (ATK * 2)" << endl;
                damage = 2 * (mteam.mMember[mOrder[m]]->getAttack() / tcount);
              }
              else
                damage = mteam.mMember[mOrder[m]]->getAttack() / tcount;
              for (int i = 0; i < pteam.getpCount(); i++)
                if (pteam.pMember[i]->getTrait() == "Tank" && pteam.pMember[i]->getHP() > 0 && (damage - pteam.pMember[i]->getDefense()) > 0)
                  pteam.pMember[i]->setHP(pteam.pMember[i]->getHP() - (damage - pteam.pMember[i]->getDefense()));
            }
            else
            {
              if (luck(mteam.mMember[mOrder[m]]->getLuck()))
              {
                cout << mteam.mMember[mOrder[m]]->getTrait() << " triggered good luck! (ATK * 2)" << endl;
                cout << mteam.mMember[mOrder[m]]->getTrait() << " triggered good luck! (ATK * 2)" << endl;
                damage = 2 * (mteam.mMember[mOrder[m]]->getAttack() / realpCount);
              }
              else
                damage = mteam.mMember[mOrder[m]]->getAttack() / realpCount;
              for (int i = 0; i < pteam.getpCount(); i++)
                if (pteam.pMember[i]->getHP() > 0 && (damage - pteam.pMember[i]->getDefense()) > 0)
                  pteam.pMember[i]->setHP(pteam.pMember[i]->getHP() - (damage - pteam.pMember[i]->getDefense()));
            }
            // 撒旦正常模式吸血
            if (mteam.mMember[mOrder[m]]->getTrait() == "Satan" && mteam.mMember[mOrder[m]]->getHP() > 2000)
            {
              if (mteam.mMember[mOrder[m]]->getHP() + 1500 > 5000)
                mteam.mMember[mOrder[m]]->setHP(5000);
              else
                mteam.mMember[mOrder[m]]->setHP(mteam.mMember[mOrder[m]]->getHP() + 1500);
            }
          }
          m++;
        }
      }
      // 結算剩餘未攻擊人數
      if (m == realmCount && p < realpCount)
      {
        // 戰鬥過程死亡
        if (pteam.pMember[pOrder[p]]->getHP() < 0)
          p++;
        else
        {
          // 若職業為補師
          bool hcheck = false;
          if (pteam.pMember[pOrder[p]]->getTrait() == "Healer" && round != 0)
          {
            string name;
            hcheck = true;
            cout << "choose a partner to heal(Enter name): ";
            // 防止不合理的輸入
            while (cin >> name)
            {
              bool found = false;
              for (int i = 0; i < pteam.getpCount(); i++)
                if (pteam.pMember[i]->getName() == name && pteam.pMember[i]->getHP() > 0)
                  found = true;
              if (cin.fail() || !found)
              {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please re-enter: ";
              }
              else
                break;
            }
            pteam.heal(name);
            if (luck(pteam.pMember[pOrder[p]]->getLuck()))
            {
              cout << pteam.pMember[pOrder[p]]->getName() << " triggered good luck! (one more)" << endl;
              cout << "choose a partner to heal(Enter name): ";
              // 防止不合理的輸入
              while (cin >> name)
              {
                bool found = 0;
                for (int i = 0; i < pteam.getpCount(); i++)
                  if (pteam.pMember[i]->getName() == name && pteam.pMember[i]->getHP() > 0)
                    found = true;
                if (cin.fail() || !found)
                {
                  cin.clear();
                  cin.ignore(numeric_limits<streamsize>::max(), '\n');
                  cout << "Invalid input, please re-enter: ";
                }
                else
                  break;
              }
              pteam.heal(name);
            }
          }
          if (hcheck)
          {
            p++;
            continue;
          }

          bool rcheck = false, wcheck = false, scheck = false;
          // 確認怪物種類以及其是否存活
          for (int i = 0; i < mteam.getCount(3); i++)
          {
            if (mteam.mMember[i]->getTrait() == "Rock" && mteam.mMember[i]->getHP() > 0)
              rcheck = true;
            else if (mteam.mMember[i]->getTrait() == "Rock" && mteam.mMember[i]->getHP() <= 0)
              rcheck = false;
            if (mteam.mMember[i]->getTrait() == "Wyvern" && mteam.mMember[i]->getHP() > 0)
              wcheck = true;
            else if (mteam.mMember[i]->getTrait() == "Wyvern" && mteam.mMember[i]->getHP() <= 0)
              wcheck = false;
            if (mteam.mMember[i]->getTrait() == "Satan" && mteam.mMember[i]->getHP() > 0)
              scheck = true;
            else if (mteam.mMember[i]->getTrait() == "Satan" && mteam.mMember[i]->getHP() <= 0)
              scheck = false;
          }
          int damage = 0;
          // 場上有石頭怪優先攻擊石頭怪
          if (rcheck)
          {
            if (luck(pteam.pMember[pOrder[p]]->getLuck()))
            {
              cout << pteam.pMember[pOrder[p]]->getName() << " triggered good luck! (ATK * 2)" << endl;
              damage = 2 * (pteam.pMember[pOrder[p]]->getAttack() / mteam.getCount(0));
            }
            else
              damage = pteam.pMember[pOrder[p]]->getAttack() / mteam.getCount(0);
            cout << pteam.pMember[pOrder[p]]->getAttack() << " " << mteam.getCount(0) << endl; //
            for (int i = 0; i < mteam.getCount(3); i++)
              if (mteam.mMember[i]->getTrait() == "Rock" && (damage - mteam.mMember[i]->getDefense()) > 0)
                mteam.mMember[i]->setHP(mteam.mMember[i]->getHP() - (damage - mteam.mMember[i]->getDefense()));
          }
          else if (wcheck || scheck)
          {
            // 只有遠程角色可以對飛龍造成傷害
            if (pteam.pMember[pOrder[p]]->getRanged())
            {
              if (luck(pteam.pMember[pOrder[p]]->getLuck()))
              {
                cout << pteam.pMember[pOrder[p]]->getName() << " triggered good luck! (ATK * 2)" << endl;
                damage = 2 * (pteam.pMember[pOrder[p]]->getAttack() / (mteam.getCount(1) + mteam.getCount(2)));
              }
              else
                damage = pteam.pMember[pOrder[p]]->getAttack() / (mteam.getCount(1) + mteam.getCount(2));
              for (int i = 0; i < mteam.getCount(3); i++)
                if (mteam.mMember[i]->getTrait() != "Rock" && mteam.mMember[i]->getHP() > 0 && (damage - mteam.mMember[i]->getDefense()) > 0)
                  // 飛龍血量小於30%防禦力2倍
                  if (mteam.mMember[i]->getTrait() == "Wyvern" && mteam.mMember[i]->getHP() < 900)
                    mteam.mMember[i]->setHP(mteam.mMember[i]->getHP() - (damage - mteam.mMember[i]->getDefense() * 2));
                  else
                    mteam.mMember[i]->setHP(mteam.mMember[i]->getHP() - (damage - mteam.mMember[i]->getDefense()));
            }
            else if (scheck)
            {
              if (luck(pteam.pMember[pOrder[p]]->getLuck()))
              {
                cout << pteam.pMember[pOrder[p]]->getName() << " triggered good luck! (ATK * 2)" << endl;
                damage = 2 * (pteam.pMember[pOrder[p]]->getAttack() / mteam.getCount(2));
              }
              else
                damage = pteam.pMember[pOrder[p]]->getAttack() / mteam.getCount(2);
              for (int i = 0; i < mteam.getCount(3); i++)
                if (mteam.mMember[i]->getTrait() != "Satan" && mteam.mMember[i]->getHP() > 0)
                  mteam.mMember[i]->setHP(mteam.mMember[i]->getHP() - (damage - mteam.mMember[i]->getDefense()));
            }
          }
        }
        p++;
      }
    }
    // 結算場上剩餘人數
    realpCount = 0, realmCount = 0;

    for (int i = 0; i < pteam.getpCount(); i++)
      if (pteam.pMember[i]->getHP() > 0)
        realpCount++;
    for (int i = 0; i < mteam.getCount(3); i++)
      if (mteam.mMember[i]->getHP() > 0)
        realmCount++;
    // 輸出戰鬥結果
    round++;
    cout << "Round " << round << endl;
    for (int i = 0; i < pteam.getpCount(); i++)
      if (pteam.pMember[i]->getHP() > 0)
        cout << pteam.pMember[i]->getName() << " HP:" << pteam.pMember[i]->getHP() << endl;
    bool rPrint = false, wPrint = false, sPrint = false;
    for (int i = 0; i < mteam.getCount(3); i++)
      if (mteam.mMember[i]->getHP() > 0)
      {
        if (mteam.mMember[i]->getTrait() == "Rock" && !rPrint)
        {
          cout << mteam.getCount(0) << " * " << mteam.mMember[i]->getTrait() << " HP:" << mteam.mMember[i]->getHP() << endl;
          rPrint = true;
        }
        if (mteam.mMember[i]->getTrait() == "Wyvern" && !wPrint)
        {
          cout << mteam.getCount(1) << " * " << mteam.mMember[i]->getTrait() << " HP:" << mteam.mMember[i]->getHP() << endl;
          wPrint = true;
        }
        if (mteam.mMember[i]->getTrait() == "Satan" && !sPrint)
        {
          cout << mteam.getCount(2) << " * " << mteam.mMember[i]->getTrait() << " HP:" << mteam.mMember[i]->getHP() << endl;
          sPrint = true;
        }
      }
    system("pause");
  }
  if (realmCount == 0)
  {
    pteam.winSetHp();
    // 計算經驗值
    int totalExp = 0;
    for (int i = 0; i < mteam.getCount(3); i++)
      totalExp += mteam.mMember[i]->getExp();
    // 將經驗值平分
    for (int i = 0; i < pteam.getpCount(); i++)
    {
      pteam.pMember[i]->levelUp(totalExp / pteam.getpCount());
    }
    return true;
  }
  else
  {
    pteam.winSetHp();
    return false;
  }
}

int main()
{
  pTeam pteam;
  string teamName, name, career[peopleType] = {"Warior", "Wizard", "Assassin", "Archer", "Tank", "Healer"};
  int level, numC;

  cout << "Please enter team name(under 25 characters): ";
  getline(cin, teamName);
  while (teamName.size() > 25)
  {
    cout << "Under 25 characters, please re-enter: ";
    getline(cin, teamName);
  }
  pteam.setName(teamName);
  cout << "Please enter added membeer information(Enter 0 to finish) : name(under 32 characters) career(1~6) level(1~20) (ex. Harry 2 5)"
       << endl
       << "career option (1)Warior (2)Wizard (3)Assassin (4)Archer (5)Tank (6)Healer\nEnter:\n";
  // 輸入團隊成員
  while (cin >> name)
  {
    // 停止輸入
    if (name == "0")
      break;
    // 避開名稱重複
    if (pteam.repeat(name))
    {
      cout << "Name has been taken, please re-enter: " << endl;
      continue;
    }
    else if (name.size() > 32)
    {
      cout << "Under 32 characters, please re-enter: " << endl;
      continue;
    }
    // 輸入職業與等級
    cin >> numC >> level;
    // 避開不合法輸入
    if (cin.fail())
    {
      cout << "Invalid input, please re-enter: " << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      continue;
    }
    else if (name == "" || level > 50 || level < 1 || numC > peopleType || numC < 1)
    {
      cout << "Invalid input, please re-enter: " << endl;
      continue;
    }
    pteam.addpMember(name, career[numC - 1], level);
    if (pteam.getpCount() >= 100)
      break;
  }
  bool exit = false;
  while (!exit)
  {
    mTeam mteam;
    int rcount = 0, wcount = 0, scount = 0;
    cout << "Enter count of monster: Rock Wyvern Satan (ex.6 2 1)\nEnter: ";
    // 輸入怪物數量
    while (true)
    {
      cin >> rcount >> wcount >> scount;
      // 避開不合法輸入
      if (cin.fail())
      {
        cout << "Invalid input, please re-enter." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
      }
      else if (rcount < 0 || wcount < 0 || scount < 0)
      {
        cout << "Invalid input, please re-enter." << endl;
        continue;
      }
      else
      {
        for (int i = 0; i < rcount; i++)
          mteam.addmMember("Rock");
        for (int i = 0; i < wcount; i++)
          mteam.addmMember("Wyvern");
        for (int i = 0; i < scount; i++)
          mteam.addmMember("Satan");
        break;
      }
    }
    pteam.print();
    mteam.print();
    if (battle(pteam, mteam))
    {
      cout << "WIN: Trash belongs in the trash can!\nExit?: 0->No and start new game | 1->Yes" << endl;
      cin >> exit;
    }
    else
    {
      cout << "LOSE: Go home and practice more.\nExit?: 0->No and start new game | 1->Yes" << endl;
      cin >> exit;
    }
  }
  return 0;
}

bool luck(int luckyNum)
{
  int num = rand() % 100;

  if (num <= luckyNum)
    return true;
  else
    return false;
}
