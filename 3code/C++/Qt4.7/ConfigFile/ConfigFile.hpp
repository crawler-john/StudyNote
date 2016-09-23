#ifndef _CONFIGFILE_HPP_
#define _CONFIGFILE_HPP_
/*****************************************************************************/
/*                                                                           */
/*    Copyright (C) - LEGATE Intelligent Equipment - All rights reserved     */
/*                                                                           */
/*****************************************************************************/
/*                                                                           */
/*  Except if expressly provided in a dedicated License Agreement, you are   */
/*  not authorized to:                                                       */
/*                                                                           */
/*  1. Use, copy, modify or transfer this software component, module or      */
/*  product, including any accompanying electronic or paper documentation    */
/*  (together, the "Software").                                              */
/*                                                                           */
/*  2. Remove any product identification, copyright, proprietary notices or  */
/*  labels from the Software.                                                */
/*                                                                           */
/*  3. Modify, reverse engineer, decompile, disassemble or otherwise attempt */
/*  to reconstruct or discover the source code, or any parts of it, from the */
/*  binaries of the Software.                                                */
/*                                                                           */
/*  4. Create derivative works based on the Software (e.g. incorporating the */
/*  Software in another software or commercial product or service without a  */
/*  proper license).                                                         */
/*                                                                           */
/*  By installing or using the "Software", you confirm your acceptance of the*/
/*  hereabove terms and conditions.                                          */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*  History:                                                                 */
/*****************************************************************************/
/*  Date       * Author          * Changes                                   */
/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Include Files                                                            */
/*                                                                           */
/*****************************************************************************/
#include <QString>
#include <QXmlStreamReader>

/*****************************************************************************/
/*                                                                           */
/*  Definitions                                                              */
/*                                                                           */
/*****************************************************************************/
#define CONFIGFILE_FULLNAME     "config.xml"

#define GETITEMPARAM(key, name, rvalue) \
        (((pConfigFile != NULL) \
        && (pConfigFile->getItemParam(key, name, rvalue))) ? true : false)


/*****************************************************************************/
/* Class Description:                                                        */
/*****************************************************************************/
/*   Class packed configuration file process functions                       */
/*                                                                           */
/* CAUTION!!!:                                                               */
/*   Only one single instance of this class is allowed to exist              */
/*                                                                           */
/*****************************************************************************/
class CConfigFile
{
    public:

        /*********************************************************************/
        /*                     Constructor & Destructor                      */
        /*********************************************************************/
        CConfigFile(QString configFileName = CONFIGFILE_FULLNAME);
        ~CConfigFile();


        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        bool getItemParam(const QString &module,  
                          const QString &name, 
                          int &rIntValue);
        bool getItemParam(const QString &module,  
                          const QString &name, 
                          uint &rUIntValue);
        bool getItemParam(const QString &module,  
                          const QString &name, 
                          long &rLongValue);
        bool getItemParam(const QString &module,  
                          const QString &name, 
                          ulong &rULongValue);
        bool getItemParam(const QString &module, 
                          const QString &name, 
                          bool &rBoolValue);
        bool getItemParam(const QString &module, 
                          const QString &name, 
                          QString &rStrValue);


    private:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/
        QString configFile;
        QXmlStreamReader *preader;  // pointer to xml reader
        QString xmlstr;             // string to stored xml text in memory


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/
        bool toParamPosition(const QString &module, 
                             const QString &name);
        bool readConfigElement(const QString &module, 
                               const QString &name);
        bool readModuleElement(const QString &name);
        void readItemElement(int& rIntValue);
        void readItemElement(uint& rUIntValue);
        void readItemElement(long& rLongValue);
        void readItemElement(ulong& rULongValue);
        void readItemElement(bool& rBoolValue);
        void readItemElement(QString &rStrValue);
        void skipUnknownElement();


    protected:

        /*********************************************************************/
        /*                            Variables                              */
        /*********************************************************************/


        /*********************************************************************/
        /*                            Functions                              */
        /*********************************************************************/


};


/*****************************************************************************/
/*                                                                           */
/*  Variable Declarations                                                    */
/*                                                                           */
/*****************************************************************************/
extern CConfigFile *pConfigFile;


/*****************************************************************************/
/*                                                                           */
/*  Function Declarations                                                    */
/*                                                                           */
/*****************************************************************************/


#endif //_CONFIGFILE_HPP_

