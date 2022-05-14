#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Document;

struct IMachine {
    virtual void print(Document& doc) = 0;
    virtual void scan(Document& doc) = 0;
    virtual void fax(Document& doc) = 0;
};

struct MFP : IMachine {
    void print(Document& doc) override {
        // ok
    }
    void scan(Document& doc) override {
        // ok
    }
    void fax(Document& doc) override {
        // ok
    }
};

struct Scanner : IMachine {
    void print(Document& doc) override {
        // should not exist on the scanner API. 
    }
    void scan(Document& doc) override {
        // ok
    }
    void fax(Document& doc) override {
        // should not exist on the scanner API. 
    }

    // we need to segregate the interface. 
};

// segregated interface. 
struct IPrinter {
    virtual void print(Document& doc) = 0;
};

struct IScanner {
    virtual void scan(Document& doc) = 0;
};

struct IFax {
    virtual void fax(Document& doc) = 0;
};

// to combine interface
struct IMachine2 : IPrinter, IScanner {
    // we could do a Decorator pattern here, later. 
};

struct Machine : IMachine2 {
    IPrinter& printer;
    IScanner& scanner;

    Machine(IPrinter& printer, IScanner& scanner) : printer(printer), scanner(scanner) {}

    void print(Document& doc) override {
        printer.print(doc);
    }
    void scan(Document& doc) override {
        scanner.scan(doc);
    }
};

int main() {

    return 0;
}