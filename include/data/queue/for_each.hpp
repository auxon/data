#ifndef DATA_QUEUE_FOR_EACH_HPP
#define DATA_QUEUE_FOR_EACH_HPP

#include <data/queue.hpp>
#include <data/fold.hpp>
#include <type_traits>

namespace data {
    
    namespace queue {
        
        template <typename function, typename Q, typename X>
        struct fold_queue {
            function Function;
            
            Q operator()(Q q, X x) {
                return queue::append(q, Function(x));
            }
        };
                
        template <typename function, typename from, typename to> 
        struct for_each : public queue::is_queue<to> {
            using input_element = typename list::is_list<from>::element;
            using output_element = std::invoke_result<function, input_element>;
            
            to operator()(function f, from l) {
                return fold(fold_queue<function, to, input_element>{f}, to{}, l);
            }
        };
        
    }

}

#endif
