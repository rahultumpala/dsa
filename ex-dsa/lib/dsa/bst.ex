defmodule DSA.BST do
  @moduledoc """
    Binary Search Tree.
    Implemented as a list of lists.

    Structure: [root, left, right]
  """
  def init() do
    [:init, [], []]
  end

  def insert(tree, element) when is_list(tree) and is_number(element) do
    tree =
      case tree do
        # assign to root if tree is empty or to be initialized
        [:init, _, _] -> [element, [], []]
        [] -> [element, [], []]
        _ -> tree
      end

    [root, left, right] = tree

    tree =
      cond do
        # do nothing when duplicates are found
        root == element ->
          tree

        element < root ->
          left = insert(left, element)
          [root, left, right]

        element > root ->
          right = insert(right, element)
          [root, left, right]
      end

    tree
  end

  def print(tree) do
    print_all(tree)
    IO.puts("")
  end

  defp print_all([root, left, right] = tree) do
    print_all(left)
    IO.write("#{root} ")
    print_all(right)
  end

  defp print_all([] = _tree), do: nil
end
