import database.mongo_client as database

db  = database.Database()

def insert(payload):
    result = db.insert(payload)
    return result

def get_data(start:int,end:int):
    result = db.get_data(start,end)
    return result

def get_avg(start:int,end:int):
    result = db.get_avg(start,end)
    return result

