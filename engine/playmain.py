import curses
import curses.ascii
from time import sleep
from scene import Scene
from chara import Chara


class Play:
    def __init__(self, x=100, y=30):
        self._frame = 0
        self._exit = 0
        self._listen = 0
        self._scenelist = []
        self._schedular = {}
        self._initscr = curses.initscr()
        self.stdscr = curses.newwin(y, x)
        self._mask = ' ' * (x * y - 1)
        curses.cbreak()
        self.stdscr.keypad(1)
        curses.noecho()
        self.stdscr.nodelay(1)

    def get_screen(self, size, begin_position):
        return curses.newwin(size[1], size[0], begin_position.y, begin_position.x)

    def add_scene(self, scene):
        self._scenelist.append(scene)

    def show_scene(self):
        self.stdscr.addstr(0, 0, self._mask)
        self.stdscr.refresh()
        for i in self._scenelist:
            i.show_scr()

    def run_func_time(self):
        for i in self._scenelist:
            i.run_func(self)

    def listen(self, key):
        keytospkey = {'esc': curses.ascii.ESC,
                      'up': curses.KEY_UP,
                      'down': curses.KEY_DOWN,
                      'left': curses.KEY_LEFT,
                      'right': curses.KEY_RIGHT}
        c = self._listen
        if len(key) > 1:
            return True if c == keytospkey[key] else False
        else:
            return True if c == ord(key) else False

    def schedule(self, frame, func, *args, time='absolute'):
        if time == 'absolute':
            if frame in self._schedular:
                self._schedular[frame][func] = args
            else:
                self._schedular[frame] = {func: args}
        elif time == 'relative':
            frame += self._frame
            if frame in self._schedular:
                self._schedular[frame][func] = args
            else:
                self._schedular[frame] = {func: args}

    def clock(self):
        if self._frame in self._schedular:
            for i in self._schedular[self._frame]:
                i(self, self._schedular[self._frame][i])
            self._schedular.pop(self._frame)

    def close(self, name):
        if isinstance(name, Scene):
            self._scenelist.remove(name)
        elif isinstance(name, Chara):
            for i in self._scenelist:
                i.close_chara(name)
        else:
            for i in self._scenelist:
                i.close_diaplay(name)

    
    def play(self):
        def main(scr):
            while not self._exit:
                self.run_func_time()
                self.clock()
                self.show_scene()
                self._listen = self.stdscr.getch()
                sleep(1/30)
                self._frame += 1
                if self._frame >= 15000:
                    break
        curses.wrapper(main)

    def exit(self):
        curses.nocbreak()
        self.stdscr.keypad(0)
        curses.echo()
        curses.endwin()
        self._exit = 1


if __name__ == '__main__':
    main = Play()
    s = Scene()
    s.shape = '############\n#########\n###########'
    def f(main, args):
        if main.listen('right'):
            a = []
            a.pop()
            main.exit()
    s.add_func_to_scene(f)
    main.add_scene(s)
    main.play()
