#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 10

// This struct represents a single menu item
struct MenuItem
{
  char name[20];
  float price;
};

// This struct represents an order
struct Order
{
  struct MenuItem items[MAX_ITEMS];
  int num_items;
};

// This function adds a new item to an order
void
add_item (struct Order *order, struct MenuItem item)
{
  if (order->num_items < MAX_ITEMS)
    {
      order->items[order->num_items] = item;
      order->num_items++;
    }
}

// This function calculates the total cost of an order
float
get_cost (struct Order order)
{
  float total_cost = 0;
  for (int i = 0; i < order.num_items; i++)
    {
      total_cost += order.items[i].price;
    }
  return total_cost;
}

int
main (void)
{
  // Read the menu from a file
  FILE *menu_file = fopen ("menu.txt", "r");
  struct MenuItem menu[MAX_ITEMS];
  int num_items = 0;
  while (fscanf
	 (menu_file, "%s %f", menu[num_items].name,
	  &menu[num_items].price) == 2)
    {
      num_items++;
    }
  fclose (menu_file);

  // Create a new order
  struct Order order;
  order.num_items = 0;

  // Prompt the user to add items to the order
  char input[20];
  while (1)
    {
      printf ("Enter item name (or 'done' to finish): ");
      scanf ("%s", input);
      if (strcmp (input, "done") == 0)
	{
	  break;
	}
      for (int i = 0; i < num_items; i++)
	{
	  if (strcmp (input, menu[i].name) == 0)
	    {
	      add_item (&order, menu[i]);
	    }
	}
    }

  // Print the bill
  printf ("--- Bill ---\n");
  for (int i = 0; i < order.num_items; i++)
    {
      printf ("%s: $%.2f\n", order.items[i].name, order.items[i].price);
    }
  printf ("Total: $%.2f\n", get_cost (order));

  // Save the bill to a file
  FILE *bill_file = fopen ("bill.txt", "w");
  for (int i = 0; i < order.num_items; i++)
    {
      fprintf (bill_file, "%s: $%.2f\n", order.items[i].name,
	       order.items[i].price);
    }
  fprintf (bill_file, "Total: $%.2f\n", get_cost (order));
  fclose (bill_file);

  return 0;
}
