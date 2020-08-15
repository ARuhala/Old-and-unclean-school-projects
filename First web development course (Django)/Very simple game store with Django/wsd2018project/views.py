from django.http import HttpResponse, Http404, HttpResponseRedirect
from django.shortcuts import render, render_to_response
from django.contrib.auth import login, authenticate
from django.contrib.auth.forms import UserCreationForm
from django.shortcuts import render, redirect
from django.contrib.auth.models import Group
from django.contrib.auth.decorators import login_required, permission_required

from users.models import GameInstance,HighScore
from users.forms import AddGameForm,DelGameForm,PlayGameForm,LoanGameForm
from django.http import Http404

from django.views.decorators.csrf import csrf_exempt
import json




def signup(request):
    if request.method == 'POST':
        form = UserCreationForm(request.POST)
        if form.is_valid():
            form.save()
            username = form.cleaned_data.get('username')
            raw_password = form.cleaned_data.get('password1')
            user = authenticate(username=username, password=raw_password)
            login(request, user)
            return redirect('home')
    else:
        form = UserCreationForm()
    return render(request, 'signup.html', {'form': form})



@login_required
def changeuserstatus(request):

    # this view toggles the user between dev/gamer
    if (request.user.developerstatus == False):
        # adding user to dev group
        my_group = Group.objects.get(name='Developers')
        my_group.user_set.add(request.user)
        request.user.developerstatus = True

        # removing user from gamer group
        my_group = Group.objects.get(name='Gamers')
        my_group.user_set.remove(request.user)
        request.user.gamerstatus = False

    else:
        # removing user from dev group
        my_group = Group.objects.get(name='Developers')
        my_group.user_set.remove(request.user)
        request.user.developerstatus = False

        # adding user to gamer group
        my_group = Group.objects.get(name='Gamers')
        my_group.user_set.add(request.user)
        request.user.gamerstatus = True

    request.user.save()
    request.session['homecookie'] = False
    return render(request, 'wsd2018project/setdevsuccess.html')

@login_required
def setgamer(request):
    # removing user from dev group
    my_group = Group.objects.get(name='Developers')
    my_group.user_set.remove(request.user)
    request.user.developerstatus = False

    # adding user to gamer group
    my_group = Group.objects.get(name='Gamers')
    my_group.user_set.add(request.user)
    request.user.gamerstatus = True

    request.user.save()
    return render(request, 'wsd2018project/setdevsuccess.html')

@login_required
def setdeveloper(request):
    # adding user to dev group
    my_group = Group.objects.get(name='Developers')
    my_group.user_set.add(request.user)
    request.user.developerstatus = True

    # removing user from gamer group
    my_group = Group.objects.get(name='Gamers')
    my_group.user_set.remove(request.user)
    request.user.gamerstatus = False

    request.user.save()
    return render(request, 'wsd2018project/setdevsuccess.html')



@login_required
def loanGame(request):
    # this view is used for loaning a game after a succesfull payment
    # template should find out what the id of the game is and send it via form
    # this view is called by a Gamer

    # if this is a POST request we need to process the form data
    if request.method == 'POST':
        form = LoanGameForm(request.POST)
        print(form.errors)
        if form.is_valid():
            loanid = form.cleaned_data.get('id')

            # actual loaning
            # we need to find an instance of the same kind as
            # the game with the given id
            # but one that has not yet been loaned (concurrent buyers)
            tempgame = GameInstance.objects.filter(id=loanid).first()
            if (tempgame != None):
                game = GameInstance.objects.get(developer=tempgame.developer, gameurl=tempgame.gameurl, loaner=None)
                game.loaner = request.user

                # so that the same game can be loaned by multiple people, we will create
                # a new instance of the game
                # we cannot create a simple copy because we need to generate new id etc
                GameInstance.objects.create(developer=game.developer, gameurl=game.gameurl, price=game.price, name=game.name)
                # redirect to a new URL:
                game.save()
            return HttpResponseRedirect('/')

    # if a GET (or any other method) we'll create a blank form
    else:
        form = LoanGameForm()
    return render(request, 'loangame.html', {'form': form})



#@login_required
#@permission_required('user.developerstatus', raise_exception=True)
#@permission_required('user.add_gameinstance')

# TODO: don't know yet how exactly the permission system works. for now let's 
# just keep this login_required
@login_required
def getAddedGameUrl(request):
    # if this is a POST request we need to process the form data
    if request.method == 'POST':
        form = AddGameForm(request.POST)
        if form.is_valid():
            # Create new game instance with given url
            gameurli = form.cleaned_data.get('url')
            priceget = form.cleaned_data.get('price')
            nameget = form.cleaned_data.get('name')

            # removing the old loanable gameinstance if such exists
            GameInstance.objects.filter(developer = request.user, gameurl = gameurli, loaner = None).delete()

            GameInstance.objects.create(developer = request.user, gameurl = gameurli, price = priceget, name = nameget)
            # redirect to a new URL:

            # creating a high score for the game if such does not yet exist
            if (HighScore.objects.filter(url=gameurli).first() == None):
                HighScore.objects.create(url=gameurli, name = nameget)
            return HttpResponseRedirect('/')

    # if a GET (or any other method) we'll create a blank form
    else:
        form = AddGameForm()

    return render(request, 'devaddgame.html', {'form': form})

