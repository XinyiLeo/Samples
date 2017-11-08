
#include<iostream>
#include<cstdlib>
#include "recursive.h"
#include "p3.h"

int size(list_t list)
/*
// EFFECTS: Returns the number of elements in "list".
//          Returns zero if "list" is empty.
*/

{
   if (list_isEmpty(list)== true)
   {
       return 0;
   }
   else
   {
       return size(list_rest(list))+1;
   }
}


int sum(list_t list)
/*
// EFFECTS: Returns the sum of each element in "list".
//          Returns zero if "list" is empty.
*/
{
    if (list_isEmpty(list)== true)
   {
       return 0;
   }
    else
   {
       return sum(list_rest(list))+list_first(list);
   }
}

int product(list_t list)
/*
// EFFECTS: Returns the product of each element in "list".
//          Returns one if "list" is empty.
*/
{
     if (list_isEmpty(list)== true)
   {
       return 1;
   }
    else
   {
       return product(list_rest(list))*list_first(list);
   }
}

int accumulate(list_t list, int (*fn)(int, int), int base)
/*
// REQUIRES: "fn" must be associative.
//
// EFFECTS: Returns "base" if "list" is empty.
//          Returns fn(list_first(list),
//                      accumulate(list_rest(list),
//                               fn, base) otherwise.
//
*/
{
       if (list_isEmpty(list))
   {
       return base;
   }
       else
   {
       return fn(list_first(list),accumulate(list_rest(list),fn,base));
   }    
}

static int list_last(list_t list)
//REQUIRE : The list is not empty
//EFFECTS: Return the last element of the list
{
   if(list_isEmpty(list_rest(list)) ==true)
     {
       return list_first(list);
     }
   else
     {
       return list_last(list_rest(list));
     }
}

static list_t list_deletelast(list_t list)
//REQUIRE: The list is not empty
//EFFECT: Return the list without the last element
{
     if(list_isEmpty(list_rest(list)) ==true)
     {
       return list_make();
     }
     else
     {
       return list_make(list_first(list),list_deletelast(list_rest(list)));
     }
}



list_t reverse(list_t list)
// EFFECTS: Returns the reverse of "list".
//
// For example: the reverse of ( 3 2 1 ) is ( 1 2 3 )
{   
      if(list_isEmpty(list) || list_isEmpty(list_rest(list)) ==true)
    {
      return list;
    }
    else
    {
     return list_make(list_last(list),reverse(list_deletelast(list)));
    }
}

list_t append(list_t first, list_t second)
/*
// EFFECTS: Returns the list (first second).
//
*/
{
      if(list_isEmpty(first)  ==true)
    {
      return second;
    }
      else
    {
      return list_make(list_first(first),append(list_rest(first),second));
    }
}

list_t filter_odd(list_t list)
/*
// EFFECTS: Returns a new list containing only the elements of the
//          original "list" which are odd in value,
//          in the order in which they appeared in list.
*/
{
     if(list_isEmpty(list)  ==true)
    {
      return list;
    }
      else
    {
      if(list_first(list) % 2 ==1)
         {
            return list_make(list_first(list),filter_odd(list_rest(list)) );
         }
      else
            return filter_odd(list_rest(list));
    }
}

list_t filter_even(list_t list)
/*
// EFFECTS: Returns a new list containing only the elements of the
//          original "list" which are even in value,
//          in the order in which they appeared in list.
*/
{
     if(list_isEmpty(list)  ==true)
    {
      return list;
    }
      else
    {
      if(list_first(list) % 2 ==0)
         {
            return list_make(list_first(list),filter_even(list_rest(list)) );
         }
      else
            return filter_even(list_rest(list));
    }
}


list_t filter(list_t list, bool (*fn)(int))
/*
// EFFECTS: Returns a list containing precisely the elements of "list"
//          for which the predicate fn() evaluates to true, in the
//          order in which they appeared in list.
*/
{
     if(list_isEmpty(list)  ==true)
    {
      return list;
    }
      else
    {
      if(fn(list_first(list))==true )
         {
            return list_make(list_first(list),filter(list_rest(list),fn));
         }
      else
            return filter(list_rest(list),fn);
    }
}

list_t insert_list(list_t first, list_t second, unsigned int n)
/*
// REQUIRES: n <= the number of elements in "first".
//
// EFFECTS: Returns a list comprising the first n elements of
//          "first", followed by all elements of "second",
//           followed by any remaining elements of "first".
*/
{
      if(n==0)
    {
      return append(second,first);
    }
      else
    {
      return list_make(list_first(first),insert_list(list_rest(first),second,n-1));
    }
}

