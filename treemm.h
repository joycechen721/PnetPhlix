#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <vector>
#include <string>
#include <iostream>
using namespace std;

template <typename KeyType, typename ValueType>
class TreeMultimap
{
    private:
      struct Node {
          Node(KeyType myKey, ValueType myValue){
              key = myKey;
              values.push_back(myValue);
              left = nullptr;
              right = nullptr;
          }
          KeyType key;
          vector<ValueType> values;
          Node* left;
          Node* right;
      };
      Node* root;
      void cleanup(Node* curr){
          if(curr == nullptr) return;
          cleanup(curr->right);
          cleanup(curr->left);
          delete curr;
      }
    
    public:
        class Iterator
        {
          public:
            Iterator()
            {
                //vector is empty, so iterator is invalid
                m_count = 0;
                m_size = 0;
            }
            
            Iterator(Node* p)
            {
                m_count = 0;
                m_size = p->values.size();
                m_values = &(p->values);
            }

            ValueType& get_value() const
            {
                return m_values->at(m_count);
            }

            bool is_valid() const
            {
                return m_count < m_size;
            }

            void advance()
            {
                m_count++;
            }

          private:
            int m_count;
            long m_size;
            vector<ValueType>* m_values;
        };

        TreeMultimap()
        {
            root = nullptr;
        }

        ~TreeMultimap()
        {
            cleanup(root);
        }

        void insert(const KeyType& key, const ValueType& value)
        {
            ValueType myVal = value;
            if(root == nullptr){
                root = new Node(key, myVal);
                return;
            }
            Node* p = root;
            for(;;){
                if(key == p->key){
                    p->values.push_back(myVal);
                    return;
                }
                if(key < p->key){
                    if(p->left != nullptr){
                        p = p->left;
                    }
                    else{
                        p->left = new Node(key, myVal);
                        return;
                    }
                }
                if(key > p->key){
                    if(p->right != nullptr){
                        p = p->right;
                    }
                    else{
                        p->right = new Node(key, myVal);
                        return;
                    }
                }
            }
        }

        Iterator find(const KeyType& key) const
        {
            if(root->key == key) return Iterator(root);
            Node* p = root;
            while(p != nullptr){
                if(key == p->key){
                    return Iterator(p);
                }
                if(key > p->key){
                    p = p->right;
                }
                else if(key < p->key){
                    p = p->left;
                }
            }
            return Iterator();
        }
};

#endif // TREEMULTIMAP_INCLUDED
