from django.db import models

# Create your models here.
# users/models.py
from django.contrib.auth.models import AbstractUser,User
from django.db import models
import uuid
from django.conf import settings


class CustomUser(AbstractUser):
    # First/last name is not a global-friendly pattern
    name = models.CharField(blank=True, max_length=255)

    developerstatus = models.BooleanField(default=False)
    gamerstatus = models.BooleanField(default=False)

    def __str__(self):
        return self.username


class GameInstance(models.Model):
    id = models.UUIDField(primary_key=True,default=uuid.uuid4)
    developer = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='developer',on_delete=models.CASCADE, null=True, blank=True)
    gameurl = models.URLField(null=True)
    loaner = models.ForeignKey(settings.AUTH_USER_MODEL, related_name='loaner', on_delete=models.SET_NULL, null=True, blank=True)
    price = models.IntegerField(default=0)
    name = models.CharField(max_length=255,blank=True,default="Unnamed game")

    def __str__(self):
        return str(self.id)


class HighScore(models.Model):
    id = models.UUIDField(primary_key=True,default=uuid.uuid4)
    name = models.CharField(max_length=255,default="Unnamed game")
    url = models.URLField(null=True)
    # there seems to be no way to create a map as a field
    # so lets just store top 10 usernames and their scores
    username1 = models.CharField(max_length=250)
    score1 = models.IntegerField(default=0)
    username2 = models.CharField(max_length=250)
    score2 = models.IntegerField(default=0)
    username3 = models.CharField(max_length=250)
    score3 = models.IntegerField(default=0)
    username4 = models.CharField(max_length=250)
    score4 = models.IntegerField(default=0)
    username5 = models.CharField(max_length=250)
    score5 = models.IntegerField(default=0)
    username6 = models.CharField(max_length=250)
    score6 = models.IntegerField(default=0)
    username7 = models.CharField(max_length=250)
    score7 = models.IntegerField(default=0)
    username8 = models.CharField(max_length=250)
    score8 = models.IntegerField(default=0)
    username9 = models.CharField(max_length=250)
    score9 = models.IntegerField(default=0)
    username10 = models.CharField(max_length=250)
    score10 = models.IntegerField(default=0)


