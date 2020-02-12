# reach-tio-agent
Reach Translation IO Agent
Reach Serial IO Agent Serial to QML Communication In order for your microcontroller to communicate with the QML Viewer
(a tool for loading QML documents that makes it easy to quickly develop and debug QML applications) 
messages being sent need to be translated. 
We have created a set of tools called the Serial Input/Output Agent (SIO) and 
Translator Input Ouput Agent (TIO) agents to make this translation happen.

# TIO Agent

TIO Agent stands for Translator Input Output Agent. 
Messages sent from the Controller Board and received by the QML GUI should not necessarily be the same, 
since that would violate a separation of concerns.
Messages are translated using Reach’s TIO Agent. The TIO Agent uses a file called translate.txt, 
which provides a list of translations. T
he file is typically included in the same folder as the QML application.

# Translate.txt File Example

A simple temperature control module has a number with a Celsius temperature, 
a number with a Fahrenheit temperature, and two buttons to raise and lower the temperature. 
It is connected to a controller board with a heater and a thermometer. 
When the thermometer detects a temperature change, 
it sends the new temperature to the UI for display. 
When the user presses the “Raise Temperature” or “Lower Temperature”, 
the UI sends a message to raise or lower the temperature by a specified amount.
For such a temperature control panel, the translate.txt file would look like this:

 M:celsius_temperature_from_thermometer=%s,T:celsius_display.text=%s
 
  M:fahrenheit_temperature_from_thermometer=%s,T:fahrenheit_display.text=%s
  
  G:raiseTempTo=%s,T:setTemperature=%s
  
  G:lowerTempTo=%s,T:setTemperature=%s
  
The %s represents the string which will be kept the same during the translation process.
M: Represents messages sent from the controller module. 
G: Represents messages sent from the GUI, in this case the QML Viewer. 
T: Represents the translation of the previous statement. 
Each entry must begin with either an M: or G: with a following statement.
Then there must be a comma and a T: indicating what the text will be translated to.

 M:message_from_controller_board=%s,T:QML_object_name_on_GUI.property=%s
 
  G:message_from_GUI=%s,T:value_to_send_controller_board=%s
  
# Technical Details

The TIO Agent runs in the background and accepts inputs from the SIO Agent. 
The translation table is typically stored with the the application at /application/src/translate.txt. 
The TIO Agent is installed to /application/bin/tio-agent on the root file system. 
The TIO Agent is started by the init system which executes the /etc/init.d/tio-agent script on start up.

The TIO Agent excepts the following command-line options:

-d or –daemon – Runs the tio-agent in the background.

-f or –file= – Uses for translations.

-o or –logfile= – Logs to file instead of standard error.

-r or –refresh= – Auto-refreshs translation file.

-s[]or –sio-port[=] – Uses TCP socket. Default is 7880.

-t[]or –tio-port[=] -Uses TCP socket. Default is 7885.

-v or –verbose – Prints debug messages.

-h or -? | –help – Prints usage information.

# Sending Messages to your Microcontroller

When you need to send messages from your QML application back to your microcontroller,
you can use the connection plug-in (specifically, the connection.sendMessage method), 
as described at QML Viewer Plugins.
