#include "exceptions.hh"

No_Binding_Exception::No_Binding_Exception(string _name): runtime_error("No binding for name: " + _name) {
  name = _name;
}

Zipping_Exception::Zipping_Exception(Object _lobjs, string _message): runtime_error("Zipping exception: " + _message) {
  message = _message;
  lobjs = _lobjs;
  clog << message << ": " << lobjs.getID() << endl;
}

Evaluation_Exception::Evaluation_Exception(Object _obj, Environment _env, string _message):
    runtime_error("Evaluation error: " + _message) {
    obj = _obj;
    env = _env;
    message = _message;
}

Bad_Type_Exception::Bad_Type_Exception(Object _obj, string _message):
    runtime_error("Evaluation error: " + _message) {
    obj = _obj;
    message = _message;
}

Memory_Exception::Memory_Exception(): runtime_error("Memory error") {
}