list_t chop(list_t list, unsigned int n)
/*
// REQUIRES: "list" has at least n elements.
//
// EFFECTS: Returns the list equal to "list" without its last n
//          elements.
*/
{
     if(n==0)
    {
      return list;
    }
      else
    {
      return chop(list_deletelast(list), n-1);
    }
}

//************************************************************
//*********                                     **************
//*********            BINARY TREE              **************
//*********                                     **************
//************************************************************

int tree_sum(tree_t tree)
/*
// EFFECTS: Returns the sum of all elements in "tree".
//          Returns zero if "tree" is empty.
*/
{
   if(tree_isEmpty(tree)==true)
    {
      return 0;
    }
      else
    {
      return tree_sum(tree_left(tree))+tree_sum(tree_right(tree))+tree_elt(tree);
    }
}

bool tree_search(tree_t tree, int key)
/*
// EFFECTS: Returns true if and only if there exists an element in
//          "tree" whose value is "key".
*/
{
    if(tree_isEmpty(tree))
    {
      return false;
    }
    else if(tree_elt(tree)==key)
    {
      return true;
    }
      else
    {
      return tree_search(tree_left(tree), key)|| tree_search(tree_right(tree),key);
    }
}

static int max(int a, int b)
//EFFECTS: returns the maximum between a and b
{
   if(a>=b)
      return a;
   else
      return b;
}

static int min(int a, int b)
//EFFECTS: returns the minimum between a and b
{
   if(a<=b)
      return a;
   else
      return b;
}

int depth(tree_t tree)
/*
// EFFECTS: Returns the depth of "tree", which equals the number of
//          layers of nodes in the tree.
//          Returns zero is "tree" is empty.
*/
{
    if(tree_isEmpty(tree)==true)
    {
      return 0;
    }
    else
      return  max(depth(tree_left(tree)),depth(tree_right(tree)) )+1 ;
}

int tree_min(tree_t tree)
/*
// REQUIRES: "tree" is non-empty.
// EFFECTS: Returns the smallest element in "tree".
*/
{
   if(tree_isEmpty(tree_left(tree)) && tree_isEmpty(tree_right(tree))==true)
       {
           return tree_elt(tree);
       }
   else
       {
           return min(tree_elt(tree),min(tree_min(tree_left(tree)),tree_min(tree_right(tree))));
       }
}


list_t traversal(tree_t tree)
/*
// EFFECTS: Returns the elements of "tree" in a list using an
//          in-order traversal.
*/
{
      if(tree_isEmpty(tree)==true)
    {
      return list_make();
    }
      else
    {
      return append(traversal(tree_left(tree)),list_make(tree_elt(tree),traversal(tree_right(tree))));
    }
}

bool tree_hasPathSum(tree_t tree, int sum)
/*
// EFFECTS: Returns true if and only if "tree" has a root-to-leaf
//          path such that adding all elements along the path
//          equals "sum".
*/
{
    if(tree_isEmpty(tree)==true)
       {
          if(sum==0)
             return true;
          else
             return false;
       }
    else
       {
          return tree_hasPathSum(tree_left(tree), sum-tree_elt(tree)) || tree_hasPathSum(tree_right(tree), sum-tree_elt(tree));
       }
 
}

bool covered_by(tree_t A, tree_t B)
/*
// EFFECTS: Returns true if tree A is covered by tree B.
*/      
{
   if(tree_isEmpty(A)==true)
     {
        return true;
     }
   else
     { 
            if(tree_isEmpty(B)==true)
              {
                 return false;
              }
        else
               {
                 if(tree_elt(A)==tree_elt(B))
             {
                 //std::cout<<"helloworld"<<std::endl;
                 return covered_by(tree_left(A),tree_left(B)) &&   covered_by(tree_right(A),tree_right(B)) ;
             }
        else
                 return false;
           }
     }
}

bool contained_by(tree_t A, tree_t B)
/*
// EFFECTS: Returns true if tree A is covered by tree B
//          or any complete subtree of B.
*/     
{
    if(tree_isEmpty(B)==true)
         {
             if(tree_isEmpty(A)==true)
                   {
                         return true;
                    }
             else
                         return false;
         }
     else
        {
            if(covered_by(A,B)==true)
                 return true;
            else
                 return contained_by(A,tree_left(B)) || contained_by(A,tree_right(B)) ;
        }
}











At 2015-06-16 13:34:17, "?" <wuxy3141@126.com> wrote:
- ?????? -


