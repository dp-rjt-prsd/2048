import random
import os

SIZE = 4
grid = [[0] * SIZE for _ in range(SIZE)]
score = 0

def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')

def initialize_game():
    for _ in range(2):
        add_new_tile()

def display_grid():
    clear_screen()
    print(f"2048 Game\t\tScore: {score}\n")
    for row in grid:
        print("\t".join(str(cell) if cell != 0 else '.' for cell in row))
    print()

def add_new_tile():
    empty = [(i, j) for i in range(SIZE) for j in range(SIZE) if grid[i][j] == 0]
    if empty:
        x, y = random.choice(empty)
        grid[x][y] = random.choice([2, 4])

def can_move():
    for i in range(SIZE):
        for j in range(SIZE):
            if grid[i][j] == 0:
                return True
            if i < SIZE - 1 and grid[i][j] == grid[i + 1][j]:
                return True
            if j < SIZE - 1 and grid[i][j] == grid[i][j + 1]:
                return True
    return False

def compress_and_merge_line(line):
    global score
    new_line = [num for num in line if num != 0]
    merged_line = []
    skip = False

    for i in range(len(new_line)):
        if skip:
            skip = False
            continue
        if i + 1 < len(new_line) and new_line[i] == new_line[i + 1]:
            merged_value = new_line[i] * 2
            score += merged_value
            merged_line.append(merged_value)
            skip = True
        else:
            merged_line.append(new_line[i])

    return merged_line + [0] * (SIZE - len(merged_line))

def move_left():
    changed = False
    for i in range(SIZE):
        new_row = compress_and_merge_line(grid[i])
        if grid[i] != new_row:
            changed = True
            grid[i] = new_row
    return changed

def move_right():
    changed = False
    for i in range(SIZE):
        reversed_row = list(reversed(grid[i]))
        new_row = compress_and_merge_line(reversed_row)
        new_row = list(reversed(new_row))
        if grid[i] != new_row:
            changed = True
            grid[i] = new_row
    return changed

def move_up():
    changed = False
    for j in range(SIZE):
        col = [grid[i][j] for i in range(SIZE)]
        new_col = compress_and_merge_line(col)
        for i in range(SIZE):
            if grid[i][j] != new_col[i]:
                changed = True
                grid[i][j] = new_col[i]
    return changed

def move_down():
    changed = False
    for j in range(SIZE):
        col = [grid[i][j] for i in range(SIZE)]
        reversed_col = list(reversed(col))
        new_col = compress_and_merge_line(reversed_col)
        new_col = list(reversed(new_col))
        for i in range(SIZE):
            if grid[i][j] != new_col[i]:
                changed = True
                grid[i][j] = new_col[i]
    return changed

def main():
    initialize_game()
    while True:
        display_grid()
        if not can_move():
            print("Game Over! Final Score:", score)
            break

        move = input("Use WASD to move (W=Up, A=Left, S=Down, D=Right): ").lower()
        valid_move = False

        if move == 'a':
            valid_move = move_left()
        elif move == 'd':
            valid_move = move_right()
        elif move == 'w':
            valid_move = move_up()
        elif move == 's':
            valid_move = move_down()
        else:
            print("Invalid move. Use W, A, S, or D.")
            input("Press Enter to continue...")
            continue


        if valid_move:
            add_new_tile()

main()
