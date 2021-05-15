#Random simple python script used to test the binance api.
import requests, json
dogePrice = requests.get("http://api.binance.com/api/v3/ticker/price", params={"symbol":"DOGEGBP"})
print(dogePrice.json()["price"])