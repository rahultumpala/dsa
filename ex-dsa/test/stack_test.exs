defmodule StackTest do
  use ExUnit.Case

  alias DSA.Stack

  test "struct -- push" do
    stk = %Stack{}

    stk = stk |> Stack.push(1)

    assert length(stk.items) == 1
  end

  test "struct -- push -- list" do
    stk = []

    stk = stk |> Stack.push(1)

    assert length(stk) == 1
  end

  test "struct -- pop" do
    stk = %Stack{}

    assert %Stack{items: [1]} ==
             stk |> Stack.push(1) |> Stack.push(2) |> Stack.pop()
  end

  test "struct -- pop -- list" do
    stk = []

    assert [1] == stk |> Stack.push(1) |> Stack.push(2) |> Stack.pop()
  end

  test "struct -- pop -- error" do
    stk = %Stack{}

    assert {:error, "Cannot pop from empty stack."} ==
             stk |> Stack.push(1) |> Stack.pop() |> Stack.pop()
  end

  test "struct -- pop -- list -- error" do
    stk = []

    assert {:error, "Cannot pop from empty stack."} ==
             stk |> Stack.push(1) |> Stack.pop() |> Stack.pop()
  end
end
