from django.core.management.base import BaseCommand
from movies.models import MovieOrAnime

class Command(BaseCommand):
    help = 'Populate the MovieOrAnime model with sample data'

    def handle(self, *args, **kwargs):
        # ลบข้อมูลเก่าทั้งหมดก่อนเพิ่มข้อมูลใหม่
        MovieOrAnime.objects.all().delete()

        # เพิ่มข้อมูลตัวอย่าง
        MovieOrAnime.objects.create(favorite_order=1, title_th='Arcane', title_en='Arcane', seasons=1, viewing_platform='Netflix')
        MovieOrAnime.objects.create(favorite_order=2, title_th='My Hero Academia', title_en='My Hero Academia', seasons=6, viewing_platform='Crunchyroll')
        MovieOrAnime.objects.create(favorite_order=3, title_th='Attack on Titan', title_en='Attack on Titan', seasons=4, viewing_platform='Crunchyroll')
        MovieOrAnime.objects.create(favorite_order=4, title_th='Demon Slayer', title_en='Demon Slayer', seasons=3, viewing_platform='Netflix')
        MovieOrAnime.objects.create(favorite_order=5, title_th='One Piece', title_en='One Piece', seasons=13, viewing_platform='Crunchyroll')

        self.stdout.write(self.style.SUCCESS('Successfully populated the MovieOrAnime model with sample data'))
