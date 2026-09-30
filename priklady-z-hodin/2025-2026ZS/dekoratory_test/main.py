from functools import wraps


def require_admin(func):
    @wraps(func)
    def wrapper(self, *args, **kwargs):
        if not self.is_admin:
            print("Pristup odmitnut")
            return
        return func(self, *args, **kwargs)
    return wrapper

def log(func):
    @wraps(func)
    def wrapper(self, *args, **kwargs):
        print(f"onjekt: {self}, argumenty: {args}, keyword argumenty: {kwargs}")
        return func(self, *args, **kwargs)
    return wrapper

class BankAccount:
    def __init__(self, name, balance, is_admin= False):
        self.name= name
        self.balance = balance
        self.is_admin = is_admin
    @log
    @require_admin
    def delete_account(self):
        print("Ucet smazan")
    
    @log
    @require_admin
    def zjisti_zustatek_na_vsech_uctech(self):
        print("Zustatek")
    
    def __str__(self):
        return f"BankAccount({self.name}, {self.balance}, {self.is_admin})"
        
if __name__ == "__main__":
    bezny = BankAccount("bezny", 100)
    admin = BankAccount("admin", 100, True)
    
    bezny.delete_account()
    admin.delete_account()