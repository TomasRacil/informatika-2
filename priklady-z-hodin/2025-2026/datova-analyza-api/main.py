import requests

response = requests.get("https://api.binance.com/api/v3/ticker/24hr")

print(response)