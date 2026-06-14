defmodule BstTest do
  use ExUnit.Case

  alias DSA.BST

  test "insert and rebalance test" do
    numbers = [91, 7, 42, 18, 63, 5, 77, 30, 56, 14]
    bst = numbers |> Enum.reduce(BST.init(), fn el, tree -> DSA.BST.insert(tree, el) end)
    sorted = Enum.sort(numbers)

    # bst |> IO.inspect()
    # bst |> BST.print()

    rebalanced = bst |> BST.rebalance()

    # rebalanced |> IO.inspect() |> BST.print()

    assert sorted == bst |> BST.bst_to_list()
    assert sorted == rebalanced |> BST.bst_to_list()
  end
end
