defmodule TrieTest do
  use ExUnit.Case

  test "insert and retrieve" do
    words = ["homework", "homeland", "holiday", "hotline", "home", "tent", "ten", "tentcity"]
    trie = words |> Enum.reduce(%{}, fn word, trie -> DSA.Trie.insert(trie, word) end)

    words
    |> Enum.each(fn word ->
      assert DSA.Trie.has_element?(trie, word) == true
    end)

    assert DSA.Trie.has_element?(trie, "nonExistentWord") == false
  end
end
