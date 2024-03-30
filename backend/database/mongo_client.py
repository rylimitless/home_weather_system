import logging
from pymongo import MongoClient
import os

# Get the current date and time


import dotenv

dotenv.load_dotenv()


class Database:
    MongoURI = os.environ['MONGO_URI']
    def __init__(self):
        self.client = MongoClient(self.MongoURI)
        self.db = self.client.dev
        self.collection = self.db.data

    def insert(self,payload):
        # self.db.connection
        try:
            result = self.collection.insert_one(payload)
            if result.acknowledged:
                return True
        except Exception as e:
            print(f"Mongo Insert Error {e}")
            return False
        return False

    def get_data(self,start:int,end:int):
        try:
            result = self.collection.find({"timestamp": {"$gte": start, "$lte": end}})
            data = []
            for i in result:
                i.pop('_id', None)
                data.append(i)
            return data
        except Exception as e:
            print(f"Mongo Insert Error {e}")
            return False
    
    def get_avg(self,start:int,end:int):
        try:
            result = []
            data = self.collection.find({"timestamp": {"$gte": start, "$lte": end}})
            count = 0
            total = 0
            temp = 0
            humidity = 0
            heat_index = 0
            for i in data:
                count += 1
                temp += i['temperature']
                humidity += i['humidity']
                heat_index += i['heat index']
            result.append({"temperature":temp/count,"humidity":humidity/count ,"heat_index":heat_index/count})
            return result
        except Exception as e:
            print(f"Mongo Insert Error {e}")
            return False
    
        
