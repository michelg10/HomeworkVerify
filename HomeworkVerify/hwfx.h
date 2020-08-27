#ifndef hwfx_h
#define hwfx_h
#include "aes.h"
#include "common_func.h"
#include <map>
struct hw {
    string id;
    ll score;
    string name;
    string date;
};
bool writeCore(string &fname,string &dtplyd, unsigned char * const aesKey,vector<string>errorlog) {
    ll newLen=dtplyd.size();
    newLen=ceil(newLen/16.0)*16;
    unsigned char* newMsg=new(nothrow) unsigned char[newLen];
    if (!newMsg) {
        errorlog.push_back("Memalloc error for length "+to_string(newLen));
        return 1;
    }
    ofstream miniF(fname,ios::binary);
    if (miniF.good()) {
        miniF<<"HwfxContents::START"<<endl<<"HwfxContents::FVERS"<<endl<<"2"<<endl<<"HwfxContents::PKGCNT"<<endl<<"1"<<endl<<"HwfxContents::DATASIZE"<<endl<<dtplyd.size()<<endl<<"HwfxContents::IVCNT"<<endl;
        ll blks=newLen/16;
        ll const mltCorem=min(8ll,blks);
        miniF<<mltCorem<<endl;
        vector<unsigned char*>iv;
        for (ll i=0;i<mltCorem;i++) {
            unsigned char* genIvTmp=new unsigned char[16];
            for (ll j=0;j<16;j++) {
                genIvTmp[j]=rand()%256;
            }
            iv.push_back(genIvTmp);
        }
        for (ll i=0;i<iv.size();i++) {
            miniF<<"HwfxContents::IV"+to_string(i)<<endl;
            for (ll j=0;j<16;j++) miniF<<(int)iv[i][j]<<endl;
        }
        miniF<<"HwfxContents::PAYLOAD"<<endl;
        for (ll i=0;i<dtplyd.size();i++) newMsg[i]=dtplyd[i];
        for (ll i=dtplyd.size();i<newLen;i++) newMsg[i]=0;
        dtplyd="";
        aes_encrypt(newMsg, newLen, aesKey, 32, iv);
        for (ll i=0;i<newLen;i++) miniF<<newMsg[i];
        delete[] newMsg;
        for (ll i=0;i<mltCorem;i++) delete[] iv[i];
    } else {
        delete[] newMsg;
        errorlog.push_back("ERR_OPEN_WRITECORE ("+fname+")");
        return 1;
    }
    miniF.close();
    return 0;
}
bool readHwfxCore(vector<string>&reLd,string pkgpth,bool &vq, bool debugMd,unsigned char* const aesKey,vector<string> &errorlog) {
    //undo encryption, encrypt again, then throw it into .hwfx files. It has the exact same header format.
    chrono::steady_clock::time_point grs=chrono::steady_clock::now();
    ifstream importHwfx(pkgpth,ios::binary);
    vector<string>fHeader;
    while (true) {
        if (importHwfx.eof()) return 0;
        string impTmp;
        getline(importHwfx,impTmp);
        if (impTmp=="HwfxContents::PAYLOAD") break;
        else fHeader.push_back(impTmp);
    }
    ll curPos=importHwfx.tellg();
    importHwfx.seekg(0,ios::end);
    ll disLen=(ll)importHwfx.tellg()-curPos;
    ll newLen=ceil(disLen/16.0)*16;
    unsigned char* decPkg=new(nothrow) unsigned char[newLen];
    if (!decPkg) {
        errorlog.push_back("Memalloc error for length "+to_string(newLen));
        return 0;
    }
    importHwfx.close();
    FILE *impE = fopen(pkgpth.c_str(),"rb");
    fseek(impE,curPos,SEEK_SET);
    fread(decPkg,1,disLen,impE);
    fclose(impE);
    for (ll i=disLen;i<newLen;i++) decPkg[i]=0;
                    
    vector<unsigned char *>iv;
    bool gotIv=false,gotFvers=false,gotDtsz=false,gotCnt=false;
    string fvers="";
    ll dtsz=0,ascnt=1,ivcnt=1;
    map<ll,ll>ivCntPlc;
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
        } else if (fHeader[i]=="HwfxContents::IVCNT") {
            if (i+1!=fHeader.size()) {
                ivcnt=atoll(fHeader[++i].c_str());
                gotIv=true;
            }
        } else if (fHeader[i]=="HwfxContents::PKGCNT") {
            if (i+1!=fHeader.size()) {
                ascnt=atoll(fHeader[++i].c_str());
                gotCnt=true;
            }
        } else if (fHeader[i].size()>=16) {
            if (fHeader[i].substr(0,16)=="HwfxContents::IV") {
                ll ivNum=atoll(fHeader[i].substr(16).c_str());
                if (ivCntPlc.find(ivNum)==ivCntPlc.end()) {
                    ivCntPlc[ivNum]=i;
                } else {
                    errorlog.push_back("IVCNT_DUP");
                }
            }
        }
    }
    if (ivCntPlc.begin()->first==0&&(--ivCntPlc.end())->first==ivCntPlc.size()-1) {
        for (ll i=0;i<ivCntPlc.size();i++) {
            ll startMkr=ivCntPlc[i]+1;
            unsigned char *tmpIv=new(nothrow) unsigned char[16];
            if (!tmpIv) {
                errorlog.push_back("Memalloc error for length 16");
                return 1;
            }
            for (ll j=startMkr;j<startMkr+16;j++) {
                if (j<fHeader.size()) {
                    if (atoll(fHeader[j].c_str())>=256||atoll(fHeader[j].c_str())<0) {
                        errorlog.push_back("IV_VALUEOUTOFBOUNDS");
                        delete[] tmpIv;
                        break;
                    }
                    tmpIv[j-startMkr]=atoll(fHeader[j].c_str());
                } else {
                    errorlog.push_back("EXPECTED_IV_GOT_EOF");
                    delete[] tmpIv;
                    break;
                }
            }
            if (errorlog.size()) break;
            iv.push_back(tmpIv);
        }
    } else {
        errorlog.push_back("IV_MISSINGIV");
    }
    if (to_string(atoll(fvers.c_str()))!=fvers) errorlog.push_back("FVERS_NaN");
    if (!gotIv) errorlog.push_back("IV_GONE");
    if (!gotFvers) errorlog.push_back("FVERS_GONE");
    if (!gotDtsz) errorlog.push_back("FSIZE_GONE");
    if (!gotCnt) errorlog.push_back("PROBCNT_MISSING");
    if (disLen<dtsz) errorlog.push_back("FSIZE_LDTSZ");
    if (iv.size()*16>newLen) errorlog.push_back("FSIZE_MIVSZ");
    if (errorlog.size()) {
        for (ll i=0;i<iv.size();i++){
            delete[] iv[i];
        }
        delete[] decPkg;
        return 0;
    }
    if (debugMd) {
        cout<<"Pre-parsing done in "<<chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - grs).count()<<"ms"<<endl;
        grs=chrono::steady_clock::now();
    }
    aes_decrypt(decPkg, newLen, aesKey, 32, iv);
    
    for (ll i=0;i<iv.size();i++) delete[] iv[i];
    if (debugMd) {
        cout<<"Decryption done in "<<chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - grs).count()<<"ms"<<endl;
    }
    string ft="";
    for (ll i=0;i<dtsz;i++) {
        if (decPkg[i]=='\n') {
            reLd.push_back(ft);
            ft="";
        } else ft+=decPkg[i];
    }
    if (ft.size()) reLd.push_back(ft);
    if (ascnt==1) vq=true;
    delete[] decPkg;
    return 1;
}
bool readHwfx(string &pkgpth,bool &vq,string &target,ll &chosenID, ll &debugMd, unsigned char * aesKey,map<ll,char>&randname,string &db,vector<hw>&asmt,vector<string> &errorlog) {
    vector<string>reLd;
    readHwfxCore(reLd,pkgpth,vq,debugMd,aesKey,errorlog);
    ll parsel=0;
    ll times=0;
    vq=true;
    while (true) {
        if (parsel>=reLd.size()) break;
        times++;
        if (times>=2) vq=false;
        ll parserr=reLd.size();
        for (ll i=parsel+1;i<reLd.size();i++) {
            if (reLd[i]=="HwfxContents::Payload") {
                parserr=i;
                break;
            }
        }
        string dtplyd;
        string nm="";
        for (ll i=parsel;i<parserr;i++) dtplyd+=reLd[i]+'\n';
        for (ll i=parsel;i<parserr;i++) {
            if (reLd[i]=="HwfxContents::Title"&&i+1<parserr) nm=nm+reLd[i+1];
        }
        ll cachel=-1,cacher=-1;
        for (ll i=parsel;i<parserr;i++) {
            if (reLd[i]=="HwfxContents::StartCache") cachel=i;
            else if (reLd[i]=="HwfxContents::EndCache") cacher=i;
        }
        parsel=parserr+1;
        if (cachel+1>cacher-1) {
            errorlog.push_back("CCHEERR ("+to_string(cachel)+", "+to_string(cacher)+")");
            continue;
        }
        string newname="";
        while (true) {
            newname="";
            for (ll i=0;i<16;i++) newname+=randname[rand()%36];
            ifstream testDup(db+newname);
            if (!testDup.good()) {
                testDup.close();
                break;
            }
            testDup.close();
        }
        if (cachel!=-1&&cacher!=-1) {
            ofstream outputCache(db+"cache"+newname);
            if (outputCache.good()) {
                outputCache<<reLd[cachel+1];
                for (ll i=cachel+2;i<=cacher-1;i++) {
                    outputCache<<endl<<reLd[i];
                }
                outputCache.close();
            } else errorlog.push_back("ERR_OPEN_CACHE ("+db+"cache"+newname+")");
        }
        
        string lvconv=db+newname;
        if (!errorlog.size()) {
            writeCore(lvconv,dtplyd,aesKey,errorlog);
            //All it needs to do:push to asmt, set target, vq, and chosenID
            asmt.push_back({newname,0,nm,date()});
            //ID SCORE NAME DATE
            target = newname;
            chosenID=asmt.size()-1;
        }
    }
    if (times==0) vq=false; // no file read, do not attempt to opem
    return 1;
}

#endif /* hwfx_h */
