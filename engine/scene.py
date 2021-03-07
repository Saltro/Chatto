from chara import Chara
from position import Position
from functools import reduce


class Scene:
    def __init__(self):
        self.shape = ''
        self.zindex = 0
        self.position = Position(1, 1)
        self._scene_chara = []
        self._listenFunc = {}
        self._display_value = {}
        self._scrsize = (30, 20)
        self._scr = None

    def ask_screen(self, main):
        self._scr = main.get_screen(self._scrsize, self.position)

    def add_chara(self, chara):
        self._scene_chara.append(chara)

    def close_chara(self, chara):
        self._scene_chara.remove(chara)

    def chara_iter(self):
        for i in self._scene_chara:
            yield i

    def regular_chara_position(self):
        for i in self._scene_chara:
            row = i.shape.split('\n')
            chara_height = len(row)
            chara_width = -1
            for x in row:
                chara_width = max(chara_width, len(x))
            if i.position.x < 0:
                i.position.x = 0
            elif i.position.x + chara_width > self._scrsize[0]:
                i.position.x = self._scrsize[0] - chara_width
            if i.position.y < 0:
                i.position.y = 0
            elif i.position.y + chara_height > self._scrsize[1]:
                i.position.y = self._scrsize[1] - chara_height

    def add_display(self, name, value, p):
        if name not in self._display_value:
            self._display_value[name] = (value, p)
        else:
            if self._display_value[name][0] == value:
                self._display_value[name] = (value, p)
            else:
                raise Exception('Display conflict!')

    def close_diaplay(self, name):
        self._display_value.pop(name)

    def show_scr(self):
        self.regular_chara_position()
        self._scr.addstr(0, 0, self.shape)
        for i in self._scene_chara:
            self._scr.addstr(i.position.y, i.position.x, i.shape)
        for i in self._display_value:
            self._scr.addstr(self._display_value[i][1].y, self._display_value[i][1].x, self._display_value[i][0])
        self._scr.refresh()

    def add_func_to_scene(self, func, *args):
        self._listenFunc[func] = args

    def run_func(self, main):
        for i in self._listenFunc:
            i(main, self._listenFunc[i])


if __name__ == '__main__':
    a = Chara()
    a.shape = '$'
    b = Chara()
    b.shape = '^'
    s = Scene()
    s._scene_chara.append(a)
    s._scene_chara.append(b)
    def f1(main, args):
        if len(args) <= 1:
            args = args[0]
        a, b = args
        print(a, b)
    def f2(main, args):
        if len(args) <= 1:
            args = args[0]
        b = args
        print(b)
    def f3(main, args):
        print(3)
    s.add_func_to_scene(f1, 'hello', 'sb')
    s.add_func_to_scene(f2, 'Chatto')
    s.add_func_to_scene(f3)
    print(s._listenFunc)
    s.run_func(3)
