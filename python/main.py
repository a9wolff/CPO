import sys


def main(argc, argv):
    print("Hello from python!")
    print(argc, argv)


if __name__ == '__main__':
    main(len(sys.argv), sys.argv)
