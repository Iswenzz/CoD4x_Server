## extraFunctions plugin
This plugins adds some simple extra functions into codx server.

To install put extraFunctions.dll (for windows) or extraFunctions.so (for linux) into a plugins folder in your Call of Duty 4 root folder.

To load plugin add this line to your servers start script

    +loadplugin extraFunctions

## Download
[Linux Binaries](https://www.dropbox.com/s/0627mvtfwfm6pvk/extraFunctions.so?dl=0)

[Windows Binaries](https://www.dropbox.com/s/otnsithi5fjynnm/extraFunctions.dll?dl=0)


## List of Functions


### isStringInt(< string >)
Check if a string is an integer value.


    if(isStringInt("34"))
        return true;

### stringToFloat(< string >)
Returns a float value from a string.

    x = stringToFloat("4.23");

### colourRGB(<int 0-255>, <int 0-255>, <int 0-255>)

Returns a colour vector from RGB colour values 0 - 255.

    hud.color = colourRGB(232,21,44);

### colourHEX(< string >)
Returns a colour vector from HEX colour string
(only supports 6 digit hex colours).

    self.scoreHud.color = colourHEX("#0D9999");

### scaleVector(< vector >, < float >)
Returns a vector scaled by a float value.

    vec1 = scaleVector((32,43,12), 30);

### mutePlayerChat(< player >, <int 0 - 1>)
Mutes a player from typing in chat. Set to 0 to unmute and 1 to mute. Player will stay muted until they leave the server.

    mutePlayerChat(self, 1);

### isPlayerChatMuted(< player >)
Returns 0 if player is not muted and 1 if player is muted.

    if(isPlayerChatMuted(self))
        return true;

### toUpper(< string >)
Returns the string in capitals

    toUpper("Hello World);
