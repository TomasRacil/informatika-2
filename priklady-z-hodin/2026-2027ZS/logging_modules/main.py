import logging
import mylib
logger = logging.getLogger(__name__)

def main():
    logging.basicConfig(
        level=logging.INFO,
        format='%(asctime)s - %(filename)s:%(levelname)s - %(message)s', # Formát zprávy
        encoding='utf-8'
        )
    logger.info('Started')
    mylib.do_something()
    logger.info('Finished')

if __name__ == '__main__':
    main()