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

  @doc """
  naive rebalance. takes 2x memory. converts tree to list and rebuilds tree.
  """
  def rebalance(tree) do
    list = bst_to_list(tree)
    count = Enum.count(list)
    build_from_list(list, Kernel.div(count, 2), 0, count - 1)
  end

  def build_from_list(list, root_idx, list_start_idx, list_end_idx) do
    cond do
      # only 1 element
      list_start_idx == list_end_idx ->
        [Enum.at(list, list_end_idx), [], []]

      # only 2 elements
      list_end_idx - list_start_idx + 1 == 2 ->
        [Enum.at(list, list_end_idx), [Enum.at(list, list_start_idx), [], []], []]

      # out of bounds
      root_idx < list_start_idx || root_idx > list_end_idx ->
        []

      true ->
        [
          Enum.at(list, root_idx),
          build_from_list(
            list,
            div(root_idx - list_start_idx + 1, 2),
            list_start_idx,
            root_idx - 1
          ),
          build_from_list(
            list,
            root_idx + div(list_end_idx - root_idx + 1, 2),
            root_idx + 1,
            list_end_idx
          )
        ]
    end
  end

  def print(tree) do
    bst_to_list(tree) |> Enum.each(&IO.write("#{&1} "))
    IO.puts("")
    tree
  end

  def bst_to_list([root, left, right]) do
    bst_to_list(left) ++ [root] ++ bst_to_list(right)
  end

  def bst_to_list([]), do: []
end
