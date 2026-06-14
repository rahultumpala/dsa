defmodule DSA.Heap do
  @moduledoc """
    For any given node C, if P is the parent node of C,
      In a max heap, the value at P is greater than or equal to the value at C.
      In a min heap, the value at P is less than or equal to the value at C.

    The node at the "top" of the heap (with no parents) is called the root node.
  """

  def heapify(list, type \\ :max) when is_list(list) do
    count = Enum.count(list)

    heapify(list, 0, count, type)
  end

  defp heapify(list, idx, len, type) do
    cur = Enum.at(list, idx)
    lc_idx = 2 * idx + 1
    rc_idx = 2 * idx + 2

    l_child = Enum.at(list, lc_idx)

    need_l_swap =
      case type do
        :min -> lc_idx < len and l_child < cur
        :max -> lc_idx < len and l_child > cur
      end

    # swap operations
    list =
      if need_l_swap do
        list
        |> List.replace_at(lc_idx, cur)
        |> List.replace_at(idx, l_child)
        |> heapify(lc_idx, len, type)
      else
        list
      end

    # re eval since these vars are obsolete
    r_child = Enum.at(list, rc_idx)
    cur = Enum.at(list, idx)

    need_r_swap =
      case type do
        :min -> rc_idx < len and r_child < cur
        :max -> rc_idx < len and r_child > cur
      end

    list =
      if need_r_swap do
        list
        |> List.replace_at(rc_idx, cur)
        |> List.replace_at(idx, r_child)
        |> heapify(rc_idx, len, type)
      else
        list
      end

    list
  end
end
