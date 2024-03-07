from pymongo import MongoClient

class Database:

    def __init__(self):
        self.client = MongoClient('mongodb://localhost:27017')
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