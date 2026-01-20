import ssl
import time

from paho.mqtt import client as mqtt_client
from paho.mqtt.client import CallbackAPIVersion

broker = "3585e2dbfcd948449aec8ccf1eb8912d.s1.eu.hivemq.cloud"
port = 8883

# To authenticate and connect to the WebClient in HiveMQ please use the test client credentials generated for testing
# Input the username and password here, with your chosen client_id
client_id = ""
username = ""
password = ""
# If using the Web Client, make sure to subscribe to all messages or to both topics "python/mqtt" and "home/presence"

def connect_mqtt():
    def on_connect(client, userdata, flags, reason_code, properties):
        if reason_code != 0:
            print(f"Failed to connect, reason code {reason_code}")
    client = mqtt_client.Client(
        client_id=client_id,
        callback_api_version=CallbackAPIVersion.VERSION2
    )

    # Auth
    client.username_pw_set(username, password)

    # TLS (required for HiveMQ Cloud)
    client.tls_set(cert_reqs=ssl.CERT_REQUIRED)

    client.on_connect = on_connect
    client.connect(broker, port)
    return client

def publish(client):
    topics = ["python/mqtt", "home/presence"]
    for topic in topics:
        # work and university topic
        if topic == "python/mqtt":
            location_msgs = ["work", "university"]
            for location in location_msgs:
                result = client.publish(topic, location)
                status = result[0]
                if status == 0:
                    print(f"Sent `{location}` to `{topic}`")
                else:
                    print("Failed to send message")
                time.sleep(5)
        # home topic
        else:
            result = client.publish(topic, "home")
            status = result[0]
            if status == 0:
                print(f"Sent home to `{topic}`")
            else:
                print("Failed to send message")
        time.sleep(5)


def run():
    client = connect_mqtt()
    client.loop_start()
    time.sleep(10)
    publish(client)
    client.loop_stop()
    client.disconnect()


if __name__ == "__main__":
    run()
