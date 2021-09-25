from PIL import Image
import os
import math

frames_loc = "../tiles/"


def get_files():
    return os.listdir(frames_loc)


def get_frame_width(frame):
    return frame.size[0]


def get_frame_height(frame):
    return frame.size[1]


def get_frame_size(frame):
    return frame.size[0], frame.size[1]


def get_sprite_sheet_size(frames) -> (int, int):
    size = int(math.ceil(math.sqrt(len(frames))))
    return size, size


def load_frames():
    files = get_files()
    frames = []
    print(f"Found these files: {files}")

    for current_file in files:
        try:
            with Image.open(frames_loc + current_file) as im:
                frames.append(im.getdata())
        except:
            print(current_file + " is not a valid image")

    return frames


def merge_frames(frames):
    tile_width, tile_height = get_frame_size(frames[0])
    sprite_sheet_width, sprite_sheet_height = get_sprite_sheet_size(frames)

    print(f"sprite sheet size: {sprite_sheet_width * tile_width} x {sprite_sheet_height * tile_height}")

    sprite_sheet = Image.new("RGBA", (int(sprite_sheet_width * tile_width), int(sprite_sheet_height * tile_height)))

    for current_frame in frames:
        top = tile_height * math.floor((frames.index(current_frame)) / sprite_sheet_width)
        left = tile_width * (frames.index(current_frame) % sprite_sheet_width)
        bottom = top + tile_height
        right = left + tile_width

        box = (left, top, right, bottom)
        box = [int(i) for i in box]
        cut_frame = current_frame.crop((0, 0, tile_width, tile_height))

        sprite_sheet.paste(cut_frame, box)

    sprite_sheet.save("sprite_sheet.png", "PNG")


def convert_to_camel_case(name: str) -> str:
    parts = name.split("_")
    res = ""
    for part in parts:
        res = res + part.capitalize()

    if res.endswith(".png") or res.endswith(".jpg"):
        res = res[:-4]

    return res


def generate_func_def(frames) -> str:
    files = get_files()
    func = """glm::vec2 Terrain::GetTextPos(BlockType blockType) {
    switch (blockType) {\n"""

    tile_width, tile_height = get_frame_size(frames[0])
    sprite_sheet_width, sprite_sheet_height = get_sprite_sheet_size(frames)

    for file in files:
        x = files.index(file) % sprite_sheet_width
        y = math.floor((files.index(file)) / sprite_sheet_width)

        func = func + f"\t\tcase BlockType::{convert_to_camel_case(file)}:\n"
        func = func + f"\t\t\treturn {{ {x}.0f, {y}.0f }};\n"

    func = func + """
    }

    assert("Block with undefined texture", false);
    return { 0.0f, 0.0f };\n}
    """

    return func


def generate_enum() -> str:
    enum = "enum class BlockType {\n"
    files = get_files()

    for file in files:
        enum = enum + f"\t{convert_to_camel_case(file)},\n"

    enum = enum + "};"

    return enum


def generate_cpp_file(frames):
    try:
        f = open("def.cpp", "x")
        f.write(generate_enum() + "\n\n" + generate_func_def(frames))
        f.close()
    except:
        print("file already exists")


if __name__ == "__main__":
    frms = load_frames()
    merge_frames(load_frames())
    generate_cpp_file(frms)
