# 参照旁边的 C++ 写的对照版喵


class NyannException(Exception):
    def __str__(self):
        return "ERROR発生nyannn!!"


def main():
    try:
        raise NyannException()
    except NyannException as e:
        print("I caught a neko!")
        print(str(e))
    except:
    # except BaseException: 
    # 这样写应该也行, 因为所有异常都继承自它
    # 但是 C++ 中不能写 catch(std::exception) 就是了
        print("unknown exception nyann!!")
    return 0

if __name__ == "__main__":
    exit(main())