defmodule QueueTest do
  use ExUnit.Case

  alias DSA.Queue

  test "enqueue and dequeue" do
    q = %Queue{}

    q = q |> Queue.enqueue(1)
    assert Queue.peek(q) == {:ok, 1}

    q = q |> Queue.enqueue(2)
    assert Queue.peek(q) == {:ok, 1}

    q = q |> Queue.enqueue(3)
    assert Queue.peek(q) == {:ok, 1}

    assert q.len == 3

    {_val, q} = q |> Queue.dequeue()

    assert q.len == 2
    assert Queue.peek(q) == {:ok, 2}

    {_val, q} = q |> Queue.dequeue()
    assert q.len == 1
    assert Queue.peek(q) == {:ok, 3}
  end

  test "read all" do
    q = %Queue{}

    q = q |> Queue.enqueue(1) |> Queue.enqueue(2) |> Queue.enqueue(3)

    assert q.len == 3
    assert [1, 2, 3] = Queue.read_all(q)
  end
end
