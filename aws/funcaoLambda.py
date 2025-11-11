# -*- coding: utf-8 -*-
"""
Created on Sat Nov 2 19:19:13 2024
@author: meslin
"""
''' requirements
pymysql
'''
import os
import pymysql
# Configurações do RDS através de variáveis de ambiente
def connect_to_rds():
    endpoint = os.getenv('RDS_ENDPOINT')
    username = os.getenv('RDS_USERNAME')
    password = os.getenv('RDS_PASSWORD')
    database = os.getenv('RDS_DATABASE')
    # Conectar ao banco de dados
    connection = pymysql.connect(
    host=endpoint,
    user=username,
    password=password,
    database=database,
    cursorclass=pymysql.cursors.DictCursor
    )
    return connection
def execute_query(connection):
    try:
        with connection.cursor() as cursor:
        cursor.execute("SELECT * FROM MTCars")
        rows = cursor.fetchall()
        return rows
    except Exception as e:
        print(f"Erro ao executar a consulta: {e}")
        return None
def lambda_handler(event, context):
    # Conectar e executar a consulta
    connection = connect_to_rds()
    result = execute_query(connection)
    connection.close()
    # Retornar resultado no formato de resposta Lambda
    if result:
        return {
        'statusCode': 200,
        'body': result
        }
    else:
        return {
        'statusCode': 500,
        'body': 'Erro ao obter dados da tabela MTCars'
    }
