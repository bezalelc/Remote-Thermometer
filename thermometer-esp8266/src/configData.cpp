#include <EEPROM.h>
#include "debugUtils.hpp"
#include "configData.hpp"

ConfigData::ConfigData()
{
    EEPROM.begin(sizeof(ConfigData));

    DEBUG_MODE_PRINT_NAMES_VALUES(sizeof(ConfigData));
    uint8_t *dataPtr = reinterpret_cast<uint8_t *>(this);

    for (uint16_t address = 0; address < sizeof(ConfigData); address++)
    {
        dataPtr[address] = EEPROM.read(address);
    }

    DEBUG_MODE_PRINT_NAMES_VALUES(wifiSSID, wifiPassword, apSSID, apPassword, userUser, userPassword);
}

ConfigData &ConfigData::getInstance()
{
    static ConfigData instance;
    return instance;
}

void ConfigData::updateConfig(CONFIG_DATA_TYPE dataType, const char *buff, uint8_t buffLen)
{
    uint8_t offset = BUFF_MAX_LEN * dataType;

    DEBUG_MODE_PRINT_NAMES_VALUES(dataType, offset, buff, buffLen - 1);

    char *ptr2Update = reinterpret_cast<char *>(this) + offset;
    memcpy(ptr2Update, buff, buffLen - 1);

    for (uint8_t address = 0; address < buffLen; address++, offset++)
    {
        EEPROM.write(offset, buff[address]);
    }
    EEPROM.commit();
}

const char &ConfigData::getUsername() const
{
    return *userUser;
}

const char &ConfigData::getUserPassword() const
{
    return *userPassword;
}