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
