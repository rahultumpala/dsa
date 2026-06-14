defmodule DSA.Heap do
  defstruct [:type, count: 0, items: []]

  @moduledoc """
    For any given node C, if P is the parent node of C,
      In a max heap, the value at P is greater than or equal to the value at C.
      In a min heap, the value at P is less than or equal to the value at C.

    The node at the "top" of the heap (with no parents) is called the root node.
  """

  @doc """
    Adds an element to the heap and returns the updated struct.
  """
  def push(%__MODULE__{count: count, items: items, type: type} = _heap, new_element) do
    %__MODULE__{
      count: count + 1,
      items: heapify([new_element | items], 0, count + 1, type),
      type: type
    }
  end

  @doc """
    Pops the top element from the struct and returns a 2 element tuple.
    {top_element, updated_struct}
  """
  def pop(%__MODULE__{count: count, items: items, type: type} = heap) do
    case count do
      0 ->
        {nil, heap}

      _ ->
        [h | rest] = items

        {h,
         %__MODULE__{
           count: count - 1,
           items: heapify(rest, 0, count - 1, type),
           type: type
         }}
    end
  end

  @doc """
    Converts the input list into a Heap.
    Type can be either of :min , :max
  """
  def heapify(list, type \\ :max) when is_list(list) do
    len = Enum.count(list)

    list =
      0..(len - 1)
      |> Enum.reverse()
      |> Enum.reduce(list, fn idx, list ->
        heapify(list, idx, len, type)
      end)

    %__MODULE__{
      count: len,
      items: list,
      type: type
    }
  end

  defp heapify([], _, _, _), do: []

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
