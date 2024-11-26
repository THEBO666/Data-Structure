import pandas as pd

# 定义初始规则集
initial_rules = [
    {'Order': 1, 'Protocol': 'TCP', 'Sip': '192.168.1.5-199', 'Sport': '1000-10000', 'Dip': '10.0.0.10-49', 'Dport': '20-1024', 'Action': 'Deny'},
    {'Order': 2, 'Protocol': 'TCP', 'Sip': '192.168.1.28', 'Sport': '5743', 'Dip': '10.0.0.55', 'Dport': '80', 'Action': 'Accept'},
]

# 将规则集转换为DataFrame
df_rules = pd.DataFrame(initial_rules)

# 处理屏蔽异常
def handle_shadowing(df):
    df = df.sort_values(by=['Order'])
    drop_indices = []
    for i in range(len(df) - 1):
        for j in range(i + 1, len(df)):
            F1 = df.iloc[i]
            F2 = df.iloc[j]
            if F2['Order'] > F1['Order'] and F2['Sip'] in F1['Sip'] and F2['Action'] != F1['Action']:
                drop_indices.append(j)
    df.drop(drop_indices, inplace=True)
    return df

df_rules = handle_shadowing(df_rules)

# 处理交叉异常
def handle_overlap(df):
    df = df.sort_values(by=['Order'])
    drop_indices = []
    for i in range(len(df) - 1):
        for j in range(i + 1, len(df)):
            F1 = df.iloc[i]
            F2 = df.iloc[j]
            if F1['Sip'] in F2['Sip'] or F2['Sip'] in F1['Sip']:
                if F1['Action'] != F2['Action']:
                    drop_indices.append(j)
    df.drop(drop_indices, inplace=True)
    return df

df_rules = handle_overlap(df_rules)

# 处理冗余异常
def handle_redundancy(df):
    df = df.sort_values(by=['Order'])
    drop_indices = []
    for i in range(len(df) - 1):
        for j in range(i + 1, len(df)):
            F1 = df.iloc[i]
            F2 = df.iloc[j]
            if F1['Sip'] == F2['Sip'] and F1['Action'] == F2['Action']:
                drop_indices.append(j)
    df.drop(drop_indices, inplace=True)
    return df

df_rules = handle_redundancy(df_rules)

# 处理包含异常
def handle_containment(df):
    df = df.sort_values(by=['Order'])
    drop_indices = []
    for i in range(len(df) - 1):
        for j in range(i + 1, len(df)):
            F1 = df.iloc[i]
            F2 = df.iloc[j]
            if F1['Sip'] in F2['Sip'] and F1['Action'] != F2['Action']:
                drop_indices.append(j)
    df.drop(drop_indices, inplace=True)
    return df

df_rules = handle_containment(df_rules)

# 规则合并
def merge_rules(df):
    merged_rules = []
    for _, rule in df.iterrows():
        merged = False
        for i in range(len(merged_rules)):
            if merged_rules[i]['Action'] == rule['Action'] and merged_rules[i]['Protocol'] == rule['Protocol']:
                # 如果动作和协议相同，合并源IP和目标IP范围
                merged_rules[i]['Sip'] += f",{rule['Sip']}"
                merged_rules[i]['Dip'] += f",{rule['Dip']}"
                merged = True
                break
        if not merged:
            merged_rules.append(rule.to_dict())
    return pd.DataFrame(merged_rules)

df_merged_rules = merge_rules(df_rules)

# 打印最终规则集
print(df_merged_rules)
