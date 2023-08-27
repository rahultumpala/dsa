#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifndef HASHTABLE_IMPL
#define HASHTABLE_IMPL

#define DEFAULT_TABLE_SIZE 4096

typedef uint64_t(hash_function)(const char *, size_t);

typedef struct _hash_table_entry
{
    char *key;
    void *value;
    struct _hash_table_entry *next; // using external chaining to handle collisions
} entry;

typedef struct _hash_table
{
    uint64_t count;
    uint64_t size;
    hash_function *hash_fn;
    entry **entries;
} hash_table;

hash_table *hash_table_create(uint64_t size, hash_function *hf)
{
    hash_table *table = (hash_table *)malloc(sizeof(hash_table));
    table->hash_fn = hf;
    table->size = size;
    table->count = 0;
    table->entries = (entry **)calloc(size, sizeof(entry *)); // calloc sets memory to zero, while malloc does not.
    return table;
}

static uint64_t get_index(hash_table *ht, char *key)
{
    return ht->hash_fn(key, strlen(key)) % ht->size;
}

entry *hash_table_lookup(hash_table *ht, char *key)
{
    if (ht == NULL || key == NULL)
        return NULL;
    uint64_t index = get_index(ht, key);
    if (index > ht->size || ht->entries[index] == NULL)
        return NULL;

    entry *head = ht->entries[index];
    while (head != NULL && strncmp(head->key, key, strlen(key)) != 0)
    {
        head = head->next;
    }
    if (head == NULL)
        return NULL; // reached end of list, didn't find element
    return head;
}

bool hash_table_insert(hash_table *ht, char *key, void *obj)
{
    // cannot store NULL as value in the table
    if (ht == NULL || key == NULL || obj == NULL)
        return false;
    entry *exists = hash_table_lookup(ht, key);
    if (exists != NULL)
    {
        // already exists, so override value
        exists->value = obj;
        return true;
    }
    // create element to be inserted
    entry *element = (entry *)malloc(sizeof(entry));
    element->key = key;
    element->value = obj;
    element->next = NULL;

    uint64_t index = get_index(ht, key);

    if (ht->entries[index] == NULL)
    {
        ht->entries[index] = element;
        return true;
    }

    // add to the head of linked list at ht->entries[index]
    element->next = ht->entries[index];
    ht->entries[index] = element;
    return true;
}

void *hash_table_delete(hash_table *ht, char *key)
{
    if (ht == NULL || key == NULL)
        return NULL;

    uint64_t index = get_index(ht, key);
    if (index > ht->size || ht->entries[index] == NULL)
        return NULL;

    entry *cur = ht->entries[index], *prev = NULL;
    while (cur != NULL && strncmp(cur->key, key, strlen(key)) != 0)
    {
        cur = cur->next;
    }
    if (cur == NULL)
        return NULL;
    if (prev == NULL)
    {
        ht->entries[index] = cur->next;
        void *value = cur->value;
        free(cur);
        return value;
    }
    // delete an element from linked list which is not at the end
    prev->next = cur->next;
    void *value = cur->value;
    free(cur);
    return value;
}

void hash_table_print(hash_table *ht)
{
    printf("--- Table Begin ---\n");
    for (uint64_t idx = 0; idx < ht->size; idx++)
    {
        if (ht->entries[idx] != NULL)
        {
            printf("\t%i\t", idx);
            entry *element = ht->entries[idx];
            while (element != NULL)
            {
                printf("\"%s\"(%p) - ", element->key, element->value);
                element = element->next;
            }
            printf("\n");
        }
    }
    printf("--- End Table ---\n");
}

void hash_table_destroy(hash_table *ht)
{
    for (uint64_t idx = 0; idx < ht->size; idx++)
    {
        while (ht->entries[idx] != NULL)
        {
            entry *element = ht->entries[idx];
            ht->entries[idx] = element->next;
            /*
             hash_table_delete gives ownership of value ptrs to user
             this function assumes ownership of key, value ptrs and frees them
            */
            free(element->key);
            free(element->value);
            free(element);
        }
    }
    free(ht->entries);
    free(ht);
}

#endif // HASHTABLE_IMPL

uint64_t sample_hash_function(const char *key, size_t length)
{
    uint64_t hash_value = 0;
    for (int i = 0; i < length; i++)
    {
        hash_value += key[i];
        hash_value = (hash_value * key[i]);
    }
    return hash_value;
}

void *get_value_on_heap(char *name)
{
    char *heap_value = (char *)malloc(strlen(name) + 1);
    strcpy(heap_value, name);
    return heap_value;
}

int main(int argc, char **argv)
{
    hash_table *ht = hash_table_create(DEFAULT_TABLE_SIZE, sample_hash_function);
    hash_table_insert(ht, "Hello", get_value_on_heap("Hello"));
    hash_table_insert(ht, "world!", get_value_on_heap("world!"));
    hash_table_insert(ht, "my", get_value_on_heap("my"));
    hash_table_insert(ht, "first", get_value_on_heap("first"));
    hash_table_insert(ht, "hash", get_value_on_heap("hash"));
    hash_table_insert(ht, "table", get_value_on_heap("table"));
    hash_table_insert(ht, "implementation", get_value_on_heap("implementation"));
    hash_table_insert(ht, "in", get_value_on_heap("in"));
    hash_table_insert(ht, "c", get_value_on_heap("c"));
    hash_table_print(ht);
    hash_table_destroy(ht);
    return 0;
}