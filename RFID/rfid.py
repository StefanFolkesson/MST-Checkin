import serial
import json
import urllib2
import time

rfid = serial.Serial("/dev/ttyAMA0")
rfid.baudrate = 9600

api_call = urllib2.Request('http://10.130.216.106/api_debug.php')
api_call.add_header('Content-Type', 'application/json')


while True:
	api_call_data = {
		"timestamp":time.time(),
		"rfid":rfid.read(14),
		"type":"verkstad"
	}
	api_response = urllib2.urlopen(api_call, json.dumps(api_call_data))
	print api_response.read()