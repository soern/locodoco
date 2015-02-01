
function nav_init()
{
	//var prototypes.loco = getElementById('loco_prototype');
}

function log(val)
{
	var logdiv = document.getElementById("log");
	logdiv.innerHTML = val;
}

/* detect whether we're on a mobile device or not
 */
function onMobile()
{
	return ('ontouchstart' in window);
}

function throttle()
{
	this.throttleEl = null;
	this.position = 0;
	this.dragging = null;
	this.scale = 4;
	this.posMax = this.scale * 100;

	this.onTouchStart = function(ev)
	{
		var inst = ev.target.instance;
		inst.dragx = ev.targetTouches[0].pageX;
		inst.dragging = true;
		ev.target.addEventListener('touchmove', inst.onTouchMove);
	}

	this.onTouchEnd = function(ev)
	{
		var inst = ev.target.instance;
		inst.dragging = false;
		inst.throttleEl.removeEventListener('touchmove', inst.onTouchMove);
	}
	this.onTouchMove = function(ev)
	{
		var inst = ev.target.instance;
		var tt = ev.targetTouches[0];

		inst.diffx = inst.dragx - tt.pageX;
		inst.dragx = tt.pageX;
		inst.dragUpdate(ev);
		log(tt.pageX);
	}
	
	this.onMouseDown = function(ev)
	{
		var inst = ev.target.instance;
		ev.target.addEventListener('mousemove', inst.onMouseMove);
		inst.dragx = ev.clientX;
		inst.dragging = true;
	}

	this.onMouseUp = function(ev)
	{
		var inst = ev.target.instance;
		inst.dragging = null;
		inst.throttleEl.removeEventListener('mousemove', inst.onMouseMove);
	}

	this.onMouseMove = function(ev)
	{
		var inst = ev.target.instance;

		if (inst.dragging == null)
			return;

		inst.diffx = inst.dragx - ev.clientX;
		inst.dragx = ev.clientX;
		inst.dragUpdate(ev);
	}

	this.dragUpdate = function(ev)
	{	
		var inst = ev.target.instance;
		var mt = ev.target; 

		inst.position -= inst.diffx;
		if (inst.position < 0)
			inst.position = 0;
		
		if (inst.position > inst.posMax)
			inst.position = inst.posMax;
			
		mt.style.backgroundPosition = -50 + (inst.position*2 / inst.scale)
			+ '% 0px';

		return true;
	}

	this.assignEventHandlers = function()
	{
		console.log(this.throttleEl);

		
		if (onMobile())
		{
			this.throttleEl.addEventListener('touchstart', this.onTouchStart);
			this.throttleEl.addEventListener('touchend', this.onTouchEnd);
		} else
		{
			this.throttleEl.addEventListener('mousedown', this.onMouseDown);
			this.throttleEl.addEventListener('mouseup', this.onMouseUp);
		}
	}

	this.init = function()
	{
		this.throttleEl = document.createElement('DIV');
		this.throttleEl.instance = this;
		//this.throttleEl.draggable = false;

		this.throttleEl.className = 'throttle';

		this.assignEventHandlers();

		return this.throttleEl;
	}
}
