//////////////////////////////////////////////////////////////////////////////
//                        DX SOURCEFILE                                     //
//////////////////////////////////////////////////////////////////////////////

/* HTMLDisplay.java
 *
 * An applet that displays HTML and responds to hyperlinks
 * and form submissions. 
 */
//
//
package dx.runtime;

import dx.net.*;
import java.net.*;
import java.util.*;
import java.awt.*;
import java.applet.*;
import javax.swing.*;
import javax.swing.text.*;
import javax.swing.text.html.*;
import javax.swing.event.*;

public class HTMLDisplay extends JApplet
    implements dx.net.DXLinkHandler, HyperlinkListener {

    public static final String CONTENT_PARAM_NAME = "CONTENT-TYPE";

    public static final String CONTENT_TYPE_HTML  = "text/html";
    public static final String CONTENT_TYPE_PLAIN = "text/plain";
    public static final String CONTENT_TYPE_RTF   = "text/rtf";
    public static final String CONTENT_TYPE_URL   = "text/url";

    public static final String[] CONTENT_TYPES = {
                CONTENT_TYPE_HTML, CONTENT_TYPE_PLAIN, CONTENT_TYPE_RTF, CONTENT_TYPE_URL
            };

    private HashMap names2index = null;
    private String[] strings = null;
    private JEditorPane	pane = null;
    private String contentType = null;
    private boolean doingUrls = false;
    private long counter = 0;
    private FormSubmitEvent fse = null;
    private boolean debugMode = false;

    //-----------------------------------------------------------------------
    public HTMLDisplay() {
        super();
    }

    //-----------------------------------------------------------------------
    public synchronized void init() {

	String dbm = this.getParameter("DEBUG");
	debugMode = dbm != null && ! "false".equals(dbm);

        // ------------------------
        int size = 0;
        this.names2index = new HashMap();
        while (true) {
            String dxlNum = "DXLOutput" + size;
            String dxlName = this.getParameter(dxlNum);
            if (dxlName == null) break;
            this.names2index.put( dxlName, new Integer(size) );
            size++;
        }
        if (size == 0) return ;

        int i = 0;
        this.strings = new String[size];
        while (i<size) {
            this.strings[i] = "";
            i++;
        }

        // ------------------------
        Font default_font = new Font("Helvetica", Font.BOLD, 14);
        Font new_font = null;
        String prop = this.getParameter("FONT");
        if ((prop == null) || ((new_font = Font.decode(prop)) == null))
            new_font = default_font;
        this.setFont(new_font);

        // ------------------------
        Color bg = this.parseColor("BACKGROUND");
        if (bg!=null) this.setBackground(bg);
        Color fg = this.parseColor("FOREGROUND");
        if (fg!=null) this.setForeground(fg);

        // ------------------------
        this.contentType = CONTENT_TYPE_HTML;
        this.doingUrls = false;
        String ct = this.getParameter(CONTENT_PARAM_NAME);
        if(ct != null) {
            int ii;
            ct = ct.toLowerCase();
            for(ii = 0; ii < CONTENT_TYPES.length; ii++){
                if( ct.equals(CONTENT_TYPES[ii]) ){
                    this.contentType = CONTENT_TYPES[ii];
                    break;
                }
            }

            if( ii >= CONTENT_TYPES.length ) {
                this.contentType = CONTENT_TYPE_PLAIN;
                debug("WARNING: Unknown content-type: " + ct
                                   + ".  Defaulting to: " + this.contentType + ".");
            }
        }

        if( this.contentType == CONTENT_TYPE_URL ){
            this.contentType = CONTENT_TYPE_HTML;
            this.doingUrls = true;
        }

        //debug( "Content-type: " + this.contentType );

        // ------------------------
        this.pane = new JEditorPane();
        this.pane.setContentType(this.contentType);
        if (fg != null) this.pane.setForeground(fg);
        if (bg != null) this.pane.setBackground(bg);
        this.pane.setEditable(false);
        if( this.contentType == CONTENT_TYPE_HTML ){
            this.pane.addHyperlinkListener(this);
	    ((HTMLEditorKit)this.pane.getEditorKit())
		.setAutoFormSubmission(false);
	}

        JScrollPane editorScrollPane = new JScrollPane(pane);
        editorScrollPane.setPreferredSize(new Dimension(640, 480));
        editorScrollPane.setMinimumSize(new Dimension(10, 10));

        // ------------------------
        this.getContentPane().setLayout (new BorderLayout());
        this.getContentPane().add(editorScrollPane, BorderLayout.CENTER);

    }

    //-----------------------------------------------------------------------
    public void setCursor(Cursor c){
	this.getContentPane().setCursor(c);
	((HTMLEditorKit)this.pane.getEditorKit()).setDefaultCursor(c);
    }

    //-----------------------------------------------------------------------
    public synchronized boolean hasHandler (String key) {
        boolean ret = this.names2index.containsKey(key);
        //debug("Has handler: key="+key+"  val="+ret);
        return ret;
    }

    //-----------------------------------------------------------------------
    public void outputHandler (String key, String msg, Object data) {
        debug(">>> handler: key("+key+")  msg("+msg+")  data("+data+")");
        try {
	    if(msg == null || msg.length() == 0)
		return;
            Integer N = (Integer) this.names2index.get(key);
            if(N == null)
                return;
            int n = N.intValue();
            this.strings[n] = msg;
            this.display();
            if(this.doingUrls && msg != null && msg.length() > 0){
		String[] tokens = msg.split("[ \t]+");
		URL url = null;
		String target = null;
		try {
		    url = new URL(tokens[0]);
		    if(tokens.length >= 2)
			target = tokens[1];
		    this.loadURL(url, target, null);
		}
		catch (Exception e){
		    debug("URL string: " + tokens[0]);
		    e.printStackTrace();
		    return;
		}
	    }
        }
        catch (Exception e){
            e.printStackTrace();
            return;
        }
    }

    //-----------------------------------------------------------------------
    private DXLinkApplication findDXLinkApplication(){
	/* Try once a second for up to 1 minute. (Tries to
	 * ameleoriate start up race condition.)
	 */
	for(int i = 1; i <= 60; i++){
            AppletContext ac = this.getAppletContext();
            Enumeration<Applet> en = ac.getApplets();
            while(en.hasMoreElements()){
                Applet a =  en.nextElement();
                if( a instanceof DXLinkApplication )
                    return (DXLinkApplication) a;
	    }
	    try {
                Thread.sleep(1000);
	    } catch(InterruptedException e){}
	}
        throw new RuntimeException("No DXLinkApplication in applet context.");
    }

    //-----------------------------------------------------------------------
    private void display(){
        if (this.pane == null) return ;
        StringBuffer sb = new StringBuffer();
        for(int i = 0; i < this.strings.length; i++){
            sb.append(this.strings[i]);
        }
        this.pane.setDocument( this.pane.getEditorKit().createDefaultDocument() );
        this.pane.setText(sb.toString());
    }

    //-----------------------------------------------------------------------

    public void loadURL(URL url, String target, String query){
	String q1 = url.getQuery();
	String q2 = query;
	query = (q1==null?"":q1) + 
	    ((q1!=null && q2!=null)?"&":"") + 
	    (q2==null?"":q2);

	if(isDxlUrl(url)){
	    if(query.length() > 0){
	        query = form2dxl(query);
		debug("Sending to DXL: " + query);
	        this.findDXLinkApplication().DXLSend(query);
	    }
	    else {
	        String r = url.getRef();
		if(r != null && r.length() > 0){
		    debug("Sending to DXL: " + r);
		    this.findDXLinkApplication().DXLSend(r);
                }
	    }
	}
	else {
	    try {
	        String file = url.getPath();
	        if(query.length()>0)
		    file = file + '?' + query;
	        URL newUrl = new URL(url.getProtocol(), url.getHost(), file);
	        AppletContext ac = this.getAppletContext();
	        if( target == null )
	            ac.showDocument(newUrl);
	        else
	            ac.showDocument(newUrl, target);
	    }
	    catch( Throwable e ){
		e.printStackTrace();
	    }
	}
    }

    //-----------------------------------------------------------------------
    public void hyperlinkUpdate(HyperlinkEvent e) {
        //debug("Got hyperlink event " + e.getEventType());
        if (e.getEventType() != HyperlinkEvent.EventType.ACTIVATED)
            return;

        debug("CLICK!! " + e.getURL());
	debug("SOURCE= " + e.getSource());
	//debug("SOURCE ELT= " + e.getSourceElement());
	//debug("SOURCE ELT ATTRS= " + e.getSourceElement().getAttributes());

        if(e instanceof FormSubmitEvent){
	    this.fse = (FormSubmitEvent) e;
	    if(fse.getMethod() ==  FormSubmitEvent.MethodType.POST){
	        debug("WARNING: POST not implemented. Trying GET...");
	    }
	    this.loadURL( fse.getURL(), fse.getTarget(), fse.getData() );
	    this.fse = null;
        }
        else if(e instanceof HTMLFrameHyperlinkEvent){
            throw new RuntimeException(
		"Don't know how to deal with FrameHyperlinkEvents.");
        }
        else {
            handleHyperlinkEvent(e);
        }
    }

    //-----------------------------------------------------------------------
    /** Turns an encoded form submission string into an assignment
     *  statement sent to DX. For example, the following string:
     *		'foo=hi+there%0Ahow+are+you%21&bar=99&bar=100&bar=-1'
     *  becomes:
     *		'foo, bar = { "hi there\nhow are you?" }, { "99" "100" "-1" } ;'
     *
     *  The data are decoded.
     *  All names (on LHS) have dots (.) are converted to underscores (_).
     *  All values (on RHS) become string lists; values for same parameter
     *  (e.g. bar) are combined into one list.
     *  All newline characters are converted into a literal \n.
     */
    public String form2dxl(String encoded){
        String[] fragments = encoded.split("&");
        HashMap<String,java.util.List<String>>
           map = new HashMap<String,java.util.List<String>> (fragments.length);
        for(int i = 0; i < fragments.length; i++){
            try {
              String nameValue[] = fragments[i].split("=", 2);
              String name = URLDecoder.decode(nameValue[0], "UTF-8");
              name = name.replaceAll("\\.","_");
              String value = URLDecoder.decode(nameValue[1], "UTF-8");
              //debug("NAME("+name+") VALUE(" + value +")");

              if(map.containsKey(name)){
                ArrayList<String> l = (ArrayList<String>) map.get(name);
                l.add(value);
              }
              else {
                ArrayList<String> l = new ArrayList<String>();
                l.add(value);
                map.put( name, l);
              }

            }
            catch(Throwable t){
              t.printStackTrace();
            }
        }

        Iterator<String> it = map.keySet().iterator();
        String[] names = new String[map.size() + 1];
        String[] values = new String[map.size() + 1];

	names[0] = getSubmittedFormName() + "__SUBMITTED__[oneshot:0]";
	values[0] = "1";

        int j = 1;
        while(it.hasNext()){
            names[j] = it.next();
            values[j] = stringJoin( map.get(names[j]), 
			"{ \"",    "\" \"",   "\" }" );
            j++;
        }

        String lhs = stringJoin(Arrays.asList(names), "", ",", "");
        String rhs = stringJoin(Arrays.asList(values), "", ",", "");

        return (lhs + " = " + rhs + ";").replaceAll("\n", "\\\\n");
    }

    //-----------------------------------------------------------------------
    /* Returns the NAME attribute from the FORM tag of the form
     * being submitted by fse. Returns empty string if form has
     * no NAME tag. Throws runtime exception if a form tag cannot
     * be found.
     */
    public String getSubmittedFormName(){
        Element e = fse.getSourceElement();
        while(e != null){
            AttributeSet as = e.getAttributes();
            if(as.getAttribute(StyleConstants.NameAttribute) == HTML.Tag.FORM){                String n = (String)as.getAttribute(HTML.Attribute.NAME);
                return (n==null ? "" : n); 
            }
            e = e.getParentElement();
        }
        throw new RuntimeException("Could not find FORM tag.");
    }

    //-----------------------------------------------------------------------
    /** Joins the list of strings together, using given separator string,
     *  and with the given prefix and suffix. A null prefix, suffix, or sep
     *  is equivalent to an empty string.
     */
    public String stringJoin(
                            java.util.List<String> list,
                            String prefix,
                            String sep,
                            String suffix)
    {
        StringBuffer sb = new StringBuffer();
        if(prefix != null)
            sb.append(prefix);
        Iterator<String> it = list.iterator();
        int i = 0;
        while(it.hasNext()){
            if(i > 0 && sep != null)
                sb.append(sep);
            sb.append(it.next());
            i++;
        }
        if(suffix != null)
            sb.append(suffix);
        return sb.toString();
    }

    //-----------------------------------------------------------------------
    /** Returns true iff the URL indicates the request should be
     *  sent to DX. A DX request is indicated by a URL
     *  of the form: http://0.0.0.0/...
     */
    public boolean isDxlUrl(URL url){
	return "0.0.0.0".equals(url.getHost());
    }

    //-----------------------------------------------------------------------
    public void handleHyperlinkEvent(HyperlinkEvent e){
        try {
	    AttributeSet aset = e.getSourceElement().getAttributes();
	    //debug("SOURCE ELT ATTRS: " + aset);
	    aset = (AttributeSet) aset.getAttribute(HTML.Tag.A);
	    //debug("\n" + aset);
	    String target = (String) 
		aset.getAttribute( HTML.Attribute.TARGET );
	    this.loadURL(e.getURL(),target, null);
        } catch (Throwable t) {
            t.printStackTrace();
        }
    }

    //-----------------------------------------------------------------------
    private Color parseColor (String param) {
        Color c = null;
        String color = this.getParameter(param);
        if (color == null) return null;
        try {
            StringTokenizer stok = new StringTokenizer(color, "[, ]");
            String redstr = stok.nextToken();
            String greenstr = stok.nextToken();
            String bluestr = stok.nextToken();
            float red = Float.valueOf(redstr).floatValue();
            float green = Float.valueOf(greenstr).floatValue();
            float blue = Float.valueOf(bluestr).floatValue();
            c = new Color(red, green, blue);
        } catch (Exception e) {
        }
        return c;
    }

    //-----------------------------------------------------------------------
    private void debug(Object s){
	if(debugMode)
            System.err.println(s.toString());
    }

}
