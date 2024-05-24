import serial
import requests
import time


serial_port = 'COM4' 
baud_rate = 115200


api_key = 'HJ507N4G1H4G3XMJ'  
url = f'https://api.thingspeak.com/update?api_key=HJ507N4G1H4G3XMJ'


ser = serial.Serial(serial_port, baud_rate, timeout=1)

try:
    while True:
        
        serial_data = ser.readline().decode().strip()
        print('Received data:', serial_data)

        
        humidity_index = serial_data.find('Humidity:')
        if humidity_index != -1:
            humidity_index += len('Humidity:')
            humidity_end_index = serial_data.find('%', humidity_index)
            humidity_str = serial_data[humidity_index:humidity_end_index].strip()

            temperature_index = serial_data.find('Temp:')
            temperature_index += len('Temp:')
            temperature_end_index = serial_data.find('°C', temperature_index)
            temperature_str = serial_data[temperature_index:temperature_end_index].strip()

            rain_index = serial_data.find('Rain:')
            rain_index += len('Rain:')
            rain_end_index = serial_data.find(',', rain_index)
            rain_str = serial_data[rain_index:rain_end_index].strip()

            soil_moisture_index = serial_data.find('Soil Moisture:')
            soil_moisture_index += len('Soil Moisture:')
            soil_moisture_str = serial_data[soil_moisture_index:].strip()

            try:
                humidity = int(humidity_str)
                temperature = int(temperature_str)
                rain = int(rain_str)
                soil_moisture = int(soil_moisture_str)

               
                payload = {'field1': humidity, 'field2': temperature, 'field3': rain, 'field4': soil_moisture}
                response = requests.post(url, data=payload)

                
                print('Response:', response.text)
            except ValueError:
                print('Invalid data format:', serial_data)
        
       
        time.sleep(10)

except KeyboardInterrupt:
    print('Keyboard Interrupt: Exiting...')
    ser.close()
