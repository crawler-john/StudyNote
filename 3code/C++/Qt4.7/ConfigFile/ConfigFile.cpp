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
/*  2011-06-07 * Ricky Gong      * Creation of the file                      */
/*  2011-06-09 * Ricky Gong      * Implemented the xml text for xml stored in*/
/*             *                 *  memory                                   */
/*  2013-02-25 * Ricky Gong      * Modified the code to parse configurations */
/*             *                 * according to the file name                */
/*             *                 *                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Include Files                                                            */
/*                                                                           */
/*****************************************************************************/
#include <QtXml>
//#include "GlobalDef.hpp"
#include "ConfigFile.hpp"

using namespace std;


/*****************************************************************************/
/*                                                                           */
/*  Definitions                                                              */
/*                                                                           */
/*****************************************************************************/
#define CONFIGURATION_FOLDER_PATH    "./Config/"

#if defined(TRACE_CONFIG_FILE)
#define LOG_FATAL MSG_FATAL
#define LOG_ERROR MSG_ERROR
#define LOG_HIGH MSG_HIGH
#define LOG_MED MSG_MED
#define LOG_LOW MSG_LOW
#else
#define LOG_FATAL(...)
#define LOG_ERROR(...)
#define LOG_HIGH(...)
#define LOG_MED(...)
#define LOG_LOW(...)
#endif


/*****************************************************************************/
/*                                                                           */
/*  Variable Declarations                                                    */
/*                                                                           */
/*****************************************************************************/
CConfigFile *pConfigFile = NULL;


/*****************************************************************************/
/*                                                                           */
/*  Function Declarations                                                    */
/*                                                                           */
/*****************************************************************************/


