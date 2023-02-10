from osrsbox import items_api
from osrsbox import monsters_api

import argparse
import csv

class StatChecker:  
    def __init__(self, item_path: str, monster_path: str):
        self.items_ = items_api.load().all_items_dict
        self.monsters_ = monsters_api.load().all_monsters_dict
        self.items_path_ = item_path
        self.monsters_path_ = monster_path
    
    def write_monsters(self):
        with open(self.monsters_path_, 'w', newline='') as csvfile:
            csv_writer = csv.writer(csvfile, delimiter=',')
            self.write_monsters_header(csv_writer)

            for monster in self.monsters_.values():
                self.write_monster(monster, csv_writer)
        self.clean_csv(self.monsters_path_)
    
    def write_monster(self, monster: monsters_api.monster_properties, csv_writer: csv.writer):
        cols = [monster.name, monster.combat_level, monster.hitpoints] 
        cols.extend([monster.attack_level, monster.strength_level, monster.defence_level, monster.ranged_level, monster.magic_level])
        cols.extend([monster.defence_stab, monster.defence_slash, monster.defence_crush, monster.defence_magic, monster.defence_ranged])
        csv_writer.writerow(cols)
    
    def write_monsters_header(self, csv_writer: csv.writer):
        cols = ['name', 'combat_level', 'hitpoints']
        cols.extend(['attack_level', 'strength_level', 'defence_level', 'ranged_level', 'magic_level'])
        cols.extend(['defence_stab', 'defence_slash', 'defence_crush', 'defence_magic', 'defence_ranged'])
        csv_writer.writerow(cols)

    def write_items(self):
        with open(self.items_path_, 'w', newline='') as csvfile:
            csv_writer = csv.writer(csvfile, delimiter=',')
            self.write_items_header(csv_writer)

            for item in self.items_.values():
                if item.equipable_by_player:
                    self.write_item(item, csv_writer)
        self.clean_csv(self.items_path_)

    def write_item(self, item: items_api.item_properties, csv_writer: csv.writer):
        cols = [item.name, item.equipable_weapon, item.icon, item.wiki_url]

        if item.equipment:
            for key, val in item.equipment.__dict__.items():
                if key != 'requirements':
                    cols.append(val)
        if item.weapon:
            for key, val in item.weapon.__dict__.items():
                if key != 'stances':
                    cols.append(val)
        
        if len(cols) != 4 + 15 + 2:
            cols_needed = 4 + 15 + 2 - len(cols)
            cols.extend([''] * cols_needed)
        csv_writer.writerow(cols)
    
    def write_items_header(self, csv_writer: csv.writer):
        cols = ['name', 'equipable_weapon', 'icon', 'wiki_url']
        cols.extend(['attack_stab', 'attack_slash', 'attack_crush', 'attack_magic', 'attack_ranged'])
        cols.extend(['defence_stab', 'defence_slash', 'defence_crush', 'defence_magic', 'defence_ranged'])
        cols.extend(['melee_strength', 'ranged_strength', 'magic_damage', 'prayer', 'slot'])
        cols.extend(['attack_speed', 'weapon_type'])
        csv_writer.writerow(cols)
    
    def clean_csv(self, csv_file: str):
        data = []
        with open(csv_file, 'r') as file:
            csv_reader = csv.reader(file)
            lines = list(csv_reader)

            header = lines[0]
            data = set([tuple(line) for line in lines[1:]])
            data = [list(line) for line in data]

        with open(csv_file, 'w', newline='') as file:
            csv_writer = csv.writer(file)
            csv_writer.writerow(header)
            csv_writer.writerows(data)

def main():
    parser = argparse.ArgumentParser(description='Check item and monster stats.')
    parser.add_argument('--item-path', type=str, default='items.csv', help='Path to write the items csv file to.')
    parser.add_argument('--monster-path', type=str, default='monsters.csv', help='Path to write the monsters csv file to.')
    args = parser.parse_args()

    print("Loading items and monsters...")
    sc = StatChecker(args.item_path, args.monster_path)
    sc.write_items()
    sc.write_monsters()
    print("Items and monsters loaded!")

if __name__ == "__main__":
    main()

