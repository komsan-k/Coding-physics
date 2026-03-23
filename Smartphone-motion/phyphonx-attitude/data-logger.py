import requests
import time
import csv

# Replace with your phone's IP and Port
# Common for Android is :8080, iOS usually uses :80 or nothing
IP_ADDRESS = "172.19.177.163:8080" 
URL = f"http://{IP_ADDRESS}/get?yaw&pitch&roll"

def fetch_data():
    try:
        response = requests.get(URL, timeout=1)
        if response.status_code == 200:
            data = response.json()
            
            # Extracting the first value from the buffer
            yaw = data['buffer']['yaw']['buffer'][0]
            pitch = data['buffer']['pitch']['buffer'][0]
            roll = data['buffer']['roll']['buffer'][0]
            
            return yaw, pitch, roll
    except Exception as e:
        print(f"Connection Error: {e}")
        return None

# Setup CSV file
with open('phyphox_data.csv', mode='w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(["Timestamp", "Yaw", "Pitch", "Roll"])

    print(f"Logging started... Press Ctrl+C to stop.")
    
    try:
        while True:
            result = fetch_data()
            if result:
                y, p, r = result
                timestamp = time.time()
                print(f"Yaw: {y:7.2f} | Pitch: {p:7.2f} | Roll: {r:7.2f}")
                writer.writerow([timestamp, y, p, r])
            
            time.sleep(0.1)  # 10Hz sampling rate
    except KeyboardInterrupt:
        print("\nLogging stopped. Data saved to phyphox_data.csv")
