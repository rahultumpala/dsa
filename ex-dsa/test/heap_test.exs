defmodule HeapTest do
  use ExUnit.Case

  alias DSA.Heap

  test "heapify test and pop test" do
    numbers = [7, 91, 42, 18, 63, 5, 77, 30, 56, 14]
    min_heap = Heap.heapify(numbers, :min)
    max_heap = Heap.heapify(numbers, :max)

    numbers_sorted = Enum.sort(numbers)

    numbers_sorted
    |> Enum.reduce(
      min_heap,
      fn number, heap ->
        {top, heap} = DSA.Heap.pop(heap)
        # assert pop always returns smallest number in the list
        assert number == top
        heap
      end
    )

    numbers_sorted
    |> List.foldr(
      max_heap,
      fn number, heap ->
        {top, heap} = DSA.Heap.pop(heap)
        # assert pop always returns largest number in the list
        assert number == top
        heap
      end
    )
  end
end
