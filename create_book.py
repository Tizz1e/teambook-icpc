import os


def print_header(open_file, data):
    separator = '///////////////////////////////////////////////////////////////////////////'
    open_file.write(separator + '\n')
    open_file.write(f'                      {data.upper()} STARTS HERE\n')
    open_file.write(separator + '\n')


def create(folder, output_name):
    with open(output_name, 'w', encoding='utf-8') as out:
        for filename in os.listdir(folder):
            file_path = os.path.join(folder, filename)
            if os.path.isfile:
                with open(file_path, 'r', encoding='utf-8') as infile:
                    print_header(out, filename)
                    out.write(infile.read())
                    out.write('\n')


folder = "C:\\Programming\\teambook-icpc\\algos"
out = 'book.txt'

create(folder, out)
