defmodule DSA.Trie do
  @moduledoc """
  A sophisticated implementation can be written using structs but this module uses nested Maps.

  Simply, a Trie can be represented as a nested Map.

  Example:
    Consider the words with the same root character ["homework", "homeland", "holiday", "home"]
    The trie version is
      h
      └── o
          ├── m
          │   └── e*     (* - denotes the end of a word)
          │       ├── w
          │       │   └── o
          │       │       └── r
          │       │           └── k*
          │       └── l
          │           └── a
          │               └── n
          │                   └── d*
          └── l
              └── i
                  └── d
                      └── a
                          └── y*
    A Map representation for these words is
    %{
      "h" => %{
        "o" => %{
          "l" => %{"i" => %{"d" => %{"a" => %{"y" => %{end: true}}}}},
          "m" => %{
            "e" => %{
              "l" => %{"a" => %{"n" => %{"d" => %{end: true}}}},
              "w" => %{"o" => %{"r" => %{"k" => %{end: true}}}},
              end: true
            }
          }
        }
      }
    }
  """

  def insert(trie = %{}, element) when is_bitstring(element) do
    list = element_to_list(element)
    insert_list(trie, list)
  end

  defp insert_list(tr, [h | tail] = _element) do
    tr =
      case Map.get(tr, h, nil) do
        nil ->
          tr |> Map.put(h, insert_list(%{}, tail))

        val ->
          tr |> Map.put(h, insert_list(val, tail))
      end

    tr
  end

  defp insert_list(tr, [] = _element) do
    tr |> Map.put(:end, true)
  end

  @doc """
    This is the interesting part.
    Reduce function allows us to do a depth first search iteratively
    without having to write a recursive function.
  """
  def has_element?(tr, element) do
    list = element_to_list(element)

    end_val =
      Enum.reduce(list, tr, fn char, tr ->
        cond do
          tr == false || !Map.has_key?(tr, char) -> false
          true -> Map.get(tr, char)
        end
      end)

    case end_val do
      false -> false
      map -> Map.has_key?(map, :end)
    end
  end

  defp element_to_list(element), do: element |> String.codepoints()
end
