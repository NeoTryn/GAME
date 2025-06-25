
/*  
// SOURCE CODE OF THE BELOW FUNCTION FROM STACKOVERFLOW
// WARNING THIS CODE IS NOT MINE!!!
// CREDIT: https://stackoverflow.com/questions/500493/c-equivalent-of-javas-instanceof
*/

template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
    return dynamic_cast<const Base*>(ptr) != nullptr;
}