/*****************************************************************************/
/*                                                                           */
/*  Function Implementations                                                 */
/*                                                                           */
/*****************************************************************************/
/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Constructor                                                             */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
CConfigFile::CConfigFile(QString configFileName)
    : configFile(CONFIGURATION_FOLDER_PATH+configFileName),
      preader(NULL),
      xmlstr("")
{
    // prepare the xml string for parsing, remove comments and unuseful spaces
    QFile file(configFile);
    // prepare to read all text into a string
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        LOG_FATAL("Can't open %s file", qPrintable(configFile));
        return;
    }
    QTextStream in(&file);
    // loop until end of the file
    while(!in.atEnd()) {
        // read a line out
        QString line = in.readLine();
        if(line.isEmpty()) {
            continue;
        }
        // comprise comments in multi-lines with spaces before and after
        if((line.count(QRegExp("\\s*<!--")) > 0) 
            && (line.count(QRegExp("-->\\s*")) == 0)) {
            // read the next lines to comprise a comment in a single line
            do {
                line += in.readLine();
            } while(line.count(QRegExp("-->\\s*")) == 0);
        }
        // remove space characters at the beginning of the string
        line.remove(QRegExp("^\\s+"));
        // remove comments and also remove spaces before and after
        line.remove(QRegExp("\\s*<!--.*-->\\s*"));
        // remove space characters at the end of the string
        line.remove(QRegExp("\\s+$"));
        if(line.isEmpty()) {
            continue;
        }
        // append to the string
        xmlstr += line;
    }
    // close file
    file.close();
    // report error
    if (file.error() != QFile::NoError) {
        LOG_FATAL("Cannot read file %s: %s", qPrintable(configFile), 
                  qPrintable(file.errorString()));
        return;
    }
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Destructor                                                              */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
CConfigFile::~CConfigFile()
{
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Get the value of a parameter in a module                                */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   module[in]:            module name of the parameter                     */
/*   name[in]:              name of the parameter                            */
/*   rIntValue[out]:        parameter output position                        */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   Result of the operation                                                 */
/*       true - operation OK                                                 */
/*       false - operation failure                                           */
/*                                                                           */
/*****************************************************************************/
bool CConfigFile::getItemParam(const QString &module, 
                               const QString &name, 
                               int &rIntValue)
{
    preader = new QXmlStreamReader(xmlstr);
    if(preader)
    {
        // read file to find the module parameter item
        if(toParamPosition(module, name)) {
            // read the item value if found
            readItemElement(rIntValue);
            return true;
        }
        delete preader;
        preader = NULL;
    }

    return false;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Get the value of a parameter in a module                                */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   module[in]:            module name of the parameter                     */
/*   name[in]:              name of the parameter                            */
/*   rUIntValue[out]:       parameter output position                        */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   Result of the operation                                                 */
/*       true - operation OK                                                 */
/*       false - operation failure                                           */
/*                                                                           */
/*****************************************************************************/
bool CConfigFile::getItemParam(const QString &module,  
                               const QString &name, 
                               uint &rUIntValue)
{
    preader = new QXmlStreamReader(xmlstr);
    if(preader)
    {
        // read file to find the module parameter item
        if(toParamPosition(module, name)) {
            // read the item value if found
            readItemElement(rUIntValue);
            return true;
        }
        delete preader;
        preader = NULL;
    }

    return false;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Get the value of a parameter in a module                                */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   module[in]:            module name of the parameter                     */
/*   name[in]:              name of the parameter                            */
/*   rLongValue[out]:       parameter output position                        */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   Result of the operation                                                 */
/*       true - operation OK                                                 */
/*       false - operation failure                                           */
/*                                                                           */
/*****************************************************************************/
bool CConfigFile::getItemParam(const QString &module, 
                               const QString &name, 
                               long &rLongValue)
{
    preader = new QXmlStreamReader(xmlstr);
    if(preader)
    {
        // read file to find the module parameter item
        if(toParamPosition(module, name)) {
            // read the item value if found
            readItemElement(rLongValue);
            return true;
        }
        delete preader;
        preader = NULL;
    }

    return false;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Get the value of a parameter in a module                                */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   module[in]:            module name of the parameter                     */
/*   name[in]:              name of the parameter                            */
/*   rULongValue[out]:      parameter output position                        */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   Result of the operation                                                 */
/*       true - operation OK                                                 */
/*       false - operation failure                                           */
/*                                                                           */
/*****************************************************************************/
bool CConfigFile::getItemParam(const QString &module,  
                               const QString &name, 
                               ulong &rULongValue)
{
    preader = new QXmlStreamReader(xmlstr);
    if(preader)
    {
        // read file to find the module parameter item
        if(toParamPosition(module, name)) {
            // read the item value if found
            readItemElement(rULongValue);
            return true;
        }
        delete preader;
        preader = NULL;
    }

    return false;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Get the value of a parameter in a module                                */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   module[in]:            module name of the parameter                     */
/*   name[in]:              name of the parameter                            */
/*   rBoolValue[out]:       parameter output position                        */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   Result of the operation                                                 */
/*       true - operation OK                                                 */
/*       false - operation failure                                           */
/*                                                                           */
/*****************************************************************************/
bool CConfigFile::getItemParam(const QString &module, 
                               const QString &name, 
                               bool &rBoolValue)
{
    preader = new QXmlStreamReader(xmlstr);
    if(preader)
    {
        // read file to find the module parameter item
        if(toParamPosition(module, name)) {
            // read the item value if found
            readItemElement(rBoolValue);
            return true;
        }
        delete preader;
        preader = NULL;
    }

    return false;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Get the value of a parameter in a module                                */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   module[in]:            module name of the parameter                     */
/*   name[in]:              name of the parameter                            */
/*   rStrValue[out]:        parameter output position                        */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   Result of the operation                                                 */
/*       true - operation OK                                                 */
/*       false - operation failure                                           */
/*                                                                           */
/*****************************************************************************/
bool CConfigFile::getItemParam(const QString &module, 
                               const QString &name, 
                               QString &rStrValue)
{
    preader = new QXmlStreamReader(xmlstr);
    if(preader)
    {
        // read file to find the module parameter item
        if(toParamPosition(module, name)) {
            // read the item value if found
            readItemElement(rStrValue);
            return true;
        }
        delete preader;
        preader = NULL;
    }

    return false;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Make the xml stream reader parse to the position of the parameter       */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   module[in]:            module name of the parameter                     */
/*   name[in]:              name of the parameter                            */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   Result of the operation                                                 */
/*       true - operation OK                                                 */
/*       false - operation failure                                           */
/*                                                                           */
/*****************************************************************************/
bool CConfigFile::toParamPosition(const QString &module, 
                                  const QString &name)
{
    if(!preader) {
        return false;
    }

    bool bRet = false;

    // go to the head
    preader->readNext();
    // loop until end of the file
    while (!preader->atEnd()) {
        // check for start element
        if (preader->isStartElement()) {
            // check for config line
            if (preader->name() == "config") {
                // found config line
                bRet = readConfigElement(module, name);
                break;
            } else {
                // raise error
                preader->raiseError(QObject::tr("Not a configuration file"));
            }
        } else {
            preader->readNext();
        }
    }

    // report error if error exists
    if (preader->hasError()) {
        LOG_FATAL("Failed to parse file %s: %s", qPrintable(configFile), 
                  qPrintable(preader->errorString()));
    }

    return bRet;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Make the xml stream reader to find the position of the module           */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   module[in]:            module name of the parameter                     */
/*   name[in]:              name of the parameter                            */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   Result of the operation                                                 */
/*       true - operation OK                                                 */
/*       false - operation failure                                           */
/*                                                                           */
/*****************************************************************************/
bool CConfigFile::readConfigElement(const QString &module, 
                                    const QString &name)
{
    if(!preader) {
        return false;
    }

    bool bRet = false;
    preader->readNext();
    while (!preader->atEnd()) {
        if (preader->isEndElement()) {
            preader->readNext();
            break;
        }

        if (preader->isStartElement()) {
            // check for "module" element
            if (preader->name() == "module") {
                // check for module element with the same "name"
                if(preader->attributes().value("name").toString() == module) {
                    // found module line
                    bRet = readModuleElement(name);
                    break;
                }
                else {
                    // skip the current element if "name" is not equal
                    skipUnknownElement();
                }
            } else {
                skipUnknownElement();
            }
        } else {
            preader->readNext();
        }
    }
    return bRet;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Make the xml stream reader to find the position of the parameter        */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   module[in]:            module name of the parameter                     */
/*   name[in]:              name of the parameter                            */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   Result of the operation                                                 */
/*       true - operation OK                                                 */
/*       false - operation failure                                           */
/*                                                                           */
/*****************************************************************************/
bool CConfigFile::readModuleElement(const QString &name)
{
    if(!preader) {
        return false;
    }

    bool bRet = false;
    preader->readNext();
    while (!preader->atEnd()) {
        if (preader->isEndElement()) {
            preader->readNext();
            break;
        }

        if (preader->isStartElement()) {
            // check for "item" element
            if(preader->name() == "item") {
                // check for module element with the same "name"
                if(preader->attributes().value("name").toString() == name) {
                    // found item line
                    bRet = true;
                    break;
                }
                else {
                    // skip the current element if "name" is not equal
                    skipUnknownElement();
                }
            } else {
                skipUnknownElement();
            }
        } else {
            preader->readNext();
        }
    }
    return bRet;
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Read the parameter out from the xml element                             */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   rIntValue[out]:        parameter output position                        */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CConfigFile::readItemElement(int& rIntValue)
{
    if(!preader) {
        return;
    }

    QString item = preader->readElementText();
    bool OK;
    // base is 0, the C language convention is used: If the string begins with 
    // "0x", base 16 is used; if the string begins with "0", base 8 is used; 
    // otherwise, base 10 is used
    rIntValue = item.toInt(&OK, 0);
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Read the parameter out from the xml element                             */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   rUIntValue[out]:       parameter output position                        */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CConfigFile::readItemElement(uint& rUIntValue)
{
    if(!preader) {
        return;
    }

    QString item = preader->readElementText();
    bool OK;
    // base is 0, the C language convention is used: If the string begins with 
    // "0x", base 16 is used; if the string begins with "0", base 8 is used; 
    // otherwise, base 10 is used
    rUIntValue = item.toUInt(&OK, 0);
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Read the parameter out from the xml element                             */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   rLongValue[out]:       parameter output position                        */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CConfigFile::readItemElement(long& rLongValue)
{
    if(!preader) {
        return;
    }

    QString item = preader->readElementText();
    bool OK;
    // base is 0, the C language convention is used: If the string begins with 
    // "0x", base 16 is used; if the string begins with "0", base 8 is used; 
    // otherwise, base 10 is used
    rLongValue = item.toLong(&OK, 0);
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Read the parameter out from the xml element                             */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   rULongValue[out]:      parameter output position                        */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CConfigFile::readItemElement(ulong& rULongValue)
{
    if(!preader) {
        return;
    }

    QString item = preader->readElementText();
    bool OK;
    // base is 0, the C language convention is used: If the string begins with 
    // "0x", base 16 is used; if the string begins with "0", base 8 is used; 
    // otherwise, base 10 is used
    rULongValue = item.toULong(&OK, 0);
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Read the parameter out from the xml element                             */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   rBoolValue[out]:       parameter output position                        */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CConfigFile::readItemElement(bool& rBoolValue)
{
    if(!preader) {
        return;
    }

    QString item = preader->readElementText();
    if(item.toLower() == "true") {
        rBoolValue = true;
    } else {
        rBoolValue = false;
    }
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Read the parameter out from the xml element                             */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   rStrValue[out]:       parameter output position                         */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CConfigFile::readItemElement(QString &rStrValue)
{
    if(!preader) {
        return;
    }

    rStrValue = preader->readElementText();
}

/*****************************************************************************/
/* Function Description:                                                     */
/*****************************************************************************/
/*   Skip the unknown xml element                                            */
/*                                                                           */
/*****************************************************************************/
/* Parameters:                                                               */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
/* Return Values:                                                            */
/*****************************************************************************/
/*   none                                                                    */
/*                                                                           */
/*****************************************************************************/
void CConfigFile::skipUnknownElement()
{
    if(!preader) {
        return;
    }

    preader->readNext();
    while (!preader->atEnd()) {
        if (preader->isEndElement()) {
            preader->readNext();
            break;
        }

        if (preader->isStartElement()) {
            skipUnknownElement();
        } else {
            preader->readNext();
        }
    }
}

