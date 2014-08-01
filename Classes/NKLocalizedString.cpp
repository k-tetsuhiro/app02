//
//  NKLocalizedString.cpp
//  app02
//
//  Created by k_tetsuhiro on 2014/08/01.
//
//

#include "NKLocalizedString.h"

USING_NS_CC;

const char* NKLocalizedString::LocalizedString(const char* searchKey, const char* comment)
{
    using namespace std;
    const char* ret = comment;
    
    static map<string, string> localizable;
    if(localizable.empty()){
        // 言語ディレクトリを検索対象にする
        CCFileUtils* fileUtils = CCFileUtils::sharedFileUtils();
        ccLanguageType lang = CCApplication::sharedApplication()->getCurrentLanguage();
        
        //英語と日本語以外の言語に対応できないため変更
        //        if (lang == kLanguageEnglish)
        //        {
        //            fileUtils->addSearchPath("en.lproj");
        //        }
        //        else if (lang == kLanguageJapanese)
        //        {
        //            fileUtils->addSearchPath("ja.lproj");
        //        }
        
        if (lang == kLanguageJapanese)
        {
            fileUtils->addSearchPath("ja.lproj");
        }else
        {
            fileUtils->addSearchPath("en.lproj");
        }
        
        // 言語ファイルを開く
        unsigned long size;
        string fullpath = fileUtils->fullPathForFilename("Localizable.strings");
        unsigned char* data = fileUtils->getFileData(fullpath.c_str(), "rb", &size);
        if (data == NULL)
        {
            return ret;
        }
        
        
        // Localizable.string のパース
        istringstream is((char*)data);
        delete [] data;
        string line;
        while (std::getline(is, line))
        {
            string::size_type sep = line.find('=');
            if (sep != string::npos)
            {
                string key = line.substr(0,sep-1);
                string val = line.substr(sep+1);
                // スペース、セミコロンなどをトリミングする
                key.erase(0, key.find_first_not_of(" \""));
                key.erase(key.find_last_not_of(" \"")+1);
                val.erase(0, val.find_first_not_of(" \""));
                val.erase(val.find_last_not_of(" \";")+1);
                // \nを改行コードに
                do {
                    sep = val.find("\\n");
                    if (sep != string::npos) {
                        val.replace(sep, 2, "\n");
                    }
                    else {
                        break;
                    }
                }
                while (true);
                
                localizable.insert(pair<string, string>(key,val));
            }
        }
    }
    // キー値の検索
    map<string,string>::iterator ite = localizable.find(searchKey);
    if (ite != localizable.end())
    {
        ret = CCString::create((ite->second).c_str())->getCString();
    }
    return ret;
}