@login_required
def getDevsGames(request):
    # this view returns a list of a spesific developers games
    # the list is used to make a table of added games
    # on a spesific developer users page
    gameslist = GameInstance.objects.filter(developer=request.user)
    return render(request, 'devsgames.html', {'games': gameslist})

@login_required
def getDeletedGameUrl(request):
    # if this is a POST request we need to process the form data
    if request.method == 'POST':
        form = DelGameForm(request.POST)
        if form.is_valid():
            # Create new game instance with given url
            gameurli = form.cleaned_data.get('url')
            GameInstance.objects.filter(developer = request.user, gameurl = gameurli).first().delete()
            # redirect to a new URL:
            return HttpResponseRedirect('/')

    # if a GET (or any other method) we'll create a blank form
    else:
        form = DelGameForm()

    return render(request, 'devdelgame.html', {'form': form})

@login_required
def getGameCatalog(request):
    # this view returns a list of a spesific developers games
    # the list is used to make a table of added games
    # on a spesific developer users page
    gameslist = GameInstance.objects.filter(loaner = None)
    return render(request, 'gamecatalog.html', {'games': gameslist})

@login_required
def chooseGame(request):
    # if this is a POST request we need to process the form data
    if request.method == 'POST':
        form = PlayGameForm(request.POST)
        if form.is_valid():
             # Create new game instance with given url
            gameid = form.cleaned_data.get('id')
            game = GameInstance.objects.filter(id=gameid, loaner=request.user).first()
            if (game != None):
                request.session['gameurl'] = game.gameurl
                request.session['gamename'] = game.name
                # redirect to a new URL:
                return HttpResponseRedirect('/playgame/')
            return render(request, 'choosegame.html', {'form': form})
    # if a GET (or any other method) we'll create a blank form
    else:
        form = PlayGameForm()
    return render(request, 'choosegame.html', {'form': form})

@login_required
def playGame(request):
    gamename = request.session['gamename']
    if gamename == None:
        raise Http404
    gameurl = request.session['gameurl']

    request.session['gamename'] = None
    # request.session['gameurl'] = None
    return render(request, 'playgame.html', {'gameurl': gameurl, 'gamename': gamename})

@login_required
def showLoans(request):
    # this view returns a list of a spesific gamers games
    # the list is used to make a table of loaned games
    # on a spesific gamers choose game page
    gameslist = GameInstance.objects.filter(loaner=request.user)
    return render(request, 'usersgames.html', {'games': gameslist})


# HIGHSCORES RELATED VIEWS
def getHighScores(request):
    # this view is used to create a list of highscore objects
    # that can be used for a html table
    # the highscores are made when a dev adds a new game
    hslist = HighScore.objects.all()
    return render(request, 'wsd2018project/highscores.html', {'highscores': hslist})

@login_required
@csrf_exempt
def updateHighScores(request):
    # the score is retrieved below
    score = next(iter(request.POST))
    gameurl = request.session['gameurl']

    highscore = HighScore.objects.filter(url=gameurl).first()
    username = request.user.username

    listofscores = [highscore.score1, highscore.score2, highscore.score3,
                    highscore.score4, highscore.score5, highscore.score6,
                    highscore.score7, highscore.score8, highscore.score9,
                    highscore.score10]
    listofusernames = [highscore.username1, highscore.username2, highscore.username3,
                       highscore.username4, highscore.username5, highscore.username6,
                       highscore.username7, highscore.username8, highscore.username9,
                       highscore.username10]

    prev = int(score)
    prevname = request.user.username
    for i in range(0,10):
        if (int(score) > listofscores[i]):
            temp = listofscores[i]
            listofscores[i] = prev
            prev = temp

            tempname = listofusernames[i]
            listofusernames[i] = prevname
            prevname = tempname

    highscore.score1 = listofscores[0]
    highscore.score2 = listofscores[1]
    highscore.score3 = listofscores[2]
    highscore.score4 = listofscores[3]
    highscore.score5 = listofscores[4]
    highscore.score6 = listofscores[5]
    highscore.score7 = listofscores[6]
    highscore.score8 = listofscores[7]
    highscore.score9 = listofscores[8]
    highscore.score10 = listofscores[9]

    highscore.username1 = listofusernames[0]
    highscore.username2 = listofusernames[1]
    highscore.username3 = listofusernames[2]
    highscore.username4 = listofusernames[3]
    highscore.username5 = listofusernames[4]
    highscore.username6 = listofusernames[5]
    highscore.username7 = listofusernames[6]
    highscore.username8 = listofusernames[7]
    highscore.username9 = listofusernames[8]
    highscore.username10 = listofusernames[9]



    highscore.save()
    return HttpResponse('')


#def handler404(request):
#    return render(request, '404.html', status=404)
#
#def handler500(request):
#    return render(request, '500.html', status=500)
