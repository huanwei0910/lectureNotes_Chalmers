#include "func.H"

class myClassFriend {
public:
  myClassFriend();
};
myClassFriend::myClassFriend() {
  myClass testMyClassFriend;
  cout << "testMyClassFriend.l_ = " << testMyClassFriend.l_ << endl;
}

int main() {
  myClassFriend myClassFriendObject;
  return 0;
}
