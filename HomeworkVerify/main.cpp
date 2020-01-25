#include <iostream>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <queue>
#include <cmath>
#include <set>
#include <filesystem>
#include "aes.h"
#include "openhelper.hpp"
#include "cores.hpp"
#include "gpphelper.hpp"
#include "handclap.hpp"
#include "highonlife.hpp"
#include "acsound.hpp"
#include "soundkill.hpp"
#include "irrlib.hpp"
#include "soundsetup.hpp"
#include "convtool.hpp"
using namespace std;
namespace fs = std::__fs::filesystem;
typedef long long ll;
typedef long double ld;
#define CANUSEFS 1
#define APPL 0
#define WIN 1
#define SYS 0
//MARK:START UTILITIES
struct hw {
    string id;
    ll score;
    string name;
    string date;
};
string safespace(string s) {
    stringstream ss;
    for (ll i=0;i<s.length();i++)
        s[i]==' ' ? ss<<"\\"<<" " : ss<<s[i];
    string rturn;
    getline(ss,rturn);
    return rturn;
}
bool readf(vector<string>&s,string path) {
    s.clear();
    ifstream in(path);
    if (in.good()) {
        while (!in.eof()) {
            string tmp;
            getline(in,tmp);
            s.push_back(tmp);
        }
    } else {
        return 0;
    }
    return 1;
}
string username = getlogin(),db;
//MARK:SYSTEM CALLS
void inAppLaunch(string s,string args) {
    if (SYS==APPL) {
        system((safespace(s)+args).c_str());
    }
}
void clc() {
    if (SYS==APPL) {
        system("clear");
    } else if (SYS==WIN) {
        system("cls");
    }
}
void removeWithinFolder(string pathWithSlash) {
#if CANUSEFS
    fs::remove_all(pathWithSlash);
    fs::create_directory(pathWithSlash);
#else
    system(("rm -r "+safespace(pathWithSlash)+"*").c_str());
#endif
}
void makeExe(string pth) {
    if (SYS==APPL) {
#if CANUSEFS
        fs::permissions(pth,fs::perms::all);
#else
        system(("chmod 755 "+safespace(pth)).c_str());
#endif
    }
    if (SYS==WIN) {
        //do nothing
    }
}
void makeDir(string pathWithSlash) {
#if CANUSEFS
    fs::create_directory(pathWithSlash);
#else
    system(("mkdir "+safespace(pathWithSlash)).c_str());
#endif
}
void removeFolder(string pathWithSlash) {
#if CANUSEFS
    fs::remove_all(pathWithSlash);
#else
    system(("rm -r "+safespace(pathWithSlash)).c_str());
#endif
}
void unzip(string from, string to) { //COMPATIBILITY ONLY
    if (SYS==APPL) {
        system(("unzip -o -qq "+safespace(to)+" -d "+safespace(from)).c_str());
    }
}
//MARK:INSTALL
void install(bool comple) {
    cout<<"Installing neccessary components... ";
    if (comple) {
        makeDir(db);
        makeDir(db+"tmp/");
        makeDir(db+"tmp2/");
        ofstream disExist(db+"tmp2/exists");
    }
    //Install cores(39824),gpphelper(48608),openhelper(135904),handclap(1818048),highonlife(1160862),acsound(94848),soundkill(31840),libirrklang.dylib(1975552),soundsetup(114720),convtool(109344)
    string pstfx="";
    if (SYS==WIN) pstfx=".exe";
    const unsigned char* tmp=cores();
    ofstream installer(db+"cores"+pstfx,ios::binary);
    for (ll i=0;i<39824;i++) installer<<tmp[i];
    installer.close();
    makeExe(db+"cores");
    
    installer.open(db+"gpphelper"+pstfx,ios::binary);
    tmp = gpphelper();
    for (ll i=0;i<48608;i++) installer<<tmp[i];
    installer.close();
    makeExe(db+"gpphelper");
    
    installer.open(db+"openhelper"+pstfx,ios::binary);
    tmp = openhelper();
    for (ll i=0;i<135904;i++) installer<<tmp[i];
    installer.close();
    makeExe(db+"openhelper");
    
    installer.open(db+"U2PQX4CHY3SOJ31E.wav",ios::binary);
    tmp=handclap();
    for (ll i=0;i<1818048;i++) installer<<tmp[i];
    installer.close();
    
    installer.open(db+"D63SR3HEXSB6JX1N.wav",ios::binary);
    tmp=highonlife();
    for (ll i=0;i<1160862;i++) installer<<tmp[i];
    installer.close();
    
    installer.open(db+"acsound"+pstfx,ios::binary);
    tmp = acsound();
    for (ll i=0;i<94848;i++) installer<<tmp[i];
    installer.close();
    makeExe(db+"acsound");
    
    installer.open(db+"soundkill"+pstfx,ios::binary);
    tmp = soundkill();
    for (ll i=0;i<31840;i++) installer<<tmp[i];
    installer.close();
    makeExe(db+"soundkill");
    
    installer.open(db+"soundsetup"+pstfx,ios::binary);
    tmp=soundsetup();
    for (ll i=0;i<114720;i++) installer<<tmp[i];
    installer.close();
    makeExe(db+"soundsetup");
    
    installer.open(db+"libirrklang.dylib",ios::binary);
    tmp=irrlib();
    for (ll i=0;i<1975552;i++) installer<<tmp[i];
    installer.close();
    
    installer.open(db+"convtool"+pstfx,ios::binary);
    tmp=convtool();
    for (ll i=0;i<109344;i++) installer<<tmp[i];
    installer.close();
    makeExe(db+"convtool");
    cout<<"done"<<endl;
}
string date() {
    time_t tmptime = chrono::system_clock::to_time_t(chrono::system_clock::now());
    string tmp = ctime(&tmptime);
    tmp.erase(tmp.size()-1,1);
    return tmp;
}
bool fcopy(string from,string to) {
    ifstream in(from);
    ofstream out(to);
    string s;
    if (in.good()&&out.good()) {
        out<<in.rdbuf();
    } else {
        in.close();
        out.close();
        return 1;
    }
    in.close();
    out.close();
    return 0;
}
string key = "FB384BE6E7009275";
string iv = "755CA3572C3FAC78";
string salt = "8C55A67258E39056";
string cmdenc = "openssl enc -aes-256-cbc -K "+key+" -iv "+iv+" -S "+salt;
//MARK:END UTILITIES
ll srtmode,mltcore,rten,compcore,cor=0,incor=0,helperver,sound,autosave,ovrflw,anslock,fsvers,expfsvers;
string lockedf,vers,expvers;
unsigned char aesKey[32]={28,57,67,10,127,108,14,197,41,73,79,16,242,2,85,227,120,13,53,121,23,109,231,129,210,147,11,128,115,1,242,150};
map<ll,char>randname;
bool cmp(hw const &a, hw const &b) {
    //    cout<<"COMPARING "<<a.name<<' '<<b.name<<endl;
    if (srtmode==1) return a.name<b.name;
    else if (srtmode==2) return a.name>b.name;
    else if (srtmode==3) {
        if (a.score==b.score) return a.name<b.name;
        return a.score<b.score;
    }
    else if (srtmode==4) {
        if (a.score==b.score) return a.name<b.name;
        return a.score>b.score;
    }
    else if (srtmode==5||srtmode==6) {
        if (a.date==b.date) {
            return a.name<b.name;
        }
        tm tm1,tm2;
        strptime(a.date.c_str(),"%a %b %d %T %Y",&tm1);
        strptime(b.date.c_str(),"%a %b %d %T %Y",&tm2);
        time_t t1,t2;
        t1=mktime(&tm1);
        t2=mktime(&tm2);
        if (t1-t2>0) {
            if (srtmode==5) return false;
            else return true;
        } else {
            if (srtmode==6) return true;
            else return false;
        }
    }
    return 0;
}
vector<hw>asmt;
struct egg {
    string ach, trig, msg;
};
vector<egg>easter;
map<string,ll*>intcont;
map<string,string*>strcont;
map<string,vector<string>>structref;
struct soundlog {
    string fname,sname;
};
struct dtCont {
    ll cnt;
    ll ipos,opos;
};
bool secret[100];
vector<soundlog>audio;
vector<ll>selaud;
struct strWithInt {
    string ply;
    ll mtd;
};
void savedata() {
    ofstream out(db+"contents.dwt");
    if (!out.good()) cout<<"Critical error! Error accessing contents.dwt save file!"<<endl;
    out<<"ACH"<<endl;
    for (ll i=0;i<easter.size();i++) out<<secret[i];
    out<<endl;
    for (map<string,ll*>::iterator it=intcont.begin();it!=intcont.end();it++) out<<it->first<<endl<<*it->second<<endl;
    for (map<string,string*>::iterator it=strcont.begin();it!=strcont.end();it++) out<<it->first<<endl<<*it->second<<endl;
    out<<"dwtReserved::STARTSTRUCT"<<endl<<"Hwf"<<endl<<"FNAME"<<endl<<"SCORE"<<endl<<"NAME"<<endl<<"DATE"<<endl<<"dwtReserved::ENDSTRUCT"<<endl<<"dwtReserved::STARTSTRUCT"<<endl<<"Song"<<endl<<"FNAME"<<endl<<"SNAME"<<endl<<"dwtReserved::ENDSTRUCT"<<endl<<"dwtReserved::STARTSTRUCT"<<endl<<"selaud"<<endl<<"AUDID"<<endl<<"dwtReserved::ENDSTRUCT"<<endl<<"dwtReserved::START"<<endl<<"Song"<<endl;
    for (ll i=0;i<audio.size();i++) out<<audio[i].fname<<endl<<audio[i].sname<<endl;
    out<<"dwtReserved::END"<<endl<<"Song"<<endl<<"dwtReserved::START"<<endl<<"Hwf";
    for (ll i=0;i<asmt.size();i++) out<<endl<<asmt[i].id<<endl<<asmt[i].score<<endl<<asmt[i].name<<endl<<asmt[i].date;
    out<<endl<<"dwtReserved::END"<<endl<<"Hwf"<<endl<<"dwtReserved::START"<<endl<<"selaud";
    for (ll i=0;i<selaud.size();i++) out<<endl<<selaud[i];
    out<<endl<<"dwtReserved::END"<<endl<<"selaud";
}
void nml(string &s) {
    if (s!="") {
        for (ll i=0;i<s.size()-1;i++) {
            if (s[i]=='\\'&&s[i+1]==' ') {
                s.erase(i,2);
                s.insert(i," ");
            }
        }
        if (s[s.size()-1]==' ') s.erase(s.size()-1);
    }
}
void changelog() {
    cout<<"What's changed in v1.5:"<<endl<<"Sandboxing for security"<<endl<<"Answer files"<<endl<<"Limit items"<<endl<<"Batch evaluation"<<endl<<"New cross platform file format:hwfx"<<endl<<"Bug fixes and improvements"<<endl;
}
//MARK:MAIN
ll pkgImport(ifstream &rdpkg, stringstream &newPkg, string impItm) {
    stringstream checkNef;
    if (rdpkg.good()) {
        checkNef<<rdpkg.rdbuf();
        string nef=checkNef.str();
        if (nef.find("HwfxContents::")==string::npos) {
            newPkg<<nef<<endl;
        } else {
            cout<<"Error! "<<impItm<<" file contains keyword \"HwfxContents::\"!"<<endl;
            return -1;
        }
    } else {
        cout<<"Error! "<<impItm<<" file missing! Make sure you have the right file hierarchy!"<<endl;
        return -1;
    }
    return 0;
}
void writeHwfx(string &pkgpth,bool &impFail,string &disTtl,stringstream &newPkg) {
    impFail=false;
    newPkg.str("");
    newPkg<<"HwfxContents::Payload"<<endl<<"HwfxContents::Title"<<endl;
    ifstream rdpkg(pkgpth+"/title.txt");
    if (pkgImport(rdpkg,newPkg,"Title")==-1) impFail=true;
    rdpkg.close();
    rdpkg.open(pkgpth+"/title.txt");
    if (rdpkg.good()) getline(rdpkg,disTtl);
    rdpkg.close();
    newPkg<<"HwfxContents::Description"<<endl;
    rdpkg.open(pkgpth+"/description.txt");
    if (pkgImport(rdpkg,newPkg,"Description")==-1) impFail=true;
    rdpkg.close();
    newPkg<<"HwfxContents::InputDes"<<endl;
    rdpkg.open(pkgpth+"/in.txt");
    if (pkgImport(rdpkg,newPkg,"Input")==-1) impFail=true;
    rdpkg.close();
    newPkg<<"HwfxContents::OutputDes"<<endl;
    rdpkg.open(pkgpth+"/out.txt");
    if (pkgImport(rdpkg,newPkg, "Output")==-1) impFail=true;
    rdpkg.close();
    ll expkgs=1;
    while (true) {
        ifstream intst(pkgpth+"/exin"+to_string(expkgs)+".txt"),outtst(pkgpth+"/exout"+to_string(expkgs)+".txt");
        if (intst.good()&&outtst.good()) {
            newPkg<<"HwfxContents::ExampleInput"<<to_string(expkgs)<<endl;
            if (pkgImport(intst,newPkg,"Example input "+to_string(expkgs))==-1) {
                impFail=true;
                break;
            }
            newPkg<<"HwfxContents::ExampleOutput"<<to_string(expkgs)<<endl;
            if (pkgImport(outtst,newPkg,"Example output "+to_string(expkgs))==-1) {
                impFail=true;
                break;
            }
            expkgs++;
        } else if (intst.good()||outtst.good()) {
            if (intst.good()) cout<<"Error! Missing exout"<<to_string(expkgs)<<".txt to match existing exin"+to_string(expkgs)+".txt"<<endl;
            else cout<<"Error! Missing exin"<<to_string(expkgs)<<".txt to match existing exout"+to_string(expkgs)+".txt"<<endl;
            impFail=true;
            expkgs--;
            break;
        } else {
            expkgs--;
            break;
        }
    }
    ll testSets=1;
    while (true) {
        ifstream intst(pkgpth+"/in"+to_string(testSets)+".txt"),outtst(pkgpth+"/out"+to_string(testSets)+".txt");
        if (intst.good()&&outtst.good()) {
            newPkg<<"HwfxContents::InputSet"<<to_string(testSets)<<endl;
            if (pkgImport(intst,newPkg,"Input "+to_string(testSets))==-1) {
                impFail=true;
                break;
            }
            newPkg<<"HwfxContents::OutputSet"<<to_string(testSets)<<endl;
            if (pkgImport(outtst,newPkg,"Output "+to_string(testSets))==-1) {
                impFail=true;
                break;
            }
            testSets++;
        } else if (intst.good()||outtst.good()) {
            if (intst.good()) cout<<"Error! Missing out"<<to_string(expkgs)<<".txt to match existing in"+to_string(expkgs)+".txt"<<endl;
            else cout<<"Error! Missing in"<<to_string(expkgs)<<".txt to match existing out"+to_string(expkgs)+".txt"<<endl;
            impFail=true;
            testSets--;
            break;
        } else {
            testSets--;
            break;
        }
    }
}
bool readHwfx(string &pkgpth,bool &vq,string &target,ll &chosenID) {
    //undo encryption, encrypt again, then throw it into .hwfx files. It has the exact same header format.
    ifstream importHwfx(pkgpth);
    vector<string>fHeader;
    while (true) {
        if (importHwfx.eof()) return 0;
        string impTmp;
        getline(importHwfx,impTmp);
        if (impTmp=="HwfxContents::PAYLOAD") break;
        else fHeader.push_back(impTmp);
    }
    stringstream transF;
    transF<<importHwfx.rdbuf();
    string fplyd=transF.str();
    transF.str("");
    importHwfx.close();
    unsigned char iv[16]={0};
    bool gotIv=false,gotFvers=false,gotDtsz=false,gotCnt=false;
    string fvers="";
    ll dtsz=0,ascnt=1;
    for (ll i=0;i<fHeader.size();i++) {
        if (fHeader[i]=="HwfxContents::FVERS") {
            if (i+1!=fHeader[i].size()) {
                fvers=fHeader[++i];
                gotFvers=true;
            }
        } else if (fHeader[i]=="HwfxContents::DATASIZE") {
            if (i+1!=fHeader.size()) {
                dtsz=atoll(fHeader[++i].c_str());
                gotDtsz=true;
            }
        } else if (fHeader[i]=="HwfxContents::IV") {
            for (ll j=i+1;j<=i+16;j++) {
                iv[j-i-1]=atoll(fHeader[j].c_str());
                if (j+1==fHeader.size()&&j-i-1!=15) {
                    cout<<"Error reading IV!"<<endl;
                    break;
                }
            }
            i+=17;
            gotIv=true;
        } else if (fHeader[i]=="HwfxContents::PKGCNT") {
            if (i+1!=fHeader.size()) {
                ascnt=atoll(fHeader[++i].c_str());
                gotCnt=true;
            }
        }
    }
    if (fvers!="2") cout<<"Alert! File version unsupported!"<<endl;
    bool goodImp=true;
    if (!gotIv) {
        cout<<"Error reading IV!"<<endl;
        goodImp=false;
    }
    if (!gotFvers) cout<<"Error reading file version!"<<endl;
    if (!gotDtsz) {
        cout<<"Error reading file size!"<<endl;
        goodImp=false;
    }
    if (!gotCnt) cout<<"Error reading assignment count!"<<endl;
    ll newLen=dtsz;
    newLen=ceil(dtsz/16.0)*16;
    unsigned char decPkg[newLen];
    for (ll i=0;i<fplyd.size();i++) decPkg[i]=fplyd[i];
    for (ll i=fplyd.size();i<newLen;i++) decPkg[i]=0;
    aes_decrypt(decPkg, ceil(dtsz/16.0)*16, aesKey, 32, iv);
    for (ll i=0;i<dtsz;i++) transF<<decPkg[i];
    vector<string>reLd;
    string ft;
    while (getline(transF,ft)) reLd.push_back(ft);
    ll parsel=0;
    if (ascnt==1) vq=true;
    while (true) {
        if (parsel>=reLd.size()) break;
        ll parserr=reLd.size();
        for (ll i=parsel+1;i<=reLd.size();i++) {
            if (reLd[i]=="HwfxContents::Payload") parserr=i;
        }
        stringstream dtplyd;
        string nm;
        for (ll i=parsel;i<parserr;i++) dtplyd<<reLd[i]<<endl;
        for (ll i=parsel;i<parserr;i++) {
            if (reLd[i]=="HwfxContents::Title"&&i+1<parserr) nm=reLd[i+1];
        }
        parsel=parserr+1;
        string newname="";
        for (ll i=0;i<16;i++) newname+=randname[rand()%36];
        ofstream miniF(db+newname);
        miniF<<"HwfxContents::"<<endl<<"HwfxContents::FVERS"<<endl<<"2"<<endl<<"HwfxContents::PKGCNT"<<endl<<"1"<<endl<<"HwfxContents::DATASIZE"<<endl<<dtplyd.str().size()<<endl<<"HwfxContents::IV"<<endl;
        unsigned char iv[16];
        for (ll i=0;i<16;i++) {
            iv[i]=rand()%256;
            miniF<<(int)iv[i]<<endl;
        }
        miniF<<"HwfxContents::PAYLOAD"<<endl;
        string plyd = dtplyd.str();
        ll newLen=plyd.size();
        newLen=ceil(newLen/16.0)*16;
        unsigned char newMsg[newLen];
        for (ll i=0;i<plyd.size();i++) newMsg[i]=plyd[i];
        for (ll i=plyd.size();i<newLen;i++) newMsg[i]=0;
        aes_encrypt(newMsg, newLen, aesKey, 32, iv);
        for (ll i=0;i<newLen;i++) miniF<<newMsg[i];
        miniF.close();
        
        //All it needs to do:push to asmt, set target, vq, and chosenID
        asmt.push_back({newname,0,nm,date()});
        //ID SCORE NAME DATE
        target = newname;
        chosenID=asmt.size()-1;
    }
    return 1;
}
int main() {
    if (__cplusplus!=201703) cout<<"Error! Use C++17!"<<endl;
    //TODO:Make helpers start on program launch. relaunch if helper is detected to be dead.
    //TODO:Reconvert openhelper
    //TODO:Add search
    intcont["SOUND"]=&sound;
    intcont["CORRECT"]=&cor;
    intcont["INCORRECT"]=&incor;
    intcont["SORT"]=&srtmode;
    intcont["MULTICORE"]=&mltcore;
    intcont["RETENTION"]=&rten;
    intcont["AUTOSAVE"]=&autosave;
    intcont["HELPERVER"]=&helperver;
    intcont["OVRFLW"]=&ovrflw;
    intcont["ANSLOCK"]=&anslock;
    intcont["FSVERS"]=&fsvers;
    strcont["LOCKEDF"]=&lockedf;
    strcont["VERS"]=&vers;
    ll const helpertar=4;
    //Defaults
    rten=6;
    mltcore=1;
    srtmode=1;
    incor=cor=0;
    sound=0;
    autosave=1;
    ovrflw=0;
    expfsvers=2;
    expvers="1.5";
    audio.push_back({"U2PQX4CHY3SOJ31E","Handclap"});
    audio.push_back({"D63SR3HEXSB6JX1N","High on Life"});
    selaud.push_back(0);
    selaud.push_back(1);
    if (true) /*Easter eggs!*/ {
        easter.push_back({"The Player's Poem","player","Roses are red, \nViolets are blue.\nI said I loved you,\nYou thought that was true.\nWell guess what player?\nYou just got played too."});
        easter.push_back({"?ldroW","hello world","!dlroW olleH"});
        easter.push_back({"Secrets...","easter egg","Secrets have been hidden..."});
        easter.push_back({"Demons","horn","Try not to get me wet"});
        easter.push_back({"ME!","credits","HOMEWORK SYSTEM MADE BY MICHEL!"});
        easter.push_back({"Ding!","tiger","Buy the Tiger Microwave and the Ding Radio Emitter!"});
        easter.push_back({"Always On!","eric","That man must be turned off"});
        easter.push_back({"You ded!","msyan","For Ms.Yan..."});
        easter.push_back({"Respects","f","You've paid your respects."});
        easter.push_back({"You kiss your mother with that mouth?","fack","If you see kay, why oh you?"});
        easter.push_back({"My name!","michel","That's me!"});
        easter.push_back({"Language of the future...","c++","That's the language!"});
        easter.push_back({"MINE! MINE!","lucy","Do your homework... and come talk to me. Tell me that I sent you"});
        easter.push_back({"Cat Spring","cucumber","Cats like them... I think"});
        easter.push_back({"Best subject","math","Awesome Math!"});
        easter.push_back({"Slap his thigh!","lightning","Lightning and the thunder..."});
        easter.push_back({"I'll do you every day.","homework","Oh yeah..."});
        easter.push_back({"Goose math!","3.16","Pi IS 3.16!"});
        easter.push_back({"Escaping red blood cells!","bleed","Rudolph's running nose..."});
        easter.push_back({"The mythical creature","unicorn","So horny..."});
        easter.push_back({"Greatest club of all time","c++ programming","Yee!"});
        easter.push_back({"Best calculator","calculatorx","Powerful."});
        easter.push_back({"VB sucks like VB","vb","One who sucks like VB"});
    }
    vector<string>tips;
    if (true) {
        tips.push_back("Type make into the main menu to create your own assignments!");
        tips.push_back("If you have too many files, consider using keep assignments and limit items in settings!");
        tips.push_back("Try setting multiple cores in settings to evaluate your assignments faster!");
        tips.push_back("Type changelog into the main menu to view the changelog!");
        tips.push_back("Type the name of a question into the main menu!");
    }
    //openssl enc -aes-256-cbc -K FB384BE6E7009275 -iv 755CA3572C3FAC78 -S 8C55A67258E39056
    clc();
    for (ll i=48;i<=57;i++) {
        randname[i-48]=i;
    }
    for (ll i=65;i<=90;i++) {
        randname[i-55]=i;
    }
    srand(time(0));
    ifstream dbtest("/Users/"+username);
    if (!dbtest.good()) {
        dbtest.close();
        bool isdev=true;
        while (true) {
            if (isdev) {
                cout<<"Automatic directory detection failed. Trying dev legitmichel777..."<<endl;
                username="legitmichel777";
                isdev=false;
            } else {
                cout<<"Automatic directory detection failed. Please enter your username."<<endl;
                getline(cin,username);
            }
            dbtest.open("/Users/"+username);
            if (dbtest.good()) {dbtest.close();break;}
            dbtest.close();
            while (true) {
                cout<<"Error! Please make sure you entered the right user and is on a supported system(macOS). Please enter your username again."<<endl;
                getline(cin,username);
                dbtest.open("/Users/"+username);
                if (dbtest.good()) {dbtest.close();break;}
                dbtest.close();
            }
            break;
        }
    }
    dbtest.close();
    db = "/Users/"+username+"/Library/Containers/com.mclm7.homework/";
    dbtest.open(db+"contents.dwt");
    bool freshins=false;
    bool newUsr=false;
    if (!dbtest.good()) {
        newUsr=true;
        freshins=true;
        install(1);
        ofstream mancreate(db+"contents.dwt");
        mancreate.close();
        helperver=helpertar;
    }
    dbtest.close();
    //1.3 ONLY
    /* **************************************************** */
    ifstream convtest(db+"contents.man");
    if (convtest.good()) {
        convtest.close();
        convtest.open(db+"contents.dwt");
        if (convtest.good()) {
            convtest.close();
        } else {
            convtest.close();
            install(0);
            cout<<"v1.3 of Homework introduces a new storage format, DWT. DWT allows for seamless compatibility between versions of Homework. We'll now convert your old MAN file to DWT!"<<endl;
            inAppLaunch(db+"convtool","");
            cout<<"Please reopen Homework."<<endl;
            return 0;
        }
        
    } else convtest.close();
    /* **************************************************** */
    //1.3 ONLY
    ifstream in(db+"contents.dwt");
    bool impissue=false;
    bool impfsVers=false;
    ofstream rmsil(db+"tmp/sl.silent");
    if (!rmsil.good()) cout<<"Error writing silent file to tmp"<<endl;
    rmsil<<"SILENCE!";
    rmsil.close();
    removeWithinFolder(db+"tmp/");
    removeWithinFolder(db+"tmp2/");
    for (ll i=0;i<easter.size();i++) secret[i]=0;
    string prefx;
    if (in.good()&&!freshins) {
        vector<string>contentsf;
        while (!in.eof()) {
            string s;
            getline(in,s);
            contentsf.push_back(s);
        }
        for (ll i=0;i<contentsf.size();i++) {
            string finkey=contentsf[i];
            if (fsvers>=2) prefx="dwtReserved::";
            if (finkey==prefx+"START") {
                bool startgood=false;
                string stname=contentsf[++i];
                for (ll j=i;j<contentsf.size()-1;j++) {
                    if (contentsf[j]==prefx+"END"&&contentsf[j+1]==stname) {
                        startgood=true;
                        break;
                    } else if (contentsf[j]==prefx+"START") break;
                    else if (contentsf[j]==prefx+"END") break;
                }
                if (startgood) {
                    ll cur=0;
                    ll ttl = structref[stname].size();
                    if (ttl) {
                        if (stname=="Hwf") {
                            hw curwt=(hw){"",0,"",""};
                            //ID,NAME,SCORE,DATE
                            while (contentsf[++i]!=prefx+"END") {
                                if (cur==ttl) {
                                    asmt.push_back(curwt);
                                    cur=0;
                                }
                                if (structref[stname][cur]=="FNAME") curwt.id=contentsf[i];
                                else if (structref[stname][cur]=="SCORE") curwt.score=atoll(contentsf[i].c_str());
                                else if (structref[stname][cur]=="NAME") curwt.name=contentsf[i];
                                else if (structref[stname][cur]=="DATE") curwt.date=contentsf[i];
                                cur++;
                            }
                            if (cur==ttl) asmt.push_back(curwt);
                        } else if (stname=="Song") {
                            audio.clear();
                            soundlog curwt=(soundlog){"",""};
                            //fname, sname
                            while (contentsf[++i]!=prefx+"END") {
                                if (cur==ttl) {
                                    audio.push_back(curwt);
                                    cur=0;
                                }
                                if (structref[stname][cur]=="FNAME") curwt.fname=contentsf[i];
                                else if (structref[stname][cur]=="SNAME") curwt.sname=contentsf[i];
                                cur++;
                            }
                            if (cur==ttl) audio.push_back(curwt);
                        } else if (stname=="selaud") {
                            selaud.clear();
                            ll curwt;
                            while (contentsf[++i]!=prefx+"END") {
                                if (cur==ttl) {
                                    selaud.push_back(curwt);
                                    cur=0;
                                }
                                if (structref[stname][cur]=="AUDID") curwt=atoll(contentsf[i].c_str());
                                cur++;
                            }
                            if (cur==ttl) selaud.push_back(curwt);
                        } else while (contentsf[++i]!=prefx+"END");
                    }
                } else impissue=true;
            } else if (finkey==prefx+"STARTSTRUCT") {
                bool structgood=false;
                for (ll j=i+1;j<contentsf.size();j++) {
                    if (contentsf[j]==prefx+"ENDSTRUCT") {
                        structgood=true; //Ending found
                        break;
                    } else if (contentsf[j]==prefx+"STARTSTRUCT") break; //No ending
                }
                if (structgood) {
                    string stuname=contentsf[++i];
                    while (contentsf[++i]!=prefx+"ENDSTRUCT") {
                        structref[stuname].push_back(contentsf[i]);
                    }
                } else impissue=true;
            } else if (intcont.count(finkey)) {
                *intcont[finkey]=atoll(contentsf[++i].c_str());
            } else if (strcont.count(finkey)) {
                *strcont[finkey]=contentsf[++i];
            } else if (finkey=="ACH") {
                i++;
                for (ll j=0;j<min(easter.size(),contentsf[i].size());j++) {
                    if (contentsf[i][j]=='0') secret[j]=0;
                    else if (contentsf[i][j]=='1') secret[j]=1;
                }
            }
        }
    }
    in.close();
    if (vers!=expvers) {
        if (vers<expvers) {
            cout<<"Welcome to Homework v1.5!"<<endl;
            changelog();
        }
    }
    ifstream checkTmp2(db+"tmp2/exists");
    if (!checkTmp2.good()) {
        makeDir(db+"tmp2/");
        ofstream nowExists(db+"tmp2/exists");
        nowExists<<"I exist!";
        nowExists.close();
    }
    if (fsvers!=0&&fsvers!=2) {
        impissue=true;
        impfsVers=true;
    }
    fsvers=2;
    vers="1.5";
    ofstream out(db+"db.txt");
    out<<db;
    out.close();
    if (helperver!=helpertar&&!newUsr) {
        install(0);
        helperver=helpertar;
    }
    inAppLaunch(db+"cores","");
    in.open(db+"cores.txt");
    if (in.good()) {
        string corefin;
        in>>corefin;
        if (to_string(atoll(corefin.c_str()))==corefin) compcore=atoll(corefin.c_str());
        else cout<<"System information gathering failed."<<endl;
    } else cout<<"System information gathering failed."<<endl;
    for (ll i=0;i<asmt.size();i++) {
        ifstream bundltest(db+asmt[i].id);
        if (!bundltest.good()) {
            asmt.erase(asmt.begin()+i);
            i--;
        }
    }
    ll timethres = 0;
    if (rten!=6) {
        if (rten==1) timethres=7;
        if (rten==2) timethres=14;
        if (rten==3) timethres=30;
        if (rten==4) timethres=60;
        if (rten==5) timethres=360;
        timethres*=24*60*60;
        for (ll i=0;i<asmt.size();i++) {
            struct tm convt;
            strptime(asmt[i].date.c_str(),"%a %b %d %T %Y",&convt);
            time_t convtt;
            convtt=mktime(&convt);
            if (difftime(chrono::system_clock::to_time_t(chrono::system_clock::now()),convtt)>timethres) {
                asmt.erase(asmt.begin()+i);
                i--;
            }
        }
    }
    bool asdisabled=false;
    if (impissue&&autosave) {
        cout<<"Autosave has been disabled."<<endl;
        autosave=0;
        asdisabled=true;
    }
    for (ll i=selaud.size()-1;i>=0;i--) {
        if (selaud[i]>=audio.size()) selaud.erase(selaud.begin()+i);
        i--;
    }
    ll grp=0;
    vector<vector<strWithInt>>showMore;
    //launch helpers
    cout<<"Launching helpers..."<<endl;
    for (ll i=1;i<=mltcore;i++) {
        makeDir(db+"tmp/"+to_string(i)+"/");
        //Copy over openhelper
        #if CANUSEFS
            ifstream checkohex(db+"tmp2/openhelper"+to_string(i));
            if (!checkohex.good()) fs::copy(db+"openhelper",db+"tmp2/openhelper"+to_string(i));
        #else
            system(("cp "+safespace(db+"openhelper")+" "+safespace(db+"tmp2/openhelper"+to_string(i))).c_str());
        #endif
        //Open openhelper
        //Write to the bridge
        ofstream foldout(db+"tmp/pth.bridge");
        if (!foldout.good()) cout<<"Critical error! Error accessing path bridge in tmp."<<endl;
        foldout<<i;
        foldout.close();
        system(("open "+safespace(db+"tmp2/openhelper"+to_string(i))).c_str());
        while (true) {
            ifstream signaltest(db+"tmp/"+to_string(i)+"/firini.signal");
            if (signaltest.good()) {
                signaltest.close();
                break;
            }
            usleep(1e4);
        }
    }
    while (true) {
        ll chosenID=0;
        string target;
        bool vq = false;
        if (impissue) {
            if (impfsVers) cout<<"!!!Contents file has wrong file system version. Press [F] to force quit. This will prevent corruption of the file"<<endl<<"You will lose all unsaved data. ";
            else cout<<"!!!Contents file corrupted. Press [F] to force quit. This will prevent further corruption of the file"<<endl<<"You will lose all unsaved data. ";
            if (asdisabled&&!autosave) {
                cout<<"Autosave has been disabled."<<endl;
            } else cout<<endl;
        }
        cout<<"Welcome to Homework(v1.5) for C++ Programming Club. Please select an action."<<endl<<"[1]New assignment"<<endl<<"[2]Achievements"<<endl<<"[3]Settings"<<endl<<"[4]Quit"<<endl;
        if (rand()%5==0) cout<<"Tip:"<<tips[rand()%tips.size()]<<endl;
        if (asmt.size()) cout<<"--------"<<endl;
        sort(asmt.begin(),asmt.end(),cmp);
        bool containsNonK=false,containsK=false;
        for (ll i=0;i<asmt.size()&&(!containsNonK||!containsK);i++) {
            if (asmt[i].score<100) containsNonK=true;
            else containsK=true;
        }
        if (grp==0) {
            showMore.clear();
            vector<strWithInt>curGroupContents;
            ll curGrpCnt=0;
            if (containsNonK) {
                curGroupContents.push_back((strWithInt){"Incomplete Assignments:",-1});
                for (ll i=0;i<asmt.size();i++) {
                    if (asmt[i].score<100) {
                        curGroupContents.push_back((strWithInt){asmt[i].name+":"+to_string(asmt[i].score),i});
                        curGrpCnt++;
                        if (ovrflw!=0) {
                            if (curGrpCnt%ovrflw==0) {
                                showMore.push_back(curGroupContents);
                                curGroupContents.clear();
                            }
                        }
                    }
                }
            }
            if (curGroupContents.size()!=0&&containsK) curGroupContents.push_back((strWithInt){"--------",-1});
            if (containsK) {
                curGroupContents.push_back((strWithInt){"Completed assignments:",-1});
                for (ll i=0;i<asmt.size();i++) {
                    if (asmt[i].score==100) {
                        curGroupContents.push_back((strWithInt){asmt[i].name+":"+to_string(asmt[i].score),i});
                        curGrpCnt++;
                        if (ovrflw!=0) {
                            if (curGrpCnt%ovrflw==0) {
                                showMore.push_back(curGroupContents);
                                curGroupContents.clear();
                            }
                        }
                    }
                }
            }
            if (curGroupContents.size()>0) {
                showMore.push_back(curGroupContents);
            }
        }
        ll outcnt = 5;
        vector<ll>hwpoint;
        if (asmt.size()) {
            for (ll i=0;i<showMore[grp].size();i++) {
                if (showMore[grp][i].mtd!=-1) {
                    cout<<"["<<outcnt<<"]";
                    hwpoint.push_back(showMore[grp][i].mtd);
                    outcnt++;
                }
                cout<<showMore[grp][i].ply<<endl;
            }
        }
        ll extended=outcnt;
        ll prevID=-1,nxtID=-1,jmpID=-1;
        if (showMore.size()>1) {
            if (showMore.size()-1) {
                cout<<"--------"<<endl<<"Page "<<grp+1<<" of "<<showMore.size()<<endl<<"["<<extended++<<"]Jump to page"<<endl;
                jmpID=extended-1;
            }
            if (grp!=0) {
                cout<<"["<<extended++<<"]Go to previous page"<<endl;
                prevID=extended-1;
            }
            if (grp!=showMore.size()-1) {
                cout<<"["<<extended++<<"]Go to next page"<<endl;
                nxtID=extended-1;
            }
        }
        string homeans;
        getline(cin,homeans);
        ll homeansNum=atoll(homeans.c_str());
        clc();
        if (homeans=="1") {
            cout<<"Enter the path of the package."<<endl;
            string pkgpth;
            getline(cin,pkgpth);
            nml(pkgpth);
            ifstream pkgverf(pkgpth);
            if (pkgverf.good()) {
                grp=0;
                bool idfile=false;
                if (pkgpth.size()>=6) {
                    if (pkgpth.substr(pkgpth.size()-6,6)==".hwpkg") {
                        if (SYS==APPL) {
                            idfile=true;
                            //COPY OVER TO TMP
                            string newname="";
                            for (ll i=0;i<16;i++) {
                                newname+=randname[rand()%36];
                            }
                            fcopy(pkgpth, db+"tmp/"+newname);
                            //UNZIP
                            system(("unzip -o -qq "+safespace(db+"tmp/"+newname)+" -d "+safespace(db+"tmp/"+newname+'u')).c_str());
                            //Read contents file
                            vector<string>pkgcontent;
                            ifstream pkgcont(db+"tmp/"+newname+"u/contents.man");
                            if (pkgcont.good()) {
                                while (!pkgcont.eof()) {
                                    string pkgconttmp;
                                    getline(pkgcont,pkgconttmp);
                                    pkgcontent.push_back(pkgconttmp);
                                }
                                pkgcont.close();
                                for (ll i=0;i<pkgcontent.size();i++) {
                                    string newnm="";
                                    ifstream pkgptverf(db+"tmp/"+newname+"u/"+pkgcontent[i]);
                                    if (pkgptverf.good()) {
                                        string newnm="";
                                        for (ll i=0;i<16;i++) newnm+=randname[rand()%36];
                                        fcopy(db+"tmp/"+newname+"u/"+pkgcontent[i],db+newnm);
                                        string pkgpeeknm;
                                        //PEEK AT PACKAGE TO LOOK AT NAME
                                        string denccmd = "openssl aes-256-cbc -d -K "+key+" -iv "+iv+" -S "+salt+" -in "+safespace(db+newnm)+" -out "+safespace(db+"tmp/"+newnm);
                                        system(denccmd.c_str());
                                        //OPEN EM
                                        system(("unzip -o -qq "+safespace(db+"tmp/"+newnm)+" -d "+safespace(db+"tmp/"+newnm+'e')).c_str());
                                        ifstream hwfnmrd(db+"tmp/"+newnm+"e/title.txt");
                                        string hwfnm;
                                        getline(hwfnmrd,hwfnm);
                                        hwfnmrd.close();
                                        asmt.push_back({newnm,0,hwfnm,date()});
                                    } else cout<<"Missing Homework file!"<<endl;
                                }
                            } else {
                                cout<<"Unexpected error:Missing contents file!"<<endl;
                                pkgcont.close();
                            }
                            removeWithinFolder(db+"tmp/");
                            if (autosave) savedata();
                            continue;
                        } else cout<<"Error! HWPKG files can only opened in macOS versions of Homework!"<<endl;
                    }
                }
                if (pkgpth.size()>=3) {
                    if (pkgpth.substr(pkgpth.size()-3,3)==".hw") {
                        if (SYS!=APPL) {
                            cout<<"Error! HW files can only be opened in the macOS version of Homework!"<<endl;
                        }
                        idfile=true;
                        string newname="";
                        for (ll i=0;i<16;i++) {
                            newname+=randname[rand()%36];
                        }
                        fcopy(pkgpth,db+newname);
                        string nm="HWSysUndefined";
                        asmt.push_back({newname,0,nm,date()});
                        //ID SCORE NAME DATE
                        target = newname;
                        vq=true;
                        chosenID=asmt.size()-1;
                    }
                }
                if (!idfile) {
                    if (pkgpth.size()>=5) {
                        if (pkgpth.substr(pkgpth.size()-5,5)!=".hwfx") {
                            cout<<"Unidentified file. Do not tamper with file extensions! Homework will take this as a hwfX file."<<endl;
                        }
                    } else cout<<"Unidentified file. Do not tamper with file extensions! Homework will take this as a hwfX file."<<endl;
                    if (!idfile) {
                        readHwfx(pkgpth,vq,target,chosenID);
                    }
                }
                if (autosave) savedata();
            } else {
                cout<<"Error reading package."<<endl;
            }
        } else if (homeans=="2") {
            cout<<"Achievements"<<endl<<"--------"<<endl<<"Academic:"<<endl<<"Success!:";
            if (cor>=1) cout<<"Completed "<<cor<<"/1 correct tries"<<endl;
            else cout<<"Complete "<<cor<<"/1 correct tries"<<endl;
            cout<<"More!:";
            if (cor>=10) cout<<"Completed "<<cor<<"/10 correct tries"<<endl;
            else cout<<"Complete "<<cor<<"/10 correct tries"<<endl;
            cout<<"Unstoppable!:";
            if (cor>=100) cout<<"Completed "<<cor<<"/100 correct tries"<<endl;
            else cout<<"Complete "<<cor<<"/100 correct tries"<<endl;
            cout<<"Godlike!:";
            if (cor>=1000) cout<<"Completed "<<cor<<"/1000 correct tries"<<endl;
            else cout<<"Complete "<<cor<<"/1000 correct tries"<<endl;
            cout<<"You can try again:";
            if (incor>=1) cout<<incor<<"/1 incorrect tries"<<endl;
            else cout<<incor<<"/1 incorrect tries done"<<endl;
            cout<<"Get up!:";
            if (incor>=10) cout<<incor<<"/10 incorrect tries"<<endl;
            else cout<<incor<<"/10 incorrect tries done"<<endl;
            cout<<"Keep going!:";
            if (incor>=100) cout<<incor<<"/100 incorrect tries"<<endl;
            else cout<<incor<<"/100 incorrect tries done"<<endl;
            cout<<"Nearly there!:";
            if (incor>=1000) cout<<incor<<"/1000 incorrect tries"<<endl;
            else cout<<incor<<"/1000 incorrect tries done"<<endl;
            cout<<"--------"<<endl<<"Secrets:"<<endl;
            for (ll i=0;i<easter.size();i++) {
                cout<<easter[i].ach<<":";
                if (secret[i]) cout<<"Input \""<<easter[i].trig<<"\" into the main menu."<<endl;
                else cout<<"A secret is required"<<endl;
            }
            cout<<"--------"<<endl<<"Press enter to continue..."<<endl;
            cin.get();
            clc();
        } else if (homeans=="3") {
            while (true) {
                cout<<"Settings"<<endl<<"[1]Sort:";
                if (srtmode==1) cout<<"Alphabetically, increasing"<<endl;
                else if (srtmode==2) cout<<"Alphabetically, decreasing"<<endl;
                else if (srtmode==3) cout<<"Scores, increasing"<<endl;
                else if (srtmode==4) cout<<"Scores, decreasing"<<endl;
                else if (srtmode==5) cout<<"Date, increasing"<<endl;
                else if (srtmode==6) cout<<"Date, decreasing"<<endl;
                else cout<<"Error"<<endl;
                cout<<"[2]Keep assignments for:";
                if (rten==1) cout<<"1 week"<<endl;
                else if (rten==2) cout<<"2 weeks"<<endl;
                else if (rten==3) cout<<"1 month"<<endl;
                else if (rten==4) cout<<"2 months"<<endl;
                else if (rten==5) cout<<"6 months"<<endl;
                else if (rten==6) cout<<"Forever"<<endl;
                else cout<<"Error"<<endl;
                cout<<"[3]Multicore:";
                if (mltcore>1) cout<<mltcore<<" cores"<<endl;
                else if (mltcore) cout<<mltcore<<" core"<<endl;
                else cout<<"Error"<<endl;
                cout<<"[4]Sound:";
                if (sound) {
                    if (selaud.size()==0) cout<<"No song selected"<<endl;
                    else if (audio.size()==selaud.size()) cout<<"All"<<endl;
                    else {
                        cout<<audio[selaud[0]].sname;
                        if (selaud.size()==2) cout<<" and "<<selaud.size()-1<<" other...";
                        else if (selaud.size()>=2) cout<<" and "<<selaud.size()-1<<" others...";
                        cout<<endl;
                    }
                }
                else cout<<"Disabled"<<endl;
                cout<<"[5]Autosave:";
                if (autosave) cout<<"Enabled"<<endl;
                else {
                    if (asdisabled) cout<<"Disabled due to import issue"<<endl;
                    else cout<<"Disabled"<<endl;
                }
                cout<<"[6]Limit items on one page to:";
                if (ovrflw) cout<<ovrflw<<" items"<<endl;
                else cout<<"Infinite"<<endl;
                cout<<"[7]Answer file:";
                if (anslock) cout<<lockedf<<endl;
                else cout<<"Disabled"<<endl;
                cout<<"[8]Exit Settings"<<endl;
                string setans;
                getline(cin,setans);
                clc();
                if (setans=="1") {
                    cout<<"Select sort mode:"<<endl<<"[1]Alphabetically, increasing"<<endl<<"[2]Alphabetically, decreasing"<<endl<<"[3]Scores, increasing"<<endl<<"[4]Scores, decreasing"<<endl<<"[5]Date, increasing"<<endl<<"[6]Date, decreasing"<<endl;
                    string srtans;
                    getline(cin,srtans);
                    if (atoll(srtans.c_str())>=1&&atoll(srtans.c_str())<=6) {
                        srtmode=atoll(srtans.c_str());
                    }
                    if (autosave) savedata();
                } else if (setans=="2") {
                    cout<<"About keep assignments:Assignments older than the set time will be automatically deleted."<<endl<<"Select your preferred time."<<endl<<"[1]1 week"<<endl<<"[2]2 weeks"<<endl<<"[3]1 month"<<endl<<"[4]2 months"<<endl<<"[5]6 months"<<endl<<"[6]Forever"<<endl;
                    string settmp;
                    getline(cin,settmp);
                    if (to_string(atoll(settmp.c_str()))==settmp) {
                        ll timetmp = atoll(settmp.c_str());
                        if (timetmp>0&&timetmp<7) {
                            rten=timetmp;
                            if (rten==1) cout<<"Assignment time successfully set to 1 week."<<endl;
                            else if (rten==2) cout<<"Assignment time successfully set to 2 weeks."<<endl;
                            else if (rten==3) cout<<"Assignment time successfully set to 1 month."<<endl;
                            else if (rten==4) cout<<"Assignment time successfully set to 2 months."<<endl;
                            else if (rten==5) cout<<"Assignment time successfully set to 6 months."<<endl;
                            else if (rten==6) cout<<"Assignment time successfully set to forever."<<endl;
                        }
                    }
                    if (autosave) savedata();
                } else if (setans=="3") {
                    cout<<"About multicore:Your processor may be capable of running multiple tasks at once. Using multicore settings will evaluate homework using more cores. "<<endl<<"Input the amount of cores."<<endl;
                    if (compcore==0) cout<<"Suggestion is unavailble."<<endl;
                    else if (compcore<=3) cout<<"Using one core is recommended."<<endl;
                    else cout<<"Using "<<compcore-2<<" cores is recommended."<<endl;
                    string settmp;
                    getline(cin,settmp);
                    if (to_string(atoll(settmp.c_str()))==settmp) {
                        ll coretmp = atoll(settmp.c_str());
                        if (coretmp>0) {
                            mltcore=coretmp;
                            if (mltcore==1) cout<<"Multicore successfully set to 1 core."<<endl;
                            else cout<<"Multicore successfully set to "<<mltcore<<" cores."<<endl;
                        }
                    }
                    if (autosave) savedata();
                } else if (setans=="4") {
                    if (SYS==APPL) {
                        bool dirlib=false;
                        bool soundlib=false;
                        ifstream libftest("/usr/local/lib");
                        if (libftest.good()) {
                            dirlib=true;
                        }
                        libftest.close();
                        if (dirlib) {
                            libftest.open("/usr/local/lib/libirrklang.dylib");
                            if (libftest.good()) {
                                soundlib=true;
                            }
                        }
                        if (dirlib&&soundlib) {
                            while (true) {
                                if (sound) {
                                    while (true) {
                                        cout<<"Current selectiion:";
                                        if (selaud.size()==audio.size()) cout<<"All";
                                        else if (selaud.size()==0) {
                                            cout<<"None";
                                        } else {
                                            cout<<audio[selaud[0]].sname;
                                            for (ll i=1;i<selaud.size();i++) {
                                                cout<<", "<<audio[selaud[i]].sname;
                                            }
                                        }
                                        bool soundcapped=true;
                                        if (audio.size()<35) soundcapped=false;
                                        cout<<endl<<"[1]Disable sound"<<endl;
                                        if (!soundcapped) cout<<"[2]Add new sounds"<<endl;
                                        cout<<"["<<3-soundcapped<<"]Delete sounds"<<endl<<"--------"<<endl<<"["<<4-soundcapped<<"]Select all"<<endl;
                                        map<char, ll>schoice;
                                        for (ll i=0;i<audio.size();i++) {
                                            if (i+5-soundcapped<=9) {
                                                cout<<"["<<i+5-soundcapped<<"]"<<audio[i].sname<<endl;
                                                schoice[i+5-soundcapped+'0']=i+1;
                                            } else {
                                                schoice['A'+i-5-soundcapped]=i+1;
                                                cout<<"["<<(char)('A'+i-5-soundcapped)<<"]"<<audio[i].sname<<endl;
                                            }
                                        }
                                        cout<<"Select songs to play after a correct submission..."<<endl;
                                        string songchoice;
                                        getline(cin,songchoice);
                                        bool fc[audio.size()];
                                        bool choosesounds=true;
                                        for (ll i=0;i<audio.size();i++) fc[i]=0;
                                        for (ll i=0;i<songchoice.length();i++) {
                                            if (songchoice[i]==4-soundcapped+'0') for (ll j=0;j<audio.size();j++) fc[j]=1;
                                            else if (schoice[songchoice[i]]!=0) fc[schoice[songchoice[i]]-1]=1;
                                            else if (songchoice[i]=='2') {
                                                choosesounds=false;
                                                cout<<"Alert! Song must be in WAV format."<<endl<<"Input the path of the song..."<<endl;
                                                string newsoundpth;
                                                getline(cin,newsoundpth);
                                                nml(newsoundpth);
                                                ifstream newsoundtest(newsoundpth);
                                                if (newsoundtest.good()) {
                                                    newsoundtest.close();
                                                    cout<<"What is the name of the song?"<<endl;
                                                    string songn;
                                                    getline(cin,songn);
                                                    string songf="";
                                                    for (ll j=0;j<16;j++) songf+=randname[rand()%36];
                                                    fcopy(newsoundpth,db+songf+".wav");
                                                    audio.push_back({songf,songn});
                                                    cout<<"Song "<<songn<<" imported successfully."<<endl;
                                                } else cout<<"Error reading song!"<<endl;
                                                //add new sounds
                                                break;
                                            } else if (songchoice[i]==3-soundcapped+'0') {
                                                choosesounds=false;
                                                for (ll i=0;i<audio.size();i++) {
                                                    cout<<"[";
                                                    i<9?cout<<i+1:cout<<(char)('A'+i-9);
                                                    cout<<"]"<<audio[i].sname<<endl;
                                                }
                                                cout<<"What song do you want to delete?"<<endl;
                                                string delschoice;
                                                getline(cin,delschoice);
                                                set<ll>delchoice;
                                                for (ll i=0;i<delschoice.length();i++) delchoice.insert(delschoice[i]>='A'?delschoice[i]-'A'+10-1:delschoice[i]-'0'-1);
                                                vector<ll>todel;
                                                for (set<ll>::iterator i=delchoice.begin();i!=delchoice.end();i++) if (*i<audio.size()) todel.push_back(*i); else break;
                                                if (todel.size()) cout<<"Are you sure you want to delete ";
                                                for (ll i=0;i<todel.size()-1;i++) cout<<audio[todel[i]].sname<<", ";
                                                if (todel.size()>1) cout<<"and ";
                                                cout<<audio[todel[todel.size()-1]].sname<<"? This action is irreversible. Input CONFIRM to confirm."<<endl;
                                                string conf;
                                                getline(cin,conf);
                                                if (conf=="CONFIRM") {
                                                    for (ll i=todel.size()-1;i>=0;i--) audio.erase(audio.begin()+todel[i]);
                                                    sort(selaud.begin(),selaud.end());
                                                    for (ll i=selaud.size();i>=0;i++) {
                                                        if (selaud[i]>=audio.size()) selaud.erase(selaud.begin()+i);
                                                        i--;
                                                    }
                                                }
                                            } else if (songchoice=="1") {
                                                cout<<"Sound disabled"<<endl;
                                                sound=false;
                                                break;
                                            }
                                        }
                                        if (choosesounds) {
                                            selaud.clear();
                                            for (ll i=0;i<audio.size();i++) if (fc[i]) selaud.push_back(i);
                                            break;
                                        }
                                    }
                                    break;
                                } else {
                                    cout<<"Sound enabled"<<endl;
                                    sound=true;
                                }
                            }
                        } else {
                            cout<<"Using sound requires the installation of external libraries. This will require an administrator password. Enter y to proceed."<<endl;
                            string confins;
                            getline(cin,confins);
                            if (confins=="y"||confins=="Y") {
                                ofstream sil(db+"tmp/sil.txt");
                                if (!sil.good()) cout<<"Error writing silent file to tmp(SOUND)"<<endl;
                                sil<<"SILENCE";
                                sil.close();
                                removeWithinFolder(db+"tmp/");
                                system(("open "+safespace(db+"soundsetup")).c_str());
                                ifstream donetest;
                                while (true) {
                                    donetest.open(db+"tmp/installed.txt");
                                    if (donetest.good()) break;
                                    donetest.close();
                                    usleep(1e4);
                                }
                                donetest.close();
                                ifstream instest("/usr/local/lib/libirrklang.dylib");
                                if (instest.good()) {
                                    cout<<"Sound enabled"<<endl;
                                    sound=true;
                                } else cout<<"Install failed."<<endl;
                                instest.close();
                            }
                        }
                        if (autosave) savedata();
                    } else {
                        cout<<"The Windows version of Homework does not support sound yet."<<endl;
                    }
                } else if (setans=="5") {
                    if (autosave) {
                        cout<<"Autosave disabled."<<endl;
                        autosave=false;
                    } else {
                        if (asdisabled) {
                            cout<<"Are you sure about enabling autosave? You may corrupt files. Input CONFIRM to confirm."<<endl;
                            string conf;
                            getline(cin,conf);
                            if (conf=="CONFIRM") {
                                cout<<"Autosave enabled."<<endl;
                                autosave=true;
                                savedata();
                                asdisabled=false;
                            }
                        } else {
                            cout<<"Autosave enabled."<<endl;
                            autosave=true;
                            savedata();
                        }
                    }
                } else if (setans=="6") {
                    cout<<"How many items to limit to? Input 0 for no limits."<<endl;
                    while (true) {
                        string itmlim;
                        getline(cin,itmlim);
                        if (to_string(atoll(itmlim.c_str()))!=itmlim) {
                            cout<<"Invalid input!"<<endl;
                            continue;
                        }
                        if (atoll(itmlim.c_str())>=0) {
                            ovrflw=atoll(itmlim.c_str());
                            break;
                        } else {
                            cout<<"Invalid input!"<<endl;
                        }
                    }
                } else if (setans=="7") {
                    cout<<"About answer file:Answer file sets a specific file for submissions."<<endl;
                    string anslockans;
                    if (anslock) {
                        while (true) {
                            cout<<"Current answer file:"<<lockedf<<endl<<"[1]Disable answer file"<<endl<<"[2]Change answer file"<<endl<<"[3]Exit"<<endl;
                            getline(cin,anslockans);
                            if (anslockans=="1") {
                                anslock=0;
                                cout<<"Answer file disabled"<<endl;
                                break;
                            } else if (anslockans=="2") {
                                cout<<"Enter the path of the file"<<endl;
                                getline(cin,anslockans);
                                if (anslockans.find("dwtReserved::")==string::npos) {
                                    lockedf=anslockans;
                                    break;
                                } else cout<<"Filename cannot contain \"dwtReserved::\"!"<<endl;
                            } else if (anslockans=="3") {
                                break;
                            }
                        }
                    } else {
                        while (true) {
                            cout<<"[1]Enable answer file"<<endl<<"[2]Exit"<<endl;
                            getline(cin,anslockans);
                            if (anslockans=="1") {
                                cout<<"Enter the path of the file"<<endl;
                                getline(cin,anslockans);
                                if (anslockans.find("dwtReserved::")==string::npos) {
                                    lockedf=anslockans;
                                    anslock=1;
                                    break;
                                } else cout<<"Filename cannot contain \"dwtReserved::\"!"<<endl;
                            } else if (anslockans=="2") break;
                        }
                    }
                } else if (setans=="8") {
                    clc();
                    break;
                }
            }
        } else if (homeans=="4") {
            //Save
            savedata();
            for (ll i=1;i<=mltcore;i++) {
                ofstream stopsig(db+"tmp/"+to_string(i)+"/pth.bridge");
                if (!stopsig.good()) cout<<"Critical error! Error accessing path bridge in "<<i<<" while planting STOP signal"<<endl;
                stopsig<<"STOP";
                stopsig.close();
            }
            return 0;
        } else if (tolower(homeans[0])=='f'&&homeans.length()==1&&impissue) {
            for (ll i=1;i<=mltcore;i++) {
                ofstream stopsig(db+"tmp/"+to_string(i)+"/pth.bridge");
                if (!stopsig.good()) cout<<"Critical error! Error accessing path bridge in "<<i<<" while planting STOP signal"<<endl;
                stopsig<<"STOP";
                stopsig.close();
            }
            return 0;
        } else if (to_string(homeansNum)==homeans&&homeansNum>=5&&homeansNum<outcnt) { //MARK:Set file
            chosenID=hwpoint[atoll(homeans.c_str())-5];
            if (chosenID==-1) cout<<"Invalid response."<<endl;
            else {
                vq=true;
                target = asmt[chosenID].id;
            }
        } else if (to_string(homeansNum)==homeans&&homeansNum==prevID&&prevID!=-1) grp--;
        else if (to_string(homeansNum)==homeans&&homeansNum==nxtID&&nxtID!=-1) grp++;
        else if (to_string(homeansNum)==homeans&&homeansNum==jmpID&&jmpID!=-1) {
            while (true) {
                cout<<"Which page would you like to jump to? Current page:Page "<<grp+1<<" of "<<showMore.size()<<endl;
                string jmpNum;
                getline(cin,jmpNum);
                ll jmpNumNum=atoll(jmpNum.c_str());
                if (to_string(jmpNumNum)==jmpNum&&jmpNumNum>=1&&jmpNumNum<=showMore.size()) {
                    grp=jmpNumNum-1;
                    break;
                } else cout<<"Jump number invalid!"<<endl;
            }
        } else {
            string vtmp=homeans;
            transform(homeans.begin(),homeans.end(),vtmp.begin(),::tolower);
            bool hitach = false;
            for (ll i=0;i<easter.size();i++) {
                if (homeans==easter[i].trig) {
                    hitach=true;
                    cout<<easter[i].msg<<endl;
                    if (!secret[i]) cout<<"Achievement \""<<easter[i].ach<<"\" complete."<<endl;
                    secret[i]=true;
                    break;
                }
            }
            if (!hitach) {
                if (vtmp=="changelog") {
                    changelog();
                } else if (vtmp=="kill") {
                    for (ll i=1;i<=mltcore;i++) {
                        ofstream stopsig(db+"tmp/"+to_string(i)+"/pth.bridge");
                        if (!stopsig.good()) cout<<"Critical error! Error accessing path bridge in "<<i<<" while planting STOP signal"<<endl;
                        stopsig<<"STOP";
                        stopsig.close();
                    }
                    return 0;
                } else if (vtmp=="crypt") {
                    if (SYS==APPL) {
                        cout<<"Crypto helper"<<endl<<"Enter the path of the file."<<endl;
                        string cryf;
                        getline(cin,cryf);
                        nml(cryf);
                        ifstream crytest(cryf);
                        if (crytest.good()) {
                            crytest.close();
                            cout<<"Enter the output file."<<endl;
                            string cryof;
                            getline(cin,cryof);
                            system((cmdenc+" -in "+safespace(cryf)+" -out "+safespace(cryof)).c_str());
                        } else cout<<"File error!"<<endl;
                    } else {
                        cout<<"Crypto system is only available on the Mac version of Homework."<<endl;
                    }
                } else if (vtmp=="batchmake") {
                    #if CANUSEFS
                    //Batch make
                    cout<<"Input directory to batch make from"<<endl;
                    string dirBtch;
                    getline(cin,dirBtch);
                    vector<string>chkobj;
                    if (true) {
                        chkobj.push_back("description.txt");
                        chkobj.push_back("in.txt");
                        chkobj.push_back("out.txt");
                        chkobj.push_back("title.txt");
                        chkobj.push_back("in1.txt");
                        chkobj.push_back("in2.txt");
                    }
                    for (const fs::directory_entry& entry : fs::recursive_directory_iterator(dirBtch)) {
                        if (fs::is_directory(entry.path())) {
                            ifstream check;
                            map<string,bool>gotF;
                            for (const fs::directory_entry& disf : fs::directory_iterator(entry.path())) {
                                string rdcpkg=disf.path();
                                while (rdcpkg.find("/")!=string::npos) rdcpkg=rdcpkg.substr(rdcpkg.find("/")+1);
                                gotF[rdcpkg]=true;
                            }
                            bool isQ=true;
                            for (ll i=0;i<chkobj.size()&&isQ;i++) if (!gotF[chkobj[i]]) isQ=false;
                            if (isQ) {
                                string pkgpth=entry.path();
                                string outpth=pkgpth+".hwfx";
                                ifstream testOverlap(outpth);
                                if (testOverlap.good()) {
                                    cout<<outpth<<" already exists."<<endl;
                                    continue;
                                }
                                string rdcpkg=pkgpth;
                                while (rdcpkg.find("/")!=string::npos) rdcpkg=rdcpkg.substr(rdcpkg.find("/")+1);
                                stringstream masterPkg;
                                ll contCnt=0;
                                bool impFail;
                                string disTtl=rdcpkg;
                                stringstream newPkg;
                                writeHwfx(pkgpth,impFail,disTtl,newPkg);
                                if (impFail) cout<<"Processing of "<<disTtl<<" failed."<<endl;
                                else {
                                    cout<<disTtl<<" successfully processed."<<endl;
                                    masterPkg<<newPkg.str();
                                    contCnt++;
                                }
                                if (contCnt>0) {
                                    ofstream fxOut(outpth);
                                    if (fxOut.good()) {
                                        fxOut<<"HwfxContents::FVERS"<<endl<<"2"<<endl<<"HwfxContents::PKGCNT"<<endl<<contCnt<<endl<<"HwfxContents::DATASIZE"<<endl<<masterPkg.str().size()<<endl<<"HwfxContents::IV"<<endl;
                                        unsigned char iv[16];
                                        for (ll i=0;i<16;i++) {
                                            iv[i]=rand()%256;
                                            fxOut<<(int)iv[i]<<endl;
                                        }
                                        fxOut<<"HwfxContents::PAYLOAD"<<endl;
                                        string plyd = masterPkg.str();
                                        ll newLen=plyd.size();
                                        newLen=ceil(newLen/16.0)*16;
                                        unsigned char newMsg[newLen];
                                        for (ll i=0;i<plyd.size();i++) newMsg[i]=plyd[i];
                                        for (ll i=plyd.size();i<newLen;i++) newMsg[i]=0;
                                        aes_encrypt(newMsg, newLen, aesKey, 32, iv);
                                        for (ll i=0;i<newLen;i++) fxOut<<newMsg[i];
                                    } else cout<<"Unable to write to out file."<<endl;
                                    fxOut.close();
                                }
                            }
                        }
                    }
                    #else
                        cout<<"Error! Filesystem is unavailable!"<<endl;
                    #endif
                } else if (vtmp=="batchimport") {
                    #if CANUSEFS
                    //Batch import
                    cout<<"Input directory to batch import from"<<endl;
                    string dirBtch;
                    getline(cin,dirBtch);
                    for (const fs::directory_entry& entry : fs::recursive_directory_iterator(dirBtch)) {
                        if (fs::is_regular_file(entry.path())) {
                            string chk=entry.path();
                            if (chk.size()>=5&&chk.substr(chk.size()-5,5)==".hwfx") {
                                bool dummy1;
                                string dummy2;
                                ll dummy3;
                                string rdcpth=chk;
                                while (rdcpth.find("/")!=string::npos) rdcpth=rdcpth.substr(rdcpth.find("/")+1);
                                if (readHwfx(chk,dummy1,dummy2,dummy3)) cout<<"Successfully imported "<<rdcpth<<endl;
                                else cout<<"Error importing "<<rdcpth<<endl;
                            }
                        }
                    }
                    if (autosave) savedata();
                    #else
                        cout<<"Error! Filesystem is unavailable!"<<endl;
                    #endif
                } else if (vtmp=="clearf") {
                    cout<<"Clear all program files? This action is irreversible(Input CLEAR in all caps to confirm)"<<endl;
                    string clearall;
                    getline(cin,clearall);
                    if (clearall=="CLEAR") {
                        removeFolder(db);
                        cout<<"Files cleared. Program will now force quit."<<endl;
                        return 0;
                    }
                } else if (vtmp=="id") {
                    cout<<"How many random length 16 IDs?"<<endl;
                    string idin;
                    getline(cin,idin);
                    if (atoll(idin.c_str())>0) {
                        for (ll i=0;i<atoll(idin.c_str());i++) {
                            string idout="";
                            for (ll j=0;j<16;j++) idout+=randname[rand()%36];
                            cout<<idout<<endl;
                        }
                    }
                } else if (vtmp=="const") cout<<"System:"<<SYS<<endl<<"Filesystem:"<<CANUSEFS<<endl;
                else if (vtmp=="make") {
                    cout<<"hwfX package maker. Example hierarchy:"<<endl<<"Add_One"<<endl<<"  |- title.txt:Title"<<endl<<"  |- description.txt:Problem description"<<endl<<"  |- exin1.txt:Example input 1"<<endl<<"  |- exin2.txt:Example input 2"<<endl<<"  |- exout1.txt:Example output 1 to match up with exin1"<<endl<<"  |- exout2.txt:Example output 2"<<endl<<"  |- in.txt:Input requirements"<<endl<<"  |- out.txt:Output requirements"<<endl<<"  |- in1.txt:Testing input set #1"<<endl<<"  |- in2.txt:Testing input set #2"<<endl<<"  |- out1.txt:Testing output #1, matches up with in1.txt"<<endl<<"  |- out2.txt:Testing output #2"<<endl<<"  |-------"<<endl<<"You may include any amount of test sets. 10-20 is recommended."<<endl<<"You may also include any amount of example inputs. 1-3 is recommended."<<endl<<"Input your assignment's directory. Don't include a / at the end of your path."<<endl;
                    string pkgpth;
                    getline(cin,pkgpth);
                    string outpth=pkgpth+".hwfx";
                    bool gogogo=false;
                    while (true) {
                        ifstream testOverlap(outpth);
                        bool goOn=false;
                        if (testOverlap.good()) {
                            while (true) {
                                cout<<"The file "<<outpth<<" already exists. Do you want to "<<endl<<"[1]Overwrite"<<endl<<"[2]Choose another path"<<endl<<"[3]Stop"<<endl;
                                string ovrlpdec;
                                getline(cin,ovrlpdec);
                                if (ovrlpdec=="1") {
                                    goOn=true;
                                    break;
                                } else if (ovrlpdec=="2") {
                                    string rdcpkg=pkgpth;
                                    while (rdcpkg.find("/")!=string::npos) rdcpkg=rdcpkg.substr(rdcpkg.find("/")+1);
                                    rdcpkg+=".hwfx";
                                    cout<<"Please input the directory for the file "<<rdcpkg<<". (Do not include / at the end)"<<endl;
                                    getline(cin,outpth);
                                    outpth=outpth+"/"+rdcpkg;
                                    testOverlap.close();
                                    break;
                                } else if (ovrlpdec=="3") {
                                    goOn=true;
                                    gogogo=true;
                                    break;
                                } else cout<<"Invalid response."<<endl;
                            }
                        } else {
                            ofstream outTst(outpth);
                            if (outTst.good()) break;
                            else cout<<"Failed to write to "<<outpth<<". Do you want to "<<endl<<"[1]Change file path"<<endl<<"[2]Stop"<<endl;
                            string badWrtRes;
                            getline(cin,badWrtRes);
                            while (true) {
                                if (badWrtRes=="1") {
                                    string rdcpkg=pkgpth;
                                    while (rdcpkg.find("/")!=string::npos) rdcpkg=rdcpkg.substr(rdcpkg.find("/")+1);
                                    rdcpkg+=".hwfx";
                                    cout<<"Please input the directory for the file "<<rdcpkg<<". (Do not include / at the end)"<<endl;
                                    getline(cin,outpth);
                                    outpth=outpth+"/"+rdcpkg;
                                    break;
                                } else {
                                    gogogo=true;
                                    break;
                                }
                            }
                        }
                        if (goOn) break;
                    }
                    string rdcpkg=pkgpth;
                    while (rdcpkg.find("/")!=string::npos) rdcpkg=rdcpkg.substr(rdcpkg.find("/")+1);
                    if (gogogo) continue;
                    stringstream masterPkg;
                    ll contCnt=0;
                    while (true) {
                        bool impFail;
                        string disTtl=rdcpkg;
                        stringstream newPkg;
                        writeHwfx(pkgpth,impFail,disTtl,newPkg);
                        if (impFail) cout<<"Importing of "<<disTtl<<" failed."<<endl;
                        else {
                            cout<<disTtl<<" successfully processed."<<endl;
                            masterPkg<<newPkg.str();
                            contCnt++;
                        }
                        cout<<"Would you like to add another file to the package?"<<endl<<"[1]Yes"<<endl<<"[2]No"<<endl;
                        string doItAgain;
                        while (true) {
                            getline(cin,doItAgain);
                            if (doItAgain!="1"&&doItAgain!="2") cout<<"Invalid response."<<endl;
                            else break;
                        }
                        if (doItAgain=="1") {
                            cout<<"Please input the assignment's directory. Don't include a / at the end of your path."<<endl;
                            getline(cin,pkgpth);
                        } else break;
                    }
                    if (contCnt>0) {
                        ofstream fxOut(outpth);
                        if (fxOut.good()) {
                            fxOut<<"HwfxContents::FVERS"<<endl<<"2"<<endl<<"HwfxContents::PKGCNT"<<endl<<contCnt<<endl<<"HwfxContents::DATASIZE"<<endl<<masterPkg.str().size()<<endl<<"HwfxContents::IV"<<endl;
                            unsigned char iv[16];
                            for (ll i=0;i<16;i++) {
                                iv[i]=rand()%256;
                                fxOut<<(int)iv[i]<<endl;
                            }
                            fxOut<<"HwfxContents::PAYLOAD"<<endl;
                            string plyd = masterPkg.str();
                            ll newLen=plyd.size();
                            newLen=ceil(newLen/16.0)*16;
                            unsigned char newMsg[newLen];
                            for (ll i=0;i<plyd.size();i++) newMsg[i]=plyd[i];
                            for (ll i=plyd.size();i<newLen;i++) newMsg[i]=0;
                            aes_encrypt(newMsg, newLen, aesKey, 32, iv);
                            for (ll i=0;i<newLen;i++) fxOut<<newMsg[i];
                        } else cout<<"Unable to write to out file."<<endl;
                        fxOut.close();
                        cout<<"hwfX file created at "<<outpth<<endl;
                    } else cout<<"No assignments loaded! No file created."<<endl;
                } else {
                    for (ll i=0;i<asmt.size();i++) {
                        string cmpTmp=asmt[i].name;
                        transform(cmpTmp.begin(),cmpTmp.end(),cmpTmp.begin(),::tolower);
                        if (vtmp==cmpTmp) {
                            chosenID=i;
                            target=asmt[chosenID].id;
                            vq=true;
                        }
                    }
                    if (!vq) cout<<"Invalid response."<<endl;
                }
                clc();
            }
        }
        if (vq) {
            clc();
            ifstream bundltest(db+target);
            if (!bundltest.good()) {
                cout<<"Error! Homework file missing."<<endl;
                continue;
            }
            string hwfxVerf;
            bundltest>>hwfxVerf;
            bundltest.close();
            
            vector<string>probdes;
            string probname="";
            vector<string>probin;
            vector<string>probout;
            vector<vector<string>>outex;
            vector<vector<string>>outdata;
            vector<vector<string>>indata;
            vector<vector<string>>inex;
            if (hwfxVerf=="HwfxContents::") {
                ifstream rd(db+target);
                vector<string>fHeader;
                while (true) {
                    string impTmp;
                    getline(rd,impTmp);
                    if (impTmp=="HwfxContents::PAYLOAD") break;
                    else fHeader.push_back(impTmp);
                }
                stringstream transF;
                transF<<rd.rdbuf();
                string fplyd=transF.str();
                transF.str("");
                rd.close();
                unsigned char iv[16]={0};
                bool gotIv=false,gotFvers=false,gotDtsz=false,gotCnt=false;
                string fvers="";
                ll dtsz=0,ascnt=0;
                for (ll i=0;i<fHeader.size();i++) {
                    if (fHeader[i]=="HwfxContents::FVERS") {
                        if (i+1!=fHeader[i].size()) {
                            fvers=fHeader[++i];
                            gotFvers=true;
                        }
                    } else if (fHeader[i]=="HwfxContents::DATASIZE") {
                        if (i+1!=fHeader.size()) {
                            dtsz=atoll(fHeader[++i].c_str());
                            gotDtsz=true;
                        }
                    } else if (fHeader[i]=="HwfxContents::IV") {
                        for (ll j=i+1;j<=i+16;j++) {
                            iv[j-i-1]=atoll(fHeader[j].c_str());
                            if (j+1==fHeader.size()&&j-i-1!=15) {
                                cout<<"Error reading IV!"<<endl;
                                break;
                            }
                        }
                        i+=17;
                        gotIv=true;
                    } else if (fHeader[i]=="HwfxContents::PKGCNT") {
                        if (i+1!=fHeader.size()) {
                            ascnt=atoll(fHeader[++i].c_str());
                            gotCnt=true;
                        }
                    }
                }
                if (!gotIv) cout<<"Error reading IV!"<<endl;
                if (!gotFvers) cout<<"Error reading file version!"<<endl;
                if (!gotDtsz) cout<<"Error reading file size!"<<endl;
                if (!gotCnt) cout<<"Error reading assignment count!"<<endl;
                if (fvers!="2") cout<<"Alert! File version unsupported!"<<endl;
                ll newLen=dtsz;
                newLen=ceil(dtsz/16.0)*16;
                unsigned char decPkg[newLen];
                for (ll i=0;i<fplyd.size();i++) decPkg[i]=fplyd[i];
                for (ll i=fplyd.size();i<newLen;i++) decPkg[i]=0;
                aes_decrypt(decPkg, ceil(dtsz/16.0)*16, aesKey, 32, iv);
                for (ll i=0;i<dtsz;i++) transF<<decPkg[i];
                vector<string>reLd;
                string ft;
                while (getline(transF,ft)) reLd.push_back(ft);
                //read in all except exin and inset
                //use maps to verify exin and inset
                //then read
                for (ll i=0;i<reLd.size();i++) {
                    if (reLd[i]=="HwfxContentws::Title") {
                        for (i++;reLd[i].find("HwfxContents::")==string::npos&&i<reLd.size();i++) probname=probname+reLd[i];
                    } else if (reLd[i]=="HwfxContents::Description") {
                        for (i++;reLd[i].find("HwfxContents::")==string::npos&&i<reLd.size();i++) probdes.push_back(reLd[i]);
                    } else if (reLd[i]=="HwfxContents::InputDes") {
                        for (i++;reLd[i].find("HwfxContents::")==string::npos&&i<reLd.size();i++) probin.push_back(reLd[i]);
                    } else if (reLd[i]=="HwfxContents::OutputDes") {
                        for (i++;reLd[i].find("HwfxContents::")==string::npos&&i<reLd.size();i++) probout.push_back(reLd[i]);
                    }
                }
                map<ll,dtCont>exCnt;
                map<ll,dtCont>stCnt;
                map<ll,dtCont>stPos;
                for (ll i=0;i<reLd.size();i++) {
                    if (reLd[i].find("HwfxContents::ExampleInput")!=string::npos) {
                        exCnt[atoll(reLd[i].substr(26).c_str())].cnt++;
                        exCnt[atoll(reLd[i].substr(26).c_str())].ipos=i;
                    } else if (reLd[i].find("HwfxContents::ExampleOutput")!=string::npos) {
                        exCnt[atoll(reLd[i].substr(27).c_str())].cnt++;
                        exCnt[atoll(reLd[i].substr(27).c_str())].opos=i;
                    } else if (reLd[i].find("HwfxContents::InputSet")!=string::npos) {
                        stCnt[atoll(reLd[i].substr(22).c_str())].cnt++;
                        stCnt[atoll(reLd[i].substr(22).c_str())].ipos=i;
                    } else if (reLd[i].find("HwfxContents::OutputSet")!=string::npos) {
                        stCnt[atoll(reLd[i].substr(23).c_str())].cnt++;
                        stCnt[atoll(reLd[i].substr(23).c_str())].opos=i;
                    }
                }
                ll rbndex=0;
                for (map<ll,dtCont>::iterator it=exCnt.begin();it!=exCnt.end();it++) {
                    if (it->second.cnt!=2) cout<<"Error with example #"<<it->first<<endl;
                    rbndex=max(rbndex,it->first);
                }
                if (rbndex!=exCnt.size()) cout<<"Missing examples! "<<exCnt.size()<<" examples found, "<<rbndex<<" examples expected."<<endl;
                ll rbndst=0;
                for (map<ll,dtCont>::iterator it=stCnt.begin();it!=stCnt.end();it++) {
                    if (it->second.cnt!=2) cout<<"Error with i/o set #"<<it->first<<endl;
                    rbndst=max(rbndst,it->first);
                }
                if (rbndst!=stCnt.size()) cout<<"Missing sets! "<<stCnt.size()<<" sets found, "<<rbndst<<" sets expected."<<endl;
                for (ll i=1;i<=rbndex;i++) {
                    vector<string>exTmp;
                    for (ll j=exCnt[i].ipos+1;reLd[j].find("HwfxContents::")==string::npos&&j<reLd.size();j++) exTmp.push_back(reLd[j]);
                    inex.push_back(exTmp);
                    exTmp.clear();
                    for (ll j=exCnt[i].opos+1;reLd[j].find("HwfxContents::")==string::npos&&j<reLd.size();j++) exTmp.push_back(reLd[j]);
                    outex.push_back(exTmp);
                }
                for (ll i=1;i<=rbndst;i++) {
                    vector<string>stTmp;
                    for (ll j=stCnt[i].ipos+1;reLd[j].find("HwfxContents::")==string::npos&&j<reLd.size();j++) stTmp.push_back(reLd[j]);
                    indata.push_back(stTmp);
                    stTmp.clear();
                    for (ll j=stCnt[i].opos+1;reLd[j].find("HwfxContents::")==string::npos&&j<reLd.size();j++) stTmp.push_back(reLd[j]);
                    outdata.push_back(stTmp);
                }
            } else {
                if (SYS==APPL) {
                    ll dtpt = 1;
                    ll ex = 1;
                    //DECRYPT
                    string denccmd = "openssl aes-256-cbc -d -K "+key+" -iv "+iv+" -S "+salt+" -in "+safespace(db+target)+" -out "+safespace(db+"tmp/"+target);
                    system(denccmd.c_str());
                    //OPEN EM
                    system(("unzip -o -qq "+safespace(db+"tmp/"+target)+" -d "+safespace(db+"tmp/"+target+'e')).c_str());
                    //READ EM
                    ifstream qread(db+"tmp/"+target+"e/description.txt");
                    if (qread.good()) {
                        while (!qread.eof()) {
                            string qreadtmp;
                            getline(qread,qreadtmp);
                            probdes.push_back(qreadtmp);
                        }
                    } else {
                        probdes.push_back("File error!");
                    }
                    qread.close();
                    qread.open(db+"tmp/"+target+"e/title.txt");
                    getline(qread,probname);
                    qread.close();
                    if (asmt[chosenID].name=="HWSysUndefined") {
                        asmt[chosenID].name=probname;
                        if (autosave) savedata();
                    }
                    qread.open(db+"tmp/"+target+"e/in.txt");
                    if (qread.good()) {
                        while (!qread.eof()) {
                            string qreadtmp;
                            getline(qread,qreadtmp);
                            probin.push_back(qreadtmp);
                        }
                    } else {
                        probin.push_back("File error!");
                    }
                    qread.close();
                    qread.open(db+"tmp/"+target+"e/out.txt");
                    if (qread.good()) {
                        while (!qread.eof()) {
                            string qreadtmp;
                            getline(qread,qreadtmp);
                            probout.push_back(qreadtmp);
                        }
                    } else {
                        probout.push_back("File error!");
                    }
                    qread.close();
                    while (true) {
                        qread.open(db+"tmp/"+target+"e/exin"+to_string(ex)+".txt");
                        if (qread.good()) {
                            vector<string>exrip;
                            while (!qread.eof()) {
                                string rdtmp;
                                getline(qread,rdtmp);
                                exrip.push_back(rdtmp);
                            }
                            inex.push_back(exrip);
                        } else {
                            break;
                        }
                        ex++;
                        qread.close();
                    }
                    ex = 1;
                    while (true) {
                        qread.open(db+"tmp/"+target+"e/exout"+to_string(ex)+".txt");
                        if (qread.good()) {
                            vector<string>exrip;
                            while (!qread.eof()) {
                                string rdtmp;
                                getline(qread,rdtmp);
                                exrip.push_back(rdtmp);
                            }
                            outex.push_back(exrip);
                        } else {
                            break;
                        }
                        ex++;
                        qread.close();
                    }
                    ex--;
                    while (true) {
                        qread.open(db+"tmp/"+target+"e/in"+to_string(dtpt)+".txt");
                        if (qread.good()) {
                            vector<string>datarip;
                            while (!qread.eof()) {
                                string rdtmp;
                                getline(qread,rdtmp);
                                datarip.push_back(rdtmp);
                            }
                            indata.push_back(datarip);
                        } else {
                            break;
                        }
                        dtpt++;
                        qread.close();
                    }
                    dtpt = 1;
                    while (true) {
                        qread.open(db+"tmp/"+target+"e/out"+to_string(dtpt)+".txt");
                        if (qread.good()) {
                            vector<string>datarip;
                            while (!qread.eof()) {
                                string rdtmp;
                                getline(qread,rdtmp);
                                datarip.push_back(rdtmp);
                            }
                            outdata.push_back(datarip);
                        } else {
                            break;
                        }
                        dtpt++;
                        qread.close();
                    }
                    dtpt--;
                    //DELETE EM
                    removeWithinFolder(db+"tmp/");
                } else cout<<"Error! HW files can only be opened in the macOS version of Homework!"<<endl;
            }
            while (true) {
                cout<<endl<<probname<<endl<<"Your current score:"<<asmt[chosenID].score<<endl<<"--------"<<endl<<"Problem description:"<<endl;
                for (ll i=0;i<probdes.size();i++) {
                    cout<<probdes[i]<<endl;
                }
                cout<<"--------"<<endl<<"Input:"<<endl;
                if (probin.size()) {
                    for (ll i=0;i<probin.size();i++) {
                        cout<<probin[i]<<endl;
                    }
                } else cout<<"None"<<endl;
                cout<<"--------"<<endl<<"Output:"<<endl;
                if (probout.size()) {
                    for (ll i=0;i<probout.size();i++) {
                        cout<<probout[i]<<endl;
                    }
                } else cout<<"None"<<endl;
                for (ll i=0;i<inex.size();i++) {
                    cout<<"--------"<<endl<<"Example input "<<i+1<<':'<<endl;
                    for (ll j=0;j<inex[i].size();j++) {
                        cout<<inex[i][j]<<endl;
                    }
                    cout<<"Example output "<<i+1<<':'<<endl;
                    for (ll j=0;j<outex[i].size();j++) {
                        cout<<outex[i][j]<<endl;
                    }
                }
                cout<<"--------"<<endl<<"[1]Submit"<<endl;
                ll cumsub=2;
                ll delchc=-1,subscclc=-1,exitclc=-1,ansfclc=-1;
                if (anslock) {
                    string simplansf=lockedf;
                    while (simplansf.find("/")!=string::npos) simplansf=simplansf.substr(simplansf.find("/")+1);
                    cout<<"["<<cumsub++<<"]Use answer file ("<<simplansf<<")"<<endl;
                    ansfclc=cumsub-1;
                }
                cout<<"["<<cumsub++<<"]Delete"<<endl;
                delchc=cumsub-1;
                bool sccode=false;
                ifstream scodetst(db+target+".cpp");
                if (scodetst.good()) sccode=true;
                scodetst.close();
                if (sccode) {
                    cout<<"["<<cumsub++<<"]View last submitted source code"<<endl;
                    subscclc=cumsub-1;
                }
                cout<<"["<<cumsub++<<"]Exit"<<endl;
                exitclc=cumsub-1;
                string hwsubans;
                getline(cin,hwsubans);
                if (hwsubans=="1"||(anslock&&hwsubans==to_string(ansfclc))) {
                    ofstream silence(db+"tmp/sl.silence");
                    if (!silence.good()) cout<<"Critical error! Error accessing TMP"<<endl;
                    silence<<"Silent!";
                    silence.close();
                    removeWithinFolder(db+"tmp/");
                    string cdpth;
                    if (hwsubans==to_string(ansfclc)) {
                        cdpth=lockedf;
                    } else {
                        cout<<"Enter code path"<<endl;
                        getline(cin,cdpth);
                    }
                    nml(cdpth);
                    ifstream codeverf(cdpth);
                    if (codeverf.good()) {
                        codeverf.close();
                        fcopy(cdpth,db+"tmp/preppedcode.cpp");
                        fcopy(cdpth,db+target+".cpp");
                        //MARK:Compile
                        inAppLaunch(db+"gpphelper"," "+username);
                        bool compile=true;
                        ifstream testcomp(db+"tmp/exe");
                        if (testcomp.good()) compile=true;
                        else compile=false;
                        if (compile) {
                            //run multicore
                            ll folders=min((ll)indata.size(),mltcore);
                            for (ll i=1;i<=folders;i++) {
                                ifstream testExist(db+"tmp/"+to_string(i));
                                if (!testExist.good()) makeDir(db+"tmp/"+to_string(i));
                            }
                            queue<ll>rmtasks;
                            for (ll i=1;i<=indata.size();i++) {
                                rmtasks.push(i);
                            }
                            //Copy over exe
                            for (ll i=1;i<=folders;i++) {
                                #if CANUSEFS
                                    fs::copy(db+"tmp/exe",db+"tmp/"+to_string(i)+"/hwexe"+to_string(i));
                                #else
                                    system(("cp "+safespace(db+"tmp/exe")+" "+safespace(db+"tmp/"+to_string(i)+"/hwexe"+to_string(i))).c_str());
                                #endif
                            }
                            //Start the first batch
                            chrono::high_resolution_clock::time_point timer[folders];
                            //MARK:START
                            for (ll i=1;i<=folders;i++) {
                                ll curtask=rmtasks.front();
                                rmtasks.pop();
                                ofstream foldout;
                                //Write in files
                                foldout.open(db+"tmp/"+to_string(i)+"/in.txt");
                                if (!foldout.good()) cout<<"Critical error! Error accessing in.txt in "<<to_string(i)<<endl;
                                if (indata[curtask-1].size()!=0) foldout<<indata[curtask-1][0];
                                for (ll j=1;j<indata[curtask-1].size();j++) {
                                    foldout<<endl<<indata[curtask-1][j];
                                }
                                foldout.close();
                                foldout.open(db+"tmp/"+to_string(i)+"/pth.bridge");
                                if (!foldout.good()) cout<<"Critical error! Error accessing path bridge in "<<i<<"."<<endl;
                                foldout<<"COM"<<endl<<db<<"tmp/"<<i<<"/"<<endl<<curtask<<endl<<db<<"tmp/"<<endl<<"hwexe"<<i;
                                foldout.close();
                                //Wait for ini.signal
                                while (true) {
                                    ifstream signaltest(db+"tmp/"+to_string(i)+"/ini.signal");
                                    if (signaltest.good()) {
                                        signaltest.close();
                                        break;
                                    }
                                    usleep(1e4);
                                }
                                timer[i-1]=chrono::high_resolution_clock::now();
                                ofstream cle(db+"tmp/"+to_string(i)+"/pth.bridge");
                                if (!cle.good()) cout<<"Critical error! Error clearing path bridge in "<<i<<"."<<endl;
                                cle.close();
                            }
                            bool mainsig[folders];
                            for (ll i=1;i<=folders;i++) {
                                mainsig[i-1]=false;
                            }
                            while (!rmtasks.empty()) {
                                for (ll i=1;i<=folders;i++) {
                                    if (!mainsig[i-1]) {
                                        //Look for TE
                                        //Look for main.signal
                                        ifstream mainsigtest(db+"tmp/"+to_string(i)+"/main.signal");
                                        if (mainsigtest.good()) {
                                            string legit;
                                            mainsigtest>>legit;
                                            if (legit=="COM") {
                                                mainsig[i-1]=true;
                                                continue;
                                            }
                                        }
                                        if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - timer[i-1]).count()>1000) {
                                            system(("killall hwexe"+to_string(i)).c_str());
                                            mainsig[i-1]=true;
                                        }
                                    }
                                }
                                for (ll i=1;i<=folders;i++) {
                                    if (rmtasks.empty()) break;
                                    if (mainsig[i-1]) { //if one of them are available...
                                        mainsig[i-1]=false;
                                        ofstream cle(db+"tmp/"+to_string(i)+"/main.signal");
                                        if (!cle.good()) cout<<"Critical error! Error clearing main.signal in "<<i<<endl;
                                        cle.close();
                                        cle.open(db+"tmp/"+to_string(i)+"/ini.signal");
                                        if (!cle.good()) cout<<"Critical error! Error clearing ini.signal in "<<i<<endl;
                                        cle.close();
                                        ll curtask=rmtasks.front();
                                        rmtasks.pop();
                                        //Write in files
                                        ofstream foldout;
                                        foldout.open(db+"tmp/"+to_string(i)+"/in.txt");
                                        if (!foldout.good()) cout<<"Critical error! Error accessing in.txt in "<<i<<endl;
                                        if (indata[curtask-1].size()!=0) foldout<<indata[curtask-1][0];
                                        for (ll j=1;j<indata[curtask-1].size();j++) {
                                            foldout<<endl<<indata[curtask-1][j];
                                        }
                                        foldout.close();
                                        //Write to the bridge
                                        foldout.open(db+"tmp/"+to_string(i)+"/pth.bridge");
                                        if (!foldout.good()) cout<<"Critical error! Error accessing path bridge in "<<i<<endl;
                                        foldout<<"COM"<<endl<<db<<"tmp/"<<i<<"/"<<endl<<curtask<<endl<<db<<"tmp/"<<endl<<"hwexe"<<i;
                                        foldout.close();
                                        //Wait for ini.signal
                                        while (true) {
                                            ifstream signaltest(db+"tmp/"+to_string(i)+"/ini.signal");
                                            string legit;
                                            if (signaltest.good()) {
                                                getline(signaltest,legit);
                                                if (legit=="Ini") break;
                                                signaltest.close();
                                            }
                                            usleep(1e4);
                                        }
                                        timer[i-1]=chrono::high_resolution_clock::now();
                                    }
                                }
                                usleep(1e4);
                            }
                            while (true) {
                                bool canbk=true;
                                for (ll i=1;i<=folders;i++) {
                                    if (!mainsig[i-1]) {
                                        canbk=false;
                                        //Something is NOT DONE AND NOT TERMINATED
                                        //Look for TE
                                        ifstream mainsigtest(db+"tmp/"+to_string(i)+"/main.signal");
                                        if (mainsigtest.good()) {
                                            string legit;
                                            getline(mainsigtest,legit);
                                            if (legit=="COM") {
                                                mainsig[i-1]=true;
                                                mainsigtest.close();
                                                continue;
                                            }
                                        }
                                        mainsigtest.close();
                                        if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - timer[i-1]).count()>1500) {
                                            system(("killall hwexe"+to_string(i)).c_str());
                                            mainsig[i-1]=true;
                                        }
                                    }
                                }
                                if (canbk) break;
                                usleep(1e4);
                            }
                            
                            //Compare output
                            ll timeres[indata.size()];
                            for (ll i=1;i<=indata.size();i++) {
                                ifstream timeread(db+"tmp/time"+to_string(i)+".txt");
                                if (!timeread.good()) timeres[i-1]=10000;
                                else timeread>>timeres[i-1];
                                timeread.close();
                            }
                            ll correct=0;
                            cout<<"Test results:"<<endl;
                            for (ll i=1;i<=indata.size();i++) {
                                if (timeres[i-1]>1000) {
                                    cout<<"#"<<i<<"-TE"<<endl;
                                } else {
                                    cout<<"#"<<i;
                                    //Evaluation:Remove last blank line
                                    vector<string>outcomp;
                                    ifstream outputc(db+"tmp/out"+to_string(i)+".txt");
                                    if (outputc.good()) {
                                        while (!outputc.eof()) {
                                            string tmp;
                                            getline(outputc,tmp);
                                            outcomp.push_back(tmp);
                                        }
                                        if (outcomp[outcomp.size()-1]=="") outcomp.erase(outcomp.begin()+outcomp.size()-1);
                                        for (ll j=0;j<outcomp.size();j++) {
                                            if (outcomp[j][outcomp[j].size()-1]==' ') {
                                                outcomp[j].erase(outcomp[j].begin()+outcomp[j].size()-1);
                                            }
                                        }
                                        if (outdata[i-1][outdata[i-1].size()-1]=="") outdata[i-1].erase(outdata[i-1].begin()+outdata[i-1].size()-1);
                                        for (ll j=0;j<outdata[i-1].size();j++) {
                                            if (outdata[i-1][j][outdata[i-1][j].size()-1]==' ') {
                                                outdata[i-1][j].erase(outdata[i-1][j].begin()+outdata[i-1][j].size()-1);
                                            }
                                        }
                                        bool ac = true;
                                        if (outdata[i-1].size()==outcomp.size()) {
                                            for (ll j=0;j<outdata[i-1].size();j++) {
                                                if (outdata[i-1][j].size()==outcomp[j].size()) {
                                                    for (ll k=0;k<outdata[i-1][j].size();k++) {
                                                        if (outdata[i-1][j][k]!=outcomp[j][k]) {
                                                            ac=false;
                                                            break;
                                                        }
                                                    }
                                                } else ac=false;
                                            }
                                        } else ac = false;
                                        if (ac) {cout<<"-AC:";correct++;}
                                        else cout<<"-WA:";
                                        cout<<timeres[i-1]<<"ms"<<endl;
                                    } else cout<<"-RTE"<<endl;
                                }
                            }
                            removeWithinFolder(db+"tmp/");
                            ll score = round(((ld)correct/indata.size())*100.0);
                            if (asmt[chosenID].score>score) cout<<"Your submission score:"<<score<<endl;
                            asmt[chosenID].score=max(asmt[chosenID].score,score);
                            cout<<"Your current score:"<<asmt[chosenID].score<<endl;
                            if (score==100) {
                                cor++;
                                if (cor==1) cout<<"Achievement \"Success\" complete."<<endl;
                                else if (cor==10) cout<<"Achievement \"More!\" complete."<<endl;
                                else if (cor==100) cout<<"Achievement \"Unstoppable\" complete."<<endl;
                                else if (cor==1000) cout<<"Achievement \"Godlike!\" complete."<<endl;
                                if (sound) {
                                    if (selaud.size()>0) {
                                        ofstream songfname(db+"songbrd");
                                        songfname<<audio[selaud[rand()%selaud.size()]].fname;
                                        system(("open "+safespace(db+"acsound")).c_str());
                                    }
                                }
                            } else {
                                if (incor==1) cout<<"Achievement \"You can try again\" complete."<<endl;
                                else if (incor==10) cout<<"Achievement \"Get up!\" complete."<<endl;
                                else if (incor==100) cout<<"Achievement \"Keep going!\" complete."<<endl;
                                else if (incor==1000) cout<<"Achievement \"Nearly there!\" complete."<<endl;
                                incor++;
                            }
                            if (autosave) savedata();
                            cout<<"Press return to continue...";
                            cin.get();
                            inAppLaunch(db+"soundkill", "");
                        } else {
                            cout<<"Compilation error."<<endl;
                        }
                    } else {
                        cout<<"Code error!";
                    }
                } else if (hwsubans==to_string(delchc)) {
                    asmt.erase(asmt.begin()+chosenID);
                    remove((db+target).c_str());
                    if (sccode) remove((db+target+".cpp").c_str());
                    clc();
                    break;
                } else if (hwsubans==to_string(subscclc)&&sccode) {
                    system(("open -a Finder "+safespace(db+target+".cpp")).c_str());
                } else if (hwsubans==to_string(exitclc)) {
                    clc();
                    break;
                } else {
                    cout<<"Invalid response."<<endl;
                }
            }
        }
    }
}
