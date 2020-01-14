// **** includes ****
#include <iostream>
//#include <thread>
#include <future>


// **** namespaces ****
using namespace std;


////
//// Thread function.
////
//void threadFn   (
//                void
//                )
//{
//
//    // **** welcome message ****
//    cout << "threadFn <<< entering\n";
//
//    // **** simulate work ****
//    cout << "threadFn <<< starting work...\n";
//    this_thread::sleep_for(chrono::seconds(3));
//    cout << "threadFn <<< done working\n";
//
//    // **** exit message ****
//    cout << "threadFn <<< bye bye\n";
//}


////
//// Asynchronous function.
////
//int asyncFn (
//            int value
//            )
//{
//
//    // **** welcome message ****
//    cout << "asyncFn <<< entering threadID: " << this_thread::get_id() << endl;
//
//    // **** do some work ****
//    cout << "asyncFn <<< starting work...\n";
//    this_thread::sleep_for(chrono::seconds(3));
//    cout << "asyncFn <<< done working\n";
//
//    // **** exit message ****
//    cout << "asyncFn <<< bye bye\n";
//
//    // **** return modified value ****
//    return value * 2;
//}


//
// Thread function that sets a promise.
// 
void ThreadFn   (
                promise<int> &myPromise
                )
{
    
    // **** welcome message ****
    cout << "ThreadFn <<< entering threadID: " << this_thread::get_id() << endl;

    // **** delay for a few ****
    cout << "ThreadFn <<< before first delay...\n";
    this_thread::sleep_for(chrono::seconds(5));
    cout << "ThreadFn <<< after first delay\n";

    // **** set the value on the promise ****
    myPromise.set_value(123);

    // **** delay for a few ****
    cout << "ThreadFn <<< before second delay...\n";
    this_thread::sleep_for(chrono::seconds(7));
    cout << "ThreadFn <<< after second delay\n";

    // **** exit message ****
    cout << "ThreadFn <<< bye bye\n";
}


//
// Test scafolding.
//
//int main    (
//            void
//            )
//{
//
//    // **** welcome message ****
//    cout << "main <<< entering\n";
//
//    // **** create thread ****
//    thread t1 { threadFn };
//
//    // **** wait for thread to complete ****
//    cout << "main <<< waiting for thread to complete...\n";
//    t1.join();
//    cout << "main <<< thread finished\n";
//
//    // **** exit message ****
//    cout << "main <<< bye bye\n";
//
//    // **** ****
//    return 0;
//}


//int main    (
//            void
//            )
//{
//
//    // **** welcome message ****
//    cout << "main <<< entering threadID: " << this_thread::get_id() << endl;
//
//    // **** start asynchronous function which will return a future ****
//    int value = 123;
//    cout << "main <<< before starting asyncFn with value: " << value << endl;
//
//    //future<void> fn = async(launch::async, asyncFn);
//    //future<void> fn = async(launch::deferred, asyncFn);
//    future<int> fn = async(launch::async, asyncFn, value);
//
//    cout << "main <<< after starting asyncFn with value: " << value << endl;
//
//    // **** do some local work ****
//    cout << "main <<< doing some work...\n";
//    this_thread::sleep_for(chrono::seconds(7));
//    cout << "main <<< done with work\n";
//
//    // **** wait for the future function to complete ****
//    cout << "main <<< wait for asyncFn to complete...\n";
//    //fn.get();
//
//    // **** check if async function completed ****
//    if (fn.valid()) {
//        value = fn.get();
//        cout << "main <<< asyncFn value: " << value << " completed line: " << __LINE__ << endl;
//    }
//    else {
//        cout << "main <<< asyncFn invalid\n";
//    }
//
//    //// **** calling get() a second time (with throw an exception) ****
//    //fn.get();
//
//    // **** ****
//    if (fn.valid()) {
//        value = fn.get();
//        cout << "main <<< asyncFn value: " << value << " completed\n";
//    }
//    else {
//        cout << "main <<< asyncFn invalid line: " << __LINE__ << endl;
//    }
//
//    // **** exit message ****
//    cout << "main <<< bye bye\n";
//
//    // **** ****
//    return 0;
//}


//int main    (
//            void
//            )
//{
//
//    // **** welcome message ****
//    cout << "main <<< entering\n";
//
//    // **** create a promise ****
//    promise<int> myPromise;
//    future<int> fut = myPromise.get_future();
//
//    // **** delay for a few ****
//    this_thread::sleep_for(chrono::seconds(5));
//
//    // **** set the promise value ****
//    cout << "main <<< before promise set_value()...\n";
//    myPromise.set_value(123);
//    cout << "main <<< after promise set_value()\n";
//
//    // **** get promise value  ****
//    cout << "main <<< before get value...\n";
//    int value = fut.get();
//    cout << "main <<< after get value: " << value << endl;
//
//    // **** exit message ****
//    cout << "main <<< bye bye\n";
//
//    // **** ****
//    return 0;
//}


int main()
{
    
    // **** welcome message ****
    cout << "main <<< entering threadID: " << this_thread::get_id() << endl;

    // **** create a promise ****
    promise<int> myPromise;
    future<int> fut = myPromise.get_future();

    // **** create a thread to deliver the promise ****
    thread t1 { ThreadFn, ref(myPromise) };

    // **** get the value of the promise ****
    cout << "main <<< before fut.get()...\n";
    int value = fut.get();
    cout << "main <<< after fut.get() value: " << value << endl;

    // **** wait for the thread to exit ****
    cout << "main <<< wait for the thread to exit...\n";
    t1.join();
    cout << "main <<< thread is done\n";

    // **** exit message ****
    cout << "main <<< bye bye\n";

    // **** ****
    return 0;
}
