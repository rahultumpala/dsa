defmodule DSA.Queue do
  defstruct len: 0,
            f: [],
            s: []

  @doc """
  Time Complexity - O(1)
  """
  def enqueue(%__MODULE__{} = q, item) do
    %__MODULE__{
      q
      | s: [item | q.s],
        len: q.len + 1
    }
  end

  @doc """
  This operation is expensive.
  Worst case Time Complexity - O(N) when all the items inserted before the first dequeue operation are read.
  All other cases - O(1)
  """
  def peek(%__MODULE__{} = q) do
    cond do
      q.len == 0 ->
        {:error, "Cannot read from empty queue."}

      q.f == [] ->
        {:ok, Enum.at(q.s, q.len - 1)}

      true ->
        {:ok, Enum.at(q.f, 0)}
    end
  end

  @doc """
  Worst case Time Complexity - O(N) when all the items inserted before the first dequeue operation are read.
  All other cases - O(1)
  Overall amortized time complexity would be O(1)
  since the reversed items are stored in the returned data structure,
  unlike the case of peek/1 where the value is only read and the data structure is not returned.
  """
  def dequeue(%__MODULE__{} = q) do
    q =
      cond do
        q.len == 0 ->
          {:error, "Cannot dequeue an element from an empty queue."}

        q.f == [] ->
          reverse(q)

        true ->
          q
      end

    val = Enum.at(q.f, 0)

    q = %__MODULE__{
      q
      | len: q.len - 1,
        f: Enum.drop(q.f, 1)
    }

    {val, q}
  end

  @doc """
  Expensive operation. Use sparingly.
  If your goal is to read all values, it would be better to loop dequeue/2 as it is more efficient.
  """
  def read_all(%__MODULE__{} = q) do
    q.f ++ Enum.reverse(q.s)
  end

  defp reverse(%__MODULE__{} = q) do
    %__MODULE__{
      q
      | f: Enum.reduce(q.s, q.f, fn item, acc -> [item | acc] end),
        s: []
    }
  end
end
