defmodule TrieTest do
  use ExUnit.Case

  test "insert and retrieve" do
    words = ["homework", "homeland", "holiday", "hotline"]
    trie = words |> Enum.reduce(%{}, fn word, trie -> DSA.Trie.insert(trie, word) end)

    assert DSA.Trie.has_element?(trie, "homework") == true
    assert DSA.Trie.has_element?(trie, "nonExistentWord") == false
  end
end
