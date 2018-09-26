/*
 * \brief  Stylable icon
 * \author Genode Labs <qoost@genode-labs.com>
 * \date   2011-02-18
 *
 * Copyright (C) 2011 by secunet Security Networks AG
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef _INCLUDE__QOOST__ICON_H_
#define _INCLUDE__QOOST__ICON_H_

/* Qt4 includes */
#include <QLabel>
#include <QIcon>
#include <QVariant>
#include <QMovie>
#include <QEvent>

/* Qoost includes */
#include <qoost/style.h>
#include <qoost/compound_widget.h>

/**
 * An 'Icon' widget is a 'QLabel' with an associated image/animation media
 * file. The actual media file and the size on screen can be styled via the
 * 'iconFile' and 'iconSize' properties. The widget supports all file types
 * supported by the installed Qt4 library, which is at least JPG, PNG and
 * (animated) GIF. Animated MNG support is not part all installations, but
 * desirable because of the alpha-channel support missing in GIF.
 *
 * Per default, the size of the 'Icon' widget itself is fixed to the configured
 * 'iconSize' property with a 'QSizePolicy' of '(Fixed, Fixed)'. This can be
 * adjusted via style-sheet size declarations, e.g. 'min-height', and
 * 'setSizePolicy()' after widget construction, e.g.
 *
 * ! setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
 */
class Icon : public QLabel
{
	Q_OBJECT

	/*
	 * Naturally, 'iconFile' is of type QString, but as of a shortcoming in the
	 * QSS parser, we have to check for non-string value in the style sheet.
	 * Using QVariant, we skip the transformation from QVariant to another type
	 * in the parser implementation and catch the special case.
	 */
	Q_PROPERTY(QVariant iconFile READ _get_icon_file WRITE _set_icon_file)
	Q_PROPERTY(QSize    iconSize READ _get_icon_size WRITE _set_icon_size)

	private:

		enum Icon_type { IMAGE, ANIMATION };

		QString         _icon_file;
		QSize           _file_size;
		QSize           _icon_size;
		Icon_type       _icon_type;

		QMember<QMovie> _movie;

		void _start_animation()
		{
			/* skip if widget is not visible or icon is not animated */
			if (!isVisible() || _icon_type != ANIMATION) return;

			/* scale movie to requested iconSize keeping aspect ratio */
			QSize scaled_size(_file_size);
			scaled_size.scale(_icon_size, Qt::KeepAspectRatio);

			/* always completely initialize movie to prevent strange behaviour */
			_movie->stop();
			_movie->setFileName(_icon_file);
			_movie->setScaledSize(scaled_size);
			setMovie(_movie);
			_movie->start();
		}

		void _stop_animation()
		{
			/* skip if icon is not animated */
			if (!isVisible() || _icon_type != ANIMATION) return;

			_movie->stop();
			setMovie(0);
		}

		void _update_image()
		{
			/* skip if icon is animated */
			if (_icon_type != IMAGE) return;

			QPixmap pixmap(_icon_file);
			if (!pixmap.isNull())
				setPixmap(pixmap.scaled(_icon_size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
			else
				setPixmap(pixmap);
		}

		void _update_icon()
		{
			_stop_animation();

			/* skip remaining steps if icon size is not valid */
			if (!_icon_size.isValid())
				return;

			_update_image();
			_start_animation();
		}

		/**********************
		 ** Property support **
		 **********************/

		void _set_icon_file(QVariant const &file)
		{
			if (file.type() != QVariant::String) {
				_icon_file = QString();
				_file_size = QSize();
				_icon_type = IMAGE;
			} else {
				_icon_file = file.toString();
				_file_size = QImage(_icon_file).size();
				_icon_type = QImageReader(_icon_file).supportsAnimation()
				           ? ANIMATION : IMAGE;

				/* set default size to file size */
				if (!_icon_size.isValid())
					_icon_size = _file_size;
			}
		}

		void _set_icon_size(const QSize &size) { _icon_size = size; }

		QString _get_icon_file() const { return _icon_file; }
		QSize _get_icon_size()   const { return _icon_size; }

	protected:

		void showEvent(QShowEvent *) { _start_animation(); }
		void hideEvent(QHideEvent *) { _stop_animation(); }

		void changeEvent(QEvent *e)
		{
			QLabel::changeEvent(e);
			if (e->type() == QEvent::StyleChange)
				_update_icon();
		}

		bool event(QEvent *e)
		{
			bool result = QLabel::event(e);
			if (e->type() == QEvent::Polish)
				_update_icon();
			return result;
		}

	public:

		Icon() : _icon_type(IMAGE)
		{
			setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
			setAlignment(Qt::AlignCenter);
		}

		void set_state(QString const &state_name) { update_style_id(this, state_name); }

		QSize sizeHint() const
		{
			/* the preferred size is the minimum icon size */
			return minimumSizeHint();
		}

		QSize minimumSizeHint() const
		{
			/* the widget has to fit the icon media and the configured margins */
			QSize margin(contentsMargins().left() + contentsMargins().right(),
			             contentsMargins().top()  + contentsMargins().bottom());
			return (_icon_size + margin);
		}
};

#endif /* _INCLUDE__QOOST__ICON_H_ */
