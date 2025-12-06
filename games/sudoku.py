# author : Buyandelger.J
# date : 01/12/2025 14:28
# title : Sudoku game, inspired by sudoku.com. In my free time, I always solve Sudoku puzzles 
# to refresh my mind. It helps me focus deeply on one thing, almost like meditation.
import random
import copy

# ANSI өнгөний код
class Colors:
    RESET = '\033[0m'
    BOLD = '\033[1m'
    
    # Текстийн өнгө
    RED = '\033[91m'
    GREEN = '\033[92m'
    YELLOW = '\033[93m'
    BLUE = '\033[94m'
    MAGENTA = '\033[95m'
    CYAN = '\033[96m'
    WHITE = '\033[97m'
    GRAY = '\033[90m'
    
    # Арын өнгө
    BG_BLUE = '\033[44m'
    BG_CYAN = '\033[46m'
    BG_GRAY = '\033[100m'

class Sudoku:
    def __init__(self):
        self.board = [[0 for _ in range(9)] for _ in range(9)]
        self.solution = None
        
    def is_valid(self, board, row, col, num):
        """num тоог board[row][col] дээр тавих боломжтой эсэхийг шалгана"""
        # Мөр шалгах
        if num in board[row]:
            return False
        
        # Багана шалгах
        if num in [board[i][col] for i in range(9)]:
            return False
        
        # 3x3 хайрцаг шалгах
        box_row, box_col = 3 * (row // 3), 3 * (col // 3)
        for i in range(box_row, box_row + 3):
            for j in range(box_col, box_col + 3):
                if board[i][j] == num:
                    return False
        
        return True
    
    def solve(self, board):
        """Судоку тааврыг backtracking аргаар шийднэ"""
        for row in range(9):
            for col in range(9):
                if board[row][col] == 0:
                    for num in range(1, 10):
                        if self.is_valid(board, row, col, num):
                            board[row][col] = num
                            
                            if self.solve(board):
                                return True
                            
                            board[row][col] = 0
                    
                    return False
        return True
    
    def generate_complete_board(self):
        """Бүтэн хүчинтэй Судоку самбар үүсгэнэ"""
        self.board = [[0 for _ in range(9)] for _ in range(9)]
        
        # Диагональ 3x3 хайрцгуудыг эхлээд дүүргэнэ (бие биетэйгээ хамааралгүй)
        for box in range(0, 9, 3):
            nums = list(range(1, 10))
            random.shuffle(nums)
            idx = 0
            for i in range(box, box + 3):
                for j in range(box, box + 3):
                    self.board[i][j] = nums[idx]
                    idx += 1
        
        # Үлдсэн хэсгийг шийднэ
        self.solve(self.board)
        self.solution = copy.deepcopy(self.board)
    
    def remove_numbers(self, difficulty='medium'):
        """Тоонуудыг устгаж таавар үүсгэнэ"""
        # Хүндийн түвшин: easy (35-40), medium (45-50), hard (55-60)
        remove_count = {
            'easy': random.randint(35, 40),
            'medium': random.randint(45, 50),
            'hard': random.randint(55, 60)
        }
        
        count = remove_count.get(difficulty, 45)
        positions = [(i, j) for i in range(9) for j in range(9)]
        random.shuffle(positions)
        
        for i in range(count):
            row, col = positions[i]
            self.board[row][col] = 0
    
    def generate_puzzle(self, difficulty='medium'):
        """Шинэ Судоку таавар үүсгэнэ"""
        self.generate_complete_board()
        self.remove_numbers(difficulty)
    
    def print_board(self, board=None, original_board=None):
        """Судоку самбарыг өнгөтэйгээр хэвлэнэ"""
        if board is None:
            board = self.board
        if original_board is None:
            original_board = board
            
        # Багануудын дугаар
        print(f"\n{Colors.CYAN}{Colors.BOLD}    1  2  3    4  5  6    7  8  9{Colors.RESET}")
        print(f"{Colors.GRAY}  ====================================={Colors.RESET}")
        
        for i in range(9):
            if i % 3 == 0 and i != 0:
                print(f"{Colors.GRAY}  -------------------------------------{Colors.RESET}")
            
            # Мөрийн дугаар
            row_str = f"{Colors.CYAN}{Colors.BOLD}{i + 1}{Colors.RESET} {Colors.GRAY}|{Colors.RESET}"
            for j in range(9):
                if j % 3 == 0 and j != 0:
                    row_str += f" {Colors.GRAY}|{Colors.RESET}"
                
                if board[i][j] == 0:
                    row_str += f" {Colors.GRAY}.{Colors.RESET} "
                else:
                    # Original тоонуудыг цэнхэр/томоор, хэрэглэгчийн оруулсан тоонуудыг ногоон
                    if original_board[i][j] != 0:
                        row_str += f" {Colors.BLUE}{Colors.BOLD}{board[i][j]}{Colors.RESET} "
                    else:
                        row_str += f" {Colors.GREEN}{board[i][j]}{Colors.RESET} "
            
            row_str += f" {Colors.GRAY}|{Colors.RESET}"
            print(row_str)
        
        print(f"{Colors.GRAY}  ====================================={Colors.RESET}")
        print(f"{Colors.CYAN}{Colors.BOLD}    1  2  3    4  5  6    7  8  9{Colors.RESET}\n")
    
    def play(self):
        print(f"\n{Colors.MAGENTA}{Colors.BOLD}🎮 Судокод тавтай морил! 🎮{Colors.RESET}")
        print(f"\n{Colors.YELLOW}Хүндийн түвшин: easy, medium, hard{Colors.RESET}")
        difficulty = input("Хүндийн түвшинг сонгоно уу (default: medium): ").lower()
        
        if difficulty not in ['easy', 'medium', 'hard']:
            difficulty = 'medium'
        
        print(f"\n{Colors.CYAN}Таавар үүсгэж байна...{Colors.RESET}")
        self.generate_puzzle(difficulty)
        
        game_board = copy.deepcopy(self.board)
        original_board = copy.deepcopy(self.board)
        
        print(f"\n{Colors.YELLOW}{Colors.BOLD}Тоглох заавар:{Colors.RESET}")
        print(f"{Colors.BLUE}• Original тоонууд{Colors.RESET}")
        print(f"{Colors.GREEN}• Таны оруулсан тоонууд{Colors.RESET}")
        print(f"{Colors.WHITE}- 'row col num' форматаар оруулна уу (жишээ: '1 1 5'){Colors.RESET}")
        print(f"{Colors.WHITE}- 'hint' бичвэл нэг нүдийг харуулна{Colors.RESET}")
        print(f"{Colors.WHITE}- 'solve' бичвэл шийдлийг харуулна{Colors.RESET}")
        print(f"{Colors.WHITE}- 'quit' бичвэл тоглоом дуусна{Colors.RESET}")
        
        hints_used = 0
        
        while True:
            self.print_board(game_board, original_board)
            
            # Шийдсэн эсэхийг шалгах
            if all(game_board[i][j] != 0 for i in range(9) for j in range(9)):
                if game_board == self.solution:
                    print(f"{Colors.GREEN}{Colors.BOLD}🎉 Баяр хүргэе! Та тааврыг шийдлээ! 🎉{Colors.RESET}")
                    print(f"{Colors.YELLOW}Хэрэглэсэн зөвлөмжийн тоо: {hints_used}{Colors.RESET}")
                    break
                else:
                    print(f"{Colors.RED}❌ Зарим тоонууд буруу байна. Үргэлжлүүлэн оролдож үзээрэй!{Colors.RESET}")
            
            command = input(f"{Colors.CYAN}Таны хөдөлгөөн: {Colors.RESET}").strip().lower()
            
            if command == 'quit':
                print(f"{Colors.YELLOW}Тоглосонд баярлалаа!{Colors.RESET}")
                break
            
            elif command == 'solve':
                print(f"\n{Colors.MAGENTA}{Colors.BOLD}📝 Шийдэл:{Colors.RESET}")
                self.print_board(self.solution, original_board)
                break
            
            elif command == 'hint':
                # Хоосон нүдийг олоод бөглөх
                empty_cells = [(i, j) for i in range(9) for j in range(9) 
                              if game_board[i][j] == 0]
                if empty_cells:
                    row, col = random.choice(empty_cells)
                    game_board[row][col] = self.solution[row][col]
                    hints_used += 1
                    print(f"{Colors.YELLOW}💡 Зөвлөмж: {self.solution[row][col]} байрлууллаа (мөр {row + 1}, багана {col + 1}){Colors.RESET}")
                else:
                    print(f"{Colors.RED}Хоосон нүд үлдээгүй байна!{Colors.RESET}")
            
            else:
                try:
                    parts = command.split()
                    if len(parts) != 3:
                        print(f"{Colors.RED}❌ Алдаатай оруулга. Формат: row col num{Colors.RESET}")
                        continue
                    
                    row, col, num = map(int, parts)
                    row -= 1  # 0-аар индекслэхэд хөрвүүлэх
                    col -= 1
                    
                    if not (0 <= row < 9 and 0 <= col < 9 and 1 <= num <= 9):
                        print(f"{Colors.RED}❌ Алдаатай оруулга. Row/col 1-9, num 1-9 байх ёстой{Colors.RESET}")
                        continue
                    
                    if original_board[row][col] != 0:
                        print(f"{Colors.RED}❌ Original тоог өөрчилж болохгүй!{Colors.RESET}")
                        continue
                    
                    game_board[row][col] = num
                    
                    if game_board[row][col] != self.solution[row][col]:
                        print(f"{Colors.YELLOW}⚠️  Энэ зөв биш мэт байна, үргэлжлүүлэн оролдож болно!{Colors.RESET}")
                    else:
                        print(f"{Colors.GREEN}✅ Зөв!{Colors.RESET}")
                
                except ValueError:
                    print(f"{Colors.RED}❌ Алдаатай оруулга. Зөвхөн тоо оруулна уу.{Colors.RESET}")


def main():
    """Судоку тоглоомд тавтай морил!"""
    sudoku = Sudoku()
    
    while True:
        print(f"\n{Colors.MAGENTA}{Colors.BOLD}{'=' * 40}{Colors.RESET}")
        print(f"{Colors.CYAN}{Colors.BOLD}          SUDOKU ТОГЛООМ{Colors.RESET}")
        print(f"{Colors.MAGENTA}{Colors.BOLD}{'=' * 40}{Colors.RESET}")
        print(f"\n{Colors.YELLOW}1. Судоку тоглох{Colors.RESET}")
        print(f"{Colors.YELLOW}2. Гарах{Colors.RESET}")
        
        choice = input(f"\n{Colors.CYAN}Сонголтоо оруулна уу (1-2): {Colors.RESET}").strip()
        
        if choice == '1':
            sudoku.play()
        
        elif choice == '2':
            print(f"\n{Colors.GREEN}Тоглосонд баярлалаа! Баяртай! 👋{Colors.RESET}")
            break
        
        else:
            print(f"{Colors.RED}❌ Алдаатай сонголт. 1 эсвэл 2 оруулна уу.{Colors.RESET}")


if __name__ == "__main__":
    main()