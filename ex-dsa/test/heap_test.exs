defmodule HeapTest do
  use ExUnit.Case

  alias DSA.Heap

  test "heapify test" do
    numbers = [7, 91, 42, 18, 63, 5, 77, 30, 56, 14]
    min_heap = Heap.heapify(numbers, :min)
    max_heap = Heap.heapify(numbers, :max)

    assert min_heap == [7, 91, 42, 18, 63, 5, 77, 30, 56, 14]
    assert max_heap == [91, 63, 42, 56, 18, 5, 77, 7, 30, 14]
  end
end
