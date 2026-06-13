defmodule BstTest do
  use ExUnit.Case

  alias DSA.BST

  test "insert and print test" do
    numbers = [42, 7, 91, 18, 63, 5, 77, 30, 56, 14]
    bst = numbers |> Enum.reduce(BST.init(), fn el, tree -> DSA.BST.insert(tree, el) end)
    bst |> IO.inspect()
    bst |> BST.print()

  end
end
