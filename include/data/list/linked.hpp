// Copyright (c) 2019 Daniel Krawisz
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DATA_LIST_LINKED
#define DATA_LIST_LINKED

#include <data/tools/iterator_list.hpp>
#include <data/fold.hpp>
#include <type_traits>
    
namespace data::list {
    template <typename elem> struct linked;
    
    namespace base {
        // base class of a linked list. 
        // I want to support linked lists that can act as std::containers, 
        // meaning that they support iterators as well as linked list
        // that contain references, which makes a lot of sense with 
        // functional programming. 
        template <typename elem, typename derived>
        struct linked {
            using returned = typename container::returned<elem>::type;
            using node = list::node<elem, derived, returned>;
            using next = ptr<node>;
            
            next Next;
        
            // if the list is empty, then this function
            // will dereference a nullptr. It is your
            // responsibility to check. 
            const returned first() const {
                return Next->first();
            }
            
            returned first() {
                return Next->first();
            }
        
            bool empty() const {
                return Next == nullptr;
            }
            
            const derived rest() const {
                if (empty()) return {};
                
                return Next->rest();
            }
            
            bool contains(elem x) const {
                if (empty()) return false;
                    
                Next->contains(x);
            }
            
            uint32 size() const {
                if (empty()) return 0;
                    
                return Next->size();
            }
            
            bool operator==(const next n) {
                return Next == n;
            }
            
            bool operator==(const linked& l) const {
                if (this == &l) return true;
                return Next == l.Next;
            }
            
            bool operator!=(const linked& l) const {
                return !(*this==l);
            }
            
            const derived from(uint32 n) const {
                if (empty()) return {};
                if (n == 0) return *this;
                return rest().from(n - 1);
            }
            
            const returned operator[](uint32 n) const {
                return from(n).first();
            }
        
            linked() : Next{nullptr} {}
            linked(linked&& l) : Next{l.Next} {
                l.Next = nullptr;
            }
        
        protected:
            linked(next n) : Next{n} {}
            // ensure the base class can't be constructed. 
            virtual ~linked() = 0; 
            
            friend struct list::linked<elem>;
        };
        
        template <typename elem, typename derived> linked<elem, derived>::~linked() {}
    }
    
    template <typename elem>
    struct linked : public base::linked<elem, linked<elem>> {
        using parent = base::linked<elem, linked<elem>>;
        using requirement = data::list::definition::complete<
            linked<elem>, elem, typename parent::returned, iterator<linked>, const iterator<linked>>;
        constexpr static requirement Satisfied{};
        
        linked() : parent{} {}
        linked(const linked& l) : parent{l.Next} {}
        linked(linked&& l) : parent{static_cast<parent&&>(l)} {
            l.Next = nullptr;
        }
        
        linked(std::initializer_list<elem> l) : linked{
            list::reverse(fold(
                plus<linked, elem>, 
                linked{}, 
                iterator_list<decltype(l.begin()), elem>(l.begin(), l.end())
            ))
        } {}
        
        linked(std::vector<elem> v);
        
        linked& operator=(const linked& l) {
            parent::Next = l.Next;
            return *this;
        } 
        
        linked prepend(elem x) const {
            return linked{std::make_shared<typename parent::node>(typename parent::node{x, *this})};
        }
        
        linked operator+(elem x) const {
            return prepend(x);
        }
        
        iterator<linked> begin();
        iterator<linked> end();
        const iterator<linked> begin() const;
        const iterator<linked> end() const;
        
    private:
        linked(typename parent::next n) : parent{n} {}
    };
    
    template <typename elem>
    struct linked<elem&> : public base::linked<elem, linked<elem>> {
        using parent = base::linked<elem, linked<elem>>;
        using requirement = data::list::definition::buildable<linked<elem>, elem, typename parent::returned>;
        constexpr static requirement Satisfied{};
        
        linked() : parent{} {}
        linked(const linked& l) : parent{l.Next} {}
        linked(linked&& l) : parent{static_cast<parent&&>(l)} {
            l.Next = nullptr;
        }
        
        linked& operator=(const linked& l) {
            parent::Next = l.Next;
            return *this;
        } 
        
        linked prepend(elem x) const {
            return linked{std::make_shared<typename parent::node>(typename parent::node{x, *this})};
        }
        
        linked operator+(elem x) const {
            return prepend(x);
        }
        
    private:
        linked(typename parent::next n) : parent{n} {}
    };
}

namespace data {
    
    template <typename X>
    inline bool empty(const list::linked<X> l) {
        return l.empty();
    }
    
    template <typename X>
    inline typename list::linked<X>::returned first(const list::linked<X> l) {
        return l.first();
    }
    
    template <typename X>
    inline const list::linked<X> rest(const list::linked<X> l) {
        return l.rest();
    }
    
    template <typename X>
    inline const list::linked<X> prepend(const list::linked<X> l, const X elem) {
        return l.prepend(elem);
    }

}

#endif
